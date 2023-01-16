#include "Application.h"

#include "GOC_Camera.h"
#include "GameObject.h"

#include "Geometry/Frustum.h"

GOC_Camera::GOC_Camera(GameObject* gameObjectAttached, int id)
{
	this->id = id;

	GOC_type = GOC_Type::GOC_CAMERA;
	gameObject = gameObjectAttached;

	

	if (gameObject != nullptr && gameObject->transform != nullptr)
	{
		vec3 a = this->gameObject->transform->transformWorld.translation();

		Position = a;
		Reference = vec3(0.0f, 0.0f, 1.0f);

		Z = normalize(Position - Reference);
		X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
		Y = cross(Z, X);

		
	}
	else
	{
		X = vec3(1.0f, 0.0f, 0.0f);
		Y = vec3(0.0f, 1.0f, 0.0f);
		Z = vec3(0.0f, 0.0f, 1.0f);

		Position = vec3(0.0f, 0.0f, 5.0f);
		Reference = vec3(0.0f, 0.0f, 0.0f);
	}

	CalculateViewMatrix();

	frustum.pos = float3(Position.x, Position.y, Position.z);
	frustum.front = float3(Z.x, Z.y, Z.z);
	frustum.up = float3(Y.x, Y.y, Y.z);

	frustum.type = PerspectiveFrustum;
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumLeftHanded);
	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 100;
	frustum.verticalFov = 60.0f * DEGTORAD;
	frustum.horizontalFov = 2.f * atan(tan(frustum.verticalFov * 0.5f) * (SCREEN_WIDTH / SCREEN_HEIGHT));

	frustumColor = Color(0, 1, 0, 1);

	cameraBody = new btCollisionObject();

	collShape = new btSphereShape(2);
	
	cameraBody->setCollisionShape(collShape);
	
	App->physics->world->addCollisionObject(cameraBody);
}

bool GOC_Camera::Execute()
{

	btTransform a;
	cameraBody->setWorldTransform(a);

	UpdateFrustum();

	frustum.GetCornerPoints(bboxPoints);

	if (drawFrustum)
	{
		DrawCube(bboxPoints, frustumColor);

	}
	return true;
}
void GOC_Camera::UpdateFrustum()
{
	//CalculateViewMatrix();

	if (gameObject != nullptr)
	{
		vec3 pos = gameObject->transform->transformWorld.translation();
		mat4x4 rot = gameObject->transform->rotationLocal;

		X = vec3(rot[0], rot[1], rot[2]);
		Y = vec3(rot[4], rot[5], rot[6]);
		Z = vec3(rot[8], rot[9], rot[10]);

		Position = pos;
	}

	frustum.pos = float3(Position.x, Position.y, Position.z);
	frustum.front = float3(Z.x, Z.y, Z.z);
	frustum.up = float3(Y.x, Y.y, Y.z);
	

}

float4x4 GOC_Camera::GetViewMatrix()
{
	float4x4 matrix;

	matrix = frustum.ViewMatrix();
	matrix.Transpose();

	return matrix;
}

float4x4 GOC_Camera::GetProjectionMatrix()
{
	float4x4 matrix;

	matrix = frustum.ProjectionMatrix();
	matrix.Transpose();

	return matrix;
}

void GOC_Camera::SetPos(float x, float y, float z)
{
	frustum.pos = float3(x, y, z);
}
void GOC_Camera::SetPos(float3 pos)
{
	frustum.pos = pos;
}

float3 GOC_Camera::GetPos()
{
	return frustum.pos;
}

void GOC_Camera::LookAt(const vec3& Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}

void GOC_Camera::DrawCube(static float3* corners, Color color)
{
	glLineWidth(2.0f);
	glColor4f(color.r, color.g, color.b, color.a);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDisable(GL_CULL_FACE);

	glBegin(GL_QUADS);

	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[3]);

	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[2]);
	glVertex3fv((GLfloat*)&corners[6]);

	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[6]);
	glVertex3fv((GLfloat*)&corners[7]);

	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[2]);

	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[6]);
	glVertex3fv((GLfloat*)&corners[2]);

	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[1]);

	glEnd();


}


