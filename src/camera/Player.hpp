/*
Player(Camera + Keybord control) libery from Ztirom's ZtEngine

*/

#pragma once

#include <camera/camera.hpp>
#include <config.hpp>

//forward declaraitions
class Mesh;
class Shader;

#define keysSIZE 1073742050

class Player: public Camera{
	private:
		bool keys[keysSIZE] = {0};
	public:
		//keybordstate array

		// a pointer to the condtion of the main loop,
		// so that the loop could be quit, if the exit event is triggert
		bool *loop;
		Shader *ptrShader;
		Mesh *ptrPlayerMesh;

		Player(glm::vec3,float,float,float,bool*);
	
		//initialization after constructor, so that the player and mesh can be initilized after openGL initizilizing
		void init_mesh(Shader*,GLuint);


		//set and get keys states funciton to reduce data coruption
		void set_key_state(int,bool);
		bool get_key_state(int);

		//translate STL_events into keys(the keyboard state array)
		void handle_events();
		
		//move the player using keys	
		void Move();

		//update fuction do not use update_camera if you want ot update the whole player
		void update_player();

		//updates the position of the mesh to player pos
		void update_mesh();
};
