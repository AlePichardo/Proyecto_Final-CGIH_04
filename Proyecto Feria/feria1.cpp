/*---------------------------------------------------------*/
/* -----------------   Proyecto ---------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*- Computación gráfica e interacción humano computadora  -*/
/*-------------         Grupo 4             ---------------*/
/*-------------      Visual Studio 2017       -------------*/
/*----------  Pichardo González Jenny Alejandra  ----------*/
/*-------  Rugerio Fernández Cobos Fanny Berenice  --------*/
/*---------------------------------------------------------*/

//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include<iostream>
#include <stdio.h>
#include "irrKlang.h"
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")


#include <string.h>
#include <cmath>
#include <vector>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_access.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh_texturizado.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"

#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"
#include"SpotLight.h"





const float toRadians = 3.14159265f / 180.0f;
float movCoche;
float movOffset;
float rotapato;
float poscanasta_x=0.0f;
float poscanasta_y=0.0f;
float poscanasta_z=0.0f;
bool avanza,patoadelante;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;
float reproduciranimacion,habilitaranimacion, guardoFrame,reinicioFrame,ciclo,ciclo2,contador=0;
Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture dadoTexture;
Texture pisoTexture;
Texture grassTexture;
Texture carroTexture;
Texture Tagave;
Texture woodTexture;
Texture steelTexture;
Texture redSteelTexture;

Texture Beach_Ball_diffuse;
Texture blue_1;
Texture red_1;
Texture purple_1;
Texture grey_1;
Texture Fencing_Diamond_Mesh;
Texture _1;
Texture _2;
Texture _Metal_Corrogated_Shiny_1;
Texture base_1_1;
Texture base3_1;
Texture boards_1;
Texture Image2;
Texture lower_roof;
Texture lower_top;
Texture M_2;
Texture Metal_Corrogated_Shiny;
Texture Metal_Rushed;
Texture mid_left;
Texture mid_right;
Texture organ;
Texture roof_pannel;
Texture top_left;
Texture top_right;
Texture top_right_1;
Texture blue_sides;
Texture green;
Texture middle_frame;
Texture oben;
Texture red_roof_and_sides;
Texture side;
Texture side_1;
Texture Stone_Vein_Gray;
Texture verz;
Texture black_1;
Texture Roofing_Shingles_Multi;
Texture markise;
Texture green_1;
Texture white_1;
Texture yellow_1;
Texture tent_1;
Texture tent_2;
Texture tent_2_1;
Texture ballons_1;
Texture Metal_Steel_Textured_White;
Texture _Metal_Steel_Textured_White_1;
Texture glass_1;
Texture red_yellow;
Texture Steel_Brushed_Stainless;
Texture _3;
Texture _4;
Texture Fencing_Wood_Old;
Texture shell_sq85;
Texture Wood_Cherry_Original;
Texture Wood_Cherry_Original_2;

//Texture ball_diffuse;
//Texture bear;
//Texture cap_diffuse2;
//Texture red_2;
//Texture Copper;
//Texture Wood_Lumber_ButtJoined;
//Texture Wood_Plywood_Knots;
//Texture _Metal_Seamed_1;
//Texture _Orange_1;
//Texture _Stone_Vein_Gray_1;
//Texture Carpet_Plush_Charcoal;
//Texture Metal_Aluminum_Anodized;
//Texture Metal_Seamed;
//Texture Translucent_Glass_Tinted;



//materiales
Material Material_brillante;
Material Material_opaco;
//luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;

Model Ball;
Model ballontower;
Model bear_M;
Model CWheel;
Model Galloper;
Model helter;
Model hotballons;
Model marketbooth;
Model Michael;
Model MidwayTent;
Model popcorn;
Model tent;
Model Ticketbooth;


Skybox skybox;
Skybox skyboxnoc;

Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

//void my_input(GLFWwindow *window);
void inputKeyframes(bool* keys);

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";
//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, 
						unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);
		
		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}




