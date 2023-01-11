
#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "Inspector.h"
#include "GOC_Camera.h"
#include "ModuleCamera3D.h"

#include "imgui_stdlib.h"

//INSPECTOR WINDOW

Inspector::Inspector()
{
	name = "Inspector";

}

Inspector::~Inspector()
{

}

update_status Inspector::Update(float dt)
{
	ImVec2 windowSize = ImVec2(0, 0);

	ImGuiIO& io = ImGui::GetIO();

	if (App->ui->inspector)
	{
		/*WindowGameObjectInfo windowGameObjectInfo = gameObject->windowGameObjectInfo;*/
		ImGui::Begin("Inspector", &App->ui->inspector, ImGuiWindowFlags_NoMove);
        windowSize = ImVec2(App->ui->screenX / 5.5f, App->ui->screenY - 18.0f);
		ImGui::SetWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) + 0.80f, 18.9f));
		ImGui::SetWindowSize(windowSize);

		std::string editingTypeText = "Editing Mode: ";

		std::string editingType = "Local";
		if (editingModeWorld)
			editingType = "World";

		std::string text = editingTypeText + editingType;
		if (ImGui::Checkbox(text.c_str(), &editingModeWorld))
		{
			int a = 0;
		}

		if (!UImanager->selectedGameObjects.empty())
		{
			GameObject* editorObject = UImanager->selectedGameObjects.at(UImanager->selectedGameObjects.size() - 1);
			if (!editorObject->pendingToDelete)
			{
				if (ImGui::CollapsingHeader("Information"))
				{
					ImGui::Text("Name:");
					ImGui::SameLine();

					char n[50];
					sprintf_s(n, 50, editorObject->name.c_str());
					ImGui::InputText("##Name", n, 50);

					std::vector<GameObject*> b = App->engineSystem->GetCurrentScene()->gameObjects;

					if (ImGui::Checkbox("Active", &editorObject->enabled))
					{
						int a = 0;
					}
			
				}
				// Current game object (the one we have selected at the moment)

				bool transformUpdated = false;
			
				for (GameObjectComponent* component : editorObject->GetComponents())
				{

					/*if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
					{
						editingModeWorld = false;
					}
					else
					{
						editingModeWorld = true;

					}*/

					float multiplier = 0.5f;
					switch (component->GetGOC_Type())
					{

					case GOC_Type::GOC_TRANSFORM:
					{
						if (ImGui::CollapsingHeader("Transform"))
						{

							float newPositionX = editorObject->transform->translationLocal.translation().x;
							float newPositionY = editorObject->transform->translationLocal.translation().y;
							float newPositionZ = editorObject->transform->translationLocal.translation().z;

							if (!editingModeWorld)
							{
								newPositionX = editorObject->transform->translationLocal.translation().x;
								newPositionY = editorObject->transform->translationLocal.translation().y;
								newPositionZ = editorObject->transform->translationLocal.translation().z;
							}

							float3 newPosition = vec(newPositionX, newPositionY, newPositionZ);

							ImGui::Text("Translation");
							if (ImGui::DragFloat3(" ", &newPosition[0], 0.05f, 0.0f, 0.0f, "%.2f"))
							{
								transformUpdated = true;
								this->position = newPosition;

								if (editingModeWorld)
								{
									editorObject->transform->translationLocal.translate(newPosition.x, newPosition.y, newPosition.z);
								}
								else
								{

									editorObject->transform->translationLocal.translate(newPosition.x, newPosition.y, newPosition.z);

								}
								editorObject->transform->ApplyTransformations();

							}
							if (ImGui::Button(("Reset Translation"), ImVec2(150, 20)))
							{
								editorObject->transform->ResetTranslation();
							}

							float3 newRotationEuler = editorObject->transform->rotationEulerLocal;

							if (!editingModeWorld)
								newRotationEuler = editorObject->transform->rotationEulerLocal;


							newRotationEuler.x = RADTODEG * newRotationEuler.x;
							newRotationEuler.y = RADTODEG * newRotationEuler.y;
							newRotationEuler.z = RADTODEG * newRotationEuler.z;


							ImGui::Text("Rotation");
							if (ImGui::DragFloat3("", &newRotationEuler[0], 0.05f, 0.0f, 0.0f, "%.2f"))
							{
								transformUpdated = true;

								newRotationEuler.x = DEGTORAD * newRotationEuler.x;
								newRotationEuler.y = DEGTORAD * newRotationEuler.y;
								newRotationEuler.z = DEGTORAD * newRotationEuler.z;

								if (editingModeWorld)
								{
									editorObject->transform->rotationEulerLocal = newRotationEuler;
								}
								{
									editorObject->transform->rotationEulerLocal = newRotationEuler;
								}

								Quat rotatorQuat = Quat::FromEulerXYZ(newRotationEuler.x, newRotationEuler.y, newRotationEuler.z);
								aiQuaternion rotationQuat(rotatorQuat.w, rotatorQuat.x, rotatorQuat.y, rotatorQuat.z);


								aiMatrix3x3* tempMat3 = new aiMatrix3x3;

								aiQuaternion* tempRotationQuat = new aiQuaternion(rotationQuat);

								//aiMatrix4FromScalingQuaternionPosition(tempMat, tempScale, tempRotationQuat, tempPosition);
								aiMatrix3FromQuaternion(tempMat3, tempRotationQuat);

								mat4x4 resMat = IdentityMatrix;

								resMat[0] = (float)tempMat3->a1;
								resMat[1] = (float)tempMat3->a2;
								resMat[2] = (float)tempMat3->a3;
								resMat[3] = 0;

								resMat[4] = (float)tempMat3->b1;
								resMat[5] = (float)tempMat3->b2;
								resMat[6] = (float)tempMat3->b3;
								resMat[7] = 0;

								resMat[8] = (float)tempMat3->c1;
								resMat[9] = (float)tempMat3->c2;
								resMat[10] = (float)tempMat3->c3;
								resMat[11] = 0;

								resMat[12] = 0;
								resMat[13] = 0;
								resMat[14] = 0;
								resMat[15] = 1;

								resMat.transpose();

								if (editingModeWorld)
								{
									editorObject->transform->rotationLocal = resMat;
									editorObject->transform->rotationQuatLocal = Quat(tempRotationQuat->x, tempRotationQuat->y, tempRotationQuat->z, tempRotationQuat->w);


								}
								else
								{
									editorObject->transform->rotationLocal = resMat;
									editorObject->transform->rotationQuatLocal = Quat(tempRotationQuat->x, tempRotationQuat->y, tempRotationQuat->z, tempRotationQuat->w);



								}
								editorObject->transform->ApplyTransformations();

								delete tempMat3;
								delete tempRotationQuat;

								//* 57.29578
							}

							if (ImGui::Button(("Reset Rotation"), ImVec2(150, 20)))
							{
								editorObject->transform->ResetRotation();
							}

							float newScaleX = editorObject->transform->scalingLocal.scaling().x;
							float newScaleY = editorObject->transform->scalingLocal.scaling().y;
							float newScaleZ = editorObject->transform->scalingLocal.scaling().z;
							if (!editingModeWorld)
							{
								newScaleX = editorObject->transform->scalingLocal.scaling().x;
								newScaleY = editorObject->transform->scalingLocal.scaling().y;
								newScaleZ = editorObject->transform->scalingLocal.scaling().z;
							}

							float3 newScale = vec(newScaleX, newScaleY, newScaleZ);


							ImGui::Text("Scale");
							if (ImGui::DragFloat3("  ", &newScale[0], 0.05f, 0.0f, 0.0f, "%.2f"))
							{
								transformUpdated = true;

								if (editingModeWorld)
								{
									editorObject->transform->scalingLocal.scale(newScale.x, newScale.y, newScale.z);
								}
								else
								{
									editorObject->transform->scalingLocal.scale(newScale.x, newScale.y, newScale.z);


								}
								editorObject->transform->ApplyTransformations();

							}
							if (ImGui::Button(("Reset Scale"), ImVec2(150, 20)))
							{
								editorObject->transform->ResetScale();
							}

							ImGui::Dummy(ImVec2(0, 20));

							if (ImGui::Button(("Reset Transform"), ImVec2(150, 30)))
							{
								editorObject->transform->ResetMatrices();
							}


							/*float3 debugRot = editorObject->transform->rotationEulerWorld;
							if (!editingModeWorld)
								debugRot = editorObject->transform->rotationEulerLocal;

							ImGui::Text("Editor Object Rotation:");
							ImGui::Text(std::to_string(debugRot[0]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugRot[1]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugRot[2]).c_str());

							mat4x4 debugMat1 = editorObject->transform->translationWorld;
							if (!editingModeWorld)
								debugMat1 = editorObject->transform->translationLocal;

							ImGui::Text("Translation:");
							ImGui::Text(std::to_string(debugMat1[0]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[1]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[2]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[3]).c_str());

							ImGui::Text(std::to_string(debugMat1[4]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[5]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[6]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[7]).c_str());

							ImGui::Text(std::to_string(debugMat1[8]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[9]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[10]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[11]).c_str());

							ImGui::Text(std::to_string(debugMat1[12]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[13]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[14]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[15]).c_str());


							mat4x4 debugMat2 = editorObject->transform->rotationWorld;
							if (!editingModeWorld)
								debugMat1 = editorObject->transform->rotationLocal;

							ImGui::Text("Rotation:");
							ImGui::Text(std::to_string(debugMat2[0]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[1]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[2]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[3]).c_str());

							ImGui::Text(std::to_string(debugMat2[4]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[5]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[6]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[7]).c_str());

							ImGui::Text(std::to_string(debugMat2[8]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[9]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[10]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[11]).c_str());

							ImGui::Text(std::to_string(debugMat2[12]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[13]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[14]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[15]).c_str());

							mat4x4 debugMat3 = editorObject->transform->transformWorld;
							if (!editingModeWorld)
								debugMat1 = editorObject->transform->transformLocal;

							ImGui::Text("Scaling:");
							ImGui::Text(std::to_string(debugMat3[0]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[1]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[2]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[3]).c_str());

							ImGui::Text(std::to_string(debugMat3[4]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[5]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[6]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[7]).c_str());

							ImGui::Text(std::to_string(debugMat3[8]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[9]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[10]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[11]).c_str());

							ImGui::Text(std::to_string(debugMat3[12]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[13]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[14]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[15]).c_str());*/
						}
					}
					break;
					case GOC_Type::GOC_CAMERA:
					{
						GOC_Camera* camera = (GOC_Camera*)component;

						if (ImGui::CollapsingHeader("Camera"))
						{

							const char* camType = camera->frustum.type == PerspectiveFrustum ? "Perspective" : "Orthographic";
							ImGui::Text("Camera type: ", camType);
							ImGui::DragFloat("Far plane distance", &camera->frustum.farPlaneDistance, 10, camera->frustum.nearPlaneDistance, 2000.0f);
							ImGui::DragFloat("Near plane distance", &camera->frustum.nearPlaneDistance, 1, 0.1, camera->frustum.farPlaneDistance);

							float fov = camera->frustum.verticalFov * RADTODEG;
							if (ImGui::DragFloat("FOV", &fov, 1, 55, 120))
							{
								camera->frustum.verticalFov = fov * DEGTORAD;
								camera->frustum.horizontalFov = 2.f * atan(tan(camera->frustum.verticalFov * 0.5f) * (float(App->window->width) / App->window->height));
							}


							if (ImGui::Checkbox("Set as Main Camera", &camera->isCurrentCamera))
							{
								if (camera->isCurrentCamera)
								{
									for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
									{
										for (GameObjectComponent* comp : go->GetComponents())
										{
											if (comp->GetGOC_Type() == GOC_Type::GOC_CAMERA && editorObject->GetID() != go->GetID())
											{
												GOC_Camera* goCam = (GOC_Camera*)comp;
												goCam->isCurrentCamera = false;
											}
										}
									}
								}
							}


							bool useCamInPlay = camera->useCameraWhileInPlay;
							if (App->ui->uiFunctions->playStopWindow->play)
							{
								if (ImGui::Checkbox("Use Camera", &useCamInPlay))
								{
									int a = 0;
								}
							}
							else
							{
								//camera->useCameraWhileInPlay = camera->isCurrentCamera;
							}

							camera->useCameraWhileInPlay = useCamInPlay;

							App->camera->SetCamera(nullptr);
							if (camera->isCurrentCamera)
							{
								App->camera->SetCamera(camera);
							}

							//if (!App->ui->uiFunctions->playStopWindow->play)
							//{
							//	if (camera->isCurrentCamera == true)
							//	{
							//		if (ImGui::Checkbox("Editor Camera", &camera->isCurrentCamera))
							//		{
							//			camera->useCameraWhileInPlay = true;
							//			camera->isCurrentCamera = false;
							//		}
							//	}
							//	
							//	if (camera->useCameraWhileInPlay == true)
							//	{
							//		App->camera->SetCamera(nullptr);
							//		App->camera->SetCamera(camera);
							//		if (ImGui::Checkbox("Game Camera", &camera->useCameraWhileInPlay))
							//		{
							//			camera->isCurrentCamera = true;
							//			camera->useCameraWhileInPlay = false;
							//		}
							//	}




					/*		else
							{
								App->camera->SetCamera(nullptr);
								App->camera->SetCamera(camera);
								if (ImGui::Checkbox("Game Camera", &camera->useCameraWhileInPlay))
								{
									camera->isCurrentCamera = true;
									camera->useCameraWhileInPlay = false;
								}

							}*/


							ImGui::Checkbox("Draw Frustum", &camera->drawFrustum);




						}

						/*if (transformUpdated)
						{


							for (GameObject* toDraw : App->engineSystem->GetCurrentScene()->gameObjects)
							{
								GOC_MeshRenderer* renderer = nullptr;
								renderer = (GOC_MeshRenderer*)toDraw->GetComponent(GOC_Type::GOC_MESH_RENDERER);


								bool test = true;
								AABB meshBBox = renderer->GetMesh().bboxTransformed;

								test = camera->frustum.Contains(meshBBox);

								if (test)
									renderer->canDraw = true;
								else
									renderer->canDraw = false;

							}
						}*/
					}

					break;
					case GOC_Type::GOC_MESH_RENDERER:
					{
						GOC_MeshRenderer* renderer = (GOC_MeshRenderer*)component;


						if (ImGui::CollapsingHeader("Mesh Renderer"))
						{
							ImGui::Text("Mesh Name:");
							ImGui::SameLine();
							ImGui::Text(renderer->GetMesh().name.c_str());

							ImGui::Text("Material Textures:");
							if (ImGui::TreeNode("Change Mesh"))
							{
								for (Mesh m : App->engineSystem->GetAllMeshes())
								{
									if (ImGui::MenuItem(m.name.c_str()))
									{
										renderer->SetMesh(&m);
										// tried some things
										//if (m.name == "Sphere")
										//{
										//	
										//	Prim_Sphere* s = new Prim_Sphere(m.bbox.HalfSize().LengthSq() / 2, 0);
										//	App->physics->AddSphere(*s, 0);
										//}
									}
								}
								ImGui::TreePop();
							}

							/*bool drawBBox = renderer->GetMesh().drawBbox;*/


						/*	if (ImGui::Checkbox("Draw Box", &renderer->GetMesh().drawBbox))
							{
								renderer->GetMesh().SetDrawBoundingBox(drawBBox);
							}*/

							/*if (ImGui::Checkbox("Draw Bounding Box", &drawBBox))
							{
								renderer->GetMesh().SetDrawBoundingBox(&drawBBox);

							}*/

							/*
							for (Texture& tex : materiatel.textures) {
								ImGui::Image((ImTextureID)tex.GetTextureId(), ImVec2(85, 85));
								ImGui::SameLine();
								ImGui::BeginGroup();
								ImGui::Text(tex.GetTexturePath());
								ImGui::PushID(tex.GetTextureId() << 8);
								if (ImGui::Button("Change Texture")) {
									panelChooser->OpenPanel("ChangeTexture", "png");
									currentTextureId = tex.GetTextureId();
							}
							ImGui::PopID();

							ImGui::PushID(tex.GetTextureId() << 16);

							if (ImGui::Button("Delete Textures")) {
								material.textures.erase(std::remove(material.textures.begin(), material.textures.end(), tex));
							}

							ImGui::PopID();
							ImGui::EndGroup();

							}
							if (ImGui::Button("Add Texture")) {
								panelChooser->OpenPanel("AddTexture", "png");

							}
							ImGui::Separator();
							if (ImGui::Button("Change Shader")) {
								panelChooser->OpenPanel("ChangeShader","glsl");
							}

							*/

						}
					}
					break;
					case GOC_Type::GOC_TEXTURE:
					{
						GOC_Texture* texture = (GOC_Texture*)component;

						if (ImGui::CollapsingHeader("Texture"))
						{
							std::string test = "N. textures: " + std::to_string(texture->GetTextures().size());
							ImGui::Text(test.c_str());
							if (texture->GetTextures().size() > 0)
							{

								for (Texture* tex : texture->GetTextures())
								{
									std::string texName = "Texture name: " + tex->name;
									ImGui::Text(texName.c_str());

									ImGui::Image((ImTextureID)tex->id, ImVec2(85, 85));
								}
							}
							else
							{
								ImGui::Text("No texture loaded.");
							}

							//ImGui::Image((ImTextureID)texture->GetTexture(), ImVec2(85, 85));
							ImGui::SameLine();
							ImGui::BeginGroup();
							/*ImGui::Text(texture->GetTexture()->name.c_str());
							ImGui::PushID(texture->GetTexture()->id << 8);*/

							if (ImGui::Button("Change Texture")) {
								/*panelChooser->OpenPanel("ChangeTexture", "png");
								currentTextureId = tex.GetTexture();*/
								OPENFILENAMEA ofn;
								char fileName[MAX_PATH] = "";
								ZeroMemory(&ofn, sizeof(ofn));
								ofn.lStructSize = sizeof(OPENFILENAMEA);
								ofn.hwndOwner = NULL;
								ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
								ofn.lpstrFile = fileName;
								ofn.nMaxFile = MAX_PATH;
								ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
								ofn.lpstrDefExt = "";

								GetOpenFileNameA(&ofn);
								if (fileName[0] != '\0')
								{
									App->engineSystem->LoadFromPath(fileName);
								}

								std::string path_s = fileName;
								int lastBar = path_s.find_last_of("\\\"");
								if (lastBar == -1)
								{
									lastBar = path_s.find_last_of("/");
								}

								std::string newTex_name = path_s.substr(lastBar + 1);



								for (Texture tex : App->engineSystem->GetAllTextures())
								{

									if (std::strcmp(tex.name.c_str(), newTex_name.c_str()) == 0)
									{
										texture->SetTexture(tex);
										texture->UpdateMeshRendererTexture(true);
										break;
									}
								}
							}
							/*ImGui::PopID();*/

							/*ImGui::PushID(texture->GetTexture() << 16);*/
							ImGui::Dummy(ImVec2(0, 0));
							if (ImGui::Button("Delete Texture"))
							{
								for (Texture tex : App->engineSystem->GetAllTextures())
								{
									if (std::strcmp(tex.name.c_str(), "default_texture.png") == 0)
									{
										texture->SetTexture(tex);
										texture->UpdateMeshRendererTexture(true);
										break;
									}
								}
							}
							/*ImGui::PopID();*/

							ImGui::EndGroup();


							if (ImGui::Button("Show Checker Texture")) {

								for (Texture tex : App->engineSystem->GetAllTextures())
								{
									if (std::strcmp(tex.name.c_str(), "checker_pattern.png") == 0)
									{
										texture->SetTexture(tex);
										texture->UpdateMeshRendererTexture(true);
										break;
									}
								}
								/*Texture a = ;
								texture->SetTexture(a);
								texture->UpdateMeshRendererTexture();*/
							}
							ImGui::Separator();

							if (ImGui::TreeNode("Change Texture:"))
							{
								for (Texture t : App->engineSystem->GetAllTextures())
								{
									if (ImGui::MenuItem(t.name.c_str()))
									{
										texture->SetTexture(t);
										texture->UpdateMeshRendererTexture(true);
									}
								}
								ImGui::TreePop();
							}
							/*if (texture->GetTexture() != nullptr)
							{
								ImGui::Text("Texture data:");
								ImGui::Text("Width:  1024");
								ImGui::Text("Height: 1024");
							}*/

						}

					}
					break;
					}

				}
			}
			/*for (GameObject* go : UImanager->selectedGameObjects)
			{

				go->CopyFromGameObject(*editorObject);

			}*/
		}
		ImGui::End();
	}
	return UPDATE_CONTINUE;
}

//Inspector
//void UIFunctions::SetPosition(const float3& newPosition)
//{
//	position = newPosition;
//}

//void UIFunctions::SetRotation(const float3& newRotation)
//{
//	Quat rotationDelta = Quat::FromEulerXYZ(newRotation.x - rotationEuler.x, newRotation.y - rotationEuler.y, newRotation.z - rotationEuler.z);
//	rotation = rotation * rotationDelta;
//	rotationEuler = newRotation;
//}
//
//void UIFunctions::SetScale(const float3& newScale)
//{
//	selectedGameObject->transform->SetScale(newScale.x, newScale.y, newScale.z);
//}


