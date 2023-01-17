#include "Scene.h"

#include "ModuleUI.h"



Scene::Scene(EngineSystem *system, bool active)
{
	name = "_";
	this->engineSystem = system;
}

Scene::Scene(std::string name, uint id, EngineSystem* system, bool active)
{
	this->name = name;
	this->sceneID = id;
	this->engineSystem = system;

}

Scene::~Scene()
{
}


bool Scene::Init()
{
	bool ret = true;


	if (!gameObjects.empty())
	{
		// Call Init() in all modules
		GameObject* item = gameObjects.front();
		int item_it = 0;

		while (item_it < gameObjects.size() && ret == true)
		{
			item = gameObjects[item_it];
			ret = item->Init();
			item_it++;
		}
	}


	return ret;
}

bool Scene::Start()
{
	bool ret = true;


	// Call Start() in all gameobjects
	if (!gameObjects.empty())
	{
		GameObject* item = gameObjects.front();
		int item_it = 0;

		item = gameObjects.front();
		item_it = 0;

		while (item_it < gameObjects.size() && ret == true)
		{
			item = gameObjects[item_it];
			ret = item->Start();
			item_it++;
		}
	}

	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Capsule.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cone.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cube.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cylinder.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Plane.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Pyramid.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Sphere.fbx", false);

	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/default_texture.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/checker_pattern.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/baker_house.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Models/baker_house.fbx");

	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Models/Street_environment_V01.FBX");

	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building-01_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building-06_-c-.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building-06_-c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_016_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_025_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building03_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building05-_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_V02_C.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_V01_C.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/green_texture.png");

	GameObject* camera = App->engineSystem->GetCurrentScene()->CreateNewGameObject();
	camera->AddComponent(GOC_Type::GOC_CAMERA);
	camera->name = "Camera 1";

	camera = App->engineSystem->GetCurrentScene()->CreateNewGameObject();
	camera->AddComponent(GOC_Type::GOC_CAMERA);
	camera->name = "Camera 2";


	//SCENE INITIIALIZATION
	GOC_Texture* texture = nullptr;

	GameObject* go = gameObjects[0];

	go = gameObjects[1];
	texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	texture->SetTexture(App->engineSystem->GetAllTextures()[2]);
	texture->UpdateMeshRendererTexture();

	go->transform->translationLocal.translate(0, 0, 0);
	go->transform->ApplyTransformations();

	go = gameObjects[2];
	texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	texture->SetTexture(App->engineSystem->GetAllTextures()[2]);
	texture->UpdateMeshRendererTexture();

	go->transform->translationLocal.translate(0, 0, 0);
	go->transform->ApplyTransformations();

	for (GameObject* go : gameObjects)
	{
		GOC_Texture* texture = nullptr;
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[2]);
		texture->UpdateMeshRendererTexture();
	}

	/*Game Object 3 (parent)*/
	
	{

		go = gameObjects[3];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[5]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(0, 0, 0);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(0 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 1;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 0;		go->transform->rotationLocal[10] = 1;

		go->transform->ApplyTransformations();

		//Game Object 4

		go = gameObjects[4];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[8]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(17.5, 0, -28.3);

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 5

		go = gameObjects[5];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[10]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(18.25, 0, 32);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 6

		go = gameObjects[6];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[6]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(38, 0, 17.65);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 7

		go = gameObjects[7];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[7]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(42.5, 0, -18.7);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = -1;
		go->transform->rotationLocal[4] = -1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 8

		go = gameObjects[8];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[6]);
		texture->UpdateMeshRendererTexture();
		go->mass = 0;
		go->transform->translationLocal.translate(-1.6, 0, -0.6);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 9

		go = gameObjects[9];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[12]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(0, 0, 0);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 10

		go = gameObjects[10];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[3]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-40.45, 0, 44.55);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 11

		go = gameObjects[11];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[6]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(38, 0, 30.6);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 12

		go = gameObjects[12];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[4]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(31.5, 0, -40.1);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 13

		go = gameObjects[13];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[8]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(28.45, 0, -18);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = -1;
		go->transform->rotationLocal[4] = -1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 14

		go = gameObjects[14];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[3]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-40.45, 0, 25.45);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;
		
		go->transform->ApplyTransformations();

		//Game Object 15

		go = gameObjects[15];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[3]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-43.3, 0, 34.6);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = -1;
		go->transform->rotationLocal[4] = -1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 16

		go = gameObjects[16];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[9]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-29, 0, -19);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = -1;
		go->transform->rotationLocal[4] = -1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 17

		go = gameObjects[17];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[6]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(38, 0, 42.2);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 18

		go = gameObjects[18];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[7]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(15.10, 0, 43);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 19

		go = gameObjects[19];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[9]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-19.75, 0, 31);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = -1;
		go->transform->rotationLocal[4] = -1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 20

		go = gameObjects[20];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[11]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-44.6, 0, 14.9);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 21

		go = gameObjects[21];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[0]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(12.2, 0, -0.7);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 22

		go = gameObjects[22];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[11]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-37.6, 0, 14.9);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 23

		go = gameObjects[23];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[11]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-33.6, 0, -32.5);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 180 * DEGTORAD);
		go->transform->rotationLocal[0] = -1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 24

		go = gameObjects[24];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[8]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(17.5, 0, -40.5);

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 25

		go = gameObjects[25];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[4]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(42.8, 0, -30.5);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 26

		go = gameObjects[26];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[9]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-20, 0, 17.40);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 180 * DEGTORAD);
		go->transform->rotationLocal[0] = -1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 27

		go = gameObjects[27];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[11]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-43.40, 0, -32.5);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = -1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 28

		go = gameObjects[28];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[4]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(31.5, 0, -28.9);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 180 * DEGTORAD);
		go->transform->rotationLocal[0] = -1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 29

		go = gameObjects[29];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[9]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-19.6, 0, -18.7);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = -1;
		go->transform->rotationLocal[4] = -1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 30

		go = gameObjects[30];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[9]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-19.9, 0, -40.9);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 180 * DEGTORAD);
		go->transform->rotationLocal[0] = -1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 31

		go = gameObjects[31];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[11]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-33.6, 0, -41.0);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 180 * DEGTORAD);
		go->transform->rotationLocal[0] = -1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 32

		go = gameObjects[32];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[11]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(-43.4, 0, -41.0);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, 180 * DEGTORAD);
		go->transform->rotationLocal[0] = -1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 1;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();

		//Game Object 33

		go = gameObjects[33];
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[10]);
		texture->UpdateMeshRendererTexture();

		go->transform->translationLocal.translate(16.5, 0, 19.2);
		go->transform->ApplyTransformations();

		go->transform->rotationEulerLocal = float3(-90 * DEGTORAD, 0 * DEGTORAD, -90 * DEGTORAD);
		go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
		go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

		go->transform->ApplyTransformations();
	}

		go = gameObjects[34];
		
		go->transform->translationLocal.translate(63.5, 26.25, -60.75);

		go->transform->rotationEulerLocal = float3(28.7 * DEGTORAD, -43.15 * DEGTORAD, 18.5 * DEGTORAD);
		go->transform->rotationLocal[0] = 0.691864;		go->transform->rotationLocal[1] = -0.033135;		go->transform->rotationLocal[2] = 0.721267;
		go->transform->rotationLocal[4] = -0.231495;		go->transform->rotationLocal[5] = 0.936031;		go->transform->rotationLocal[6] = 0.265060;
		go->transform->rotationLocal[8] = -0.683911;		go->transform->rotationLocal[9] = -0.350355;		go->transform->rotationLocal[10] = 0.639936;

		go->transform->ApplyTransformations();

		go = gameObjects[35];

		go->transform->translationLocal.translate(0, 23.5, 85);

		go->transform->rotationEulerLocal = float3(-20.65 * DEGTORAD, -180 * DEGTORAD, 0 * DEGTORAD);
		go->transform->rotationLocal[0] = -1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
		go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0.935752;		go->transform->rotationLocal[6] = -0.352658;
		go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = -0.352658;		go->transform->rotationLocal[10] = -0.935753;

		go->transform->ApplyTransformations();





	
	App->ui->AppendToOutput(DEBUG_LOG("%s", name.c_str()));
	return ret;
}



