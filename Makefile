# Declare compiler tools and flags
CC      = g++
CFLAGS = -g -I/usr/include -I./src -I./
LDLIBS  = -lGL -lSDL2 -lSDL2_image -ldl
FILES  = src/main.cpp
FILES += ./glad/glad.c 
FILES += src/shader/shader.cpp 
FILES += src/camera/camera.cpp
FILES += src/camera/Player.cpp
FILES += src/textures.cpp
FILES += src/mesh.cpp
FILES += src/chunks/chunk_build_helper.cpp 
FILES += src/chunks/chunk.cpp 
FILES += src/chunks/world.cpp
FILES += src/scene.cpp
FILES += src/hitbox.cpp


# Build the main executable
all:
	$(CC)  -o main $(FILES) $(CFLAGS) $(LDLIBS)


# Helper target that cleans up build artifacts
clean:
	rm main
