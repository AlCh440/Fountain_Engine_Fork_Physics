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
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
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


//	glGenBuffers(1, &VBO);
//	glGenVertexArrays(1, &VAO);
//
//	// ..:: Initialization code :: ..
//// 1. bind Vertex Array Object
//	glBindVertexArray(VAO);
//	// 2. copy our vertices array in a vertex buffer for OpenGL to use
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), indices, GL_STATIC_DRAW);
//	// 3. copy our index array in a element buffer for OpenGL to use
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), indices, GL_STATIC_DRAW);
//	// 4. then set the vertex attributes pointers
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);

	return true;
}

bool GameObject::Start()
{
	mesh.vertices = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	mesh.indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	return true;
}

update_status GameObject::Update(float dt)
{

	/*glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/

	App->ui->AppendToOutput(DEBUG_LOG("gameobject"));

	return UPDATE_CONTINUE;
}

update_status GameObject::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

bool GameObject::CleanUp()
{

	return true;
}

bool GameObject::LoadState(JSON_Value* file)
{

	return true;
}

bool GameObject::SaveState(JSON_Value* file) const
{

	return true;
}