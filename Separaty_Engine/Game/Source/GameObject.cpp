#include "GameObject.h"

#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

GameObject::GameObject(bool start_enabled)
{

}

GameObject::~GameObject()
{

}

bool GameObject::Init()
{
	GLfloat vertices[] = {
		1.0,	1.0,	1.0,
		0.0f,	1.0,	1.0,
		1.0,	1.0,	0.0f,
		0.0f,	1.0,	0.0f,
		1.0,	0.0f,	1.0,
		0.0f,	0.0f,	1.0,
		0.0f,	0.0f,	0.0f,
		1.0,	0.0f,	0.0f
	};
	GLuint indices[] = {  // note that we start from 0!
		3, 2, 6, 7, 4, 2, 0,
		3, 1, 6, 5, 4, 1, 0
	};

	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//int  success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}


	//

	//// ..:: Initialization code :: ..
	//// 1. bind Vertex Array Object
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);
	//// 2. copy our vertices array in a vertex buffer for OpenGL to use
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// 3. copy our index array in a element buffer for OpenGL to use
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//// 4. then set the vertex attributes pointers
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	return true;
}

bool GameObject::Start()
{
	meshRenderer = new GOC_MeshRenderer();

	std::vector<GLfloat> vertices = {
		1.0,	1.0,	1.0,
		0.0f,	1.0,	1.0,
		1.0,	1.0,	0.0f,
		0.0f,	1.0,	0.0f,
		1.0,	0.0f,	1.0,
		0.0f,	0.0f,	1.0,
		0.0f,	0.0f,	0.0f,
		1.0,	0.0f,	0.0f
	};

	std::vector<uint> indices = {  // note that we start from 0!
		3, 2, 6, 7, 4, 2, 0,
		3, 1, 6, 5, 4, 1, 0
	};

	meshRenderer->SetMesh(vertices, indices);

	return true;
}

update_status GameObject::Update(float dt)
{

	/*glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/

	//App->ui->AppendToOutput(DEBUG_LOG("gameobject"));

	meshRenderer->Execute();
	return UPDATE_CONTINUE;
}

update_status GameObject::PostUpdate(float dt)
{
	/*RenderAxis();*/

	return UPDATE_CONTINUE;
}

bool GameObject::CleanUp()
{

	return true;
}

//void GameObject::RenderAxis()
//{
//
//	glPushMatrix();
//	glMultMatrixf(transform.M);
//
//	// Draw Axis Grid
//	glLineWidth(1.0f);
//
//	glBegin(GL_LINES);
//
//	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
//
//	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
//	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);
//
//	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
//
//	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
//	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
//	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
//	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);
//
//	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
//
//	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
//	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
//	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
//	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);
//
//	glEnd();
//
//	glLineWidth(1.0f);
//
//	glPopMatrix();
//}


bool GameObject::LoadState(JSON_Value* file)
{

	return true;
}

bool GameObject::SaveState(JSON_Value* file) const
{

	return true;
}