//----------------------------------------------------------------------------------
// File:        tutorial\EasyOpenGL_Basic/EasyOpenGL_Basic.cpp
// SDK Version: v3.00 
// Email:       gameworks@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2014-2015, NVIDIA CORPORATION. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// ar
// 
// 
// 
// 
// 
// 
// e met:
//
//----------------------------------------------------------------------------------
#include "EasyOpenGL_Basic.h"
#include "NvAppBase/NvFramerateCounter.h"
#include "NV/NvStopWatch.h"

#include "NvAppBase/NvInputTransformer.h"
#include "NvAssetLoader/NvAssetLoader.h"
#include "NvGLUtils/NvGLSLProgram.h"
#include "NvGLUtils/NvShapesGL.h"
#include "NvUI/NvTweakBar.h"
#include "NV/NvLogs.h"



#define VERTEX_SHADER_FILE "shaders/test05_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test05_fs.glsl"
//#define VERTEX_SHADER_FILE "shaders/plain.vert"
//#define FRAGMENT_SHADER_FILE "shaders/plain.frag"


GLfloat points[] = { 0.0f, 0.5f, -0.0f,
                     0.5f, -0.5f, -0.5f, 
                    -0.5f, -0.5f, -0.5f
                    ,0.0f, -0.5f, 0.5f
};

GLfloat colours[] = { 1.0f, 0.1f, 0.0f, 
                      0.0f, 1.0f, 0.1f,
                      0.1f, 0.0f, 1.0f
                     ,1.0f, 1.0f, 0.0f
                    };

GLint indices[] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
    0, 3, 1    // second triangle
    , 0, 2, 3
    , 1, 3, 2
};

EasyOpenGL_Basic::EasyOpenGL_Basic()
    : m_right_left(0.0f), m_up_down(0.0f), m_front_back(0.0f),
    m_showEdges(1), m_LineWidth(1.0f)

{
    m_transformer->setTranslationVec(nv::vec3f(0.0f, -0.0f, -4.5f));
    m_transformer->setRotationVec(nv::vec3f(NV_PI*0.0f, 0.0f, 0.0f));

    // Required in all subclasses to avoid silent link issues
    forceLinkHack();
}

EasyOpenGL_Basic::~EasyOpenGL_Basic()
{
    LOGI("EasyOpenGL_Basic: destroyed\n");
}

void EasyOpenGL_Basic::configurationCallback(NvGLConfiguration& config)
{ 
    config.depthBits = 24; 
    config.stencilBits = 0; 
    config.apiVer = NvGLAPIVersionGL4();
}


////////////////////////////////////////////////////////////////////////////////
// SoftShadows::handleGamepadChanged()
////////////////////////////////////////////////////////////////////////////////
bool EasyOpenGL_Basic::handleKeyInput(uint32_t code, NvKeyActionType::Enum action)
{
    if (action != NvKeyActionType::UP) // so down OR repeat...
    {
        switch (code)
        {
        case NvKey::K_ARROW_LEFT:
            m_right_left +=  0.1f;
            break;

        case NvKey::K_ARROW_RIGHT:
            m_right_left -= 0.1f;
            break;

        case NvKey::K_ARROW_UP:
            m_front_back += 0.1f;
            break;

        case NvKey::K_ARROW_DOWN:
            m_front_back -= 0.1f;
            break;

        case NvKey::K_PAGE_DOWN:
            m_up_down += 0.1f;
            break;

        case NvKey::K_PAGE_UP:
            m_up_down -= 0.1f;
            break;

        default:
            return false;
        };

        return true;
    }

    return false;
}



////////////////////////////////////////////////////////////////////////////////
//
//  Method: NV_OpenGL_Test::initRendering()
//
//    Sets up initial rendering state and creates meshes
//
////////////////////////////////////////////////////////////////////////////////

void EasyOpenGL_Basic::initRendering(void) {
    NvAssetLoaderAddSearchPath("tutorial/EasyOpenGL_Basic");
//    NvAssetLoaderAddSearchPath("C:\\C_APPS\\antons_opengl_tutorials_book\\05_virtual_camera");

    mProgram = NvGLSLProgram::createFromFiles(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    CHECK_GL_ERROR();

    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK);    // cull back face
    glFrontFace(GL_CW);     // GL_CCW for counter clock-wise


}

