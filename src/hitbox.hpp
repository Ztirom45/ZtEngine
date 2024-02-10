/*
Ztirom's EngineArt hitbox liberry

WARNING: this hitbox lib is experimental and doesn't work right. Please dont use it, if you don't no what you doing!
*/
#pragma once
#include "scene.hpp"
#include <config.hpp>
#include <glm/fwd.hpp>

class Hitbox{
	public:
		/*
		  Importend: w,h,d are coordinates
				not relative to x,y,z
		*/
		CubeF box = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
		Mesh *ptrDebugMesh;
		Hitbox();
		
		/*
		initilize after shader and open Gl stuf

		*/
		void init(Mesh*,Scene*);

		/*
		 update Mesh
		*/

		void update_mesh(Mesh*);

		/*
		colide without model matrix manitpulation
		*/
		bool colide_no_rotpos(glm::vec3);
		bool colide_no_rotpos(Hitbox);
		
		bool colide(glm::vec3);
		bool colide(Hitbox);
		bool colide(World*);
};
