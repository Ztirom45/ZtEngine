/*
Scene liberry header from Ztrom45's ZtEngine

*/

#pragma once

//forward declaration of World, Shader and Texture
class World;
class Shader;
class Texture;
class FirstPersonPlayer;

class Scene{
	public:	
		Shader *ptrShader;	
		Textures *ptrTextures;
		FirstPersonPlayer *ptrPlayer;
		World* ptrWorld;

		Scene(Shader*,FirstPersonPlayer*);
		
		~Scene();

		//init the whole scene after initilizing openGL
		void init();
		
		//update the whole scene
		void update();
		
		//draw the whole scene
		void draw();
};
