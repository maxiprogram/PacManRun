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

                for (int j=0; j<100; j++)
                {
                    ///*Particle
                    QHash<QString, QString> prop;
                    prop.insert("id_sprite", QString::number(16));
                    prop.insert("time_life", QString::number(qrand()%15000));
                    prop.insert("width", QString::number(qrand()%48));
                    prop.insert("height", QString::number(qrand()%48));

                    float angle = qrand()%360;
                    float speed = qrand()%15;
                    Transformer tr;
                    tr.SetRotZ(angle);
                    QVector3D vel;
                    vel.setX(1);
                    vel.setY(0);
                    vel = vel * tr.GetMatrix();
                    vel.normalize();
                    vel = vel * speed;
                    prop.insert("vel_x", QString::number(vel.x()));
                    prop.insert("vel_y", QString::number(vel.y()));

                    GameObject* part = new Particle;
                    QVector3D pos_particle = list.at(i)->GetPos();
                    pos_particle.setX(pos_particle.x()+24);
                    pos_particle.setY(pos_particle.y()+24);
                    pos_particle.setZ(0.14);
                    part->SetPos(pos_particle);
                    part->SetRotZ(Geometry::RadianToDegree(qrand()%360));
                    part->SetScal(QVector3D(16, 16, 1));

                    part->Init(prop);
                    Resources::GAMESCENE()->GetValue("Level")->AddGameObject(part);
                    //Particle*/
                }

                Resources::GAMESCENE()->GetValue("Level")->DeleteGameObject(list.at(i));
                qDebug()<<"Remove Ghost";
            }
        }
        //Взаимодействие с Ghost*/

        ///*Взаимодействие с Goal
        QList<GameObject*> list_goal = ManagerGameObject::getInstance()->GetValues("Goal");
        for(int i=0; i<list_goal.size(); i++)
        {
            QRectF rect_pos(this->GetPosX(), this->GetPosY(), this->GetScalX(), this->GetScalY());
            QRectF rect_goal_pos(list_goal.at(i)->GetPosX(), list_goal.at(i)->GetPosY(), list_goal.at(i)->GetScalX(), list_goal.at(i)->GetScalY());
            if (rect_pos.intersects(rect_goal_pos)==true)
            {
                this->SetScal(QVector3D(100, 100, 1));
                flag_move = false;
                frame = 0;

                ///*Подмена тайлов
                Goal* goal = (Goal*)list_goal.at(i);
                QStringList list_x = goal->list_x.split(",");
                QStringList list_y = goal->list_y.split(",");
                int value_tile = goal->value_tile;

                for(int j=0; j<list_x.size(); j++)
                {
                    qDebug()<<"Tile GOAL Main:"<<Resources::TILEMAP()->GetLayer("Main")->GetValue(list_x.at(j).toInt(), list_y.at(j).toInt());
                    qDebug()<<"Tile GOAL Object:"<<Resources::TILEMAP()->GetLayer("Object")->GetValue(list_x.at(j).toInt(), list_y.at(j).toInt());
                    Resources::TILEMAP()->GetLayer("Main")->SetValue(list_x.at(j).toInt(), list_y.at(j).toInt(), value_tile);
                    Resources::TILEMAP()->GetLayer("Object")->SetValue(list_x.at(j).toInt(), list_y.at(j).toInt(), value_tile);
                }
                qDebug()<<"Goal connect";
                //Подмена тайлов*/
            }
        }
        //Взаимодействие с Goal*/

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
    glDepthMask(false);
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
    glDepthMask(true);
}
