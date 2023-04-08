#version 330 core

	out vec4 FragColor;
	in vec4 vertexColor;
	in vec2 texCoord;

	uniform vec3 objectColor;
	uniform vec3 lightColor;

	uniform sampler2D tex0;
	

	void main() {
	
    FragColor = (texture(tex0, texCoord));
	}
	