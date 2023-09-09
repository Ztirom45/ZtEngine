/*
Ztirom's ZtEngine mesh libery


TIP: if you want to know more abbout the functions,you can take a look int mesh.hpp
*/

#include <config.hpp>
#include <camera/FirstPersonPlayer.hpp>
#include <shader/shader.hpp>
#include <mesh.hpp>

Mesh::Mesh(Shader *ptrShader,GLuint texture_id,glm::vec3 model_pos,glm::vec3 model_rot){
	this->ptrShader = ptrShader;
	this->texture_id = texture_id;
	
	this->model_pos = model_pos;
	this->model_rot = model_rot;
	this->update_model_matrix();
}

void Mesh::update_model_matrix(){
	this->m_model = glm::translate(glm::mat4(1.0f),this->model_pos);
	this->m_model = glm::rotate(m_model,glm::radians(this->model_rot.x),{1,0,0});
	this->m_model = glm::rotate(m_model,glm::radians(this->model_rot.y),{0,1,0});
	this->m_model = glm::rotate(m_model,glm::radians(this->model_rot.z),{0,0,1});
}

void Mesh::add_point(glm::vec3 pos,glm::vec3 col,glm::vec2 tex,int position){//if posion == 0 resize else add to position
	//resize and get loacation
	
	if(position==-1){//save performence if a rect resizes only one time
		int last_size = vertex_pos.size()/3;
		this->vertex_pos.resize((last_size+1)*3);
		this->vertex_col.resize((last_size+1)*3);
		this->vertex_tex.resize((last_size+1)*2);
		position = last_size;
	}
	//add position
	this->vertex_pos[position*3+0] = pos.x;
	this->vertex_pos[position*3+1] = pos.y;
	this->vertex_pos[position*3+2] = pos.z;
	//add color
	this->vertex_col[position*3+0] = col.x;
	this->vertex_col[position*3+1] = col.y;
	this->vertex_col[position*3+2] = col.z;
	//add texture
	this->vertex_tex[position*2+0] = tex.x;
	this->vertex_tex[position*2+1] = tex.y;
};

