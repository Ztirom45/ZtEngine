/*
voxel World libery from Ztirom's ZtEngine

TIP:
Take a look into world.hpp if you want to know more abbout the functions
*/

#include <config.hpp>
#include <camera/FirstPersonPlayer.hpp>
#include <shader/shader.hpp>
#include <textures.hpp>
#include <mesh.hpp>
#include <chunks/world.hpp>
#include <scene.hpp>

World::World(GLuint TextureMap,Scene *ptrScene){
	this->ptrShader = ptrScene->ptrShader;
	this->ptrPlayer = ptrScene->ptrPlayer;
	this->TextureMap = TextureMap;
	this->updatePlayerChunkPos();
	for(int i=0;i<WORLD_AREA;i++){
		int chunkz = (i/WORLD_SIZE);
		int chunkx = (i-chunkz*WORLD_SIZE);
		chunkz+=this->playerChunkPos.y-WORLD_SIZE_OFFSET;
		chunkx+=this->playerChunkPos.x-WORLD_SIZE_OFFSET;
		printf("chunkspos: %d %d\n",chunkx,chunkz);
		this->chunks[i] = new Chunk(glm::vec3((float)chunkx,0.0f,(float)chunkz),this);

	}
	this->isInit = true;
}

void World::init(){
	//init all element in chunks
	for(int i=0;i<WORLD_AREA;i++){
		this->chunks[i]->init();
	}
};

void World::updateChunks(){
	//update all chunks
	for(int i=0;i<WORLD_AREA;i++){
		this->chunks[i]->update();
	}
};

void World::updatePlayerChunkPos(){
	//old playerChunkPos
	glm::ivec2 oldPlayerChunkPos = this->playerChunkPos;
	

	//update playerChunkPos
	this->playerChunkPos.x = (int)(this->ptrPlayer->position.x/CHUNK_SIZE);
	this->playerChunkPos.y = (int)(this->ptrPlayer->position.z/CHUNK_SIZE);
	if(this->ptrPlayer->position.x<0){playerChunkPos.x-=1;}
	if(this->ptrPlayer->position.z<0){playerChunkPos.y-=1;}


	//move chunks
	if(this->isInit){
		bool moved = false;
		glm::ivec2 moveDirection = {0,0};//the direction to move the chunks
		if(playerChunkPos.x!=oldPlayerChunkPos.x){
			moved = true;
			moveDirection.x = playerChunkPos.x - oldPlayerChunkPos.x;
			printf("updated X\n");
		}
		if(playerChunkPos.y!=oldPlayerChunkPos.y){
			moved = true;
			moveDirection.y = playerChunkPos.y - oldPlayerChunkPos.y;
			printf("update Y\n");
		}
		if(moved){
			//this->moveChunkPos(moveDirection);
		}
	}
	
};

void World::moveChunkPos(glm::ivec2 moveDirection){
	for(int i=0;i<WORLD_SIZE;i++){
		this->chunks[i]->position.x+=moveDirection.x;
		this->chunks[i]->position.y+=moveDirection.y;
		//TODO recycle existing chunks
	}
	this->updateChunks();
};

void World::update(){
	this->updatePlayerChunkPos();
};

void World::draw(){
	//draw all chunks
	for(int i=0;i<WORLD_AREA;i++){
		this->chunks[i]->draw();
	}
};

World::~World(){
	//draw all chunks
	for(int i=0;i<WORLD_AREA;i++){
		delete this->chunks[i];
	}
}
