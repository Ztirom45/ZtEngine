#include "types.hpp"
#include <cstdio>
#include <hitbox.hpp>

Hitbox::Hitbox(){
}

void Hitbox::init(Mesh *ptrMesh){
	this->update_mesh(ptrMesh);
}

void Hitbox::update_mesh(Mesh* ptrMesh){
	int vertex_pos_size = ptrMesh->vertex_pos.size(); 
	if(vertex_pos_size==0){
		this->box = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
		return;
	}
	box.x = ptrMesh->vertex_pos[0];
	box.y = ptrMesh->vertex_pos[1];
	box.z = ptrMesh->vertex_pos[2];
	box.w = ptrMesh->vertex_pos[0];
	box.h = ptrMesh->vertex_pos[1];
	box.d = ptrMesh->vertex_pos[2];
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
	printf("end\n");	
}

bool Hitbox::colide(glm::vec3 pos){
	return  pos.x>this->box.x&&pos.x<this->box.w&&
		pos.y>this->box.y&&pos.y<this->box.h&&
		pos.z>this->box.z&&pos.z<this->box.d;
}
