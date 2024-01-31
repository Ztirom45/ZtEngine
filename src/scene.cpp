/*
Scene libery from Ztirom45's ZtEngine

TIP: If you want to know more about the functions take a look into the header
*/

#include <shader/shader.hpp>

Scene::Scene(Shader* ptrShader,Player* ptrPlayer) {
	this->ptrTextures = new Textures;
	this->ptrShader = ptrShader;
	this->ptrPlayer = ptrPlayer;
}

Scene::~Scene(){
	delete this->ptrWorld;
	delete this->ptrTextures;
}

void Scene::init(){
	this->ptrTextures->load_GL_textures();	
	this->ptrWorld = new World(this->ptrTextures->textures[std::string("img/tiles32.png")],this);
	std::cout << "img/tiles32.png: " << this->ptrTextures->textures[std::string("img/tiles32.png")] << "\n";
	this->ptrWorld->init();
	//init player
	float W = 20;
	float H = 14;

	std::vector<RectF> texRects = {
		(RectF){0.0f,0.0f,0.5f,10.0f/H},
		(RectF){0.5f,0.0f,0.5f,10.0f/H},
		(RectF){0.0f,10.0f/H,8.0f/W,4.0f/H},
		(RectF){8.0f/W,10.0f/H,4.0f/W,4.0f/H},
		(RectF){12.0f/W,10.0f/H,3.0f/W,3.0f/H},
	};
	
	this->ptrPlayer->init_model(this->ptrShader,this->ptrTextures->textures[std::string("img/Alien.png")]);
	
	//head
	this->ptrPlayer->ptrPlayerMesh->add_cube({-0.25,0.4,-0.25},
			{	texRects[0],
				texRects[0],
				texRects[0],
				texRects[1],
				texRects[0],
				texRects[0],

			},{1,1,1,1,1,1},0.5);
		
	//body
	this->ptrPlayer->ptrPlayerMesh->add_cube({-0.2,0.2,-0.1},
			{	texRects[2],
				texRects[2],
				texRects[3],
				texRects[2],
				texRects[2],
				texRects[3],

			},{1,1,1,1,1,1},0.2,{2.0f,1.0f,1.0f});
		
	//left hand
	this->ptrPlayer->ptrPlayerMesh->add_cube({-0.35,0.15,0},
			{	texRects[4],
				texRects[4],
				texRects[4],
				texRects[4],
				texRects[4],
				texRects[4],

			},{1,1,1,1,1,1},0.15);
		
	//right Hand
	this->ptrPlayer->ptrPlayerMesh->add_cube({0.2,0.15,0},
			{	texRects[4],
				texRects[4],
				texRects[4],
				texRects[4],
				texRects[4],
				texRects[4],

			},{1,1,1,1,1,1},0.15);
			
	//left foot
	this->ptrPlayer->ptrPlayerMesh->add_cube({-0.25,0,-0.05},
			{	texRects[3],
				texRects[3],
				texRects[3],
				texRects[3],
				texRects[3],
				texRects[3],

			},{1,1,1,1,1,1},0.2);
		
	//right foot
	this->ptrPlayer->ptrPlayerMesh->add_cube({0.05,0,-0.05},
			{	texRects[3],
				texRects[3],
				texRects[3],
				texRects[3],
				texRects[3],
				texRects[3],

			},{1,1,1,1,1,1},0.2);
		this->ptrPlayer->update_model();

};
void Scene::update(){
	this->ptrWorld->update();
	this->ptrPlayer->update_mesh_arguments();
};

void Scene::draw(){
	this->ptrWorld->draw();
	this->ptrPlayer->ptrPlayerMesh->draw();
}

