/*
voxel World libery from Ztirom's ZtEngine 

*/

#pragma once

//forward declerations:
class Scene;

#include "chunk.hpp"

class World{
	public:
		Chunk *chunks[WORLD_AREA];	
		Shader *ptrShader;
		GLuint TextureMap;
		//player pos stuff
		FirstPersonPlayer *ptrPlayer;
		glm::ivec2 playerChunkPos = {0,0};
		bool isInit = false;	
		
		World(GLuint,Scene*);
		
		~World();	

		//init after openGL intialisazion
		void init();
	
		//updates playerChunksPos if changed
		void updatePlayerChunkPos();
		
		//moves the position of every chunk
		void moveChunkPos(glm::ivec2);
		
		//update chunks
		void update();
		

		//draw chunks
		void draw();
		
};