void CreateObjects() 
{
	unsigned int indices[] = {		
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
	//	x      y      z			u	  v			nx	  ny    nz
		-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};



	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4); //meshList[3]

	unsigned int trackIndices[] = {
		0,1,2,
		0,1,3,
		3,4,18,
		3,17,18,
		17,18,5,
		6,5,17,
		6,5,7,
		6,7,8,
		5,7,9,
		7,9,10,
		9,10,11,
		11,12,10,
		11,12,13,
		13,12,14,
		13,14,15,
		15,16,13,
		16,13,1,
		1,16,2,
	};

	GLfloat trackVertices[] = {
		0.0f, 0.0f, -0.75f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f, //0
		-2.0f, 0.0f, -2.25f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		0.0f, 0.0f, -2.25f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-2.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f, //3
		-2.0f, 0.0f, -1.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-15.0f, 2.25f,-1.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-15.0f, 2.25f, -0.0f, 0.0f, 0.0f,0.0f,-1.0f,0.0f, //6
		-18.0f, 2.25f, -1.5f,0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-17.5f, 2.25f, -1.15f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-16.0f, 2.25f, -3.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,//9
		-18.0f, 2.25f, -3.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-4.0f,  0.0f, -14.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-5.0f, 0.0f, -16.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f, //12
		-2.0f, 0.0f, -14.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-2.0f, 0.0f, -16.75f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-0.0f, 0.0f, -16.75f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,//15
		-0.0f, 0.0f, -16.75f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-9.0f, 0.0f, -0.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-9.0f, 0.0f, -1.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f
	};

	Mesh *obj5 = new Mesh();
	obj5->CreateMesh(trackVertices, trackIndices, 300, 60);
	meshList.push_back(obj5); //Meshlist[4]

	unsigned int carro_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		//20, 21, 22,
		//22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat carro_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.3671f,	0.3984f,	0.0f,	0.0f,	-1.0f,	//0
		1.25f, -0.5f,  0.5f,	0.677f, 0.4042f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.66f,	0.6367f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.3671f,  0.6171f,			0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		1.25f, -0.5f,  0.5f,	0.084f,0.0507f,		-1.0f,	0.0f,	0.0f,
		1.25f, -0.5f,  -0.5f,	0.5371f,0.0507f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.4941f,0.2578f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.1347f,0.2558f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.3671f,  0.6171f,	0.0f,	0.0f,	1.0f,
		1.25f, -0.5f, -0.5f,	0.66f,	0.6367f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.677f, 0.4042f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.3671f,	0.3984f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.6738f, 0.06835f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.9492f, 0.0703f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.8945f, 0.2676f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.7324f, 0.2676f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.1347f,0.7441f,		0.0f,	1.0f,	0.0f,
		1.25f,  -0.5f,  0.5f,	0.084f,  0.9375f,		0.0f,	1.0f,	0.0f,
		 1.25f,  -0.5f,  -0.5f,	0.1347f,0.5390f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.4941f,0.7441f,	0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		// -0.5f, 0.5f,  0.5f,	0.27f,	0.68f,		0.0f,	-1.0f,	0.0f,
		 //0.5f,  0.5f,  0.5f,	0.48f,  0.68f,		0.0f,	-1.0f,	0.0f,
		 // 0.5f, 0.5f,  -0.5f,	0.48f,	0.98f,		0.0f,	-1.0f,	0.0f,
		// -0.5f, 0.5f,  -0.5f,	0.27f,	0.98f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh *carro = new Mesh();
	carro->CreateMesh(carro_vertices, carro_indices, 192, 36);
	meshList.push_back(carro);//Meshlist[5]
/*
	unsigned int estruc_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		//20, 21, 22,
		//22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat estruc_vertices[] = {
		// bot
		//x		y		z		S		T			NX		NY		NZ
		1.0f,  0.0f,  0.0f,	   0.3671f,	0.3984f,	0.0f,	0.0f,	-1.0f,	//0
		0.0f,  0.0f,  0.0f,	   0.677f,  0.4042f,	0.0f,	0.0f,	-1.0f,	//1
		0.0f,  0.0f,  1.0f,	   0.66f,   0.6367f,	0.0f,	0.0f,	-1.0f,	//2
		1.0f,  0.0f,  1.0f,	   0.3671f, 0.6171f,	0.0f,	0.0f,	-1.0f,	//3
		//top 
		//x		y		z		S		T
		1.0f,  10.0f,  0.0f,	0.084f,0.0507f,		-1.0f,	0.0f,	0.0f,
		0.0f,  10.0f,  0.0f,	0.5371f,0.0507f,	-1.0f,	0.0f,	0.0f,
		0.0f,  10.0f,  1.0f,	0.4941f,0.2578f,	-1.0f,	0.0f,	0.0f,
		1.0f,  10.0f,  1.0f,	0.1347f,0.2558f,	-1.0f,	0.0f,	0.0f,
		//cara1
		0.0f,  10.0f,  0.0f,	0.3671f,  0.6171f,	0.0f,	0.0f,	1.0f,
		0.0f,   0.0f,  0.0f,	0.66f,	0.6367f,		0.0f,	0.0f,	1.0f,
		0.0f,   0.0f,  1.0f,	0.677f, 0.4042f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.3671f,	0.3984f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.6738f, 0.06835f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.9492f, 0.0703f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.8945f, 0.2676f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.7324f, 0.2676f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.1347f,0.7441f,		0.0f,	1.0f,	0.0f,
		1.25f,  -0.5f,  0.5f,	0.084f,  0.9375f,		0.0f,	1.0f,	0.0f,
		 1.25f,  -0.5f,  -0.5f,	0.1347f,0.5390f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.4941f,0.7441f,	0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		// -0.5f, 0.5f,  0.5f,	0.27f,	0.68f,		0.0f,	-1.0f,	0.0f,
		 //0.5f,  0.5f,  0.5f,	0.48f,  0.68f,		0.0f,	-1.0f,	0.0f,
		 // 0.5f, 0.5f,  -0.5f,	0.48f,	0.98f,		0.0f,	-1.0f,	0.0f,
		// -0.5f, 0.5f,  -0.5f,	0.27f,	0.98f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh *carro = new Mesh();
	carro->CreateMesh(carro_vertices, carro_indices, 192, 36);
	meshList.push_back(carro);//Meshlist[5]
	*/
	/*unsigned int trackIndices[] = {
		0,1,2,
		0,1,3,
		3,4,18,
		3,17,18,
		17,18,5,
		6,5,17,
		6,5,7,
		6,7,8,
		5,7,9,
		7,9,10,
		9,10,11,
		11,12,10,
		11,12,13,
		13,12,14,
		13,14,15,
		15,16,13,
		16,13,1,
		1,16,2,
	};

	GLfloat trackVertices[] = {
		0.0f, 0.0f, -0.75f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f, //0
		-2.0f, 0.0f, -2.25f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		0.0f, 0.0f, -2.25f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-2.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f, //3
		-2.0f, 0.0f, -1.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-15.0f, 2.25f,-1.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-15.0f, 2.25f, -0.0f, 0.0f, 0.0f,0.0f,-1.0f,0.0f, //6
		-18.0f, 2.25f, -1.5f,0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-17.5f, 2.25f, -1.15f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-16.0f, 2.25f, -3.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,//9
		-18.0f, 2.25f, -3.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-4.0f,  0.0f, -14.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-5.0f, 0.0f, -16.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f, //12
		-2.0f, 0.0f, -14.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-2.0f, 0.0f, -16.75f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-0.0f, 0.0f, -16.75f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,//15
		-0.0f, 0.0f, -16.75f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-9.0f, 0.0f, -0.0f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f,

		-9.0f, 0.0f, -1.5f,	0.0f, 0.0f,	0.0f,-1.0f,0.0f
	};

	Mesh *piso = new Mesh();
	piso->CreateMesh(trackVertices, trackIndices, 300, 60);
	meshList.push_back(piso); //Meshlist[6]*/

