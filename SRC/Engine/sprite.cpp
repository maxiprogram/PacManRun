#include "sprite.h"

Sprite::Sprite()
{
    mesh = 0;
    shader = 0;
    texture = 0;
    key_mesh = 0;
    key_shader = 0;
    key_texture = 0;
    buf_tex = new float[6 * 2];

    ///*ST - 1 вершины
    buf_tex[0] = buf_tex[1] = 0.0f;
    //*/

    ///*ST - 2 вершины
    buf_tex[2] = 1.0f;
    buf_tex[3] = 0.0f;
    //*/

    ///*ST - 3 вершины
    buf_tex[4] = 0.0f;
    buf_tex[5] = 1.0f;
    //*/

    ///*ST - 4 вершины
    buf_tex[6] = 1.0f;
    buf_tex[7] = 0.0f;
    //*/

    ///*ST - 5 вершины
    buf_tex[8] = buf_tex[9] = 1.0f;
    //*/

    ///*ST - 6 вершины
    buf_tex[10] = 0.0f;
    buf_tex[11] = 1.0f;
    //*/
}

Sprite::~Sprite()
{
    vbo_tex.destroy();;
    vao.destroy();
    delete [] buf_tex;
    qDebug()<<"~Sprite";
}

void Sprite::SetMeshKey(int key)
{
    key_mesh = key;
    mesh = ManagerMesh::getInstance()->GetValue(key);
}

void Sprite::SetShaderKey(int key)
{
    key_shader = key;
    shader = ManagerShader::getInstance()->GetValue(key);
}

void Sprite::SetTextureKey(int key)
{
    key_texture = key;
    texture = ManagerTexture::getInstance()->GetValue(key);
}

int Sprite::GetMeshKey()
{
    return key_mesh;
}

int Sprite::GetShaderKey()
{
    return key_shader;
}

int Sprite::GetTextureKey()
{
    return key_texture;
}

Mesh* Sprite::GetMesh()
{
    return mesh;
}

Shader* Sprite::GetShader()
{
    return shader;
}

Texture* Sprite::GetTexture()
{
    return texture;
}

void Sprite::Create()
{
    vao.create();
    vao.bind();

    mesh->Bind();
    shader->enableAttributeArray(shader->GetNameVertex().toStdString().c_str());
    shader->setAttributeBuffer(shader->GetNameVertex().toStdString().c_str(), GL_FLOAT, 0, 3);

    vbo_tex.create();
    vbo_tex.bind();
    vbo_tex.allocate(buf_tex, 6 * 2 * sizeof(float));
    shader->enableAttributeArray(shader->GetNameTexture().toStdString().c_str());
    shader->setAttributeBuffer(shader->GetNameTexture().toStdString().c_str(), GL_FLOAT, 0, 2);
}

void Sprite::Bind(int width, int height, int frameX, int frameY, bool atlas)
{
    shader->bind();
    texture->Bind();
    vao.bind();
    if (atlas == false)
    {
        if (width == 0 && height == 0)
        {
            QMatrix4x4 mat_tex;
            mat_tex.setToIdentity();
            shader->setUniformValue(shader->GetNameMatrixTex().toStdString().c_str(), mat_tex);
        }else
        {
            QMatrix4x4 mat_tex;
            float scal_x = (float)width / texture->GetWidth();
            float scal_y = (float)height / texture->GetHeight();
            mat_tex.scale(scal_x, scal_y);
            mat_tex.translate(frameX, frameY);
            shader->setUniformValue(shader->GetNameMatrixTex().toStdString().c_str(), mat_tex);
        }
    }else
    {
        QMatrix4x4 mat_tex;
        float pos_x = (float)frameX / texture->GetWidth();
        float pos_y = (float)frameY / texture->GetHeight();
        float scal_x = (float)width / texture->GetWidth();
        float scal_y = (float)height / texture->GetHeight();
        mat_tex.translate(pos_x, pos_y);
        mat_tex.scale(scal_x, scal_y);
        shader->setUniformValue(shader->GetNameMatrixTex().toStdString().c_str(), mat_tex);
    }
}

void Sprite::UnBind()
{
    vao.release();
    texture->UnBind();
    shader->release();
}
