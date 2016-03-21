#include "player.h"

Player::Player()
{
}

Player::~Player()
{
    qDebug()<<"Destroy ~Player";
}

QRectF Player::GetBoundBox()
{
    QRectF rect(this->GetPosX(), this->GetPosY(), this->GetScalX(), this->GetScalY());
    return rect;
}

void Player::Init(QHash<QString, QString> property)
{
    this->SetScalX(property.value("scal_x").toFloat());
    this->SetScalY(property.value("scal_y").toFloat());
    this->SetPosX(property.value("pos_x").toFloat());
    this->SetPosY(property.value("pos_y").toFloat());
    id_sprite = property.value("id_sprite").toInt();
    id_close = property.value("id_close").toInt();
    speed_x = property.value("speed_x").toFloat();
    accel_y = property.value("accel_y").toFloat();
    speed_y = 15;
    accel_x = 0;

    direction.setX(0);
    direction.setY(0);
    Status = Down;
    count_bonus = 0;
    count_bonus_shoot = 0;
    rotation_shoot = 0;
    y_sprite = 1;

    frame = 0;
}

void Player::Update(float dt)
{
    ///*Движение и проверка коллизии
    this->MoveX((speed_x+accel_x)*dt);
    direction.setX(1);
    QVector3D new_pos = this->GetPos();
    TileMap::getInstance()->CollisionX("Main", new_pos, this->GetBoundBox(), this->direction);
    this->SetPos(new_pos);
    accel_x = 0;

    //УБРАТЬ
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_P))
    {
        if (speed_x)
            speed_x = 0;
        else
            speed_x = 10;
        Resources::KEYBOARD()->SetKey(Qt::Key_P, false);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Escape))
    {
        qDebug()<<"CurrentStatusGame Pause";
        CurrentStatusGame = Pause;
        Resources::KEYBOARD()->SetKey(Qt::Key_Escape, false);
    }

    int m_x = Resources::MOUSE()->GetX();
    int m_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();

    ///*Если нажата мышка
    if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
    {
        ///*Если нажата на Close
        if (m_x>(Setting::GetViewPort().width()-58-10) && m_x<(Setting::GetViewPort().width()-10))
        {
            if (m_y>Setting::GetViewPort().height()-58-10 && m_y<Setting::GetViewPort().height()-10)
            {
                CurrentStatusGame = Pause;
                Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
            }
        }
        //Если нажата на Close*/
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space) && Status==OnGround)
    {
        Status = Jump;
        speed_y = 15;
        direction.setY(1);
        Resources::KEYBOARD()->SetKey(Qt::Key_Space, false);
    }

    if(Status==Jump)
    {
        if (speed_y>0)
        {
            //qDebug()<<"JUMP DO Speed:"<<speed_y<<"Pos:"<<GetPos();
            speed_y-=accel_y;
            direction.setY(1);
            MoveY(speed_y);
            //qDebug()<<"JUMP Speed:"<<speed_y<<"Pos:"<<GetPos();
        }else
        {
            Status = Down;
            direction.setY(-1);
        }
    }
    if (Status==Down)
    {
        //qDebug()<<"DOWN DO Speed:"<<speed_y<<"Pos:"<<GetPos();
        if (speed_y>-30)
        {
            speed_y-=accel_y;
        }
        MoveY(speed_y);
        direction.setY(-1);
        //qDebug()<<"DOWN Speed:"<<speed_y<<"Pos:"<<GetPos();
    }

    new_pos=this->GetPos();

    if(TileMap::getInstance()->CollisionY("Main", new_pos, this->GetBoundBox(), this->direction))
    {
        if (direction.y()==-1)
        {
            Status = OnGround;
            speed_y = 0;
            //qDebug()<<"ONGROUND";
        }
    }else
    {
        if (Status!=Jump)
        {
            Status = Down;
            direction.setY(-1);
        }
    }
    this->SetPos(new_pos);
    //Движение и проверка коллизии*/

    ///*Взаимодействие с объктами
    QVector<Tile> tiles = TileMap::getInstance()->GetTiles("Object", GetBoundBox());
    for (int i=0; i<tiles.size(); i++)
    {
        //Если монета
        if (tiles.at(i).id==13)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                TileMap::getInstance()->GetLayer("Object")->SetValue(tiles.at(i).ij.y(), tiles.at(i).ij.x(), 0);
                PlayProfile::score+=1;
            }
        }
        //Если шип
        if (tiles.at(i).id==16 || tiles.at(i).id==17 || tiles.at(i).id==18)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                speed_x = 0;
                frame = 4;
                y_sprite = 1;
                qDebug()<<"DEAD";
                CurrentStatusGame = Dead;
            }
        }
        //Если лед
        if (tiles.at(i).id==10)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                accel_x=10;
            }
        }
        //Если жвачка
        if (tiles.at(i).id==7)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                accel_x=-4;
            }
        }
        //Если прунжина
        if (tiles.at(i).id==4)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                Status = Jump;
                speed_y = 30;
                direction.setY(1);
            }
        }
        //Если портал
        if (tiles.at(i).id==1)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                QList<GameObject*> list = ManagerGameObject::getInstance()->GetValues("Portal");
                for(int i1=0; i1<list.size(); i1++)
                {
                    if(tiles.at(i).ij.x()==((Portal*)list.at(i1))->GetPosStart().x() &&
                            tiles.at(i).ij.y()==((Portal*)list.at(i1))->GetPosStart().y())
                    {
                        QVector3D pos = this->GetPos();
                        pos.setX(((Portal*)list.at(i1))->GetPosFinish().x() * 32 - 48);
                        pos.setY((TileMap::getInstance()->GetTileCountHeight() - ((Portal*)list.at(i1))->GetPosFinish().y() -1) * 32);
                        this->SetPos(pos);
                        break;
                    }
                }
            }

        }
        //Если бонус
        if (tiles.at(i).id==14)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                TileMap::getInstance()->GetLayer("Object")->SetValue(tiles.at(i).ij.y(), tiles.at(i).ij.x(), 0);
                count_bonus++;
            }
        }
        //Если разрушающая земля
        if (tiles.at(i).id==20)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                TileMap::getInstance()->GetLayer("Object")->SetValue(tiles.at(i).ij.y(), tiles.at(i).ij.x(), 0);
            }
        }
        //Если оружие
        if (tiles.at(i).id==15)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                TileMap::getInstance()->GetLayer("Object")->SetValue(tiles.at(i).ij.y(), tiles.at(i).ij.x(), 0);
                count_bonus_shoot++;
            }
        }
    }
    ///*Взаимодействие с Ghost
    QList<GameObject*> list = ManagerGameObject::getInstance()->GetValues("Ghost");
    for(int i=0; i<list.size(); i++)
    {
        QRectF rect_new_pos = this->GetBoundBox();
        QRectF rect_ghost_pos(list.at(i)->GetPosX(), list.at(i)->GetPosY(), list.at(i)->GetScalX(), list.at(i)->GetScalY());
        if (rect_new_pos.intersects(rect_ghost_pos)==true)
        {
            if (count_bonus>0)
            {
                count_bonus--;
                Resources::GAMESCENE()->GetValue("Level")->DeleteGameObject(list.at(i));
                //int n = ManagerGameObject::getInstance()->GetHashTab()->remove("Ghost", list.at(i));
                qDebug()<<"Remove Ghost";
            }else
            {
                speed_x = 0;
                frame = 4;
                y_sprite = 1;
                qDebug()<<"DEAD";
                CurrentStatusGame = Dead;
                break;
            }
        }
    }
    //Взаимодействие с Ghost*/

    //Взаимодействие с объктами*/

    ///*Задание местоположения камеры
    ManagerCamera::getInstance()->GetCurrentCamera()->SetTargetX(GetPosX()-(Setting::GetViewPort().width()/2-GetScalX()/2));
    ManagerCamera::getInstance()->GetCurrentCamera()->SetTargetY(GetPosY()-(Setting::GetViewPort().height()/2-GetScalY()/2));
    //Задание местоположения камеры*/

    ///*Определение угла вращения Shoot
    if (count_bonus_shoot>0)
    {
        QVector3D center;
        center.setX(Setting::GetViewPort().width()/2);
        center.setY(Setting::GetViewPort().height()/2);
        //center.normalize();

        QVector3D mouse_pos;
        mouse_pos.setX(m_x); mouse_pos.setY(m_y);
        //mouse_pos.normalize();

        QVector3D res;
        res = mouse_pos - center;
        res.normalize();

        float dot = QVector3D::dotProduct(QVector3D(1, 0, 0), res);
        if (res.x()>0 && res.y()>0)
            rotation_shoot = acos(dot);
        if(res.x()>0 && res.y()<0)
            rotation_shoot = -acos(dot);

        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            ///*Выстрел пули
            QHash<QString, QString> prop;
            prop.insert("x", QString::number(res.x()));
            prop.insert("y", QString::number(res.y()));
            if ((res.x()>0 && res.y()>0) || (res.x()>0 && res.y()<0))
            {
                GameObject* bullet = new Bullet;
                bullet->SetPos(this->GetPos());
                bullet->SetRotZ(Geometry::RadianToDegree(rotation_shoot));
                bullet->SetScal(QVector3D(32, 16, 1));
                bullet->Init(prop);
                Resources::GAMESCENE()->GetValue("Level")->AddGameObject(bullet);
                count_bonus_shoot--;
            }
            //Выстрел пули*/
            Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
        }

    }
    //Определение угла вращения Shoot*/

    if (GetPosY()<=0)
    {
        speed_x = 0;
        frame = 4;
        y_sprite = 1;
        qDebug()<<"DEAD";
        CurrentStatusGame = Dead;
    }

    if (GetPosX()>=Resources::TILEMAP()->GetTileWidth()*Resources::TILEMAP()->GetTileCountWidth()-48)
    {
        speed_x = 0;
        qDebug()<<"FINISH";
        if ((PlayProfile::current_level+1)==PlayProfile::last_level)
            PlayProfile::last_level = PlayProfile::last_level + 1;
        CurrentStatusGame = Finish;
    }

    if (CurrentStatusGame!=Dead)
    {
        ///*Анимация
        frame+=0.08;
        if (frame>3)
            frame = 0;
        //Анимация*/

        if (count_bonus>0)
            y_sprite = 0;
        else
            y_sprite = 1;
    }

}

