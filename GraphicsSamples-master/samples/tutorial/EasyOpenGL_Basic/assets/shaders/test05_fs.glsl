#version 420

in vec3 vColor;
out vec4 frag_colour;

void main(void)
{
	frag_colour = vec4 (vColor, 1.0);
//    gl_FragColor = vColor;
}


//#version 100

//in vec3 colour;
//out vec4 frag_colour;

//void main() {
//	frag_colour = vec4 (colour, 1.0);
//}

