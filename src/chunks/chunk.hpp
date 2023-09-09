/*
voxel Chunk libery from Ztirom's ZtEngine 

config in chunk_build_helper

*/

#pragma once


#include <chunks/chunk_build_helper.hpp>

class Chunk{
	public:
		glm::vec3 position;//position of chunk in the world
		Uint8 data[CHUNK_VOL] = {0};
		int** ptrAllChunkData = new int*[WORLD_AREA];
		bool is_zero = true;
		World* ptrWorld;
		Mesh *ptrChunkMesh;
		
		
		Chunk(glm::vec3,World*);
		
		//init function needs to be called after initialising OpenGL
		void init();

		//update chunk
		void update();

		//fill chunk with type void(0)
		void clear();
		
		
		//add cubes to mesh using this->data
		void build_mesh();
	
		//draw mesh of chunk
		void draw();

		//write data of voxel positions into data
		void build_voxels();		

		//clean up all pointers
		~Chunk();
};
