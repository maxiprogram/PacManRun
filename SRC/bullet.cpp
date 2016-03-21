#include "bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
    qDebug()<<"Destroy ~Bullet";
}

void Bullet::Init(QHash<QString, QString> property)
{
    id_sprite = 6;
    x = property.value("x").toFloat();
    y = property.value("y").toFloat();
    speed = 2;
    distance = 400;
    start.setX(this->GetPosX());
    start.setY(this->GetPosY());
}

void Bullet::Update(float dt)
{
    ///*Движение
    this->MovePos(QVector3D(speed * x, speed * y, 0));
    //Движение*/

    //qDebug()<<"LENGTH="<<(this->GetPos().length()-start.length())<<"FINISH="<<distance;
    if((this->GetPos().length()-start.length())>distance)
    {
        Resources::GAMESCENE()->GetValue("Level")->DeleteGameObject(this);
    }

    ///*Анимация
    frame+=0.08;
    if (frame>3)
        frame = 0;
    //Анимация*/
}

void Bullet::Draw()
{
    ///*Вывод Bullet
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(this->GetScalX(), this->GetScalY(), qFloor(frame));
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Bullet*/
}
