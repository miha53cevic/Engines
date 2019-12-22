#version 400

in vec4 vertexColour;

out vec4 fragColour;

void main(void) {
	fragColour = vertexColour;
}