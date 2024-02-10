/*
hitbox library from Ztirom45's ZtEngine

TIP: If you want to know more about the functions take a look into the header
*/

#include "types.hpp"
#include <cstdio>
#include <glm/fwd.hpp>
#include <hitbox.hpp>

Hitbox::Hitbox(){
}

void Hitbox::init(Mesh *ptrMesh,Scene* ptrScene){
	this->update_mesh(ptrMesh);
	
	this->ptrDebugMesh = new Mesh(ptrScene->ptrShader,0,
			glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f));
	this->ptrDebugMesh->setup_mesh();
}

void Hitbox::update_mesh(Mesh* ptrMesh){
	int vertex_pos_size = ptrMesh->vertex_pos.size(); 
	if(vertex_pos_size==0){
		this->box = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
		return;
	}
	this->box.x = ptrMesh->vertex_pos[0];
	this->box.y = ptrMesh->vertex_pos[1];
	this->box.z = ptrMesh->vertex_pos[2];
	this->box.w = ptrMesh->vertex_pos[0];
	this->box.h = ptrMesh->vertex_pos[1];
	this->box.d = ptrMesh->vertex_pos[2];
	for(int i=0;i<vertex_pos_size/3;i++){
		if(this->box.x>ptrMesh->vertex_pos[3*i+0]){
			this->box.x=ptrMesh->vertex_pos[3*i+0];}
		if(this->box.y>ptrMesh->vertex_pos[3*i+1]){
			this->box.y=ptrMesh->vertex_pos[3*i+1];}
		if(this->box.z>ptrMesh->vertex_pos[3*i+2]){
			this->box.z=ptrMesh->vertex_pos[3*i+2];}
		if(this->box.w<ptrMesh->vertex_pos[3*i+0]){
			this->box.w=ptrMesh->vertex_pos[3*i+0];}
		if(this->box.h<ptrMesh->vertex_pos[3*i+1]){
			this->box.h=ptrMesh->vertex_pos[3*i+1];}
		if(this->box.d<ptrMesh->vertex_pos[3*i+2]){
			this->box.d=ptrMesh->vertex_pos[3*i+2];}
	}
	this->ptrDebugMesh->add_cube(glm::vec3(this->box.x,this->box.y,this->box.z),{
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20}},
			{1,1,1,1,1,1},1,glm::vec3(box.w,box.h,box.d));

	/*
	this->ptrDebugMesh->add_cube(glm::vec3(box.x,box.y,box.z),{
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20},
			(RectF){0.0f,0.0f,0.5f,10.0f/20}
		},{1,1,1,1,1,1},1.0f,{box.w,box.h,box.d});*/
	this->ptrDebugMesh->update_mesh();
	this->ptrDebugMesh->m_model = ptrMesh->m_model;
}

//TODO own position + rotation
bool Hitbox::colide_no_rotpos(glm::vec3 pos){
	return  pos.x>this->box.x&&pos.x<this->box.w&&
		pos.y>this->box.y&&pos.y<this->box.h&&
		pos.z>this->box.z&&pos.z<this->box.d;
}

bool Hitbox::colide_no_rotpos(Hitbox ptrHitbox2){
	return	ptrHitbox2.box.w>this->box.x&&ptrHitbox2.box.x<this->box.w&&
		ptrHitbox2.box.h>this->box.y&&ptrHitbox2.box.y<this->box.h&&
		ptrHitbox2.box.d>this->box.z&&ptrHitbox2.box.z<this->box.d;

}

bool Hitbox::colide(glm::vec3 pos){
	return false;
}

bool Hitbox::colide(Hitbox box){
	return false;
}

bool Hitbox::colide(World* ptrWorld){
	for(int x=(int)this->box.x;x<=(int)this->box.w;x++){
		for(int z=(int)this->box.z;z<=(int)this->box.d;z++){
			printf("Debug:%d %d\n",x,z);
		}
	}
	return false;
}
