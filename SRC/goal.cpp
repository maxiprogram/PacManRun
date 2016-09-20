#include "goal.h"

Goal::Goal()
{

}

Goal::~Goal()
{
    qDebug()<<"Destroy ~Goal";
}

void Goal::Init(QHash<QString, QString> property)
{
    this->SetScalX(property.value("scal_x").toFloat());
    this->SetScalY(property.value("scal_y").toFloat());
    this->SetPosX(property.value("pos_x").toFloat());
    this->SetPosY(property.value("pos_y").toFloat());
    this->SetPosZ(0.16);

    id_sprite = property.value("id_sprite").toInt();
    list_x = property.value("list_x");
    list_y = property.value("list_y");
    value_tile = property.value("value_tile").toInt();
}

void Goal::Update(float dt)
{

}

void Goal::Draw()
{
    ///*Вывод Goal
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(this->GetScalX(), this->GetScalY());
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Goal*/
}

