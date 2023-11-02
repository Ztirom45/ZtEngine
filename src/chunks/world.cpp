/*
voxel World libery from Ztirom's ZtEngine

TIP:
Take a look into world.hpp if you want to know more abbout the functions
*/

#include <config.hpp>
#include <camera/Player.hpp>
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
		this->chunks[i] = new Chunk(glm::ivec3(chunkx,0.0f,chunkz),this);

	}
	this->isInit = true;
}

void World::init(){
	//init all element in chunks
	for(int i=0;i<WORLD_AREA;i++){
		this->chunks[i]->init_mesh();
		this->chunks[i]->build_voxels();
	}
	//build mesh must happen after building chunks!!!
	for(int i=0;i<WORLD_AREA;i++){
		this->chunks[i]->build_mesh();
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

	printf("(%d %d)  (%f %f)\n",playerChunkPos.x,playerChunkPos.y,
		this->ptrPlayer->position.x,this->ptrPlayer->position.z);


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
			this->moveChunkPos(moveDirection);
		}
	}
	
};

void World::moveChunkPos(glm::ivec2 moveDirection){
	//TODO copiing memory corectly
	//array that will be copied into chunks after moving and index changing
	
	Chunk *chunks_copy[WORLD_AREA];

	for(int i=0;i<WORLD_AREA;i++){
		int chunkz = (i/WORLD_SIZE);
		int chunkx = (i-chunkz*WORLD_SIZE);
		
		//old positioon of the data for this chunk
		int old_chunk_x_index = chunkx+moveDirection.x;
		//std::cout << chunkx << " " << old_chunk_x_index << "\n";
		int old_chunk_z_index = chunkz+moveDirection.y;
		
		int old_chunk_index = old_chunk_x_index+old_chunk_z_index*WORLD_SIZE;
		
		chunkz+=this->playerChunkPos.y-WORLD_SIZE_OFFSET;
		chunkx+=this->playerChunkPos.x-WORLD_SIZE_OFFSET;
		
		
		
		std::cout << i << " " << old_chunk_index << "\n";
		if(0 <= old_chunk_x_index && old_chunk_x_index < WORLD_SIZE &&
		   0 <= old_chunk_z_index && old_chunk_z_index < WORLD_SIZE){
			chunks_copy[i] = this->chunks[old_chunk_x_index+old_chunk_z_index*WORLD_SIZE]
			;	
		}else{
			old_chunk_x_index -= WORLD_SIZE*moveDirection.x;
			old_chunk_z_index -= WORLD_SIZE*moveDirection.y;
			chunks_copy[i] = this->chunks[old_chunk_x_index+old_chunk_z_index*WORLD_SIZE];
			chunks_copy[i]->position = glm::ivec3(chunkx*CHUNK_SIZE,0,chunkz*CHUNK_SIZE);
			chunks_copy[i]->build_voxels();


		}

	}
	
	//update all chunks
	for(int i=0;i<WORLD_AREA;i++){
		this->chunks[i] = chunks_copy[i];
		this->chunks[i]->build_mesh();
		
	}	
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
