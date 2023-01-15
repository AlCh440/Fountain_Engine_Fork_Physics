#include "Globals.h"
#include "Application.h"
#include "Car.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	//LOG("Loading player");
	
	
	
	

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 1, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.bridge_size.Set(2, 1, 2);
	car.bridge_offset.Set(0, 2.5, 0);
	/*car.chassis_size.Set(2.0f, 0.75f, 3.0f);
	car.chassis_offset.Set(0.0f, 0.5f, 0.0f);
	car.bridge_size.Set(0.8f, 0.75f, 2.0f);
	car.bridge_offset.Set(0.0f, 0.5f, 2.5f);
	car.front_wing_size.Set(2.0f, 0.25f, 0.7f);
	car.front_wing_offset.Set(0.0f, 0.5f, 3.75f);
	car.rear_wing_size.Set(1.2f, 0.05f, 0.5f);
	car.rear_wing_offset.Set(0.0f, 1.25f, -1.25f);
	car.vertical_wing_size.Set(0.05f, 0.5f, 0.5);
	car.vertical_wing_offset.Set(0.6f, 1.2f, -1.25f);
	car.upper_size.Set(0.7f, 0.4f, 1.6f);
	car.upper_offset.Set(0.0f, 1.2f, -0.2f);*/
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x * 0.5f;
	float half_length = car.chassis_size.z * 0.5f;
	float rear_wheels = car.chassis_size.z * 0.6f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	
	//car.jointOffset = car.chassis_offset;
	//car.joint = App->physics->AddBody(Cube(0.1f,0.1f,0.1f),1.0f);


	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 1, 10);

	vehicle->collision_listeners.add(this);

	//decorBody = App->physics->AddBody(*decor);
	//App->physics->AddConstraintP2P(*decorBody->body, *vehicle->body, car.rear_chassis_offset, car.rear_chassis_offset);

	//Initializing Forces
	drag = 0;
	lift = 0;
	friction = 0.05f * GRAVITY.y() * car.mass;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	//LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if (alive)
	{
		lift = 0.000325f * (3 * 4) * (pow(vehicle->GetKmh(), 2) * 1.225f) / 2; //Lift = Cl * A * v^2 * density / 2
		btVector3 liftVec = { 0, -10.0f + lift, 0 };
		App->physics->world->setGravity(liftVec);

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			if (vehicle->GetKmh() < 60) acceleration = MAX_ACCELERATION;
		}
		// DRAG/FRICTION FUYM 1
		else if (vehicle->GetKmh() >= 0)
		{
			drag = 1.2 * 3 * (pow(vehicle->GetKmh(), 2) * 1.225f) / 2; //Drag = Cd * A * (v^2 * density) / 2 	
			acceleration -= drag - friction;
			car.mass = 500.0f;
			App->physics->world->setGravity(GRAVITY);
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			if (vehicle->GetKmh() > 0.0f) brake = BRAKE_POWER;

			else if (vehicle->GetKmh() <= 0.0f && vehicle->GetKmh() > -50)
				acceleration = -MAX_ACCELERATION;
		}
		// DRAG/FRICTION FUYM 2
		else if (vehicle->GetKmh() <= 0)
		{
			drag = 1.2 * 3 * (pow(vehicle->GetKmh(), 2) * 1.225f) / 2; //Drag = Cd * A * (v^2 * density) / 2 	
			acceleration += drag - friction;
		}
	}

	

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	if (vehicle->GetKmh() >= -0.5 && vehicle->GetKmh() <= 0.5) sprintf_s(title, "%.1f Km/h", 0);
	else sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	float speed_cam = 0.09;
	//vec3 p = vehicle->GetPos();
	vec3 f = vehicle->GetForwardVector();

	vec3 dist_to_car = { -16.0f, 8.0f, -16.0f };
	//vec3 camera_new_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
	//vec3 speed_camera = camera_new_position - App->camera->Position;

	//App->camera->Look(App->camera->Position + (speed_cam * speed_camera), p);

	/*
	mat4x4 decorMatrix;
	decorBody->GetTransform(&decorMatrix);
	decor->transform = decorMatrix;
	decor->Render();
	*/

	return UPDATE_CONTINUE;
}