#include "EngineSystem.h"
#include "GOC_Camera.h"
#include "GOC_Primitive.h"
#include <stdio.h>
#include <errno.h>
#define _CRT_SECURE_NO_WARNINGS

EngineSystem::EngineSystem()
{
	name = "EngineSystem";
}

EngineSystem::~EngineSystem()
{
}

bool EngineSystem::Start()
{
	bool ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->Start();
			item_it++;
		}
	}

	currentScene = CreateNewScene();
	currentScene->Start();

	return true;
}

bool EngineSystem::Init()
{
	bool ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->Init();
			item_it++;
		}
	}

	modelExtensionsAccepted.push_back("FBX");
	modelExtensionsAccepted.push_back("fbx");
	modelExtensionsAccepted.push_back("obj");

	imageExtensionsAccepted.push_back("png");
	imageExtensionsAccepted.push_back("jpg");
	imageExtensionsAccepted.push_back("bmp");
	imageExtensionsAccepted.push_back("tga");

	return ret;

}


update_status EngineSystem::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->PreUpdate(dt);
			item_it++;
		}
	}

	return UPDATE_CONTINUE;
}

update_status EngineSystem::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{
		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->Update(dt);
			item_it++;
		}

	}

	if (App->input->FileJustDropped())
	{
		LoadFromPath(App->input->GetDroppedFileDir());
	}

	return ret;
}
update_status EngineSystem::PostUpdate(float dt)
{

	update_status ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->PostUpdate(dt);
			item_it++;
		}

	}

	return UPDATE_CONTINUE;

}

bool EngineSystem::CleanUp()
{
	return true;

}

bool EngineSystem::LoadScene()
{
	return true;
}

Scene* EngineSystem::CreateNewScene()
{
	std::string scene_name = "scene " + std::to_string(scenes.size() + 1);

	Scene* scene = new Scene(scene_name, scenes_id, this);
	scene->Init();
	scenes.push_back(scene);


	return scene;
}


Scene* EngineSystem::GetCurrentScene() const
{
	return currentScene;
}

GameObject* EngineSystem::CreateNewGameObject()
{
	GameObject* go = new GameObject(gameObjectsLastID, this);

	std::string gameobject_name = "GameObject " + std::to_string(gameObjectsLastID);

	go->name = gameobject_name;
	go->Init();
	go->Start();
	allGameObjects.push_back(go);

	gameObjectsLastID++;
	App->ui->AppendToOutput(DEBUG_LOG("Created GameObject, id: %i", go->GetID()));

	return go;
}

ModuleVehicle* EngineSystem::CreateNewGameObjectVehicle()
{
	ModuleVehicle* go = new ModuleVehicle(gameObjectsLastID, this);

	std::string gameobject_name = "GameObjectVehicle " + std::to_string(gameObjectsLastID);

	go->name = gameobject_name;
	go->Init();
	go->Start();
	go->StartVehicle();
	allGameObjects.push_back(go);

	gameObjectsLastID++;
	App->ui->AppendToOutput(DEBUG_LOG("Created GameObject, id: %i", go->GetID()));

	return go;
}


GameObjectComponent* EngineSystem::CreateNewGOC(GameObject* goAttached, GOC_Type type)
{
	
	switch (type)
	{
	case GOC_Type::GOC_TRANSFORM:
	{
		GOC_Transform* comp = new GOC_Transform(goAttached, allGameObjectComponents.size());
		allGameObjectComponents.push_back(comp);
		return (GOC_Transform*)comp;
	}
	case GOC_Type::GOC_MESH_RENDERER:
	{
		GOC_MeshRenderer* comp = new GOC_MeshRenderer(goAttached, goAttached->transform->Get4x4Matrix(), allGameObjectComponents.size());
		allGameObjectComponents.push_back(comp);
		return (GOC_MeshRenderer*)comp;
	}
	break;
	case GOC_Type::GOC_TEXTURE:
	{
		GOC_Texture* comp = new GOC_Texture(goAttached, allGameObjectComponents.size());
		allGameObjectComponents.push_back((GOC_Texture*)comp);
		return (GOC_Texture*)comp;
	}
	break;
	case GOC_Type::GOC_CAMERA:
	{
		
		GOC_Camera* comp = new GOC_Camera(goAttached, allGameObjectComponents.size());
		allGameObjectComponents.push_back((GOC_Camera*)comp);
		return (GOC_Camera*)comp;
		
	}
	case GOC_Type::GOC_PRIMITIVE:
	{
		
		GOC_Primitive* comp = new GOC_Primitive(goAttached, allGameObjectComponents.size());
		allGameObjectComponents.push_back((GOC_Primitive*)comp);
		return (GOC_Primitive*)comp;

	}
	break;
	default:
		break;
	}

	
}


