#include "pausegame.h"

PauseGame::PauseGame()
{

}

PauseGame::~PauseGame()
{

}

void PauseGame::Init(QHash<QString, QString> property)
{
    id_header = property.value("id_header").toInt();
    id_button = property.value("id_button").toInt();
    id_blood = property.value("id_blood").toInt();
    id_cherry = property.value("id_cherry").toInt();
    SetPivot(QVector3D(0.5, 0.5, 0));

    time_pause_dead = 1 * 40;//2 секунд при fps 40

    if (!background_music.openFromFile("Resources/background_play.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'background_play.ogg'!");
    }
    background_music.setLoop(true);
    background_music.setVolume(50);

    if (!background_music1.openFromFile("Resources/background_play1.ogg"))
    {
        QMessageBox::critical(0, "Error load file", "Error load file 'background_play1.ogg'!");
    }
    background_music1.setLoop(true);
    background_music1.setVolume(50);
}

void PauseGame::Update(float dt)
{
    int m_x = Resources::MOUSE()->GetX();
    int m_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();

    ///*Если стату Play
    if (CurrentStatusGame==Play && PlayProfile::current_level!=15 && PlayProfile::current_level!=16 && PlayProfile::current_level!=17)
    {
        if (PlayProfile::setting_sound==0)
            background_music.stop();
        else
            if (background_music.getStatus()!=2)
                background_music.play();
            /*if (background_music.getStatus()==1)
            {
                background_music.play();
            }else
            if (background_music.getStatus()!=2)
            {
                int rnd = qrand()%220;
                //QMessageBox::information(0, "qrand", QString::number(rnd));
                background_music.play();
                sf::Time pos = background_music.getPlayingOffset() + sf::seconds(rnd);
                background_music.setPlayingOffset(sf::Time(pos));
            }*/
    }else
        if (CurrentStatusGame==Play && PlayProfile::current_level>=15 && PlayProfile::current_level<=17)
        {
            if (PlayProfile::setting_sound==0)
                background_music1.stop();
            else
                if (background_music1.getStatus()!=2)
                    background_music1.play();
        }else
    {
        background_music.pause();
        background_music1.pause();
    }
    //Если стату Pause*/

    ///*Если стату Pause
    if (CurrentStatusGame==Pause)
    {
        if (Resources::KEYBOARD()->GetKey(Qt::Key_Escape))
        {
            CurrentStatusGame = Play;
            Resources::KEYBOARD()->SetKey(Qt::Key_Escape, false);
        }

        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            ///*Если нажата на Continue
            if (m_x>(Setting::GetViewPort().width()/2-100) && m_x<(Setting::GetViewPort().width()/2+100))
            {
                if (m_y>Setting::GetViewPort().height()/2+80-39/2 && m_y<Setting::GetViewPort().height()/2+80+39/2)
                {
                    CurrentStatusGame = Play;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Continue*/

            ///*Если нажата на Restart
            if (m_x>(Setting::GetViewPort().width()/2-100) && m_x<(Setting::GetViewPort().width()/2+100))
            {
                if (m_y>Setting::GetViewPort().height()/2-39/2 && m_y<Setting::GetViewPort().height()/2+39/2)
                {
                    CurrentStatusGame = Load_Level;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Restart*/

            ///*Если нажата на Main menu
            if (m_x>(Setting::GetViewPort().width()/2-100) && m_x<(Setting::GetViewPort().width()/2+100))
            {
                if (m_y>Setting::GetViewPort().height()/2-80-39/2 && m_y<Setting::GetViewPort().height()/2-80+39/2)
                {
                    CurrentStatusGame = Load_Main_Menu;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Main menu*/
        }
    }
    //Если стату Pause*/

    ///*Если стату Dead
    if (CurrentStatusGame==Dead)
    {
//        if (time_pause_dead==40)
//        {
//            for (int j=0; j<100; j++)
//            {
//                ///*Particle
//                QHash<QString, QString> prop;
//                prop.insert("id_sprite", QString::number(16));
//                prop.insert("time_life", QString::number(qrand()%15000));
//                prop.insert("width", QString::number(qrand()%32));
//                prop.insert("height", QString::number(qrand()%32));

//                float angle = qrand()%360;
//                float speed = qrand()%10;
//                Transformer tr;
//                tr.SetRotZ(angle);
//                QVector3D vel;
//                vel.setX(1);
//                vel.setY(0);
//                vel = vel * tr.GetMatrix();
//                vel.normalize();
//                vel = vel * speed;
//                prop.insert("vel_x", QString::number(vel.x()));
//                prop.insert("vel_y", QString::number(vel.y()));

//                GameObject* part = new Particle;
//                QVector3D pos_particle = Resources::GAMEOBJECT()->GetValue("Player")->GetPos();
//                pos_particle.setX(pos_particle.x()+24);
//                pos_particle.setY(pos_particle.y()+24);
//                pos_particle.setZ(0.14);
//                part->SetPos(pos_particle);
//                part->SetRotZ(Geometry::RadianToDegree(qrand()%360));
//                part->SetScal(QVector3D(16, 16, 1));

//                part->Init(prop);
//                Resources::GAMESCENE()->GetValue("Level")->AddGameObject(part);
//                //Particle*/
//            }
//        }

        if (time_pause_dead>0)
            time_pause_dead--;

        if (time_pause_dead==0)
        {
            if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
            {
                ///*Если нажата на Restart
                if (m_x>(Setting::GetViewPort().width()/2-100) && m_x<(Setting::GetViewPort().width()/2+100))
                {
                    if (m_y>Setting::GetViewPort().height()/2-39/2 && m_y<Setting::GetViewPort().height()/2+39/2)
                    {
                        CurrentStatusGame = Load_Level;
                        Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                    }
                }
                //Если нажата на Restart*/

                ///*Если нажата на Main menu
                if (m_x>(Setting::GetViewPort().width()/2-100) && m_x<(Setting::GetViewPort().width()/2+100))
                {
                    if (m_y>Setting::GetViewPort().height()/2-80-39/2 && m_y<Setting::GetViewPort().height()/2-80+39/2)
                    {
                        CurrentStatusGame = Load_Main_Menu;
                        Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                    }
                }
                //Если нажата на Main menu*/
            }
        }
    }
    //Если стату Dead*/

    ///*Если стату Finish
    if (CurrentStatusGame==Finish)
    {
        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            ///*Если нажата на Continue
            if (m_x>(Setting::GetViewPort().width()/2-100) && m_x<(Setting::GetViewPort().width()/2+100))
            {
                if (m_y>Setting::GetViewPort().height()/2+80-39/2 && m_y<Setting::GetViewPort().height()/2+80+39/2)
                {
                    PlayProfile::current_level = PlayProfile::current_level + 1;
                    CurrentStatusGame = Load_Level;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Continue*/

            ///*Если нажата на Restart
            if (m_x>(Setting::GetViewPort().width()/2-100) && m_x<(Setting::GetViewPort().width()/2+100))
            {
                if (m_y>Setting::GetViewPort().height()/2-39/2 && m_y<Setting::GetViewPort().height()/2+39/2)
                {
                    CurrentStatusGame = Load_Level;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Restart*/

            ///*Если нажата на Main menu
            if (m_x>(Setting::GetViewPort().width()/2-100) && m_x<(Setting::GetViewPort().width()/2+100))
            {
                if (m_y>Setting::GetViewPort().height()/2-80-39/2 && m_y<Setting::GetViewPort().height()/2-80+39/2)
                {
                    CurrentStatusGame = Load_Main_Menu;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Main menu*/
        }
    }
    //Если стату Finish*/


}

void PauseGame::Draw()
{
    if (CurrentStatusGame==Pause)
    {
        ///*Вывод заголовка Pause
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+200, 1));
        SetScal(QVector3D(256, 50, 0));
        ManagerSprite::getInstance()->GetValue(id_header)->Bind(256, 50, 0, 0);
        ManagerSprite::getInstance()->GetValue(id_header)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_header)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_header)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_header)->UnBind();
        //Вывод заголовка Pause*/


        ///*Вывод кнопки Continue
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+80, 1));
        SetScal(QVector3D(201, 39, 0));
        ManagerSprite::getInstance()->GetValue(id_button)->Bind(201, 39, 0, 2);
        ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_button)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_button)->UnBind();
        //Вывод кнопки Continue*/

        ///*Вывод кнопки Restart
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY(), 1));
        SetScal(QVector3D(201, 39, 0));
        ManagerSprite::getInstance()->GetValue(id_button)->Bind(201, 39, 0, 1);
        ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_button)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_button)->UnBind();
        //Вывод кнопки Restart*/

        ///*Вывод кнопки Main menu
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()-80, 1));
        SetScal(QVector3D(201, 39, 0));
        ManagerSprite::getInstance()->GetValue(id_button)->Bind(201, 39, 0, 0);
        ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_button)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_button)->UnBind();
        //Вывод кнопки Main menu*/
    }

    ///*Если стату Dead
    if (CurrentStatusGame==Dead && time_pause_dead==0)
    {
        ///*Вывод заголовка Game over
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+200, 1));
        SetScal(QVector3D(256, 50, 0));
        ManagerSprite::getInstance()->GetValue(id_header)->Bind(256, 50, 0, 1);
        ManagerSprite::getInstance()->GetValue(id_header)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_header)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_header)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_header)->UnBind();
        //Вывод заголовка Game Over*/

        ///*Вывод кнопки Restart
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY(), 1));
        SetScal(QVector3D(201, 39, 0));
        ManagerSprite::getInstance()->GetValue(id_button)->Bind(201, 39, 0, 1);
        ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_button)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_button)->UnBind();
        //Вывод кнопки Restart*/

        ///*Вывод кнопки Main menu
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()-80, 1));
        SetScal(QVector3D(201, 39, 0));
        ManagerSprite::getInstance()->GetValue(id_button)->Bind(201, 39, 0, 0);
        ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_button)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_button)->UnBind();
        //Вывод кнопки Main menu*/

        ///*Вывод Blood
        //SetPivot(QVector3D(0, 0, 0));
        SetPos(QVector3D(Setting::GetViewPort().width()/4+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY(), 1.1));
        SetScal(QVector3D(132, Setting::GetViewPort().height(), 1));
        ManagerSprite::getInstance()->GetValue(id_blood)->Bind(132, 207);
        ManagerSprite::getInstance()->GetValue(id_blood)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_blood)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_blood)->GetMesh()->GetCountVertex());

        SetPos(QVector3D(Setting::GetViewPort().width()/2+Setting::GetViewPort().width()/4+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY(), 1.1));
        SetScal(QVector3D(132, Setting::GetViewPort().height(), 1));
        ManagerSprite::getInstance()->GetValue(id_blood)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_blood)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_blood)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_blood)->UnBind();
        //Вывод кнопки Blood*/
    }
    //Если стату Dead*/

    ///*Если стату Finish
    if (CurrentStatusGame==Finish)
    {
        ///*Вывод заголовка Pause
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+200, 1));
        SetScal(QVector3D(256, 50, 0));
        ManagerSprite::getInstance()->GetValue(id_header)->Bind(256, 50, 0, 2);
        ManagerSprite::getInstance()->GetValue(id_header)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_header)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_header)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_header)->UnBind();
        //Вывод заголовка Pause*/

        ///*Вывод Cherry
        Player* player = (Player*)Resources::GAMEOBJECT()->GetValue("Player");
        int score = player->score;
        int procent = score*1.0/PlayProfile::score_plan[PlayProfile::current_level]*100;
        //qDebug()<<"Plan="<<PlayProfile::score_plan[PlayProfile::current_level]<<"Current="<<PlayProfile::score[PlayProfile::current_level];
        //qDebug()<<"Score="<<score<<"Procent="<<procent;
        if (score>0)
        {
            SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX()-100, Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+140, 1));
            SetScal(QVector3D(64, 64, 0));
            ManagerSprite::getInstance()->GetValue(id_cherry)->Bind();
            ManagerSprite::getInstance()->GetValue(id_cherry)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_cherry)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                            Setting::GetProjection() *
                                                                                            ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                            this->GetMatrix());
            glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_cherry)->GetMesh()->GetCountVertex());
            ManagerSprite::getInstance()->GetValue(id_cherry)->UnBind();
        }

        if (procent>=60)
        {
            SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+140, 1));
            SetScal(QVector3D(64, 64, 0));
            ManagerSprite::getInstance()->GetValue(id_cherry)->Bind();
            ManagerSprite::getInstance()->GetValue(id_cherry)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_cherry)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                            Setting::GetProjection() *
                                                                                            ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                            this->GetMatrix());
            glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_cherry)->GetMesh()->GetCountVertex());
            ManagerSprite::getInstance()->GetValue(id_cherry)->UnBind();
        }

        if (procent>=80)
        {
            SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX()+100, Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+140, 1));
            SetScal(QVector3D(64, 64, 0));
            ManagerSprite::getInstance()->GetValue(id_cherry)->Bind();
            ManagerSprite::getInstance()->GetValue(id_cherry)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_cherry)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                            Setting::GetProjection() *
                                                                                            ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                            this->GetMatrix());
            glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_cherry)->GetMesh()->GetCountVertex());
            ManagerSprite::getInstance()->GetValue(id_cherry)->UnBind();
        }
        //Вывод Cherry*/

        ///*Вывод кнопки Continue
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+80, 1));
        SetScal(QVector3D(201, 39, 0));
        ManagerSprite::getInstance()->GetValue(id_button)->Bind(201, 39, 0, 2);
        ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_button)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_button)->UnBind();
        //Вывод кнопки Continue*/

        ///*Вывод кнопки Restart
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY(), 1));
        SetScal(QVector3D(201, 39, 0));
        ManagerSprite::getInstance()->GetValue(id_button)->Bind(201, 39, 0, 1);
        ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_button)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_button)->UnBind();
        //Вывод кнопки Restart*/

        ///*Вывод кнопки Main menu
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()-80, 1));
        SetScal(QVector3D(201, 39, 0));
        ManagerSprite::getInstance()->GetValue(id_button)->Bind(201, 39, 0, 0);
        ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_button)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_button)->UnBind();
        //Вывод кнопки Main menu*/
    }
    //Если стату Finish*/
}
