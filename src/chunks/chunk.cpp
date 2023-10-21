/*
voxel Chunk libery from Ztirom's ZtEngine 

Important
config in chunk_build_helper

TIP:
Take a look into world.hpp if you want to know more abbout the functions
*/

#include <config.hpp>
#include <camera/FirstPersonPlayer.hpp>
#include <shader/shader.hpp>
#include <textures.hpp>
#include <mesh.hpp>
#include <chunks/world.hpp>
#include <chunks/chunk.hpp>
		
Chunk::Chunk(glm::ivec3 position_number,World* ptrWorld){
	this->ptrWorld = ptrWorld;
	this->position = glm::ivec3(
		position_number.x*CHUNK_SIZE,
		position_number.y*CHUNK_H,
		position_number.z*CHUNK_SIZE);
	
	this->ptrChunkMesh = new Mesh(
		this->ptrWorld->ptrShader,
		this->ptrWorld->TextureMap,
		position,
		glm::vec3(0.0f));

	
	
}

void Chunk::init_mesh(){
	this->ptrChunkMesh->setup_mesh();
};
void Chunk::clear(){
	for(int i=0;i<CHUNK_VOL;i++){
		this->data[i] = 0;
	}
};

void Chunk::build_mesh(){
	//update mesh pos
	this->ptrChunkMesh->model_pos = this->position;

	//clear old data
	this->ptrChunkMesh->clear();
	
	int global_x,global_y,global_z;

	//get chunk, witch the player is within
	glm::ivec2 PlayerChunkPos = this->ptrWorld->playerChunkPos;

	for(int x=0;x<CHUNK_SIZE;x++){for(int z=0;z<CHUNK_SIZE;z++){for(int y=0;y<CHUNK_H;y++){
		global_x = x+position.x;
		global_y = y+position.y;
		global_z = z+position.z;
		if(!is_block_void(global_x,global_y,global_z,this->ptrWorld,PlayerChunkPos)){
			this->ptrChunkMesh->add_cube(glm::vec3(x,y,z),
				get_block_faces(get_block_type(glm::vec3(x,y,z),&this->data)),
				//Buttom,Down,Left,Front,Top,Right
				(vec6b){
				is_block_void(global_x, global_y, global_z-1,this->ptrWorld,PlayerChunkPos),
				is_block_void(global_x, global_y-1, global_z,this->ptrWorld,PlayerChunkPos),
				is_block_void(global_x-1, global_y, global_z,this->ptrWorld,PlayerChunkPos),
				is_block_void(global_x, global_y, global_z+1,this->ptrWorld,PlayerChunkPos),
				is_block_void(global_x, global_y+1, global_z,this->ptrWorld,PlayerChunkPos),
				is_block_void(global_x+1, global_y, global_z,this->ptrWorld,PlayerChunkPos)
				});
				
		}
		
	}}}
	this->is_zero = !(bool)this->ptrChunkMesh->vertex_pos.size();
	if(!this->is_zero){
		this->ptrChunkMesh->update_mesh();
	}else{
		//allert if chunk is empty (shuoldn't happen)
		printf("empty chunk allert\n");
	}
};

void Chunk::draw(){
	if(!is_zero){
		this->ptrChunkMesh->draw();
	}
};

void Chunk::build_voxels(){
	for(int x=0;x<CHUNK_SIZE;x++){
		for(int z=0;z<CHUNK_SIZE;z++){
			for(int y=0;y<CHUNK_H;y++){
				//world pos of woxels 
				int wx = this->position.x+x;
				int wy = this->position.y+y;
				int wz = this->position.z+z;
				this->data[x+z*CHUNK_SIZE+y*CHUNK_AREA] = chunk_build_function(this->position,glm::vec3(x,y,z),glm::vec3(wx,wy,wz));

			}
		}
	}
};

Chunk::~Chunk(){
	delete this->ptrChunkMesh;
};