bool GOC_Camera::SaveState(JSON_Value* file, std::string root) const
{
	/*
	
	frustum.type = PerspectiveFrustum;
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumLeftHanded);
	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 100;
	frustum.verticalFov = 60.0f * DEGTORAD;
	frustum.horizontalFov = 2.f * atan(tan(frustum.verticalFov * 0.5f) * (SCREEN_WIDTH / SCREEN_HEIGHT));
	
	*/

	json_object_dotset_number(json_object(file), std::string(root + "frustum.type").c_str(), (int)frustum.type);
	json_object_dotset_boolean(json_object(file), std::string(root + "frustum.draw").c_str(), drawFrustum);
	json_object_dotset_number(json_object(file), std::string(root + "frustum.frustumProjectiveSpace").c_str(), (int)frustum.ProjectiveSpace());
	json_object_dotset_number(json_object(file), std::string(root + "frustum.handedness").c_str(), (int)frustum.Handedness());
	json_object_dotset_number(json_object(file), std::string(root + "frustum.nearPlaneDistance").c_str(), (float)frustum.nearPlaneDistance);
	json_object_dotset_number(json_object(file), std::string(root + "frustum.farPlaneDistance").c_str(), (float)frustum.farPlaneDistance);
	json_object_dotset_number(json_object(file), std::string(root + "frustum.verticalFov").c_str(), (float)frustum.verticalFov);
	json_object_dotset_number(json_object(file), std::string(root + "frustum.horizontalFov").c_str(), (float)frustum.horizontalFov);
	json_object_dotset_number(json_object(file), std::string(root + "frustum.color.r").c_str(), (float)frustumColor.r);
	json_object_dotset_number(json_object(file), std::string(root + "frustum.color.g").c_str(), (float)frustumColor.g);
	json_object_dotset_number(json_object(file), std::string(root + "frustum.color.b").c_str(), (float)frustumColor.b);

	json_object_dotset_boolean(json_object(file), std::string(root + "current").c_str(), (float)isCurrentCamera);
	json_object_dotset_boolean(json_object(file), std::string(root + "use").c_str(), (float)useCameraWhileInPlay);


	return true;
}

bool GOC_Camera::LoadState(JSON_Value* file, std::string root)
{

	frustum.type = (FrustumType)json_object_dotget_number(json_object(file), std::string(root + "frustum.type").c_str());
	drawFrustum = (FrustumType)json_object_dotget_boolean(json_object(file), std::string(root + "frustum.draw").c_str());
	frustum.projectiveSpace = (FrustumProjectiveSpace)json_object_dotget_number(json_object(file), std::string(root + "frustum.frustumProjectiveSpace").c_str());
	frustum.handedness = (FrustumHandedness)json_object_dotget_number(json_object(file), std::string(root + "frustum.handedness").c_str());
	frustum.nearPlaneDistance = (float)json_object_dotget_number(json_object(file), std::string(root + "frustum.nearPlaneDistance").c_str());
	frustum.farPlaneDistance = (float)json_object_dotget_number(json_object(file), std::string(root + "frustum.farPlaneDistance").c_str());
	frustum.verticalFov = (float)json_object_dotget_number(json_object(file), std::string(root + "frustum.verticalFov").c_str());
	frustum.horizontalFov = (float)json_object_dotget_number(json_object(file), std::string(root + "frustum.horizontalFov").c_str());
	frustumColor.r = (float)json_object_dotget_number(json_object(file), std::string(root + "frustum.color.r").c_str());
	frustumColor.g = (float)json_object_dotget_number(json_object(file), std::string(root + "frustum.color.g").c_str());
	frustumColor.b = (float)json_object_dotget_number(json_object(file), std::string(root + "frustum.color.b").c_str());

	isCurrentCamera = json_object_dotget_boolean(json_object(file), std::string(root + "current").c_str());
	useCameraWhileInPlay = json_object_dotget_boolean(json_object(file), std::string(root + "use").c_str());



	return true;
}

