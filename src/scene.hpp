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
		
		//draw debug stuff like hitboxes
		void draw_debug();

		//draw models and the whole scene
		void draw_scene();
		//draw function calls draw_debug and draw_scene
		//used in main
		void draw();
};
