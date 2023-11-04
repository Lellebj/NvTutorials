//----------------------------------------------------------------------------------
// File:        tutorial\basic/Basic.cpp
// SDK Version: v3.00 
// Email:       gameworks@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2014-2015, NVIDIA CORPORATION. All rights reserved.
//
//
//----------------------------------------------------------------------------------
#include "Basic.h"
#include "NvAppBase/NvInputTransformer.h"
#include "NvAssetLoader/NvAssetLoader.h"
#include "NvGLUtils/NvGLSLProgram.h"
#include "NvGLUtils/NvShapesGL.h"
#include "NvUI/NvTweakBar.h"
#include "NV/NvLogs.h"

Basic::Basic()
{


    m_transformer->setTranslationVec(nv::vec3f(0.0f, 0.0f, -2.2f));
    m_transformer->setRotationVec(nv::vec3f(NV_PI*0.35f, 0.20f, 0.0f));

    // Required in all subclasses to avoid silent link issues
    forceLinkHack();
}

Basic::~Basic()
{



    LOGI("Basic: destroyed\n");
}

void Basic::configurationCallback(NvGLConfiguration& config)
{ 
    config.depthBits = 24; 
    config.stencilBits = 0; 
    config.apiVer = NvGLAPIVersionGL4();
}

void Basic::initRendering(void) {
    NvAssetLoaderAddSearchPath("tutorial/Basic");

    mProgram = NvGLSLProgram::createFromFiles("shaders/plain.vert", "shaders/plain.frag");

}

void Basic::shutdownRendering(void) {

    // destroy other resources here
}

void Basic::initUI(void) {
    if (mTweakBar) {
//        NvTweakVarBase *var;

        mTweakBar->syncValues();
    }
}


void Basic::reshape(int32_t width, int32_t height)
{
    glViewport( 0, 0, (GLint) width, (GLint) height );
}


void Basic::draw(void)
{
    CHECK_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    CHECK_GL_ERROR();

    nv::matrix4f projection_matrix;
    nv::perspective(projection_matrix, 3.14f * 0.25f, m_width/(float)m_height, 0.1f, 30.0f);
    nv::matrix4f camera_matrix = projection_matrix * m_transformer->getModelViewMat();
    CHECK_GL_ERROR();

    mProgram->enable();

    mProgram->setUniformMatrix4fv("uViewProjMatrix", camera_matrix._array, 1, GL_FALSE);
    CHECK_GL_ERROR();

    NvDrawQuadGL(mProgram->getAttribLocation("aPosition"));
    CHECK_GL_ERROR();

    mProgram->disable();
}

NvAppBase* NvAppFactory() {
    return new Basic();
}