void EngineSystem::EraseGameObjectComponentFromGameObject(GameObject* gameobject)
{
	for (GameObjectComponent* comp : gameobject->GetComponents())
	{
		for (size_t i = 0; i < allGameObjectComponents.size(); i++)
		{
			if (allGameObjectComponents[i]->GetID() == comp->GetID())
			{
				allGameObjectComponents.erase(allGameObjectComponents.begin() + i);
			}
		}

	}
}

void EngineSystem::EraseGameObjectFromScenes(GameObject* gameObject)
{
	for (Scene* scene : scenes)
	{
		scene->EraseGameObjectFromList(gameObject);
	}

}

void EngineSystem::EraseGameObjectFromEngine(GameObject* gameObject)
{
	for (size_t i = 0; i < allGameObjects.size(); i++)
	{
		if (allGameObjects[i]->GetID() == gameObject->GetID())
		{
			allGameObjects.erase(allGameObjects.begin() + i);
		}
	}

}

void EngineSystem::RemoveFromGameObjectsSelected(GameObject* toRemove)
{
	for (size_t i = 0; i < selectedGameObjects.size(); i++)
	{
		if (selectedGameObjects[i]->GetID() == toRemove->GetID())
		{
			selectedGameObjects.erase(selectedGameObjects.begin() + i);
		}
	}

	App->ui->uiFunctions->EraseFromSelectedGoList(toRemove);
}

void EngineSystem::ExecutePendingToDelete()
{
	for (size_t i = 0; i < allGameObjects.size(); i++)
	{
		if (allGameObjects[i]->pendingToDelete)
		{
			App->ui->uiFunctions->EraseFromSelectedGoList(allGameObjects[i]);
			allGameObjects[i]->Delete();
			i--;			
		}
	}

}

