//----------------------------------------------------------------------------------
// File:        tutorial\EasyOpenGL_Basic\assets\shaders/plain.vert
// SDK Version: v3.00 
// Email:       gameworks@nvidia.com
// Site:        http://developer.nvidia.com/
//----------------------------------------------------------------------------------
#version 100
attribute highp vec2 aPosition;

uniform mediump mat4 uViewProjMatrix;

varying lowp vec4 vColor;

void main(void)
{
    gl_Position = uViewProjMatrix * vec4(aPosition.x, aPosition.y, 0.0, 1.0);
    vColor = vec4(aPosition.x * 0.8 + 0.5, aPosition.y * 0.5 + 0.5, 0.4, 1.0);
}
