#pragma once
//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//OGL

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

//STD
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

//config
#define Win_W 1024
#define Win_H 780

#include <types.hpp>
#include <camera/Player.hpp>
#include <shader/shader.hpp>
#include <textures.hpp>
#include <mesh.hpp>
#include <chunks/chunk_build_helper.hpp>
#include <chunks/chunk.hpp>
#include <chunks/world.hpp>
#include <hitbox.hpp>
#include <scene.hpp>