bool EngineSystem::LoadModel(char* path,std::string extension, bool createGameobject)
{
	std::string path_s = path;
	
	int lastBar = path_s.find_last_of("\\\"");
	if (lastBar == -1)
	{
		lastBar = path_s.find_last_of("/");
	}

	std::string name = path_s.substr(lastBar + 1);


	Model* modelToAdd = new Model(path, this);
	GameObject* go = nullptr;
	GOC_MeshRenderer* renderer = nullptr;

	if (createGameobject)
	{
		go = App->engineSystem->currentScene->CreateNewGameObject();
		renderer = (GOC_MeshRenderer*)go->GetComponent(GOC_Type::GOC_MESH_RENDERER);
		renderer->meshPathProcedence = path;
		renderer->modelOrder = 0;
	}

	

	int meshNr = 0;

	if (modelToAdd->GetMeshes().size() > 1)
	{
		char* name_ = new char[512];
		strncpy_s(name_, 512, name.c_str(), name.length() - extension.length() - 1);

		for (Mesh mesh : modelToAdd->GetMeshes())
		{

			std::string tempName = name_;
			tempName += std::to_string(meshNr);
			mesh.name = tempName;
			App->ui->AppendToOutput(DEBUG_LOG("Loaded Mesh %s", mesh.name.c_str()));

			GameObject* meshGo = nullptr;
				if (go != nullptr)
				{
					std::string meshGoName = mesh.name;
					meshGo = go->CreateChildren();
					meshGo->name = meshGoName;
					renderer = (GOC_MeshRenderer*)meshGo->GetComponent(GOC_Type::GOC_MESH_RENDERER);
					renderer->meshPathProcedence = path;
					renderer->modelOrder = meshNr + 1;
				}

			

			bool alreadyLoaded = false;

			for (Mesh m : allMeshes)
			{
				if (std::strncmp(m.name.c_str(), mesh.name.c_str(), mesh.name.length()) == 0)
				{
					
					App->ui->AppendToOutput(DEBUG_LOG("Mesh [%s] already loaded! [path: %s]", m.name.c_str(), path));
					if (meshGo != nullptr)
					{
						renderer->SetMesh(&m);
						renderer->SetTextures(m.textures);
					}

					alreadyLoaded = true;

				}
			}

			if (!alreadyLoaded)
			{
				if (meshGo != nullptr)
				{
					renderer->SetMesh(&mesh);
					renderer->SetTextures(mesh.textures);
				}
				Save_Mesh(&mesh);
				allMeshes.push_back(mesh);

			}
			else
			{
				App->ui->AppendToOutput(DEBUG_LOG("Mesh [%s] loaded! [path: %s]", mesh.name.c_str(), path));
			}
			meshNr++;

		}
		delete[] name_;

	}
	else
	{

		char* name_ = new char[512];
		strncpy_s(name_, 512, name.c_str(), name.length() - extension.length() - 1);

		Mesh mesh = modelToAdd->GetMeshes()[0];
		mesh.name = name_;

		App->ui->AppendToOutput(DEBUG_LOG("Loaded Mesh %s", mesh.name.c_str()));

		if (createGameobject)
		{
			std::string meshGoName = mesh.name /*+ std::to_string(meshNr)*/;
			go->name = meshGoName;

			renderer = (GOC_MeshRenderer*)go->GetComponent(GOC_Type::GOC_MESH_RENDERER);
			renderer->SetMesh(&mesh);
			renderer->SetTextures(mesh.textures);
			renderer->meshPathProcedence = path;
			renderer->modelOrder = -1;
		}
		
		allMeshes.push_back(mesh);
		delete[] name_;

	}

	
	meshNr = 0;
	for (size_t i = 0; i < modelToAdd->GetTextures().size(); i++)
	{
		modelToAdd->GetTextures()[i].name = name;/* + " " + std::to_string(meshNr);*/

		allTextures.push_back(modelToAdd->GetTextures()[i]);

		App->ui->AppendToOutput(DEBUG_LOG("Loaded Texture %s", modelToAdd->GetTextures()[i].name.c_str()));
		meshNr++;
	}


	App->ui->AppendToOutput(DEBUG_LOG("Loaded Model (%s)", path));


	delete modelToAdd;

	//make gameobject when loading model

	return true;
}


bool EngineSystem::LoadFromPath(char* draggedFileDir, bool createGameobject)
{
	bool ret = false;
	std::string sDraggedFileDir = draggedFileDir;
	

	int dotPos = sDraggedFileDir.find_last_of(".");

	std::string fileExtension = sDraggedFileDir.substr(dotPos + 1);

	int a;
	for (std::string ext : modelExtensionsAccepted)
	{
		a = strncmp(fileExtension.c_str(), ext.c_str(), fileExtension.length());
		if ( a == 0)
		{
			LoadModel(draggedFileDir, ext, createGameobject);
			ret = true;

			return ret;
		}
	}

	for (int i = 0; i < imageExtensionsAccepted.size(); i++)
	{
		a = strncmp(fileExtension.c_str(), imageExtensionsAccepted[i].c_str(), fileExtension.length());
		if (a == 0)
		{
			std::string path_s = draggedFileDir;
			int lastBar = path_s.find_last_of("\\\"");
			if (lastBar == -1)
			{
				lastBar = path_s.find_last_of("/");
			}

			std::string name = path_s.substr(lastBar + 1);

			bool alreadyLoaded = false;

			for (Texture tCmp : allTextures)
			{
				int b = strncmp(name.c_str(), tCmp.name.c_str(),name.length());

				if (b == 0)
					alreadyLoaded = true;

				if (alreadyLoaded) 
					break;
					
			}

			if (!alreadyLoaded)
			{
				Texture tex = LoadTexture(draggedFileDir);

				tex.name = name;

				Save_Texture(&tex);
				allTextures.push_back(tex);

				ret = true;
				App->ui->AppendToOutput(DEBUG_LOG("Loaded Texture [%s]. [path: %s]", name.c_str(), draggedFileDir));
			}
			else
			{
				ret = true;
				App->ui->AppendToOutput(DEBUG_LOG("Texture [%s] is already loaded! [path: %s]", name.c_str(), draggedFileDir));
			}

			

			return ret;
		}
	}

	App->ui->AppendToOutput(DEBUG_LOG("Could not load file. File not supported (%s)", fileExtension.c_str()));
	

	return ret;
}

