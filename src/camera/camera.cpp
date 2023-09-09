/*
Camera libery from Ztirom's ZtEngine

TIP:
If you want to know more abbout the functions or macros,
you can take a look into the header 
*/
#include <config.hpp>
#include <camera/camera.hpp>
Camera::Camera(glm::vec3 pos,float yaw,float pitch){	
	this->position = pos;
	this->yaw = yaw;
	this->pitch = pitch;
	
	this->up = glm::vec3(0.0f,1.0f,0.0f);
	this->right = glm::vec3(1.0f,0.0f,0.0f);
	this->forward = glm::vec3(-1.0f,0.0f,0.0f);
	
	this->m_proj = glm::perspective(V_FOV, ASPECT_RATIO, NEAR, FAR);
	this->m_view = glm::mat4();
	

	
};

void Camera::update_camera(){
	this->update_vectors();
	this->update_view_matrix();
};

void Camera::update_view_matrix(){
	this->m_view = glm::lookAt(this->position,this->position + this->forward,this->up);
};

void Camera::update_vectors(){
	this->forward.x = glm::cos(this->yaw)*glm::cos(this->pitch);
	this->forward.y = glm::sin(this->pitch);
	this->forward.z = glm::sin(this->yaw)*glm::cos(this->pitch);
	
	this->forward = glm::normalize(this->forward);
	this->right = glm::normalize(glm::cross(this->forward,glm::vec3(0,1,0)));
	this->up = glm::normalize(glm::cross(this->right,this->forward));

};

void Camera::rotate_pitch(float delta_y){
	this->pitch -= delta_y;
	this->pitch = glm::clamp(this->pitch,-PITCH_MAX,PITCH_MAX);
};

void Camera::rotate_yaw(float delta_x){
	this->yaw += delta_x;
};

void Camera::move_left(float velocity){
	this->position -= this->right * velocity;
};

void Camera::move_right(float velocity){
	this->position += this->right * velocity;
};

void Camera::move_up(float velocity){
	this->position += this->up * velocity;
};

void Camera::move_down(float velocity){
	this->position -= this->up * velocity;
};

void Camera::move_forward(float velocity){
	this->position += this->forward * velocity;
};

void Camera::move_back(float velocity){
	this->position -= this->forward * velocity;
};
