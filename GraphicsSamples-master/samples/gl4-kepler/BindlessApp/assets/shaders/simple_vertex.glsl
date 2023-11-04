//----------------------------------------------------------------------------------
// File:        gl4-kepler\NV_OpenGL_Test\assets\shaders/simple_vertex.glsl
// SDK Version: v3.00 
//----------------------------------------------------------------------------------
#version 420
#extension GL_NV_shader_buffer_load : require
#extension GL_NV_bindless_texture : require
#extension GL_NV_gpu_shader5 : require // uint64_t

struct PerMeshUniforms
{ 
  float r, g, b, a, u, v;
};


// Input attributes
layout(location=0) in vec4             iPos;
layout(location=1) in vec4             iColor;
layout(location=2) in PerMeshUniforms* bindlessPerMeshUniformsPtr;
layout(location=3) in vec4             iAttrib3; 
layout(location=4) in vec4             iAttrib4; 
layout(location=5) in vec4             iAttrib5; 
layout(location=6) in vec4             iAttrib6; 
layout(location=7) in vec4             iAttrib7; 

uniform uint64_t samplers[256];
uniform int useBindless;
uniform int currentFrame;

// Outputs
layout(location=0) smooth out vec4 oColor;
layout(location=1) flat out vec2 oUV;


// Uniforms
layout(std140, binding=2) uniform TransformParams
{
    mat4 ModelView;
    mat4 ModelViewProjection;
    bool Use_NV_OpenGL_Test_Uniforms;
};

layout(std140, binding=3) uniform NonBindlessPerMeshUniforms
{
  PerMeshUniforms nonBindlessPerMeshUniforms;
};


void main() 
{
  float r, g, b, u, v;

  if(Use_NV_OpenGL_Test_Uniforms)
  {
    // For bindless uniforms, we pass in a pointer in GPU memory to the uniform data through a vertex attribute.
    // We use this pointer to load the uniform data.
    // *** INTERESTING ***
    r = bindlessPerMeshUniformsPtr->r;
    g = bindlessPerMeshUniformsPtr->g;
    b = bindlessPerMeshUniformsPtr->b;
    u = bindlessPerMeshUniformsPtr->u;
    v = bindlessPerMeshUniformsPtr->v;
  }
  else
  {
    // For non-bindless uniforms, we directly used the uniforms
    r = nonBindlessPerMeshUniforms.r;
    g = nonBindlessPerMeshUniforms.g;
    b = nonBindlessPerMeshUniforms.b;
    u = 0.0;
    v = 0.0;
  }

  vec4 positionModelSpace;
  positionModelSpace = iPos;
  if (useBindless>0) {
      sampler2D s = sampler2D(samplers[currentFrame]);
     positionModelSpace.y += texture2D(s, vec2(u, v)).g*5.0f;
  }
  else positionModelSpace.y += sin(positionModelSpace.y * r) * 2.8f;
  gl_Position = ModelViewProjection * positionModelSpace;
    
  oColor.r = iColor.r * r;
  oColor.g = iColor.g * g;
  oColor.b = iColor.b * b;
  oColor.a = iColor.a;
  oUV.x = u;
  oUV.y = v;
}
