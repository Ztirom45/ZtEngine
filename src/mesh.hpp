/*
Ztirom's ZtEngine mesh libery header



*/
#pragma once

#include <textures.hpp>
class Mesh{
	public:
		//position and rotation
		glm::vec3 model_pos;
		glm::vec3 model_rot;
		glm::mat4 m_model;
		
		//VAO (vertex array object)
		GLuint VertexArrayObject;

		//VBO (vertex buffer object)
		GLuint VertexBufferObject;//positions
		GLuint VertexBufferObject2;//colors
		GLuint VertexBufferObject3;//textures
		
		std::vector<GLfloat> vertex_pos = {};
		std::vector<GLfloat> vertex_col = {};
		std::vector<GLfloat> vertex_tex = {};
		
		//texture map
		GLuint texture_id;
		
		//Shader pointer
		Shader *ptrShader;
		
		//sahder texture position rotation
		Mesh(Shader*,GLuint,glm::vec3,glm::vec3);
		
		//updates the model matrix using model_rot and model_pos,
		//so that the shader can position and rotate the mesh currectly
		void update_model_matrix();

		/*
		add a a point to the mesh params: position, col, texture, 
		position/resize:
			if position == -1 the function autoresizes 
			else the position must be given in position
		*/
		void add_point(glm::vec3,glm::vec3,glm::vec2,int);	

		/*
		add a rectangle to the mesh
		params:
			postion (rect{x,y,w,h})
			depth: other coord for example z if the direction xy
			texture coords on the texture map (rect{x,y,w,h})
			position (see add point position)
		directions 1: xy 2: xz 3: yz
		*/
		void add_rect(RectF,float,int,RectF,int);	
		
		/*
		add a cube to the mesh
		vec6 page scheme: Buttom,Down,Left,Front,Top,Right
		params:
			position,
			int texture type using get_texture_quad from <textures.hpp>,
			enabled pages, so that you can draw a cube without for example a front page

		*/
		void add_cube(glm::vec3,vec6i,vec6b);
		
		/*
		add a cube to the mesh
		vec6 page scheme: Buttom,Down,Left,Front,Top,Right
		params:
			position,
			rects of the texture_map for every page (vector<rectF>)	
			enabled pages, so that you can draw a cube without for example a front page,
			cube_size to manipulate the width height and depht of the cube at the same time
		*/
		void add_cube(glm::vec3,std::vector<RectF>,vec6b,float);
		
		/*
		add a cube to the mesh
		vec6 page scheme: Buttom,Down,Left,Front,Top,Right
		params:
			position,
			rects of the texture_map for every page (vector<rectF>)	
			enabled pages, so that you can draw a cube without for example a front page,
			scale to manipulate the width height and depht of the cube appart from eatch other
		*/
		void add_cube(glm::vec3,std::vector<RectF>,vec6b,float,glm::vec3);	
		
		//resets every float in the arrays with 0 (could be used for debug perposes)
		void clear();		

		
		//initizlize VBOs and VAO after the initilization of OpenGL
		void setup_mesh();
				
		//update the VAO to the VRAM
		void update_mesh();
	
		//draw the mesh
		void draw();
	
};
