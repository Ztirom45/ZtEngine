/*
Voxel Chunk build helper libery from Ztirom's ZtEngine 
 
Importend: take a look ino chunk_build_helper.hpp if you want to know more abbout the functions
*/
#include <config.hpp>
#include <camera/FirstPersonPlayer.hpp>
#include <shader/shader.hpp>
#include <textures.hpp>
#include <mesh.hpp>
#include <chunks/chunk.hpp>
#include <chunks/world.hpp>
#include <chunks/chunk_build_helper.hpp>

bool is_block_void(int global_x,int global_y,int global_z,World* ptrWorld,glm::vec2 player_pos){
	//calculates all nessesary position relations
	
	global_x = global_x-(player_pos.x-WORLD_SIZE_OFFSET)*CHUNK_SIZE;
	global_z = global_z-(player_pos.y-WORLD_SIZE_OFFSET)*CHUNK_SIZE;

	int chunk_x = global_x/CHUNK_SIZE;
	int chunk_z = global_z/CHUNK_SIZE;
	
	int local_x = global_x-(chunk_x*CHUNK_SIZE);
	int local_y = global_y;
	int local_z = global_z-(chunk_z*CHUNK_SIZE);

	glm::vec3 pos = glm::vec3(local_x,local_y,local_z);

	//cheacks if cube is in a chunk
	if(pos.x < 0 || pos.x >= CHUNK_SIZE || pos.y < 0 || pos.y >= CHUNK_H || pos.z < 0 || pos.z >= CHUNK_SIZE){
		return true;
	}

	//cheaks if index out of range (sholdn't happen)
	int chunk_index = (int)(pos.x+pos.z*CHUNK_SIZE+pos.y*CHUNK_AREA);
	if(chunk_index<0||chunk_index>=CHUNK_VOL){
		printf("Chunk index overflow in is void index:%d!!!\n",chunk_index);
		return true;
	}
	
	//cheaks if chunk is in the World
	
	if(chunk_x < 0 || chunk_x >= WORLD_SIZE ||
	chunk_z < 0 || chunk_z >= WORLD_SIZE){
		return true;
	}
	
	//cheaks if the chunkindex is out of range (shouldn't happen)	
	int world_index = chunk_x+chunk_z*WORLD_SIZE;//TODO
	if(world_index < 0 || world_index > WORLD_AREA){
		printf("Error world index out of range (index:%d)/n",world_index);
		return true;
	}
	
	Chunk *current_chunk = &(*(ptrWorld->chunks)[world_index]);
	Uint8 *data = current_chunk->data;
	return !(bool)*(data+chunk_index);
}

Uint8 chunk_build_function(glm::vec3 chunk_pos,glm::vec3 local_pos,glm::vec3 global_pos){
	return (Uint8)(glm::simplex(global_pos*0.1f)+1);
}

//TODO:
Uint8 get_block_type(glm::vec3 pos,Uint8 (*data)[CHUNK_VOL]){
	return ((*data)[(Uint8)(pos.x+pos.z*CHUNK_SIZE+pos.y*CHUNK_AREA)]);
}

//TODO:
vec6i get_block_faces(Uint8 block_type){
	return (vec6i){3,3,3,3,3,3};
}
