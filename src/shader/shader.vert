#version 460 core

layout(location=0) in vec3 position;
layout(location=1) in vec4 vertexColor;
layout(location=2) in vec2 TexCoord;

//send stuff to fragment shader

out vec4 VertexColorOut;
out vec2 TexCoordOut;

//uniform vars
uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_proj;

void main() {
	//sending the vertex color to the fragment shader
	//VertexColorOut = vertexColor;
	TexCoordOut = TexCoord;
	
	gl_Position = m_proj * m_view * m_model * vec4(position, 1.0f);
	//gl_Position = m_proj * m_view * m_model * vec4(TexCoord,1.0f, 1.0f);
}
