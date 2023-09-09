/*
Ztirom's ZtEngine texture liberry header

TIP:
If you want to use a global config file for camera consts define `TEXTURE_IN_GLOBAL_CONFIG`

*/

#pragma once

#ifndef TEXTURE_IN_GLOBAL_CONFIG
	#define TEXTURE_IN_LOCAL_CONFIG

	//grid texture map
	#define ImgTileW 7
	#define ImgTileH 1
#endif

class Textures{
	public:
		std::map<std::string, GLuint> textures;
		
		//clean up
		~Textures();

		//load open gl texture pointers into this->textures
		void load_GL_textures();

};


/*
a function for claculating a rect in a grid texture map
IMPORTENT: supports only rows at the time TODO

uses macros: ImgTileW
*/
#define get_texture_quad(index) (RectF){\
	((float)1/ImgTileW)*index,\
	0,\
	(float)1/ImgTileW,\
	1/ImgTileH\
}

