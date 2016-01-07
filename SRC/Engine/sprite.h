#ifndef SPRITE_H
#define SPRITE_H

#include <QOpenGLVertexArrayObject>

#include "managermesh.h"
#include "managershader.h"
#include "managertexture.h"

class Sprite
{
public:
    Sprite();
    ~Sprite();
    void SetMeshKey(int key);
    void SetShaderKey(int key);
    void SetTextureKey(int key);
    int GetMeshKey();
    int GetShaderKey();
    int GetTextureKey();
    Mesh* GetMesh();
    Shader* GetShader();
    Texture* GetTexture();
    void Create();
    void Bind(int width = 0, int height = 0, int frameX = 0, int frameY = 0, bool atlas = false);
    void UnBind();
protected:
    Mesh* mesh;
    Shader* shader;
    Texture* texture;
    int key_mesh;
    int key_shader;
    int key_texture;
    float* buf_tex;
    QOpenGLBuffer vbo_tex;
    QOpenGLVertexArrayObject vao;
};

#endif // SPRITE_H
