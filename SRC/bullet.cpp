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
    id_sprite_fire = 7;
    x = property.value("x").toFloat();
    y = property.value("y").toFloat();
    speed = 20;
    distance = 600;
    start.setX(this->GetPosX());
    start.setY(this->GetPosY());
    flag_move = true;
    frame = 0;
    frame_y = 9;
}

void Bullet::Update(float dt)
{
    if (flag_move)
    {
        ///*Движение
        this->MovePos(QVector3D(speed * x, speed * y, 0));
        //Движение*/

        if((this->GetPos().length()-start.length())>distance)
        {
            this->SetScal(QVector3D(100, 100, 1));
            flag_move = false;
            frame = 0;
            //Resources::GAMESCENE()->GetValue("Level")->DeleteGameObject(this);
        }

        ///*Взаимодействие с Ghost
        QList<GameObject*> list = ManagerGameObject::getInstance()->GetValues("Ghost");
        for(int i=0; i<list.size(); i++)
        {
            QRectF rect_pos(this->GetPosX(), this->GetPosY(), this->GetScalX(), this->GetScalY());
            QRectF rect_ghost_pos(list.at(i)->GetPosX(), list.at(i)->GetPosY(), list.at(i)->GetScalX(), list.at(i)->GetScalY());
            if (rect_pos.intersects(rect_ghost_pos)==true)
            {
                this->SetScal(QVector3D(100, 100, 1));
                flag_move = false;
                frame = 0;
                Resources::GAMESCENE()->GetValue("Level")->DeleteGameObject(list.at(i));
                qDebug()<<"Remove Ghost";
            }
        }
        //Взаимодействие с Ghost*/

        ///*Анимация
        frame+=0.08;
        if (frame>3)
            frame = 0;
        //Анимация*/
    }else
    {
        Player* player = (Player*)Resources::GAMEOBJECT()->GetValue("Player");
        player->SetJolt(true);
        frame+=2;
        if (frame>9)
        {
            frame = 0;
            frame_y--;
            if (frame_y<0)
            {
                player->SetJolt(false);
                Resources::GAMESCENE()->GetValue("Level")->DeleteGameObject(this);
            }
        }
    }
}

void Bullet::Draw()
{
    if (flag_move)
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
    }else
    {
        ///*Вывод Fire
        ManagerSprite::getInstance()->GetValue(id_sprite_fire)->Bind(this->GetScalX(), this->GetScalY(), qFloor(frame), qFloor(frame_y));
        ManagerSprite::getInstance()->GetValue(id_sprite_fire)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite_fire)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite_fire)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_sprite_fire)->UnBind();
        //Вывод Fire*/
    }
}