unsigned int canasta_indices[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	4, 5, 6,
	6, 7, 4,
	// back
	8, 9, 10,
	10, 11, 8,

	// left
	12, 13, 14,
	14, 15, 12,
	// bottom
	16, 17, 18,
	18, 19, 16,
	// top
	//20, 21, 22,
	//22, 23, 20,
};
//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
GLfloat canasta_vertices[] = {
	// front
	//x		y		z		S		T			NX		NY		NZ
	-0.5f, -0.5f,  0.5f,	0.3671f,	0.3984f,	0.0f,	0.0f,	-1.0f,	//0
	0.5f, -0.5f,  0.5f,	0.677f, 0.4042f,		0.0f,	0.0f,	-1.0f,	//1
	0.5f,  0.5f,  0.5f,		0.66f,	0.6367f,		0.0f,	0.0f,	-1.0f,	//2
	-0.5f,  0.5f,  0.5f,	0.3671f,  0.6171f,			0.0f,	0.0f,	-1.0f,	//3
	// right
	//x		y		z		S		T
	0.5f, -0.5f,  0.5f,	0.084f,0.0507f,		-1.0f,	0.0f,	0.0f,
	0.5f, -0.5f,  -0.5f,	0.5371f,0.0507f,		-1.0f,	0.0f,	0.0f,
	0.5f,  0.5f,  -0.5f,	0.4941f,0.2578f,		-1.0f,	0.0f,	0.0f,
	0.5f,  0.5f,  0.5f,	    0.1347f,0.2558f,		-1.0f,	0.0f,	0.0f,
	// back
	-0.5f, -0.5f, -0.5f,	0.3671f,  0.6171f,	0.0f,	0.0f,	1.0f,
	0.5f, -0.5f, -0.5f,	0.66f,	0.6367f,		0.0f,	0.0f,	1.0f,
	0.5f,  0.5f, -0.5f,		0.677f, 0.4042f,		0.0f,	0.0f,	1.0f,
	-0.5f,  0.5f, -0.5f,	0.3671f,	0.3984f,		0.0f,	0.0f,	1.0f,

	// left
	//x		y		z		S		T
	-0.5f, -0.5f,  -0.5f,	0.6738f, 0.06835f,		1.0f,	0.0f,	0.0f,
	-0.5f, -0.5f,  0.5f,	0.9492f, 0.0703f,		1.0f,	0.0f,	0.0f,
	-0.5f,  0.5f,  0.5f,	0.8945f, 0.2676f,		1.0f,	0.0f,	0.0f,
	-0.5f,  0.5f,  -0.5f,	0.7324f, 0.2676f,		1.0f,	0.0f,	0.0f,

	// bottom
	//x		y		z		S		T
	-0.5f, -0.5f,  0.5f,	0.1347f,0.7441f,		0.0f,	1.0f,	0.0f,
	0.5f,  -0.5f,  0.5f,	0.084f,  0.9375f,		0.0f,	1.0f,	0.0f,
	 0.5f,  -0.5f,  -0.5f,	0.1347f,0.5390f,		0.0f,	1.0f,	0.0f,
	-0.5f, -0.5f,  -0.5f,	0.4941f,0.7441f,	0.0f,	1.0f,	0.0f,

	//UP
	 //x		y		z		S		T
	// -0.5f, 0.5f,  0.5f,	0.27f,	0.68f,		0.0f,	-1.0f,	0.0f,
	 //0.5f,  0.5f,  0.5f,	0.48f,  0.68f,		0.0f,	-1.0f,	0.0f,
	 // 0.5f, 0.5f,  -0.5f,	0.48f,	0.98f,		0.0f,	-1.0f,	0.0f,
	// -0.5f, 0.5f,  -0.5f,	0.27f,	0.98f,		0.0f,	-1.0f,	0.0f,

};

Mesh *canasta = new Mesh();
canasta->CreateMesh(canasta_vertices, canasta_indices, 192, 36);
meshList.push_back(canasta);//Meshlist[6]
}


void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.27f,  0.35f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.48f,	0.35f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.48f,	0.64f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.27f,	0.64f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.52f,  0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.73f,	0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.73f,	0.64f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.52f,	0.64f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.77f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.98f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.98f,	0.64f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.77f,	0.64f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,	0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.23f,  0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.23f,	0.64f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.64f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.27f,	0.02f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.48f,  0.02f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.48f,	0.31f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.27f,	0.31f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.27f,	0.68f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.48f,  0.68f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.48f,	0.98f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.27f,	0.98f,		0.0f,	-1.0f,	0.0f,

	};
	
	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(cubo);

}



