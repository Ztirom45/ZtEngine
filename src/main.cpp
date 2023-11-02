//compile: `$ make`

#include <config.hpp>


#include <camera/FirstPersonPlayer.hpp>
#include <shader/shader.hpp>
#include <textures.hpp>
#include <mesh.hpp>
#include <chunks/world.hpp>
#include <chunks/chunk.hpp>
#include <scene.hpp>



class App{
	public:
	
	//Win vars
	SDL_Window* screen;
	SDL_GLContext GLContext;
	
	bool loop = true;
	
	FirstPersonPlayer *ptrPlayer = new FirstPersonPlayer(glm::vec3(0.0f,32.0f,0.0f),4.0f,0.0f,0.0f,&loop);
	//it cant be bigger than 24bit in + and - becouase of glsl floats (could be buggi by to high numbers)
	Shader *ptrShader = new Shader(ptrPlayer);
	Scene *ptrScene = new Scene(this->ptrShader,this->ptrPlayer);

	void GetOpenGLVersionInfo(){
		std::cout << "Vendor:\t\t\t\t" << glGetString(GL_VENDOR) <<"\n";
		std::cout << "Renderer:\t\t\t" << glGetString(GL_RENDERER) <<"\n";
		std::cout << "Version:\t\t\t" << glGetString(GL_VERSION) <<"\n";
		std::cout << "Shading Language:\t\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) <<"\n";
		
		
		
	};

	void init(){
		//init stuff
		SDL_Init(SDL_INIT_VIDEO);

		//gl Atributs
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);//24bit DepthBuffer
		
		//create open gl window
		screen = SDL_CreateWindow("SDL+OGL",0,32,Win_W,Win_H,SDL_WINDOW_OPENGL);
		
		//create ogl context
		GLContext = SDL_GL_CreateContext(screen);
		
		//init glad lib
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			std::cout << "can't init glad\n";
			exit(1);
		}
		
		//print version
		GetOpenGLVersionInfo();
		
		//enable GL capabilities
		glEnable(GL_TEXTURE_2D);

		
	};

	void clean(){
		//cleanup sdl and OGL
		SDL_GL_DeleteContext(GLContext);
		SDL_DestroyWindow(this->screen);
		SDL_Quit();
		
		
		//clean up egine pointer
		delete this->ptrPlayer;
		delete this->ptrScene;
	};

	void pre_draw(){
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		
		glViewport(0,0,Win_W,Win_H);
		glClearColor(1.f,1.f,0.f,1.f);
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		glUseProgram(ptrShader->ShaderProgramm);
	}

	void draw(){
		glEnable(GL_DEPTH_TEST);
		//send stuff to GPU:
		this->ptrScene->draw();
		glDisable(GL_DEPTH_TEST);
	};

	void run(){
		// 1. Setup graphics program
		init();
		//2. init Scene
		this->ptrScene->init();
		
		
		//3. Create shader
		ptrShader->CreateShader();
		
		//4. main loop
		while(loop){
			//update objects
			ptrPlayer->update_player();
			ptrScene->update();

			//draw stuff
			pre_draw();
			draw();
			
			//Update Screen
			SDL_GL_SwapWindow(screen);
		}
		
		//5. clean
		clean();
	};
};

int main(){
	srand(time(NULL));//REMOVE later (debug purpose: random spawn position)
	App app;
	app.run();
	return 0;
}
