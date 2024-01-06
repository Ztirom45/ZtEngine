/*
Shader liberry from Ztirom45's ZtEngine

Tip:
take a look into shaders.hpp if you want to know more abbout the functions

*/

#include <config.hpp>
#include <camera/Player.hpp>
#include <shader/shader.hpp>

Shader::Shader(Camera* ptrCamera){
	this->ptr_m_view = &ptrCamera->m_view;
	this->ptr_m_proj = &ptrCamera->m_proj;

	this->load_fs_file("src/shader/shader.frag");
	this->load_vs_file("src/shader/shader.vert");
};

Shader::Shader(Player* ptrPlayer){
	this->ptr_m_view = &ptrPlayer->m_view;
	this->ptr_m_proj = &ptrPlayer->m_proj;
	
	this->load_fs_file("src/shader/shader.frag");
	this->load_vs_file("src/shader/shader.vert");
};
		
		
void Shader::load_vs_file(std::string path){
	std::ifstream myfile(path);
	std::string line;
	vs_data = "";
	if (myfile.is_open()){
		while(getline(myfile,line)){
			vs_data.append(line);
			vs_data.append("\n");
		}
	}else{
		std::cout << "couldn't open vertex shader\n";
	}
	myfile.close();
};

void Shader::load_fs_file(std::string path){
	std::ifstream myfile(path);
	std::string line;
	fs_data = "";
	if (myfile.is_open()){
		while(getline(myfile,line)){
			fs_data.append(line);
			fs_data.append("\n");
		}
	}else{
		std::cout << "couldn't open fragment shader\n";
	}
	myfile.close();
};

GLuint Shader::CompileShader(GLuint type, const std::string& code){
	GLuint shaderObject;
	
	shaderObject = glCreateShader(type);
	
	const char* c_code = code.c_str();
	glShaderSource(shaderObject,1,&c_code, nullptr);
	glCompileShader(shaderObject);
	
	//error messages
	GLint success;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		GLint info_log_length;
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &info_log_length);
		
		std::cout <<"log len:"<< info_log_length<< "\n";
		
		size_t log_len_size = info_log_length;
		GLchar* info_log;
		info_log = (GLchar*)malloc(log_len_size);
		glGetShaderInfoLog(shaderObject, info_log_length, NULL, info_log);

		printf("failed to compile shader:\n%s\n", info_log);
		free(info_log);
	}else{
		std::cout << "copilation succes\n";
	}

	return shaderObject;
};

void Shader::CreateShader(){
	ShaderProgramm = glCreateProgram();
	
	GLuint VetexShader = CompileShader(GL_VERTEX_SHADER,vs_data);
	GLuint FragmentShader = CompileShader(GL_FRAGMENT_SHADER,fs_data);
	
	glAttachShader(ShaderProgramm,VetexShader);
	glAttachShader(ShaderProgramm,FragmentShader);
	glLinkProgram(ShaderProgramm);
	
	//validate our program
	glValidateProgram(ShaderProgramm);
	//glDetachShader, glDetachShader
};


void Shader::update_uniforms(glm::mat4 m_model,GLuint texture_id){
	//update view using the matrix of the camera
	
	GLint ViewLocation = glGetUniformLocation(this->ShaderProgramm,"m_view");
	if(ViewLocation>=0){
		glUniformMatrix4fv(ViewLocation,1,GL_FALSE,&(*this->ptr_m_view)[0][0]);
	}else{
		std::cout << "error: couldn't find view uniform\n";
		//exit(EXIT_FAILURE);
	}
	
	//update perspevtiv using the matrix of the camera
	
	GLint ProjectionLocation = glGetUniformLocation(this->ShaderProgramm,"m_proj");
	
	if(ProjectionLocation>=0){
		glUniformMatrix4fv(ProjectionLocation,1,GL_FALSE,&(*this->ptr_m_proj)[0][0]);
	}else{
		std::cout << "error: couldn't find perspective\n";
		//exit(EXIT_FAILURE);
	}
	
	//update Models pos using the input of the function
	GLint ModelLocation = glGetUniformLocation(this->ShaderProgramm,"m_model");
	
	if(ModelLocation>=0){
		glUniformMatrix4fv(ModelLocation,1,GL_FALSE,&m_model[0][0]);
	}else{
		std::cout << "error: couldn't find rotation\n";
		exit(EXIT_FAILURE);
	}
	
	//Update Texure
	glEnable(GL_TEXTURE_2D);
	GLint TextureLocation = glGetUniformLocation(this->ShaderProgramm, "Texture");
;	
	if(TextureLocation>=0){
		//std::cout << "tex_id: "<< texture_id << "\n";
		glActiveTexture(GL_TEXTURE0+0);//texture at position texture_id
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glUniform1i(TextureLocation,0);//texture from position texture_id
	}else{
		std::cout << "error: couldn't find Texture\n";
		//exit(EXIT_FAILURE);
	}
	//glDisable(GL_TEXTURE_2D);
}