void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;



//NEW// Keyframes
float posXavion = 2.0, posYavion = 2.0, posZavion = 0;
float movAvion_x = 0.0f, movAvion_y = 0.0f, movAvion_z = 0.0f;
float giroAvion = 0;
float Aux = 0;

float movCarro_x = 0.0f, movCarro_y = 0.0f, movCarro_z = 0.0f;
float giroCarro = 0;
float AuxCarro = 0;

#define MAX_FRAMES 12
int i_max_steps = 90;
int i_curr_steps = 5; //offset para evitar que sobreescribamos los frames que ya teniamos
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movAvion_x;		//Variable para PosicionX
	float movAvion_y;		//Variable para PosicionY
	float movAvion_z;		//Variable para PosicionZ
	float movAvion_xInc;		//Variable para IncrementoX
	float movAvion_yInc;		//Variable para IncrementoY
	float movAvion_zInc;		//Variable para IncrementoZ
	float giroAvion;
	float giroAvionInc;
	float Aux;
	float AuxInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
FRAME KeyCarro[MAX_FRAMES];
int FrameIndex = 5;
int FrameCarro = 12;		//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movAvion_x = movAvion_x*(deltaTime*0.1);
	KeyFrame[FrameIndex].movAvion_y = movAvion_y*(deltaTime*0.1);
	KeyFrame[FrameIndex].movAvion_z = movAvion_z*(deltaTime*0.1);
	KeyFrame[FrameIndex].giroAvion=giroAvion*(deltaTime*0.1);
	KeyFrame[FrameIndex].Aux = Aux * (deltaTime*0.1);

	FrameIndex++;
}

void resetElements(FRAME * KeyFrame)
{
	
	movAvion_x = KeyFrame[0].movAvion_x;
	movAvion_y = KeyFrame[0].movAvion_y;
	movAvion_z = KeyFrame[0].movAvion_y;
	giroAvion= KeyFrame[0].giroAvion;
	Aux= KeyFrame[0].Aux;
}

void interpolation(FRAME * KeyFrame)
{
	KeyFrame[playIndex].movAvion_xInc = (KeyFrame[playIndex + 1].movAvion_x - KeyFrame[playIndex].movAvion_x) / i_max_steps;
	KeyFrame[playIndex].movAvion_yInc = (KeyFrame[playIndex + 1].movAvion_y - KeyFrame[playIndex].movAvion_y) / i_max_steps;
	KeyFrame[playIndex].movAvion_zInc = (KeyFrame[playIndex + 1].movAvion_z - KeyFrame[playIndex].movAvion_z) / i_max_steps;
	KeyFrame[playIndex].giroAvionInc = (KeyFrame[playIndex + 1].giroAvion - KeyFrame[playIndex].giroAvion) / i_max_steps;
	KeyFrame[playIndex].AuxInc = (KeyFrame[playIndex + 1].Aux - KeyFrame[playIndex].Aux) / i_max_steps;
}


void animate(FRAME* KeyFrame, int FrameIndex)
{
	//Movimiento del objeto
	if (play)
	{	
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation(KeyFrame);
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation
			movAvion_x += KeyFrame[playIndex].movAvion_xInc;
			movAvion_y += KeyFrame[playIndex].movAvion_yInc;
			movAvion_z += KeyFrame[playIndex].movAvion_zInc;
			giroAvion += KeyFrame[playIndex].giroAvionInc;
			Aux += KeyFrame[playIndex].AuxInc;
			i_curr_steps++;
		}

	}
}

/* FIN KEYFRAMES*/



