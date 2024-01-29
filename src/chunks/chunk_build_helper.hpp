/*
Voxel Chunk build helper libery from Ztirom's ZtEngine 
 
TIP:
If you want to use a global config file for chunk consts define `CHUNK_IN_GLOBAL_CONFIG`

TIP:
If you want to use a global config file for World consts define `WORLD_IN_GLOBAL_CONFIG`


*/
#pragma once

#include <config.hpp>
class World;
class Chunk;

//consts
#ifndef CHUNK_IN_GLOBAL_CONFIG
	#define CHUNK_IN_LOCAL_CONFIG

	#define CHUNK_H (int)32
	#define CHUNK_SIZE 16
	#define CHUNK_VEC glm::vec3(CHUNK_SIZE,CHUNK_H,CHUNK_SIZE)
	#define CHUNK_AREA CHUNK_SIZE*CHUNK_SIZE
	#define CHUNK_VOL CHUNK_AREA*CHUNK_H
	
#endif

//consts
#ifndef WORLD_IN_GLOBAL_CONFIG
	#define WORLD_IN_LOCAL_CONFIG

	#define WORLD_SIZE 7
	#define WORLD_AREA WORLD_SIZE*WORLD_SIZE
	#define WORLD_SIZE_OFFSET (int)(WORLD_SIZE/2)
#endif

//function to cheack if the current block is type void (0)
//param: x,y,z ,chunkTODO:
bool is_block_void(int,int,int,World*,glm::vec2);


//funciton witch generate the chunks
Uint8 chunk_build_function(glm::vec3,glm::vec3,glm::vec3);


//function witch ask for the block type
//TODO:
Uint8 get_block_type(glm::vec3 pos,Uint8 (*data)[CHUNK_VOL]);


//function witch gets a blocktype and return the faces of te block
//TODO:
vec6i get_block_faces(Uint8);
