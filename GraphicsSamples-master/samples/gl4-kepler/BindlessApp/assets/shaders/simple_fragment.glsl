//----------------------------------------------------------------------------------
// File:        gl4-kepler\NV_OpenGL_Test\assets\shaders/simple_fragment.glsl
// SDK Version: v3.00 
//----------------------------------------------------------------------------------
#version 420 compatibility
#extension GL_NV_bindless_texture : require
#extension GL_NV_gpu_shader5 : require // uint64_t

layout(location=0) smooth in vec4  iColor;
layout(location=1) flat in vec2  iUV;
layout(location=0) out vec4 fragColor;
uniform uint64_t samplers[256];
uniform int useBindless;
uniform int currentFrame;

void main() {
    sampler2D s = sampler2D(samplers[currentFrame]);
    if (useBindless>0) fragColor = texture2D(s, iUV);
    else fragColor = iColor;
}