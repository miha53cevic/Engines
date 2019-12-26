#version 400

layout (location = 0) in vec3 position;

out vec4 vertexColour;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void) {
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
	vertexColour = vec4(1.0);
}