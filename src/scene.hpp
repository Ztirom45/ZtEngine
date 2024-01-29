/*
Scene liberry header from Ztrom45's ZtEngine

*/

#pragma once

#include <config.hpp>

class Scene{
	public:	
		Shader *ptrShader;	
		Textures *ptrTextures;
		Player *ptrPlayer;
		World* ptrWorld;

		Scene(Shader*,Player*);
		
		~Scene();

		//init the whole scene after initilizing openGL
		void init();
		
		//update the whole scene
		void update();
		
		//draw the whole scene
		void draw();
};