int main() 
{
	ISoundEngine * engine = irrklang::createIrrKlangDevice();

	if (!engine)
	{
		printf("Could not startup engine\n");
		return 0; // error starting up the engine
	}

	// To play a sound, we only to call play2D(). The second parameter
	// tells the engine to play it looped.

	// play some sound stream, looped
	engine->play2D("Witchyworld.mp3", true);

	// In a loop, wait until user presses 'q' to exit or another key to
	// play another sound.
	// After we are finished, we have to delete the irrKlang Device created earlier
	// with createIrrKlangDevice(). Use ::drop() to do that. In irrKlang, you should
	// delete all objects you created with a method or function that starts with 'create'.
	// (an exception is the play2D()- or play3D()-method, see the documentation or the
	// next example for an explanation)
	// The object is deleted simply by calling ->drop().

	engine->drop(); // delete engine
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();
	GLint gradiente=0;
	CreateObjects();
	CrearCubo();
	CreateShaders();
	float i = 0.0f;
	int c = 0;
	int g = 0;
	float v = 0;
	float y = 0.0f;
	float s = -1.5f;
	float rota = 0.0;
	int r = 0;
	float x = 0.0f;
	int dian=0;
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f, glm::vec3(0.0f, 0.0f, -1.0f));

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	carroTexture = Texture("Textures/carroRojo.tga");
	carroTexture.LoadTextureA();
	grassTexture = Texture("Textures/grass.tga");
	grassTexture.LoadTextureA();
	dadoTexture = Texture("Textures/dado.tga");
	dadoTexture.LoadTextureA();
	pisoTexture= Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	Tagave = Texture("Textures/Agave.tga");
	Tagave.LoadTextureA();
	woodTexture = Texture("Textures/whitewood.tga");
	woodTexture.LoadTextureA();
	steelTexture = Texture("Textures/whiteSteel.tga");
	steelTexture.LoadTextureA();
	redSteelTexture = Texture("Textures/redsteel.tga");
	redSteelTexture.LoadTextureA();

	Beach_Ball_diffuse = Texture("Textures/Beach_Ball_diffuse.png");
	Beach_Ball_diffuse.LoadTextureA();
	blue_1 = Texture("Textures/blue_1.png");
	blue_1.LoadTextureA();
	red_1 = Texture("Textures/red_1.png");
	red_1.LoadTextureA();
	grey_1 = Texture("Textures/grey_1.png");
	grey_1.LoadTextureA();
	purple_1 = Texture("Textures/purple_1.png");
	purple_1.LoadTextureA();
	tent_1 = Texture("Textures/tent_1.png");
	tent_1.LoadTextureA();
	tent_2 = Texture("Textures/tent_2.png");
	tent_2.LoadTextureA();
	tent_2_1 = Texture("Textures/tent_2_1.png");
	tent_2_1.LoadTextureA();

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	
	
	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt.3ds");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/k_rueda.3ds");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Camino_M = Model();
	Camino_M.LoadModel("Models/railroad track.obj");

	Ball = Model();
	Ball.LoadModel("Models/Ball.obj");
	CWheel = Model();
	CWheel.LoadModel("Models/CWheel.obj");
	Galloper = Model();
	Galloper.LoadModel("Models/Galloper.obj");
	Michael = Model();
	Michael.LoadModel("Models/Michael.obj");
	Ticketbooth = Model();
	Ticketbooth.LoadModel("Models/Ticketbooth.obj");
	ballontower = Model();
	ballontower.LoadModel("Models/ballontower.obj");
	tent = Model();
	tent.LoadModel("Models/tent.obj");
	hotballons = Model();
	hotballons.LoadModel("Models/hotballons.obj");
	helter = Model();
	helter.LoadModel("Models/helter.obj");
	marketbooth = Model();
	marketbooth.LoadModel("Models/marketbooth.obj");

	//bear_M = Model();
	//bear_M.LoadModel("Models/bear.obj");
	//MidwayTent = Model();
	//MidwayTent.LoadModel("Models/MidwayTent.obj");
	//popcorn = Model();
	//popcorn.LoadModel("Models/popcorn.obj");

	
	
	
	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
								0.3f, 0.3f,
								0.0f, 0.0f, -1.0f);

 // delete engine*/
