#include "GameObject.h"
#include "ModuleInput.h"

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
