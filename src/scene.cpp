/*
Scene libery from Ztirom45's ZtEngine

TIP: If you want to know more about the functions take a look into the header
*/

#include <config.hpp>

#include <camera/Player.hpp>
#include <shader/shader.hpp>
#include <textures.hpp>
#include <mesh.hpp>
#include <chunks/world.hpp>
#include <chunks/chunk.hpp> 

#include <scene.hpp>

Scene::Scene(Shader* ptrShader,Player* ptrPlayer) {
	this->ptrTextures = new Textures;
	this->ptrShader = ptrShader;
	this->ptrPlayer = ptrPlayer;
	this->ptrWorld = new World(this->ptrTextures->textures[std::string("img/tiles32.png")],this);
}

Scene::~Scene(){
	delete this->ptrWorld;
	delete this->ptrTextures;
}

void Scene::init(){
	this->ptrTextures->load_GL_textures();	
	this->ptrWorld->init();


};
void Scene::update(){
	this->ptrWorld->update();
};

void Scene::draw(){
	this->ptrWorld->draw();
}

