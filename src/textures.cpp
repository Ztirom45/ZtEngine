/*
Ztirom's ZtEngine texture libery

TIP:
take a look into textures.hpp if you want know more about the functions 
*/
#include <config.hpp>

#include <textures.hpp>

Textures::~Textures(){
	for (const auto &texture : this->textures) {
		std::cout << "cleaned up: " << texture.first << " with value: " << texture.second << '\n';
		glDeleteTextures(1,&texture.second);
	}
}


void Textures::load_GL_textures(){
	if (DIR *dir = opendir("img")) {
		while (dirent *f = readdir(dir)) {
			if (!f || f->d_name[0] == '.')
				continue; // skip hidden files
			
			//load SDL surface
			char str[64] = "img/";
			strcat(str, f->d_name);
			SDL_Surface* surface	= IMG_Load(str);
			
			//glut image
			glGenTextures(1, &(this->textures)[str]);
			glBindTexture(GL_TEXTURE_2D, this->textures[str]);
			
			//texture settings: cord up to 0 and 1
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
			//texture settings: scale filter
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			
			//generate image
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,surface->w,surface->h,0,GL_RGBA,GL_UNSIGNED_BYTE,surface->pixels);
			
			//clear surface
			SDL_FreeSurface(surface);

			printf("%s: %d\n",str,this->textures[str]);
		}
		closedir(dir);
	}else{//error if directory doens't exist
		printf("error: couldn't find diretory `img`");
	}
};