//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
								0.0f, 1.0f,
								2.0f, 1.5f,1.5f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;
	
	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		0.0f, 2.0f,
		10.0f, 0.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	spotLightCount++;
	//luz de faro
	spotLights[2] = SpotLight(0.0f, 1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, -1.5f, 0.0f,
		-4.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	spotLightCount++;
	//luz de helicoptero
	spotLights[3] = SpotLight(0.0f, 0.0f, 1.0f,
		0.0f, 1.0f,
		2.0 - movCoche, 2.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	spotLightCount++;

	spotLights[4] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		-3.5f, 2.25f, 11.0f,
		1.1f, 0.0f,13.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	spotLightCount++;
	glm::vec3 posblackhawk = glm::vec3(2.0f, 0.0f, 0.0f);
	glm::vec3 poscanasta = glm::vec3(0.0f, 0.0f, 0.0f);
	std::vector<std::string> skyboxFaces;
	std::vector<std::string> skyboxnoche;

		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");
		skybox = Skybox(skyboxFaces);
		
		skyboxnoche.push_back("Textures/Skybox/cupertin-lake-night_rt.tga");
		skyboxnoche.push_back("Textures/Skybox/cupertin-lake-night_lf.tga");
		skyboxnoche.push_back("Textures/Skybox/cupertin-lake-night_dn.tga");
		skyboxnoche.push_back("Textures/Skybox/cupertin-lake-night_up.tga");
		skyboxnoche.push_back("Textures/Skybox/cupertin-lake-night_bk.tga");
		skyboxnoche.push_back("Textures/Skybox/cupertin-lake-night_ft.tga");
		skyboxnoc= Skybox(skyboxnoche);
	
	
	

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 300.0f);
	
	movCoche = 0.0f;
	movOffset = 1.0f;
	avanza = 1;
	
	//KEYFRAMES DECLARADOS INICIALES
	
	/*KeyFrame[0].movAvion_x = 0.0f;
	KeyFrame[0].movAvion_y = 0.0f;
	KeyFrame[0].giroAvion = 0;


	KeyFrame[1].movAvion_x = 1.0f;
	KeyFrame[1].movAvion_y = 2.0f;
	KeyFrame[1].giroAvion = 0;


	KeyFrame[2].movAvion_x = 2.0f;
	KeyFrame[2].movAvion_y = 0.0f;
	KeyFrame[2].giroAvion = 0;


	KeyFrame[3].movAvion_x = 3.0f;
	KeyFrame[3].movAvion_y = -2.0f;
	KeyFrame[3].giroAvion = 0;

	KeyFrame[4].movAvion_x = 4.0f;
	KeyFrame[4].movAvion_y = 0.0f;
	KeyFrame[4].giroAvion = 0.0f;

	/*KeyFrame[5].movAvion_x = 0.0f;
	KeyFrame[5].movAvion_y = 0.0f;
	KeyFrame[5].giroAvion = 180.0f;*/
	/*Montaña Rusa*/
	KeyCarro[0].movAvion_x = 0.0f;
	KeyCarro[0].movAvion_y = 0.0f;
	KeyCarro[0].movAvion_z = 0.0f;
	KeyCarro[0].giroAvion = 0.0f;
	KeyCarro[0].Aux = 0.0f;


	KeyCarro[1].movAvion_x = 0.125f;
	KeyCarro[1].movAvion_y = 0.0f;
	KeyCarro[1].movAvion_z = 0.025f;
	KeyCarro[1].giroAvion = -77.43;
	KeyCarro[1].Aux = 0.0f;


	KeyCarro[2].movAvion_x = 0.0f;
	KeyCarro[2].movAvion_y = 0.0f;
	KeyCarro[2].movAvion_z = 7.5f;
	KeyCarro[2].giroAvion = -77.43;
	KeyCarro[2].Aux = 0.0f;


	KeyCarro[3].movAvion_x = 0.0f;
	KeyCarro[3].movAvion_y = 0.15f;
	KeyCarro[3].movAvion_z = 8.0f;
	KeyCarro[3].giroAvion = -77.43;
	KeyCarro[3].Aux = 23.0f;

	KeyCarro[4].movAvion_x = 0.0f;
	KeyCarro[4].movAvion_y = 2.35f;
	KeyCarro[4].movAvion_z = 15.0f;
	KeyCarro[4].giroAvion = -77.43;
	KeyCarro[4].Aux = 23.0f;

	KeyCarro[5].movAvion_x = 0.0f;
	KeyCarro[5].movAvion_y = 2.25f;
	KeyCarro[5].movAvion_z = 15.5f;
	KeyCarro[5].giroAvion = -77.43;
	KeyCarro[5].Aux = 0.0f;

	KeyCarro[6].movAvion_x = -2.20f;
	KeyCarro[6].movAvion_y = 2.25f;
	KeyCarro[6].movAvion_z = 16.5f;
	KeyCarro[6].giroAvion = -198.43;
	KeyCarro[6].Aux = 0.0f;

	KeyCarro[7].movAvion_x = -2.20f;
	KeyCarro[7].movAvion_y = 2.25f;
	KeyCarro[7].movAvion_z = 16.5f;
	KeyCarro[7].giroAvion = -198.43;
	KeyCarro[7].Aux = -8.0f;

	KeyCarro[8].movAvion_x = -14.20f;
	KeyCarro[8].movAvion_y = 0.0f;
	KeyCarro[8].movAvion_z = 3.7f;
	KeyCarro[8].giroAvion = -198.43;
	KeyCarro[8].Aux = -8.0f;

	KeyCarro[9].movAvion_x = -14.0f;
	KeyCarro[9].movAvion_y = 0.0f;
	KeyCarro[9].movAvion_z = 1.0f;
	KeyCarro[9].giroAvion = -230.43;
	KeyCarro[9].Aux = 0.0f;

	KeyCarro[10].movAvion_x = -13.625f;
	KeyCarro[10].movAvion_y = 0.0f;
	KeyCarro[10].movAvion_z = 0.0f;
	KeyCarro[10].giroAvion = -310;
	KeyCarro[10].Aux = 0.0f;

	KeyCarro[11].movAvion_x = 0.0f;
	KeyCarro[11].movAvion_y = 0.0f;
	KeyCarro[11].movAvion_z = 0.0f;
	KeyCarro[11].giroAvion = -310;
	KeyCarro[11].Aux = 0.0f;
	//Agregar Kefyrame[5] para que el avión regrese al inicio


	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		rota = rota + 1.0f;
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime; 
		//deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		if (avanza)
		{
			if (movCoche < 10.0f)
			{
//				movCoche += movOffset*deltaTime;
				movCoche += movOffset;
				avanza = 1;
			}
			else
			{
				avanza = 0;
			}
		}
		else
		{
			if (movCoche > -10.0f)
			{
				movCoche -= movOffset*deltaTime;
			}
			else
			{
				avanza = 1;
			}


		}
		
		
		//Recibir eventos del usuario
		glfwPollEvents();
		c = mainWindow.getc();
		dian = mainWindow.getdian();
		if (c % 6 == 0) {
			camera.keyControl(mainWindow.getsKeys(), deltaTime);
			camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		}
		if (c % 6 == 1) {
			camera = Camera(glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -0.0f, -90.0f, 5.0f, 0.5f, glm::vec3(-9.0f, -9.0f, -2.0f));
			
		}
		if (c % 6 == 2) {
			camera = Camera(glm::vec3(9.0f, 9.0f, 9.0f), glm::vec3(0.0f, 1.0f, 0.0f), 175.0f, -40.0f, 5.0f, 0.5f, glm::vec3(-0.0f, -0.0f, -1.0f));
		}
		if (c % 6 == 3) {
			camera = Camera(glm::vec3(movAvion_x-0.1f, movAvion_y+1.05f, movAvion_z+0.1f), glm::vec3(0.0f, 1.0f, 0.0f), 20.0f-giroAvion,1.0f+Aux, 5.0f, 0.5f, glm::vec3(-0.0f, -0.0f, -1.0f));
		}
		if (c % 6 == 4) {
			camera = Camera(glm::vec3(5.15f, 3.25f, -2.5f), glm::vec3(0.0f, 1.0f, 0.0f), 17.0f, 1.0f, 8.0f, 0.5f, glm::vec3(-0.0f, -0.0f, -1.0f));
		}
		if (c % 6 == 5) {
			camera = Camera(poscanasta+glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 200.0f+mainWindow.gety2(), 1.0f + mainWindow.getz2(), 5.0f, 0.5f, glm::vec3(-0.0f, -0.0f, -1.0f));
		}
		printf("c: %i", c);
		//camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		//para keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate(KeyCarro,FrameCarro);
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (dian % 2 == 0) {
			skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		if (dian % 2 == 1) {
			skyboxnoc.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0);
		glm::mat4 mattemp(1.0);


		model = glm::mat4(1.0); //piso
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f,30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//pisoTexture.UseTexture();
		grassTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, 0.0f, -0.7f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));//kitt
		model = glm::translate(model, glm::vec3(x+movAvion_x, s+2.04f+movAvion_y, i+movAvion_z));//kitt
		model = glm::rotate(model, (giroAvion*1.15f)* toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, Aux * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carroTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//Kitt_M.RenderModel();
		meshList[5]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, -0.15f, 1.0f)); //del der
		model = glm::translate(model, glm::vec3(0.7f, -0.15f, -0.5f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, g * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Llanta_M.RenderModel();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -1.0f)); //del izq
		//model = glm::translate(model, glm::vec3(1.0f, -0.03f, -0.5f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, g * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Llanta_M.RenderModel();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.10f, -0.0f, 0.0f));//tras izq
		//model = glm::translate(model, glm::vec3(1.0f, -0.03f, -0.5f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, g * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Llanta_M.RenderModel();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f)); //tras der
		//model = glm::translate(model, glm::vec3(1.0f, -0.03f, -0.5f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, g * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Llanta_M.RenderModel();

		
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movCoche, -1.5f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Kitt_M.RenderModel();
		spotLights[2].SetPos(glm::vec3(movCoche, -1.5f, 0.0f));*/

		/*model = glm::mat4(1.0);
		posblackhawk = glm::vec3(posXavion,posYavion, posZavion);
		model = glm::translate(model, posblackhawk);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, -90* toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90* toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, giroAvion * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Blackhawk_M.RenderModel();*/
		spotLights[3].SetPos(posblackhawk);
		
		
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.53f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Camino_M.RenderModel();*/
		mattemp=glm::mat4 (1.0);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.18f, -1.0f, 0.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		
		mattemp=model = glm::translate(mattemp, glm::vec3(0.4f, 0.0f, 1.0f));//0.58f, -1.0f, 1.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		
		mattemp=model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp=model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		
		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 2.48f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 3.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 3.9f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 4.65f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 5.45f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 6.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp=model = glm::translate(mattemp, glm::vec3(-0.33f, 0.0f, 1.0f));//ant=0.58f, -1.0f, 1.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 6.5f, 0.2f));//Actual=0.25f, -1.0f,15.0f
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp=model = glm::translate(mattemp, glm::vec3(-0.4f, 0.0f, 1.0f)); //Actual=-0.15f,-1.0f,16.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 6.5f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp=model = glm::translate(mattemp, glm::vec3(-0.35f, 0.0f, 1.0f));//actual=-0.5f, -1.0f, 17.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 6.5f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.75f, 0.0f, 0.0f));//actual=-1.25f, -1.0f, 17.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 6.4f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp=model = glm::translate(mattemp, glm::vec3(-1.15f, 0.0f, 0.0f)); //actual=-2.4f, -1.0f, 17.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 6.4f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp=model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));//-3.4f, -1.0f, 16.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 5.9f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 5.6f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 5.3f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 5.0f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 4.6f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 4.3f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 3.95f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 3.6f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 3.25f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 2.9f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f));
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 2.55f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.0f, -1.0f)); //-14.4f, -1.0f, 5.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 2.25f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh(); //ctrl+v

	
		mattemp=model = glm::translate(mattemp, glm::vec3(-0.6f, 0.0f, -1.0f));//-15.0f, -1.0f, 4.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp=model = glm::translate(mattemp, glm::vec3(-0.4f, 0.0f, -1.0f));//-15.4f, -1.0f, 3.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp=model = glm::translate(mattemp, glm::vec3(-0.3f, 0.0f, -1.0f));//-15.7f, -1.0f, 2.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.2f, 0.0f, -1.0f));//-15.9f, -1.0f, 1.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.0f, 0.0f, -1.0f));//-15.9f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.9f, 0.0f, 0.0f));//-15.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-14.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-13.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-12.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-11.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-10.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-9.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-8.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-7.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-6.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-5.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-4.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-3.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-2.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, 0.0f, 0.0f));//-1.0f,-1.0f,0.0f
		mattemp = model;
		model = glm::scale(model, glm::vec3(0.2f, 1.99f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		woodTexture.UseTexture();
		meshList[7]->RenderMesh();
	
		//Agave ¿qué sucede si lo renderizan antes del coche y de la pista?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.7f, -2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Tagave.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		
		//Rueda de la fortuna
		mattemp = glm::mat4(1.0);
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(15.0f, 5.0f, -0.0f));//eje de rotacion
		model = glm::rotate(model, rota*0.10f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		mattemp= model = glm::translate(model, glm::vec3(0.0f, -3.45f, 0.0f));//5.0,1.0,0.0
		mattemp = model;
		model = glm::rotate(model, 90* toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 90* toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp=model = glm::translate(mattemp, glm::vec3(-2.0f, 0.4f, 1.76f));
		mattemp = model;
		model = glm::rotate(model, 60.22f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 60.22f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, 1.30f, 1.325f));
		mattemp = model;
		model = glm::rotate(model, 30.11f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 30.11f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, 1.75f, 0.475f));
		mattemp = model;
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, 1.80f, -0.470f));
		mattemp = model;
		model = glm::rotate(model, -30.11f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, -30.11f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, 1.25f, -1.27f));
		mattemp = model;
		model = glm::rotate(model, -60.22f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, -60.22f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, 0.48f, -1.75f));
		mattemp = model;
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, -0.50f, -1.8f));
		mattemp = model;
		model = glm::rotate(model, 60.22f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 60.22f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, -1.3f, -1.3f));
		mattemp = model;
		model = glm::rotate(model, 30.11f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 30.11f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, -1.75f, -0.475f));
		mattemp = model;
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, -1.8f, 0.5f));
		mattemp = model;
		model = glm::rotate(model, -30.11f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, -30.11f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, -1.2f, 1.25f));
		mattemp = model;
		model = glm::rotate(model, -60.22f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, -60.22f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, -0.44f, 0.85f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 2.0f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.9f, 1.55f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, -0.0f, -5.2f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 1.6f, -0.95f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, 7.05f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 2.0f, 0.0f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -7.05f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 1.495f, 0.95f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.05f, 5.15f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.95f, -1.6f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -2.0f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 2.3f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, -3.6f, 1.0f));
		mattemp = model;
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 3.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(1.0f, -0.0f, -0.05f));
		mattemp = model;
		model = glm::rotate(model, 15.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, 0.2f, 0.05f));
		mattemp = model;
		model = glm::rotate(model, 15.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 45.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 45.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 75.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 75.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 105.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 105.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 135.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 135.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.0f, 0.0f, -0.0f));
		mattemp = model;
		model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 7.0f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-1.0f, 0.1f, 3.6f));//canasta 1
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.5f, -2.0f, 0.0f));//canasta 2
		mattemp = model;
		poscanasta = glm::column(mattemp, 3);
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.5f, -2.0f, -1.0f));//canasta 3
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.5f, -1.1f, -1.5f));//canasta 4
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.5f,-0.25f, -2.0f));//canasta 5
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.4f, 0.75f, -1.7f));//canasta 6
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.5f, 1.25f, -1.0f));//canasta 7
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 1.8f, -0.0f));//canasta 7
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 1.25f, 1.05f));//canasta 8
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, -0.1f, 5.1f));//canasta 9
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.6f, -1.5f));//canasta 10
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, -0.25f, -2.0f));//canasta 11
		mattemp = model;
		model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.55f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[6]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-0.45f, 0.225f, 0.0f));
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.925f, 0.0f, 0.0f));
		mattemp = model;
		//model = glm::rotate(model, -rota*0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 165.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.10f, 1.0f, 0.10f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		steelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = glm::mat4(1.0);
		model = glm::mat4(1.0);

		mattemp = model = glm::translate(model, glm::vec3(14.7f, 1.6f, 3.2f));//soporte
		//mattemp = model;
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -45.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 9.5f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(2.65f, 0.1f, -0.1f));//soporte
		//mattemp = model;
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -45.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 9.5f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(0.0f, 0.0f, -6.125f));//soporte
		//mattemp = model;
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 9.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[7]->RenderMesh();

		mattemp = model = glm::translate(mattemp, glm::vec3(-2.6f, 0.0f, 0.0f));//soporte
		//mattemp = model;
		//model = glm::rotate(model, -rota * 0.1f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 9.0f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		redSteelTexture.UseTexture();
		meshList[7]->RenderMesh();

		//Tickets
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, -2.0f, 7.0f));
		model = glm::scale(model, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Ticketbooth.RenderModel();

		//Pelota
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-15.0f, -2.0f, -5.0f));
		////model = glm::translate(model, glm::vec3(0.0f, posY, posX));
		//model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//Ball.RenderModel();

		//CWheel
	/*	model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CWheel.RenderModel();*/

		//Galloper
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -2.0f, 30.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, movBear));
		model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Galloper.RenderModel();

		//Tickets
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -2.0f, 16.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Ticketbooth.RenderModel();

		//Tienda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -2.0f, -25.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Michael.RenderModel();

		//Tickets
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, -2.0f, -5.0f));
		model = glm::scale(model, glm::vec3(0.0015f, 0.0015f, 0.0015f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Ticketbooth.RenderModel();

		//Balloons Tower
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, -2.0f, 34.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ballontower.RenderModel();

		//Tent
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, -2.0f, -18.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		tent.RenderModel();

		//Globos aerostaticos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, 0.0f, -28.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		hotballons.RenderModel();

		//Tobogan
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, -2.0f, -20.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		helter.RenderModel();

		//Market
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -2.0f, 58.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		marketbooth.RenderModel();

		//glDisable(GL_BLEND);
			glUseProgram(0);

			

		mainWindow.swapBuffers();
	}

	return 0;
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if(reproduciranimacion<1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements(KeyCarro);
				//First Interpolation				
				interpolation(KeyCarro);
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;
			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
	}
	
	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("movAvion_x es: %f\n", movAvion_x);
			//printf("movAvion_y es: %f\n", movAvion_y);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame=0;
		}
	}
	
	
	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_x += 1.0f;
			printf("movAvion_x es: %f\n", movAvion_x);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}
		
	}
	if (keys[GLFW_KEY_2])
	{
		if(ciclo2<1)
		{
		ciclo = 0;
		}
	}
	if (keys[GLFW_KEY_3])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_x -= 1.0f;
			printf("movAvion_x es: %f\n", movAvion_x);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_4])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			giroAvion -= 1.0f;
			printf("giro es: %f\n", movAvion_x);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}

	}


}