bool EngineSystem::Save_Mesh(Mesh* mesh)
{
	float* meshVertices = new float[sizeof(float*) * mesh->vertices.size() * 3];

	int MeshSize = mesh->vertices.size() * 3;

	for (size_t i = 0; i < mesh->vertices.size(); i++)
	{
		meshVertices[i] = mesh->vertices[i].Position.x;
		meshVertices[i + 1] = mesh->vertices[i].Position.y;
		meshVertices[i + 2] = mesh->vertices[i].Position.z;
	}

	uint* meshIndices = new uint[sizeof(uint*) * mesh->indices.size()];

	for (size_t i = 0; i < mesh->indices.size(); i++)
	{
		meshIndices[i] = mesh->indices[i];
	}

	uint ranges[2] = {mesh->indices.size(), mesh->vertices.size() };
	uint size = sizeof(ranges) + sizeof(uint) * mesh->indices.size() + sizeof(float) * mesh->vertices.size() * 3;
	char* fileBuffer = new char[size]; // Allocate
	char* cursor = fileBuffer;
	uint bytes = sizeof(ranges); // First store ranges
	memcpy(cursor, ranges, bytes);
	cursor += bytes;
	// Store indices
	bytes = sizeof(uint) * mesh->indices.size();
	memcpy(cursor, meshIndices, bytes);
	cursor += bytes;


	std::string filePath;

	if (mesh->renderer != nullptr)
	{
		filePath = std::string("Library/Meshes/") + mesh->name.c_str() + "_" + std::to_string(mesh->renderer->modelOrder) + std::string(MESH_FILE_EXTENSION);
	}
	else
	{
		filePath = std::string("Library/Meshes/") + mesh->name.c_str() + std::string(MESH_FILE_EXTENSION);

	}

	FILE* file;
	
	fopen_s(&file, filePath.c_str(), "w");
	
	if (file != NULL) {
		fwrite(fileBuffer, sizeof(fileBuffer), 1, file);

		fclose(file);
	}

	filePath.clear();


	return true;
}

bool EngineSystem::Load_Mesh(Mesh* mesh, char* pointer)
{
	char* cursor = pointer;

	float* meshVertices = new float[sizeof(float*) * mesh->vertices.size() * 3];

	int MeshSize = mesh->vertices.size() * 3;

	for (size_t i = 0; i < mesh->vertices.size(); i++)
	{
		meshVertices[i] = mesh->vertices[i].Position.x;
		meshVertices[i + 1] = mesh->vertices[i].Position.y;
		meshVertices[i + 2] = mesh->vertices[i].Position.z;
	}

	uint* meshIndices = new uint[sizeof(uint*) * mesh->indices.size()];

	for (size_t i = 0; i < mesh->indices.size(); i++)
	{
		meshIndices[i] = mesh->indices[i];
	}

	// amount of indices / vertices / colors / normals / texture_coords
	uint ranges[5];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);
	cursor += bytes;
	/*mesh->indices.size() = ranges[0];
	mesh->vertices.size() = ranges[1];*/

	// Load indices
	bytes = sizeof(uint) * mesh->indices.size();
	meshIndices = new uint[mesh->indices.size()];
	memcpy(meshIndices, cursor, bytes);
	cursor += bytes;

	// Load vertices
	bytes = sizeof(uint) * mesh->vertices.size();
	meshVertices = new float[mesh->vertices.size()];
	memcpy(meshVertices, cursor, bytes);
	cursor += bytes;





	return true;
}

