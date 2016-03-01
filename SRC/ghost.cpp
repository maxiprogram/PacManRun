#include "ghost.h"

Ghost::Ghost()
{
}

Ghost::~Ghost()
{
    qDebug()<<"Destroy ~Ghost";
}

void Ghost::Init(QHash<QString, QString> property)
{
    this->SetScalX(property.value("scal_x").toFloat());
    this->SetScalY(property.value("scal_y").toFloat());
    this->SetPosX(property.value("pos_x").toFloat());
    this->SetPosY(property.value("pos_y").toFloat());

    start_pos.setX(this->GetPosX());
    start_pos.setY(this->GetPosY());

    id_sprite = property.value("id_sprite").toInt();
    radius = property.value("radius").toFloat();
    speed_x = property.value("speed_x").toFloat();
    speed_y = property.value("speed_y").toFloat();
    frame = 0;
    direction.setX(1);
    direction.setY(1);

}

void Ghost::Update(float dt)
{
    if (direction.x()==1)
        this->MoveX(speed_x);
    if (direction.x()==-1)
        this->MoveX(-speed_x);

    if (direction.y()==1)
        this->MoveY(speed_y);
    if (direction.y()==-1)
        this->MoveY(-speed_y);

    ///*Если привысил радиус движения по X
    if (this->GetPosX()>start_pos.x()+radius && direction.x()==1)
    {
        direction.setX(-1);
    }
    if (this->GetPosX()<start_pos.x()-radius && direction.x()==-1)
    {
        direction.setX(1);
    }
    //Если привысил радиус движения по X*/

    ///*Если привысил радиус движения по Y
    if (this->GetPosY()>start_pos.y()+radius && direction.y()==1)
    {
        direction.setY(-1);
    }
    if (this->GetPosY()<start_pos.y()-radius && direction.y()==-1)
    {
        direction.setY(1);
    }
    //Если привысил радиус движения по Y*/

    ///*Анимация
    frame+=0.08;
    if (frame>3)
        frame = 0;
    //Анимация*/
}

void Ghost::Draw()
{
    ///*Вывод Ghost1
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(this->GetScalX(), this->GetScalY(), qFloor(frame));
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Ghost1*/

}
