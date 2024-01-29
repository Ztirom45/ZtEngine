#include <hitbox.hpp>

Hitbox::Hitbox(){

}

void Hitbox::init(Mesh *ptrMesh){
	this->update_mesh(ptrMesh);
}

void Hitbox::update_mesh(Mesh* ptrMesh){
	this->box = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	for(int i=0;i<ptrMesh->vertex_pos.size()/3;i++){
		if(this->box.x<ptrMesh->vertex_pos[3*i+0]){
			this->box.x=ptrMesh->vertex_pos[3*i+0];}
		if(this->box.y<ptrMesh->vertex_pos[3*i+1]){
			this->box.y=ptrMesh->vertex_pos[3*i+1];}
		if(this->box.z<ptrMesh->vertex_pos[3*i+2]){
			this->box.z=ptrMesh->vertex_pos[3*i+2];}
		if(this->box.x<ptrMesh->vertex_pos[3*i+0]){
			this->box.x=ptrMesh->vertex_pos[3*i+0];}
		if(this->box.y<ptrMesh->vertex_pos[3*i+1]){
			this->box.y=ptrMesh->vertex_pos[3*i+1];}
		if(this->box.z<ptrMesh->vertex_pos[3*i+2]){
			this->box.z=ptrMesh->vertex_pos[3*i+2];}
	}
}

bool Hitbox::colide(glm::vec3 pos){
	return  pos.x>this->box.x&&pos.x<this->box.w&&
		pos.y>this->box.y&&pos.y<this->box.h&&
		pos.z>this->box.z&&pos.z<this->box.d;
}
