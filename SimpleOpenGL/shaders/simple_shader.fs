#version 400

in vec3 colour;

out vec4 out_color;

void main(void) {
	out_color = vec4(colour, 1.0);
}