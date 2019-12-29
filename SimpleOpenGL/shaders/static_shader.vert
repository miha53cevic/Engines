#version 400

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void)
{
	// Multiply order matters: Projection * View * Trans - MVP
	gl_Position =  projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
	pass_textureCoords = textureCoords;
}