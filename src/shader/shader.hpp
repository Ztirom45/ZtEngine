/*
Shader liberry header from Ztirom45 ZtEngine

*/

#pragma once


#include <config.hpp>

class Shader{
	public:
		
		//Program Object (for our shader)
		GLuint ShaderProgramm = 0;

		std::string fs_data;
		std::string vs_data;
		
		glm::mat4 *ptr_m_view;
		glm::mat4 *ptr_m_proj;
		
		Shader(Camera*);
		Shader(Player*);		
		
		//load vertex Shader Files arg: Filename
		void load_vs_file(std::string);

		//laod fragment shader File args: Filename
		void load_fs_file(std::string);	
		
		//compile shader code
		GLuint CompileShader(GLuint, const std::string&);
		
		//load and compile shader
		void CreateShader();
		
		//pass uniforms of the engine to the shader
		void update_uniforms(glm::mat4,GLuint);
};