update_status Scene::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	   
	if (!gameObjects.empty())
	{

		Module* item = gameObjects.front();
		int item_it = 0;

		while (item_it < gameObjects.size() && ret == true && item->enabled)
		{
			item = gameObjects[item_it];
			ret = item->PreUpdate(dt);
			item_it++;
		}

		item = gameObjects.front();
		item_it = 0;

		while (item_it < gameObjects.size() && ret == true && item->enabled)
		{
			item = gameObjects[item_it];
			ret = item->Update(dt);
			item_it++;
		}

		item = gameObjects.front();
		item_it = 0;

		while (item_it < gameObjects.size() && ret == true && item->enabled)
		{
			item = gameObjects[item_it];
			ret = item->PostUpdate(dt);
			item_it++;
		}
	}


	//if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT)
	//{


	//	std::string path = "C:\\Users\\Brandon AM\\Documents\\GitHub\\Separaty_Engine\\Separaty_Engine\\Output\\Assets\\Project_1\\Assets\\Models\\baker_house.fbx";

	//	char* path_c = new char(path.length() + 1);

	//	strncpy_s(path_c, 512, path.c_str(), path.length());

	//	//load baker_house and its textures
	//	App->engineSystem->LoadFromPath(path_c);

	//	path = "Assets/Project_1/Assets/Textures/checker_pattern.png";
	//	strncpy_s(path_c, 512, path.c_str(), path.length());

	//	//load checker_pattern
	//	App->engineSystem->LoadFromPath(path_c);


	//	GameObject* houseAll = App->engineSystem->GetCurrentScene()->CreateNewGameObject();
	//	GameObject* house = houseAll->CreateChildren();
	//	GameObject* chimney = houseAll->CreateChildren();


	//	goRenderer = (GOC_MeshRenderer*)house->GetComponent(GOC_Type::GOC_MESH_RENDERER);

	//	goRenderer->SetMesh(&App->engineSystem->GetAllMeshes()[1]);
	//	goRenderer->SetTexture(&App->engineSystem->GetAllTextures()[0]);

	//	goRenderer = (GOC_MeshRenderer*)chimney->GetComponent(GOC_Type::GOC_MESH_RENDERER);

	//	goRenderer->SetMesh(&App->engineSystem->GetAllMeshes()[0]);
	//	goRenderer->SetTexture(&App->engineSystem->GetAllTextures()[1]);

	//	delete path_c;
	//	loadedBasics = true;
	//}

	/*if (App->ui->createCube == true)
	{
		GameObject* go = CreateNewGameObject();

		go->transform->SetPos(0, 0, go->GetID());

	}*/

	return UPDATE_CONTINUE;

}


