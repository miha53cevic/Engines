#version 400

layout (location = 0) in vec3 position;

out vec4 vertexColour;

void main(void) {
	gl_Position = vec4(position, 1.0);
	vertexColour = vec4(position.x+0.5, 1.0, position.y+0.5, 1.0);
}