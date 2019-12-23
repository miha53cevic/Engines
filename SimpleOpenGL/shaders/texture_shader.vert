#version 400

in vec3 position;
in vec2 textureCoords;

out vec2 pass_textureCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	// Multiply order matters: Projection * View * Trans
	gl_Position =  projectionMatrix * transformationMatrix * vec4(position, 1.0);
	pass_textureCoords = textureCoords;
}