GameObject* Scene::CreateNewGameObject()
{
	GameObject* go = engineSystem->CreateNewGameObject();

	gameObjects.push_back(go);

	return go;
}

ModuleVehicle* Scene::CreateNewGameObjectVechicle()
{
	ModuleVehicle* go = engineSystem->CreateNewGameObjectVehicle();

	gameObjects.push_back(go);

	return go;
}

/*ModulePhysics* Scene::CreateNewGameObjectP2PConstraint()
{

}*/

GameObject* Scene::GetSelectedGameObject()
{
	for (GameObject* go : gameObjects)
	{
		if (go->selected)
		{
			return go;
		}
	}

	return nullptr;
}

bool Scene::CleanUp()
{
	return true;

}


void Scene::EraseGameObjectFromList(GameObject* gameObject)
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetID() == gameObject->GetID())
		{
			gameObjects.erase(gameObjects.begin() + i);

		}
	}
}



bool Scene::SaveState(JSON_Value* file, std::string root) const
{
	std::string r = "[" + name + "].";

	int i = 0;
	for (GameObject* go : gameObjects)
	{
		if (go->parent == nullptr)
		{
			go->SaveState(file, std::string(r + "[Element_" + std::to_string(i) + "]."));
			i++;
		}
		
	}
	json_object_dotset_number(json_object(file), std::string(r + "count").c_str(), (int)i);

	return true;
}
bool Scene::LoadState(JSON_Value* file, std::string root)
{
	std::string r = "[" + name + "].";

	int totalGos = json_object_dotget_number(json_object(file), std::string(r + "count").c_str());


	for (size_t i = 0; i < totalGos; i++)
	{
		GameObject* go = CreateNewGameObject();
		go->LoadState(file, std::string(r + "[Element_" + std::to_string(i) + "]."));
	}

	//int i = 0;
	//for (GameObject* go : gameObjects)
	//{
	//	if (go->parent == nullptr)
	//	{
	//		go->LoadState(file, std::string(r + "[Element_" + std::to_string(i) + "]."));
	//		i++;
	//	}
	//	
	//}
	return true;
}

