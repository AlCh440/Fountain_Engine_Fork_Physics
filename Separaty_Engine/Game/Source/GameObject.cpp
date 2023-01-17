#include "GameObject.h"
#include "ModuleInput.h"
#include "GOC_Primitive.h"
#define MAX_ACCELERATION 10000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 10000.0f

GameObject::GameObject(uint id, EngineSystem* system, bool start_enabled)
{
	this->id = id;
	this->engineSystem = system;
}

GameObject::~GameObject()
{

}

bool GameObject::Init()
{
	AddComponent(GOC_Type::GOC_TRANSFORM);
	transform = (GOC_Transform*)components[0];
	AddComponent(GOC_Type::GOC_MESH_RENDERER);
	AddComponent(GOC_Type::GOC_TEXTURE);
	return true;
}

bool GameObject::Start()
{

	AddComponent(GOC_Type::GOC_PRIMITIVE);


	return true;
}

update_status GameObject::Update(float dt)
{
	bool ret = UPDATE_CONTINUE;

	GameObjectComponent* item = components.front();
	int item_it = 0;

	while (item_it < components.size() && ret == true)
	{
		item = components[item_it];
		ret = item->Execute();
		item_it++;
	}
	

	return UPDATE_CONTINUE;
}

update_status GameObject::PostUpdate(float dt)
{
	GOC_Primitive* comp_prim = (GOC_Primitive*)GetComponent(GOC_Type::GOC_PRIMITIVE);
	GOC_Transform* comp_transform = (GOC_Transform*)GetComponent(GOC_Type::GOC_TRANSFORM);

	if (comp_prim->primitive != NULL)
	{
		//float3 pos;
		//float3 rot;
		//float3 scale;
		//float axis;
		//
		//comp_prim->primitive->GetPosRotScaleAxis(pos, rot, axis, scale);
		//transform->translationLocal.translate(pos.x, pos.y, pos.z);
		//transform->ApplyTransformations();
	}
	return UPDATE_CONTINUE;
}

bool GameObject::CleanUp()
{
	bool ret = UPDATE_CONTINUE;

	GameObjectComponent* item = components.front();
	int item_it = 0;

	while (item_it < components.size() && ret == true)
	{
		item = components[item_it];
		delete item;
		item_it++;
	}

	return true;
}

void GameObject::Delete()
{
	//delete children
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->Delete();
		i--;
	}

	//detach from parent
	if (parent != nullptr)
	{
		parent->RemoveChild(this);
	}

	//delete components associated with gameobject
	App->engineSystem->EraseGameObjectComponentFromGameObject(this);


	//delete self from engineSystem and scene
	App->engineSystem->EraseGameObjectFromScenes(this);
	App->engineSystem->EraseGameObjectFromEngine(this);

	//call clean
	CleanUp();
	//delete self;
	delete this;

}



bool GameObject::SaveState(JSON_Value* file, std::string root) const
{
	std::string name = this->name;
	const char* buf = name.c_str();

	json_object_dotset_string(json_object(file), std::string(root + "name").c_str(), std::string(name).c_str());
	json_object_dotset_number(json_object(file), std::string(root + "components.count").c_str(), components.size());

	int a = 0;
	for (GameObjectComponent* comp : components)
	{
		std::string r = root + "components.[Element_" + std::to_string(a) + "].";
		GOC_Type goc_type = comp->GetGOC_Type();
		json_object_dotset_number(json_object(file), std::string(r + "type").c_str(), (int)goc_type);

		switch (goc_type)
		{
		case GOC_Type::GOC_NULL:
		{
			
		}
			break;
		case GOC_Type::GOC_TRANSFORM:
		{
			GOC_Transform* c = (GOC_Transform*)comp;
			c->SaveState(file, r);
		}
			break;
		case GOC_Type::GOC_MESH_RENDERER:
		{
			GOC_MeshRenderer* c = (GOC_MeshRenderer*)comp;
			c->SaveState(file, r);
		}
			break;
		case GOC_Type::GOC_TEXTURE:
		{
			GOC_Texture* c = (GOC_Texture*)comp;
			c->SaveState(file, r);
		}
			break;
		case GOC_Type::GOC_CAMERA:
		{
			GOC_Camera* c = (GOC_Camera*)comp;
			c->SaveState(file, r);
		}
			break;
		default:
			break;
		}
		a++;
	}

	json_object_dotset_number(json_object(file), std::string(root + "children.count").c_str(), children.size());

	int i = 0;
	for (GameObject* go : children)
	{
		go->SaveState(file, std::string(root + "children.[Element_" + std::to_string(i) + "]."));
		i++;
	}

	json_serialize_to_file(file, "project1.json");
	return true;
}