void EasyOpenGL_Basic::shutdownRendering(void) {

    // destroy other resources here
}

void EasyOpenGL_Basic::initUI(void) {
    if (mTweakBar) 
    {
//      NvTweakVarBase *var;

// sample apps automatically have a tweakbar they can use.
        if (mTweakBar) 
        { // create our tweak ui
            mTweakBar->addValue("Show Edges",  m_showEdges);
            mTweakBar->addValue("Use Mytest", mytest);
            mTweakBar->addValue("Line Width", m_LineWidth, 0.5f, 5.0f);

            mTweakBar->addValue("Use bindless uniforms", m_Use_NV_OpenGL_Test_Uniforms);
            mTweakBar->addValue("Use per mesh uniforms", m_usePerMeshUniforms);
            mTweakBar->addValue("Update uniforms every frame", m_updateUniformsEveryFrame);
            mTweakBar->addValue("Set vertex format for each mesh", m_setVertexFormatOnEveryDrawCall);
            mTweakBar->addValue("Use heavy vertex format", m_useHeavyVertexFormat);
            mTweakBar->addValue("Use bindless textures", m_useBindlessTextures);
            mTweakBar->addValue("Draw calls per state", m_drawCallsPerState, 1, 10);
        }
        mTweakBar->syncValues();

    }

    if (mFPSText) {
        NvUIRect tr;
        mFPSText->GetScreenRect(tr);
        m_drawCallsPerSecondText = new NvUIValueText("HejÅhÅ", NvUIFontFamily::SANS, mFPSText->GetFontSize(), NvUITextAlign::RIGHT,
            0.0f, 2, NvUITextAlign::RIGHT);
        m_drawCallsPerSecondText->SetColor(NV_PACKED_COLOR(0x30, 0xD0, 0xD0, 0xB0));
        m_drawCallsPerSecondText->SetShadow();
        mUIWindow->Add(m_drawCallsPerSecondText, tr.left, tr.top + tr.height + 8);
    }

    // Change the filtering for the framerate
    mFramerate->setMaxReportRate(.2f);
    mFramerate->setReportFrames(20);

    // Disable wait for vsync
    getGLContext()->setSwapInterval(1);

}


void EasyOpenGL_Basic::reshape(int32_t width, int32_t height)
{
    glViewport( 0, 0, (GLint) width, (GLint) height );
}


void EasyOpenGL_Basic::draw(void)
{
    glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CHECK_GL_ERROR();

    nv::matrix4f View = m_transformer->getModelViewMat();

    nv::matrix4f Proj;
    nv::perspective(Proj, 3.14f * 0.5f, m_width/(float)m_height, 0.1f, 30.0f);
    nv::matrix4f Offset;
    nv::translation(Offset, m_right_left, m_front_back, m_up_down);

    CHECK_GL_ERROR();

    //+++++++++++++++++++++++++++++++++++++++++


    //nv::matrix4f OffsetView = Offset * View;

    //m_viewProj = proj * OffsetView;

    //-----------------------------------------


    mProgram->enable();

    mProgram->setUniformMatrix4fv("view", View._array, 1, GL_FALSE);
    mProgram->setUniformMatrix4fv("offset", Offset._array, 1, GL_FALSE);
    mProgram->setUniformMatrix4fv("proj", Proj._array, 1, GL_FALSE);

    glLineWidth(m_LineWidth);


    glBindVertexArray(vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling


    glPolygonMode(GL_FRONT, GL_FILL);
    mProgram->setUniform1i("dolines", 0);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);


    if (m_showEdges)
    {
        mProgram->setUniform1i("dolines", 1);
        glPolygonMode(GL_FRONT, GL_LINE);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
    }

    CHECK_GL_ERROR();

    glBindVertexArray(0);

    mProgram->disable();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Update the rendering stats in the UI
    float drawCallsPerSecond;
    drawCallsPerSecond = mFramerate->getMeanFramerate();
    m_drawCallsPerSecondText->SetValue(drawCallsPerSecond);

    m_currentTime += getFrameDeltaTime();
    if (m_currentTime > ANIMATION_DURATION) m_currentTime = 0.0;
    m_currentFrame = (int)(180.0f * m_currentTime / ANIMATION_DURATION);

}

NvAppBase* NvAppFactory() {
    return new EasyOpenGL_Basic();
}