//directions 1: xy 2: xz 3: yz
void Mesh::add_rect(RectF pos,float depth,int direction,RectF tex,int position){
		
	//resize vertex arrays
	int rect_last_size = position;
	if(position == -1){
		rect_last_size = vertex_pos.size()/3;
		this->vertex_pos.resize((rect_last_size+6)*3);
		this->vertex_col.resize((rect_last_size+6)*3);
		this->vertex_tex.resize((rect_last_size+6)*2);
	}
	
	//add vertex
	if(direction == 1){

			
			this->add_point({pos.x		,pos.y,			depth},{1,1,1},{tex.x,		tex.y		},rect_last_size+0);
			this->add_point({pos.x		,pos.y+pos.h,	depth},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+1);
			this->add_point({pos.x+pos.w	,pos.y,			depth},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+2);
			
			this->add_point({pos.x+pos.w	,pos.y+pos.h,	depth},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},rect_last_size+3);
			this->add_point({pos.x		,pos.y+pos.h,	depth},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+4);
			this->add_point({pos.x+pos.w	,pos.y,			depth},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+5);
			
	}else if(direction==2){//xz
			this->add_point({pos.x		,depth,	pos.y,			},{1,1,1},{tex.x,		tex.y		},rect_last_size+0);
			this->add_point({pos.x		,depth,	pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+1);
			this->add_point({pos.x+pos.w	,depth,	pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+2);
			
			this->add_point({pos.x		,depth,	pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+3);
			this->add_point({pos.x+pos.w	,depth,	pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+4);
			this->add_point({pos.x+pos.w	,depth,	pos.y+pos.h,	},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},rect_last_size+5);
	}else if(direction == 3){//yz
			this->add_point({depth,	pos.x+pos.w	,pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+0);
			this->add_point({depth,	pos.x		,pos.y,			},{1,1,1},{tex.x,		tex.y		},rect_last_size+1);
			this->add_point({depth,	pos.x		,pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+2);
			
			this->add_point({depth,	pos.x+pos.w	,pos.y+pos.h,	},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},rect_last_size+3);
			this->add_point({depth,	pos.x		,pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+4);
			this->add_point({depth,	pos.x+pos.w	,pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+5);
	}
};

//pages: Buttom,Down,Left,Front,Top,Right
void Mesh::add_cube(glm::vec3 pos,vec6i page_texture,vec6b enabled_pages){
	
	//resize
	int quad_last_size = vertex_pos.size()/3;
	//number of quads to draw
	int quads_num =	 (int)enabled_pages.v1
					+(int)enabled_pages.v2
					+(int)enabled_pages.v3
					+(int)enabled_pages.v4
					+(int)enabled_pages.v5
					+(int)enabled_pages.v6;
	
	//6pages  6points per page 3 codinates per point
	this->vertex_pos.resize((quad_last_size+6*quads_num)*3);
	this->vertex_col.resize((quad_last_size+6*quads_num)*3);
	this->vertex_tex.resize((quad_last_size+6*quads_num)*2);
	
	//counts every page, so that the gap will be leaved out
	int page_counter = 0;
	
	if(enabled_pages.v1){
		this->add_rect({pos.x,pos.y,1,1},pos.z,1,get_texture_quad(page_texture.v1),quad_last_size);
		page_counter++;
	}
	if(enabled_pages.v2){
		this->add_rect({pos.x,pos.z,1,1},pos.y,2,get_texture_quad(page_texture.v2),quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v3){
		this->add_rect({pos.y,pos.z,1,1},pos.x,3,get_texture_quad(page_texture.v3),quad_last_size+6*page_counter);
		page_counter++;
	}
	
	if(enabled_pages.v4){
		this->add_rect({pos.x,pos.y,1,1},pos.z+1,1,get_texture_quad(page_texture.v4),quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v5){
		this->add_rect({pos.x,pos.z,1,1},pos.y+1,2,get_texture_quad(page_texture.v5),quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v6){
		this->add_rect({pos.y,pos.z,1,1},pos.x+1,3,get_texture_quad(page_texture.v6),quad_last_size+6*page_counter);
		page_counter++;
	}
	
};

void Mesh::add_cube(glm::vec3 pos,std::vector<RectF> page_texture,vec6b enabled_pages,float cube_size){
	//resize
	int quad_last_size = vertex_pos.size()/3;
	//number of quads to draw
	int quads_num =	 (int)enabled_pages.v1
					+(int)enabled_pages.v2
					+(int)enabled_pages.v3
					+(int)enabled_pages.v4
					+(int)enabled_pages.v5
					+(int)enabled_pages.v6;
	
	//6pages  6points per page 3 codinates per point
	this->vertex_pos.resize((quad_last_size+6*quads_num)*3);
	this->vertex_col.resize((quad_last_size+6*quads_num)*3);
	this->vertex_tex.resize((quad_last_size+6*quads_num)*2);
	
	//counts every page, so that the gap will be leaved out
	int page_counter = 0;
	
	if(enabled_pages.v1){
		this->add_rect((RectF){pos.x,pos.y,cube_size,cube_size},pos.z,1,page_texture[0],quad_last_size);
		page_counter++;
	}
	if(enabled_pages.v2){
		this->add_rect((RectF){pos.x,pos.z,cube_size,cube_size},pos.y,2,page_texture[1],quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v3){
		this->add_rect((RectF){pos.y,pos.z,cube_size,cube_size},pos.x,3,page_texture[2],quad_last_size+6*page_counter);
		page_counter++;
	}
	
	if(enabled_pages.v4){
		this->add_rect((RectF){pos.x,pos.y,cube_size,cube_size},pos.z+cube_size,1,page_texture[3],quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v5){
		this->add_rect((RectF){pos.x,pos.z,cube_size,cube_size},pos.y+cube_size,2,page_texture[4],quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v6){
		this->add_rect((RectF){pos.y,pos.z,cube_size,cube_size},pos.x+cube_size,3,page_texture[5],quad_last_size+6*page_counter);
		page_counter++;
	}
	
};

void Mesh::add_cube(glm::vec3 pos,std::vector<RectF> page_texture,vec6b enabled_pages,float cube_size,glm::vec3 scale){
	
	//resize
	int quad_last_size = vertex_pos.size()/3;
	//number of quads to draw
	int quads_num =	 (int)enabled_pages.v1
					+(int)enabled_pages.v2
					+(int)enabled_pages.v3
					+(int)enabled_pages.v4
					+(int)enabled_pages.v5
					+(int)enabled_pages.v6;
	
	//6pages  6points per page 3 codinates per point
	this->vertex_pos.resize((quad_last_size+6*quads_num)*3);
	this->vertex_col.resize((quad_last_size+6*quads_num)*3);
	this->vertex_tex.resize((quad_last_size+6*quads_num)*2);
	
	//counts every page, so that the gap will be leaved out
	int page_counter = 0;
	
	if(enabled_pages.v1){
		this->add_rect((RectF){pos.x,pos.y,cube_size*scale.x,cube_size*scale.y},pos.z*scale.z,1,page_texture[0],quad_last_size);
		page_counter++;
	}
	if(enabled_pages.v2){
		this->add_rect((RectF){pos.x,pos.z,cube_size*scale.x,cube_size*scale.z},pos.y*scale.y,2,page_texture[1],quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v3){
		this->add_rect((RectF){pos.y,pos.z,cube_size*scale.y,cube_size*scale.z},pos.x,3,page_texture[2],quad_last_size+6*page_counter);
		page_counter++;
	}
	
	if(enabled_pages.v4){
		this->add_rect((RectF){pos.x,pos.y,cube_size*scale.x,cube_size*scale.y},pos.z+cube_size*scale.z,1,page_texture[3],quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v5){
		this->add_rect((RectF){pos.x,pos.z,cube_size*scale.x,cube_size*scale.z},pos.y+cube_size*scale.y,2,page_texture[4],quad_last_size+6*page_counter);
		page_counter++;
	}
	if(enabled_pages.v6){
		this->add_rect((RectF){pos.y,pos.z,cube_size*scale.y,cube_size*scale.z},pos.x+cube_size*scale.x,3,page_texture[5],quad_last_size+6*page_counter);
		page_counter++;
	}
};

void Mesh::clear(){
	
	for(long unsigned int i=0;i<vertex_pos.size()/3;i++){
		this->vertex_pos[i*3+0] = 0.0f;
		this->vertex_pos[i*3+1] = 0.0f;
		this->vertex_pos[i*3+2] = 0.0f;
		
		this->vertex_col[i*3+0] = 0.0f;
		this->vertex_col[i*3+1] = 0.0f;
		this->vertex_col[i*3+2] = 0.0f;
		
		this->vertex_tex[i*2+0] = 0.0f;
		this->vertex_tex[i*2+1] = 0.0f;
	}
	
	this->vertex_pos.resize(0);
	this->vertex_col.resize(0);
	this->vertex_tex.resize(0);
}

void Mesh::setup_mesh(){
	
	//genereate VAO
	glGenVertexArrays(1,&this->VertexArrayObject);
	glBindVertexArray(this->VertexArrayObject);

	//generate VBO
	glGenBuffers(1,&this->VertexBufferObject);
	glGenBuffers(1,&this->VertexBufferObject2);
	glGenBuffers(1,&this->VertexBufferObject3);
	
	//update vertex position VBO at 0

	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		this->vertex_pos.size()*sizeof(GLfloat),
		this->vertex_pos.data(),
		GL_DYNAMIC_DRAW);
	
	//linking up the vertex position VBO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(	0,
							3,//x,y,z
							GL_FLOAT,
							GL_FALSE,
							0,
							(void*)0
	);
		
	
	//generate vertex color VBO
	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject2);
	glBufferData(GL_ARRAY_BUFFER,
		this->vertex_col.size()*sizeof(GLfloat),
		this->vertex_col.data(),
		GL_DYNAMIC_DRAW);
	
	//linking up the vertex color VBO
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(	1,
							3,//r,g,b
							GL_FLOAT,//type
							GL_FALSE,//do something with values
							0,
							(void*)0//offset
	);
	
	
	//generate texture VBO
	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject3);
	glBufferData(GL_ARRAY_BUFFER,
		this->vertex_tex.size()*sizeof(GLfloat),
		this->vertex_tex.data(),
		GL_DYNAMIC_DRAW);
	
	//linking up the texture VBO
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(	2,//position
							2,//x,y
							GL_FLOAT,//type
							GL_FALSE,//do something with values
							0,
							(void*)0//offset
	);
	
	//unbind VAO
	
	glBindVertexArray(0);
	//disable attrib arrays
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	

}

void Mesh::update_mesh(){
	
	//bind VAO
	glBindVertexArray(this->VertexArrayObject);

	//update vertex position VBO
	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		this->vertex_pos.size()*sizeof(GLfloat),
		this->vertex_pos.data(),
		GL_DYNAMIC_DRAW);
	
	//linking up the vertex position VBO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(	0,
							3,//x,y,z
							GL_FLOAT,
							GL_FALSE,
							0,
							(void*)0
	);
		
	
	//update vertex color VBO
	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject2);
	glBufferData(GL_ARRAY_BUFFER,
		this->vertex_col.size()*sizeof(GLfloat),
		this->vertex_col.data(),
		GL_DYNAMIC_DRAW);
	
	//linking up the color array
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(	1,
							3,//r,g,b
							GL_FLOAT,//type
							GL_FALSE,//do something with values
							0,
							(void*)0//offset
	);
	
	
	//generate texture VBO
	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject3);
	glBufferData(GL_ARRAY_BUFFER,
		this->vertex_tex.size()*sizeof(GLfloat),
		this->vertex_tex.data(),
		GL_DYNAMIC_DRAW);
	
	//linking up the texture VBO
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(	2,//position
							2,//x,y
							GL_FLOAT,//type
							GL_FALSE,//do something with values
							0,
							(void*)0//offset
	);
	
	//unbind VAO
	glBindVertexArray(0);
	//disable attrib arrays
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	

}

void Mesh::draw(){
	//update uniforms
	ptrShader->update_uniforms(this->m_model,this->texture_id);
	
	//draw triangles
	glBindVertexArray(this->VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject2);
	glBindBuffer(GL_ARRAY_BUFFER,this->VertexBufferObject3);
	glDrawArrays(GL_TRIANGLES,0,this->vertex_pos.size()/3);
}


