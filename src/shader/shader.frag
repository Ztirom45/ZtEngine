#version 460 core
in vec4 VertexColorOut;
in vec2 TexCoordOut;

out vec4 color;

uniform sampler2D Texture;

void main() {
	color = texture(Texture, TexCoordOut);
	//color = texture(Texture, TexCoordOut)*VertexColorOut;
	//color = VertexColorOut;
}

