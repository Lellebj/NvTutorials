#version 420

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

uniform mat4 view,offset,proj;
uniform bool dolines;

out  vec3 vColor;

void main(void)
{
 	gl_Position = proj * offset * view * vec4 (vertex_position, 1.0);
	if (dolines)
	{
	vColor = vec3(0.5, 0.9, 0.7);
	}
	else vColor = vertex_colour;

}

//#version 100

//layout(location = 0) in vec3 vertex_position;
//layout(location = 1) in vec3 vertex_colour;

//uniform mat4 view, proj;

//out vec3 colour;

//void main() {
//	colour = vertex_colour;
//	gl_Position = proj * view * vec4 (vertex_position, 1.0);
//}
