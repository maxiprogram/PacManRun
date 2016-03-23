#include "decor.h"

Decor::Decor()
{
}

Decor::~Decor()
{
    qDebug()<<"Destroy ~Decor";
}

void Decor::Init(QHash<QString, QString> property)
{
    this->SetPosX(property.value("pos_x").toFloat());
    this->SetPosY(property.value("pos_y").toFloat());
    this->SetPosZ(property.value("pos_z").toFloat());

    this->SetScalX(property.value("scal_x").toFloat());
    this->SetScalY(property.value("scal_y").toFloat());
    atlas_x = property.value("atlas_x").toFloat();
    atlas_y = property.value("atlas_y").toFloat();
    width = property.value("width").toInt();
    height = property.value("height").toInt();;

    id_sprite = property.value("id_sprite").toInt();
}

void Decor::Update(float dt)
{

}

void Decor::Draw()
{
    ///*Вывод Decor
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(width, height, atlas_x, atlas_y, true);
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Decor*/
}
