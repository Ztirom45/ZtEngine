/*
Ztirom's EngineArt hitbox liberry

*/
#pragma once
#include <config.hpp>

class Hitbox{
	public:
		/*
		  Importend: w,h,d are coordinates
				not relative to x,y,z
		*/
		CubeF box = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
		Hitbox();
		
		/*
		initilize after shader and open Gl stuf

		*/
		void init(Mesh* ptrMesh);

		/*
		 update Mesh
		*/

		void update_mesh(Mesh* ptrMesh);

		/*
		colide with:
			- vec3
			- Hitbox
			- world
		*/
		bool colide(glm::vec3 pos);
};
