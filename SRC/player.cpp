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

void Player::SetJolt(bool flag)
{
    flag_jolt = flag;
}

void Player::Init(QHash<QString, QString> property)
{
    this->SetScalX(property.value("scal_x").toFloat());
    this->SetScalY(property.value("scal_y").toFloat());
    this->SetPosX(property.value("pos_x").toFloat());
    this->SetPosY(property.value("pos_y").toFloat());
    this->SetPosZ(0.1);
    id_sprite = property.value("id_sprite").toInt();
    id_close = property.value("id_close").toInt();
    speed_x = property.value("speed_x").toFloat();
    accel_y = property.value("accel_y").toFloat();
    speed_y = 15;
    accel_x = 0;

    ///*Load Sound
    if (!buffer_jump.loadFromFile("Resources/jump.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'jump.ogg'!");
    }
    sound_jump.setBuffer(buffer_jump);

    if (!buffer_spring.loadFromFile("Resources/spring.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'spring.ogg'!");
    }
    sound_spring.setBuffer(buffer_spring);

    if (!buffer_bonus.loadFromFile("Resources/bonus.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'bonus.ogg'!");
    }
    sound_bonus.setBuffer(buffer_bonus);

    if (!buffer_kill.loadFromFile("Resources/kill.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'kill.ogg'!");
    }
    sound_kill.setBuffer(buffer_kill);

    if (!buffer_score.loadFromFile("Resources/score.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'score.ogg'!");
    }
    sound_score.setBuffer(buffer_score);

    if (!buffer_death.loadFromFile("Resources/death.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'death.ogg'!");
    }
    sound_death.setBuffer(buffer_death);

    if (!buffer_portal.loadFromFile("Resources/portal.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'portal.ogg'!");
    }
    sound_portal.setBuffer(buffer_portal);

    if (!buffer_brick.loadFromFile("Resources/brick.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'brick.ogg'!");
    }
    sound_brick.setBuffer(buffer_brick);

    if (!buffer_win.loadFromFile("Resources/win.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'win.ogg'!");
    }
    sound_win.setBuffer(buffer_win);
    //Load Sound*/

    direction.setX(0);
    direction.setY(0);
    Status = Down;
    count_bonus = 0;
    count_bonus_shoot = 0;
    rotation_shoot = 0;
    y_sprite = 1;
    flag_jolt = false;
    score = 0;

    Resources::FONT()->GetValue("green")->SetKerning(1);
    Resources::FONT()->GetValue("orange")->SetKerning(1);

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

        sound_jump.play();

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
                score++;
                sound_score.play();
            }
        }
        //Если шип
        if (tiles.at(i).id==16 || tiles.at(i).id==17 || tiles.at(i).id==18 || tiles.at(i).id==22 || tiles.at(i).id==23 || tiles.at(i).id==24)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                speed_x = 0;
                frame = 4;
                y_sprite = 1;
                sound_death.play();
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
                sound_spring.play();
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
                        sound_portal.play();
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
                sound_bonus.play();
            }
        }
        //Если разрушающая земля
        if (tiles.at(i).id==20)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                sound_brick.play();
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
                sound_kill.play();

                for (int j=0; j<100; j++)
                {
                    ///*Particle
                    QHash<QString, QString> prop;
                    prop.insert("id_sprite", QString::number(16));
                    prop.insert("time_life", QString::number(qrand()%15000));
                    prop.insert("width", QString::number(qrand()%32));
                    prop.insert("height", QString::number(qrand()%32));

                    float angle = qrand()%360;
                    float speed = qrand()%10;
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
            }else
            {
                speed_x = 0;
                frame = 4;
                y_sprite = 1;
                sound_death.play();
                qDebug()<<"DEAD";
                CurrentStatusGame = Dead;
                break;
            }
        }
    }
    //Взаимодействие с Ghost*/

    //Взаимодействие с объктами*/

    ///*Задание местоположения камеры
    int width_x = Resources::TILEMAP()->GetTileCountWidth() * 32;
    if (ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX()<width_x-Setting::GetViewPort().width())
    {
        ManagerCamera::getInstance()->GetCurrentCamera()->SetTargetX(GetPosX()-(Setting::GetViewPort().width()/2-GetScalX()/2));
        if (PlayProfile::current_level==14 || PlayProfile::current_level==20 || PlayProfile::current_level==21 || PlayProfile::current_level==22 || PlayProfile::current_level==23 || PlayProfile::current_level==24)
            ManagerCamera::getInstance()->GetCurrentCamera()->SetTargetY(GetPosY()-(Setting::GetViewPort().height()/2-GetScalY()/2));

    }
    //Тряска камеры
    if (flag_jolt)
    {
        //qDebug()<<"Jolt"<<qrand()%20-10<<qrand()%20-10;
        ManagerCamera::getInstance()->GetCurrentCamera()->SetTargetX(GetPosX()-(Setting::GetViewPort().width()/2-GetScalX()/2)+qrand()%20-10);
        ManagerCamera::getInstance()->GetCurrentCamera()->SetTargetY(GetPosY()-(Setting::GetViewPort().height()/2-GetScalY()/2)+qrand()%20-10);
    }
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
        if (res.x()<0 && res.y()>0)
            rotation_shoot = Geometry::DegreeToRadian(180) - acos(dot);
        if (res.x()<0 && res.y()<0)
            rotation_shoot = Geometry::DegreeToRadian(180) + acos(dot);

        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            ///*Выстрел пули
            QHash<QString, QString> prop;
            if ((res.x()<0 && res.y()>0) || (res.x()<0 && res.y()<0))
            {
                res.setX(fabs(res.x()));
            }
            prop.insert("x", QString::number(res.x()));
            prop.insert("y", QString::number(res.y()));
            GameObject* bullet = new Bullet;
            QVector3D pos_bullet = this->GetPos();
            pos_bullet.setX(pos_bullet.x()+24);
            pos_bullet.setY(pos_bullet.y()+24);
            pos_bullet.setZ(0.15);
            bullet->SetPos(pos_bullet);
            bullet->SetRotZ(Geometry::RadianToDegree(rotation_shoot));
            bullet->SetScal(QVector3D(48, 16, 1));

            bullet->Init(prop);
            Resources::GAMESCENE()->GetValue("Level")->AddGameObject(bullet);
            count_bonus_shoot--;
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
        sound_death.play();
        qDebug()<<"DEAD";
        CurrentStatusGame = Dead;
    }

    if (GetPosX()>=Resources::TILEMAP()->GetTileWidth()*Resources::TILEMAP()->GetTileCountWidth()-48)
    {
        speed_x = 0;
        qDebug()<<"FINISH";
        sound_win.play();
        //qDebug()<<"ScorePlan="<<PlayProfile::score_plan[PlayProfile::current_level]<<"ScorePrev="<<PlayProfile::score[PlayProfile::current_level];
        if ((PlayProfile::current_level+1)==PlayProfile::last_level)
            PlayProfile::last_level = PlayProfile::last_level + 1;
        if (PlayProfile::score[PlayProfile::current_level]<score)
            PlayProfile::score[PlayProfile::current_level] = score;
        PlayProfile::Save();
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
    Resources::FONT()->GetValue("green")->Draw("Score:"+QString::number(score), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + 10,
                   Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 10, 1);

    Resources::FONT()->GetValue("orange")->Draw("Level-"+QString::number(PlayProfile::current_level+1), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + Setting::GetViewPort().width()/2 - 50,
                   Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 10, 1);

    ///*  :) балуемся с динамикой sprite :)
    if (count_bonus>0)
    {
        int tmp_id_tex = ManagerSprite::getInstance()->GetValue(id_sprite)->GetTextureKey();
        //qDebug()<<"id_tmp"<<tmp_id_tex;
        ManagerSprite::getInstance()->GetValue(id_sprite)->SetTextureKey(0);

        Transformer pos;
        pos.SetScal(QVector3D(32, 32, 1));
        pos.SetPos(QVector3D(Resources::CAMERA()->GetCurrentCamera()->GetPosX()+10,
                             Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 50 - 32, 1) );

        ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(32, 32, 1, 3);
        ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        pos.GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();


        ManagerSprite::getInstance()->GetValue(id_sprite)->SetTextureKey(tmp_id_tex);

        Resources::FONT()->GetValue("green")->Draw(" "+QString::number(count_bonus), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + 32 + 10,
                       Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 50, 1);
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
                             Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 50 - 32, 1) );

        ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(32, 32, 2, 3);
        ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        pos.GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();


        ManagerSprite::getInstance()->GetValue(id_sprite)->SetTextureKey(tmp_id_tex);

        Resources::FONT()->GetValue("green")->Draw(" "+QString::number(count_bonus_shoot), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + 32 + 10,
                       Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 50, 1);

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
        tmp_pos.setZ(0.2);
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
                        Resources::CAMERA()->GetCurrentCamera()->GetPosY()+Setting::GetViewPort().height()-58-10, 1));
    ManagerSprite::getInstance()->GetValue(id_close)->Bind();
    ManagerSprite::getInstance()->GetValue(id_close)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_close)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    tr.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_close)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_close)->UnBind();
    //Вывод Close*/
}
