
//----------------------------------------------------------------------------------
// File:        tutorial\EasyOpenGL_Basic/EasyOpenGL_Basic.h
// SDK Version: v3.00 
// Email:       gameworks@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2014-2015, NVIDIA CORPORATION. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------------
#include "NvAppBase/gl/NvSampleAppGL.h"

#include "KHR/khrplatform.h"
#include "NvGamepad/NvGamepad.h"
#include "NV/NvMath.h"
#include "NvAppBase/NvInputTransformer.h"


#define ANIMATION_DURATION 5.0f

class NvStopWatch;
class NvGLSLProgram;
class NvFramerateCounter;

class EasyOpenGL_Basic : public NvSampleAppGL
{
public:
    EasyOpenGL_Basic();
    ~EasyOpenGL_Basic();
    
    virtual void initRendering(void);
    void shutdownRendering(void);
    void initUI(void);
    virtual void draw(void);
    void reshape(int32_t width, int32_t height);

    virtual void configurationCallback(NvGLConfiguration& config);
    virtual bool handleKeyInput(uint32_t code, NvKeyActionType::Enum action);

    NvGLSLProgram* mProgram;

    GLuint vao;
    GLuint colours_vbo;
    GLuint points_vbo;
    GLuint EBO;


private:

   bool m_enableVBUM;
   bool mytest;

   float  m_right_left, m_up_down, m_front_back;

   bool m_Use_NV_OpenGL_Test_Uniforms;
   bool m_showEdges;
   bool m_usePerMeshUniforms;
   bool m_updateUniformsEveryFrame;
   bool m_setVertexFormatOnEveryDrawCall;
   bool m_useHeavyVertexFormat;
   bool m_useBindlessTextures;
   GLfloat m_LineWidth;

   uint32_t m_drawCallsPerState;

   NvUIValueText* m_drawCallsPerSecondText;

   int  m_currentFrame;
   float m_currentTime;

};