bool GameObject::LoadState(JSON_Value* file, std::string root)
{


	

	std::string name = json_object_dotget_string(json_object(file), std::string(root + "name").c_str());
	int count = (int)json_object_dotget_number(json_object(file), std::string(root + "components.count").c_str());

	this->name = name;
	


	for (size_t i = 0; i < count; i++)
	{
		std::string r = root + "components.[Element_" + std::to_string(i) + "].";
		GOC_Type goc_type = (GOC_Type)json_object_dotget_number(json_object(file), std::string(r + "type").c_str());

		if (goc_type != GOC_Type::GOC_TRANSFORM &&
			goc_type != GOC_Type::GOC_MESH_RENDERER &&
			goc_type != GOC_Type::GOC_TEXTURE)
			AddComponent(goc_type);

		GameObjectComponent* comp = nullptr;
		comp = GetComponent(goc_type);

		switch (goc_type)
		{
		case GOC_Type::GOC_NULL:
		{

		}
		break;
		case GOC_Type::GOC_TRANSFORM:
		{
			GOC_Transform* c = nullptr;
			c = (GOC_Transform*)comp;
			c->LoadState(file, r);
		}
		break;
		case GOC_Type::GOC_MESH_RENDERER:
		{
			GOC_MeshRenderer* c = nullptr;
			c = (GOC_MeshRenderer*)comp;
			c->LoadState(file, r);
		}
		break;
		case GOC_Type::GOC_TEXTURE:
		{
			GOC_Texture* c = nullptr;
			c = (GOC_Texture*)comp;
			c->LoadState(file, r);
		}
		break;
		case GOC_Type::GOC_CAMERA:
		{
			GOC_Camera* c = nullptr;
			c = (GOC_Camera*)comp;
			c->LoadState(file, r);
		}
		break;
		default:
			break;
		}
	}

	int childrenCount = json_object_dotget_number(json_object(file), std::string(root + "children.count").c_str());


	for (size_t i = 0; i < childrenCount; i++)
	{
		GameObject* go = CreateChildren();
		go->LoadState(file, std::string(root + "children.[Element_" + std::to_string(i) + "]."));
	}
	return true;
}


void GameObject::AddComponent(GOC_Type type)
{

	for (auto component : components)
	{
		if (component->GetGOC_Type() == type)
		{
			App->ui->AppendToOutput(DEBUG_LOG("There already exists a component of that type in %s!", name.c_str()));
			return;
		}
	}
	
	GameObjectComponent* comp = engineSystem->CreateNewGOC(this, type);
	components.push_back(comp);

}

GameObjectComponent* GameObject::GetComponent(GOC_Type type)
{
	for (auto component : components)
	{
		if (component->GetGOC_Type() == type)
		{
			
			return component;
		}
	}

	//App->ui->AppendToOutput(DEBUG_LOG("There is not any component of that type in %s!", name.c_str()));

}

GameObject* GameObject::CreateChildren()
{
	GameObject* go = App->engineSystem->GetCurrentScene()->CreateNewGameObject();
	go->parent = this;
	children.push_back(go);

	return go;
}

void GameObject::CopyFromGameObject(GameObject gameobject)
{
	*this = gameobject;
}


void GameObject::AttachChild(GameObject* child)
{
	if (child->parent != nullptr)
		child->parent->RemoveChild(child);

	child->parent = this;
	children.push_back(child);
	//child->transform->NewAttachment();
	//child->PropagateTransform();
}

void GameObject::RemoveChild(GameObject* child)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i]->GetID() == child->GetID())
		{
			children.erase(children.begin() + i);
		}
	}
}

//void GameObject::Delete()
//{
//	//erase children
//	for (GameObject* child : children)
//	{
//		child->Delete();
//	}
//	children.clear();
//
//
//
//	for (GameObjectComponent* component : components)
//	{
//		std::vector<GameObjectComponent*>::iterator posGoc;
//		for (GameObjectComponent* goc : App->engineSystem->GetAllGameObjectComponents())
//		{
//			if (goc->GetGameObject()->id == id)
//			{
//				App->engineSystem->GetAllGameObjectComponents().erase(posGoc);
//			}
//			posGoc++;
//		}
//
//		delete component;
//	}
//	components.clear();
//
//
//
//	std::vector<GameObject*>::iterator pos;
//	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
//	{
//		if (go->id == id)
//		{
//			App->engineSystem->GetCurrentScene()->gameObjects.erase(pos);
//		}
//		pos++;
//	}
//
//	std::vector<GameObject*>::iterator pos1;
//	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
//	{
//		if (go->id == id)
//		{
//			App->engineSystem->GetAllGameObjects().erase(pos1);
//		}
//		pos++;
//	}
//
//}


ModuleVehicle::ModuleVehicle(uint id, EngineSystem* system, bool start_enabled) : GameObject(id, system, start_enabled), vehicle(NULL)
{
	this->id = id;
	this->engineSystem = system;
	turn = acceleration = brake = 0.0f;
}

ModuleVehicle::~ModuleVehicle()
{}

// Load assets
bool ModuleVehicle::StartVehicle()
{
	//LOG("Loading player");

	vehicle_raycaster = new btDefaultVehicleRaycaster(App->physics->world);



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


	vehicle = App->physics->AddVehicle(car, vehicle_raycaster);
	vehicle->SetPos(0, 5, 10);

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
bool ModuleVehicle::CleanUp()
{
	//LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModuleVehicle::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if (vehicle)
	{
		lift = 0;//.000325f * (3 * 4) * (pow(vehicle->GetKmh(), 2) * 1.225f) / 2; //Lift = Cl * A * v^2 * density / 2
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