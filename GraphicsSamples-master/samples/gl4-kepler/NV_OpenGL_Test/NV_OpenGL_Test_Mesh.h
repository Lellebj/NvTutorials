//----------------------------------------------------------------------------------
// File:        gl4-kepler\NV_OpenGL_Test/Mesh.h
// SDK Version: v3.00 
//----------------------------------------------------------------------------------
#ifndef MESH_H
#define MESH_H

#include <NvSimpleTypes.h>


#include <NV/NvPlatformGL.h>
#include <vector>

class Vertex
{
public:
    Vertex(float x, float y, float z, float r, float g, float b, float a);

    float                m_position[3];
    uint8_t              m_color[4];
    float                m_attrib0[4];
    float                m_attrib1[4];
    float                m_attrib2[4];
    float                m_attrib3[4];
    float                m_attrib4[4];
    float                m_attrib5[4];
    float                m_attrib6[4];

    static const int32_t PositionOffset = 0;
    static const int32_t ColorOffset    = 12;
    static const int32_t Attrib0Offset  = 16;
    static const int32_t Attrib1Offset  = 32;
    static const int32_t Attrib2Offset  = 48;
    static const int32_t Attrib3Offset  = 64;
    static const int32_t Attrib4Offset  = 72;
    static const int32_t Attrib5Offset  = 96;
    static const int32_t Attrib6Offset  = 112;
};


class Mesh
{
public:
    int32_t         m_vertexCount;            // Number of vertices in mesh
    int32_t         m_indexCount;             // Number of indices in mesh
    GLuint          m_vertexBuffer;           // vertex buffer object for vertices
    GLuint          m_indexBuffer;            // vertex buffer object for indices
    GLuint          m_paramsBuffer;           // uniform buffer object for params
    GLint           m_vertexBufferSize; 
    GLint           m_indexBufferSize;
    GLuint64EXT     m_vertexBufferGPUPtr;     // GPU pointer to m_vertexBuffer data
    GLuint64EXT     m_indexBufferGPUPtr;      // GPU pointer to m_indexBuffer data

    static bool     m_enableVBUM;
    static bool     m_setVertexFormatOnEveryDrawCall;
    static bool     m_useHeavyVertexFormat;
    static uint32_t m_drawCallsPerState;

    Mesh(void);
    ~Mesh(void);

    // TODO should NV_ASSERT in copy constructor since it can incorrectly delete the OpenGL buffer objects on copy
    
    static void renderPrep();
    static void renderFinish();

    void render(void);
    void update(std::vector<Vertex>& vertices, std::vector<uint16_t>& indices);
};

#endif