void Player::Draw()
{
    ///*Вывод текста
    Resources::FONT()->GetValue("green")->Draw("Score:"+QString::number(PlayProfile::score), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + 10,
                   Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 10);

    Resources::FONT()->GetValue("orange")->Draw("Level-"+QString::number(PlayProfile::current_level+1), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + Setting::GetViewPort().width()/2 - 50,
                   Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 10);

    ///*  :) балуемся с динамикой sprite :)
    if (count_bonus>0)
    {
        int tmp_id_tex = ManagerSprite::getInstance()->GetValue(id_sprite)->GetTextureKey();
        //qDebug()<<"id_tmp"<<tmp_id_tex;
        ManagerSprite::getInstance()->GetValue(id_sprite)->SetTextureKey(0);

        Transformer pos;
        pos.SetScal(QVector3D(32, 32, 1));
        pos.SetPos(QVector3D(Resources::CAMERA()->GetCurrentCamera()->GetPosX()+10,
                             Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 50 - 32, 0) );

        ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(32, 32, 1, 2);
        ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        pos.GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();


        ManagerSprite::getInstance()->GetValue(id_sprite)->SetTextureKey(tmp_id_tex);

        Resources::FONT()->GetValue("green")->Draw(" "+QString::number(count_bonus), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + 32 + 10,
                       Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 50);
    }
    //Отображение bonus_shoot
    if (count_bonus_shoot>0)
    {
        int tmp_id_tex = ManagerSprite::getInstance()->GetValue(id_sprite)->GetTextureKey();
        //qDebug()<<"id_tmp"<<tmp_id_tex;
        ManagerSprite::getInstance()->GetValue(id_sprite)->SetTextureKey(0);

        Transformer pos;
        pos.SetScal(QVector3D(32, 32, 1));
        pos.SetPos(QVector3D(Resources::CAMERA()->GetCurrentCamera()->GetPosX()+10,
                             Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 50 - 32, 0) );

        ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(32, 32, 2, 2);
        ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        pos.GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();


        ManagerSprite::getInstance()->GetValue(id_sprite)->SetTextureKey(tmp_id_tex);

        Resources::FONT()->GetValue("green")->Draw(" "+QString::number(count_bonus_shoot), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + 32 + 10,
                       Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 50);

    }
    //  :) балуемся с динамикой sprite :) */

    //Вывод текста*/

    ///*Вывод Player
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(this->GetScalX(), this->GetScalY(), qFloor(frame), y_sprite);
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Player*/

    ///*Вывод Shoot
    if (count_bonus_shoot>0)
    {
        Transformer tr;
        tr.SetScal(QVector3D(48, 24, 1));
        QVector3D tmp_pos = this->GetPos();
        tmp_pos.setX(tmp_pos.x()+24);
        tmp_pos.setY(tmp_pos.y()+24);
        //tmp_pos.setZ(1);
        tr.SetRotZ(Geometry::RadianToDegree(rotation_shoot));
        tr.SetPivot(QVector3D(0.2, 0.2, 0));
        tr.SetPos(tmp_pos);
        ///*Вывод Shoot
        ManagerSprite::getInstance()->GetValue(5)->Bind(48, 24);
        ManagerSprite::getInstance()->GetValue(5)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(5)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        tr.GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(5)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
        //Вывод Shoot*/
    }
    //Вывод Shoot*/

    ///*Вывод Close
    Transformer tr;
    tr.SetScal(QVector3D(58, 58, 0));
    tr.SetPos(QVector3D(Resources::CAMERA()->GetCurrentCamera()->GetPosX()+Setting::GetViewPort().width()-58-10,
                        Resources::CAMERA()->GetCurrentCamera()->GetPosY()+Setting::GetViewPort().height()-58-10, 0));
    ManagerSprite::getInstance()->GetValue(id_close)->Bind();
    ManagerSprite::getInstance()->GetValue(id_close)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_close)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    tr.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_close)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_close)->UnBind();
    //Вывод Close*/
}
