/*
FirstPersonPlayer libery from Ztirom's ZtEngine

TIP if you want to know more about the functions take a look into the header
*/

#include <config.hpp>
#include <camera/FirstPersonPlayer.hpp>

FirstPersonPlayer::FirstPersonPlayer(glm::vec3 pos,
	float CameraDistanceToPlayer,float yaw,float pitch,
	bool *LoopConditionVar)
	:Camera(pos,CameraDistanceToPlayer,yaw,pitch){
	this->loop = LoopConditionVar;
}
void FirstPersonPlayer::set_key_state(int position,bool state){
	if(position>=0&&position<keysSIZE){
		this->keys[position] = state;
	}else{
		printf("Error: key array index out of range (index:%d).\n",position);
	}
}

bool FirstPersonPlayer::get_key_state(int position){
	if(position>=0&&position<keysSIZE){
		return keys[position];
	}else{
		printf("Error: key array index out of range (index:%d).\n",position);
		return false;
	}
}
void FirstPersonPlayer::handle_events(){
	SDL_Event event;
	const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				*this->loop = false;
				break;
			case SDL_KEYDOWN:
				this->set_key_state(event.key.keysym.sym,true);
				break;
			case SDL_KEYUP:
				this->set_key_state(event.key.keysym.sym,false);
				break;
			default:
				break;
		}
	}
}
void FirstPersonPlayer::Move(){//move the player with the inputs in keys

	//transformation
	if(this->keys[SDLK_w]){
		this->move_forward(0.1);
	}
	if(this->keys[SDLK_s]){
		this->move_back(0.1);
	}
	if(this->keys[SDLK_a]){
		this->move_left(0.1);
	}
	if(this->keys[SDLK_d]){
		this->move_right(0.1);
	}
	if(this->keys[SDLK_SPACE]){
		this->move_up(0.1);
	}
	if(this->keys[SDLK_LSHIFT]){
		this->move_down(0.1);
	}

	//rotation

	if(this->keys[SDLK_UP]){
		this->rotate_pitch(glm::radians(1.0f));
	}
	if(this->keys[SDLK_DOWN]){
		this->rotate_pitch(glm::radians(-1.0f));
	}

	if(this->keys[SDLK_LEFT]){
		this->rotate_yaw(glm::radians(1.0f));
	}

	if(this->keys[SDLK_RIGHT]){
		this->rotate_yaw(glm::radians(-1.0f));
	}

};

void FirstPersonPlayer::update_player(){
	this->handle_events();
	this->Move();
	this->update_camera();
};
