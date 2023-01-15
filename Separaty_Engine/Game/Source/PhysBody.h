#pragma once
#ifndef __PhysBody_H__
#define __PhysBody_H__



#include "p2List.h"

class btRigidBody;

class Module;
class vec3;


struct PhysBody
{
public:
	PhysBody(btRigidBody* body);
	~PhysBody();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);

	void SetLinearVelocity(float x, float y, float z);
	void SetAngularVelocity(float x, float y, float z);
	vec3 GetLinearVelocity() const;

	//const vec3 GetPos() const;

public:

	
	
	//btRigidBody* body;
	p2List<Module*> collision_listeners;
	btRigidBody* body;
	//ColissionObject collType;
	

private:
	
};
#endif