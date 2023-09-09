/*
Camera libery header from Ztirom's ZtEngine

TIP:
If you want to use a global config file for camera consts define `CAMERA_IN_GLOBAL_CONFIG`

IMPORTEND:
You need to define or replayce Win_W Win_H with your window resulution
*/


#pragma once

#ifndef CAMERA_IN_GLOBAL_CONFIG
	#define CAMERA_IN_LOCAL_CONFIG
	
	#define ASPECT_RATIO (float)Win_W/Win_H
	//verticalFOV
	#define FOV_DEG 50.0f
	#define V_FOV glm::radians(FOV_DEG) 
	//calculate horizontal FOV with aspectratio
	#define H_FOV 2 * atan(tan(V_FOV*0.5)*ASPECT_RATIO)

	#define NEAR 0.1f
	#define FAR 2000.0f
	
	#define PITCH_MAX glm::radians(89.0f)
#endif

class Camera{
	public:
		glm::vec3 position;
		//angles
		float yaw;
		float pitch;
	
		//vectors
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 forward;
		
		glm::mat4 m_proj;
		glm::mat4 m_view;
		
		//constructor args: pos yaw roll
		Camera(glm::vec3,float,float);
		
		
		//update function
		void update_camera();	

		//update the viev matrix, so that the shader can use it
		void update_view_matrix();

		//update up right and forward vector in the current rotation
		void update_vectors();

		//update pitch angle
		void rotate_pitch(float);

		//update yaw angle
		void rotate_yaw(float);

		/*
			move_ left right up down forward back
			args: velocity
		
		*/
		void move_left(float);
		void move_right(float);
		void move_up(float);	
		void move_down(float);
		void move_forward(float);
		void move_back(float);    
};
