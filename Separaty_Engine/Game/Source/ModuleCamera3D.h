#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "MathGeoLib.h"
#include "MathGeoLibFwd.h"
#include "GOC_Camera.h"

#include "GameObject.h"
#include "GameObjComponent.h"
#include "EngineSystem.h" 

class EngineSystem;
class btMatrix3x3;
class btCollisionObject;
class btSphereShape;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	mat4x4 GetViewMatrix();
	btMatrix3x3 GetViewMatrix3();
	void SetCamera(GOC_Camera* camera)
	{
		//if (this->currentCamera != nullptr)
		//{
		//	this->currentCamera->useCameraWhileInPlay = false;
		//}
		this->currentCamera = camera;
	}

	btCollisionObject* cameraBody;
	btSphereShape* collShape;

	vec3 prevPos;
	vec3 prevReference;
	vec3 prevX;
	vec3 prevY;
	vec3 prevZ;
	
	vec pickStart = vec(0,0,0);
	vec pickDirection = vec(0,0,0);

	vec bboxPoints[8];

private:

	void CalculateViewMatrix();
	void Zoom(const float& zoom_speed);
	void MousePick();

	//void SetZoomSpeed(const float& zoom_speed);
	//float GetZoomSpeed() const;

	float zoomSpeed = 2.0f;

public:


	GameObject* gameObject;

	bool isCurrent = false;

	GOC_Camera* currentCamera;
	GOC_Camera* mainCamera;
	GOC_Camera* goCamera;
	 
	vec3 X, Y, Z, Position, currentReference;
private:


	/*LCG lcg;*/
	mat4x4 ViewMatrix, ViewMatrixInverse;


};