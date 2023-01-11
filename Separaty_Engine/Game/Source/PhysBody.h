#pragma once

class btRigidBody;

struct PhysBody
{
public:
	PhysBody(btRigidBody* body);
	~PhysBody();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);

	btRigidBody* body = nullptr;
private:
	
};