bool EngineSystem::Save_Texture(Texture* texture)
{


	std::string filePath;
	
	filePath = std::string("Library/Textures/") + texture->name.c_str() + std::string(TEXTURE_FILE_EXTENSION);

	FILE* file;

	uint* meshIndices = new uint[sizeof(uint*) * texture->name.size()];

	uint range = { texture->name.size()};
	uint size = sizeof(range) + sizeof(uint) * texture->name.size();
	char* fileBuffer = new char[size]; // Allocate
	char* cursor = fileBuffer;
	uint bytes = sizeof(range); // First store ranges
	memcpy(cursor, &range, bytes);
	cursor += bytes;
	// Store indices
	bytes = sizeof(uint) * texture->name.size();
	memcpy(cursor, meshIndices, bytes);
	cursor += bytes;

	
	fopen_s(&file, filePath.c_str(), "w");
	

	if (file != NULL) {
		fwrite(fileBuffer, sizeof(fileBuffer), 1, file);

		fclose(file);
	}
	filePath.clear();


	//ilEnable(IL_FILE_OVERWRITE);
	//ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);

	//ILuint size = ilSaveL(IL_PNG, nullptr, 0);

	//if (size > 0)
	//{
	//	ILubyte* data = new ILubyte[size];

	//	if (ilSaveL(IL_PNG, data, size) > 0)
	//	{
	//		std::string filePath;
	//		//filePath = std::string("Library/Textures/") + texture->objMain_->name_.c_str() + std::string(TEXTURE_FILE_EXTENSION);
	//		filePath = std::string("Library/Textures/") + std::to_string(textPostfix) + std::string(TEXTURE_FILE_EXTENSION);
	//		textPostfix++;

	//		PHYSFS_file* fs_file;

	//		fs_file = PHYSFS_openWrite(filePath.c_str());

	//		if (fs_file != nullptr)
	//		{
	//			char* fileBuffer = (char*)data;
	//			uint written = (uint)PHYSFS_write(fs_file, fileBuffer, 1, size);
	//			if (written != size)
	//			{
	//				LOG("PhysFS error while writing to file %s: %s", filePath, PHYSFS_getLastError());
	//			}

	//			bool closesCorrectly = PHYSFS_close(fs_file);
	//			if (closesCorrectly == false)
	//			{
	//				LOG("PhysFS error while closing file %s: %s", filePath, PHYSFS_getLastError());
	//			}
	//		}
	//		else
	//		{
	//			LOG("PhysFS error while opening file %s: %s", filePath, PHYSFS_getLastError());
	//		}

	//		filePath.clear();
	//	}
	//}

	//Load_Texture(texture, pointer, size);
	return true;
}

bool Load_Texture(Texture* texture, char** pointer, uint size)
{
	//ILuint il_image = 0;																				
	//ilGenImages(1, &il_image);																		
	//ilBindImage(il_image);

	//success = ilLoadL(IL_TYPE_UNKNOWN, (const void*)pointer, size);

	//if (success == true)
	//{
	//	uint color_channels = ilGetInteger(IL_IMAGE_CHANNELS);
	//	if (color_channels == 3)
	//	{
	//		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);											
	//	}
	//	else if (color_channels == 4)
	//	{
	//		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);										
	//	}																								
	//	else
	//	{
	//		LOG("Texture has less than 3 color channels!");
	//	}
	//}

	//if (success == true)
	//{
	//	ILinfo il_info;
	//	iluGetImageInfo(&il_info);

	//	ilGenImages(1, (ILuint*)&texture->objectTexture->image_ID);
	//	ilBindImage(texture->objectTexture->image_ID);

	//	if (il_info.Origin == IL_ORIGIN_UPPER_LEFT) iluFlipImage();

	//	texture->objectTexture->texture_ID = ilutGLBindTexImage();

	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//	glGenTextures(1, (GLuint*)&texture->objectTexture->texture_ID);
	//	glBindTexture(GL_TEXTURE_2D, texture->objectTexture->texture_ID);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	//	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, 0);

	//	//texture->objectTexture->width = il_info.Width;
	//	//texture->objectTexture->height = il_info.Height;
	//	//texture->objectTexture->image_ID = il_info.Id;
	//	//texture->objectTexture->format = il_info.Format;
	//}

	//ilDeleteImages(1, &il_image);

	return true;
}

bool EngineSystem::SaveState(JSON_Value* file, std::string root) const
{
	for (Scene* var : scenes)
	{
		var->SaveState(file);
	}
	return true;
}

bool EngineSystem::LoadState(JSON_Value* file, std::string root)
{
	for (Scene* var : scenes)
	{
		var->LoadState(file);
	}
	return true;
}

bool EngineSystem::Save() 
{

	return true;
}