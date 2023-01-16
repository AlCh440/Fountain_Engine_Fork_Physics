#ifndef __Camera_H__
#define __Camera_H__


#include "GameObject.h"
#include "Globals.h"
#include <vector>
#include "GameObjComponent.h";


#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glmath.h"

#include "MathGeoLib/MathGeoLib.h"

class GameObject;
class GameObjectComponent;
class btCollisionObject;
class btSphereShape;
class GOC_Camera : public GameObjectComponent
{
public:
	GOC_Camera(GameObject* gameObjectAttached, int id);

	void UpdateFrustum();
	void DrawCube(static float3* corners, Color color);


	bool Execute();


	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

	~GOC_Camera() {}


	void		SetPos(float x, float y, float z);
	void		SetPos(float3 pos);
	float3		GetPos();

	void LookAt(const vec3& Spot);

public:
	Frustum frustum;

	btCollisionObject* cameraBody;
	btSphereShape* collShape;
	float nearPlaneDistance = 0.0f;
	float farPlaneDistance = 0.0f;
	float verticalFov = 0.0f;
	float horizontalFov = 0.0f;

	enum FructumSide
	{
		BEHIND,
		OUT_,
		IN_,
		INTERSECT
	};

	// tests if a AaBox is within the frustrum
	int ContainsAaBox(const AABB& refBox) const
	{
		vec vCorner[8];
		int iTotalIn = 0;
		refBox.GetCornerPoints(vCorner); // get the corners of the box into the vCorner array
		// test all 8 corners against the 6 sides
		// if all points are behind 1 specific plane, we are out
		// if we are in with all points, then we are fully in
		for (int p = 0; p < 6; ++p) {
			int iInCount = 8;
			int iPtIn = 1;
			for (int i = 0; i < 8; ++i) {
				// test this point against the planes
				bool a = frustum.GetPlane(p).IsOnPositiveSide(vCorner[i]);
				if (a == BEHIND) { //<-- “IsOnPositiveSide” from MathGeoLib
					iPtIn = 0;
					--iInCount;
				}
			}
			// were all the points outside of plane p?
			if(iInCount == 0)
				return(OUT_);
			// check if they were all on the right side of the plane
			iTotalIn += iPtIn;
		}
		// so if iTotalIn is 6, then all are inside the view
		if (iTotalIn == 6)
			return(IN_);
		// we must be partly in then otherwise
		return(INTERSECT);
	}

	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;

	bool isCurrentCamera = false;
	bool useCameraWhileInPlay = false;

	vec3 X, Y, Z, Position, Reference;
	vec bboxPoints[8];
	Color frustumColor;

	bool drawFrustum = true;;
private:


	/*LCG lcg;*/
	mat4x4 ViewMatrix, ViewMatrixInverse;

	void CalculateViewMatrix()
	{
		ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
		ViewMatrixInverse = inverse(ViewMatrix);
	}
};

#endif // !__Camera_H__
#pragma once
