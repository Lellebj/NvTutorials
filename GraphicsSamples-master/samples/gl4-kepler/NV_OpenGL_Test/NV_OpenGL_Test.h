//----------------------------------------------------------------------------------
// File:        gl4-kepler\NV_OpenGL_Test/NV_OpenGL_Test.h
// SDK Version: v3.00 
// Email:       gameworks@nvidia.com
//----------------------------------------------------------------------------------
#ifndef BINDLESS_APP_H
#define BINDLESS_APP_H

#include "NvAppBase/gl/NvSampleAppGL.h"

#include "NV/NvMath.h"
#include "NvAppBase/NvInputTransformer.h"
#include "NV_OpenGL_Test_Mesh.h"

#include <vector>

#define SQRT_BUILDING_COUNT 100
#define TEXTURE_FRAME_COUNT 181
#define ANIMATION_DURATION 5.0f
class NvGLSLProgram;
class NvStopWatch;
class NvFramerateCounter;

class NV_OpenGL_Test : public NvSampleAppGL
{
public:
    NV_OpenGL_Test();
    ~NV_OpenGL_Test();
    
    void initUI();
    void initRendering(void);
    void draw(void);
    void reshape(int32_t width, int32_t height);
    void updatePerMeshUniforms(float t);
	void InitBindlessTextures();

    void configurationCallback(NvGLConfiguration& config);

private:
    struct TransformUniforms
    {
        nv::matrix4f ModelView;
        nv::matrix4f ModelViewProjection;
        int32_t      Use_NV_OpenGL_Test_Uniforms;
    };

    struct PerMeshUniforms
    {
        float r, g, b, a, u, v;
    };

    void createBuilding(Mesh& mesh, nv::vec3f pos, nv::vec3f dim, nv::vec2f uv);
    void createGround(Mesh& mesh, nv::vec3f pos, nv::vec3f dim);
    void randomColor(float &r, float &g, float &b);
    
    // Simple collection of meshes to render
    std::vector<Mesh>             m_meshes;

    // Shader stuff
    NvGLSLProgram*                m_shader;
    GLuint                        m_bindlessPerMeshUniformsPtrAttribLocation;

    // uniform buffer object (UBO) for tranform data
    GLuint                        m_transformUniforms;
    TransformUniforms             m_transformUniformsData;
    nv::matrix4f                  m_projectionMatrix;

    // uniform buffer object (UBO) for mesh param data
    GLuint                        m_perMeshUniforms;
    std::vector<PerMeshUniforms>  m_perMeshUniformsData; 
    GLuint64EXT                   m_perMeshUniformsGPUPtr;

	//bindless texture handle
	GLuint64EXT*				  m_textureHandles;
	GLuint*						  m_textureIds;
	GLint					      m_numTextures;
	bool						  m_useBindlessTextures;
	int							  m_currentFrame;
	float						  m_currentTime;

    // UI stuff
    NvUIValueText*                m_drawCallsPerSecondText;
    bool                          m_Use_NV_OpenGL_Test_Uniforms;
    bool                          m_updateUniformsEveryFrame;
    bool                          m_usePerMeshUniforms;

    // Timing related stuff
    float                         m_t;
    float                         m_minimumFrameDeltaTime;
};

#endif
