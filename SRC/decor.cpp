#include "decor.h"

Decor::Decor()
{
}

Decor::~Decor()
{
    qDebug()<<"Destroy ~Decor";
}

void Decor::SetCountFrame(int count)
{
    count_frame = count;
}

void Decor::Init(QHash<QString, QString> property)
{
    this->SetPosX(property.value("pos_x").toFloat());
    this->SetPosY(property.value("pos_y").toFloat());
    this->SetPosZ(property.value("pos_z").toFloat());

    this->SetScalX(property.value("scal_x").toFloat());
    this->SetScalY(property.value("scal_y").toFloat());
    count_frame = property.value("count_frame").toInt();
    atlas_x = property.value("atlas_x").toFloat();
    atlas_y = property.value("atlas_y").toFloat();
    width = property.value("width").toInt();
    height = property.value("height").toInt();;

    frame = 0;
    id_sprite = property.value("id_sprite").toInt();
}

void Decor::Update(float dt)
{
    ///*Анимация
    frame+=0.15;
    if (frame>count_frame)
        frame = 0;
    //Анимация*/
}

void Decor::Draw()
{
    ///*Вывод Decor
    if(count_frame==0)
        ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(width, height, atlas_x, atlas_y, true);
    else
        ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(width, height, width*qFloor(frame), height*qFloor(frame), qFloor(frame));
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Decor*/

    //qDebug()<<this->GetName();
}
