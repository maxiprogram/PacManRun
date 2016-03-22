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
    SetPivot(QVector3D(0.5, 0.5, 0));

    time_pause_dead = 1 * 40;//2 секунд при fps 40
}

void PauseGame::Update(float dt)
{
    int m_x = Resources::MOUSE()->GetX();
    int m_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();

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
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+200, 0));
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
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY(), 0));
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
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()-80, 0));
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
    //Если стату Dead*/

    ///*Если стату Finish
    if (CurrentStatusGame==Finish)
    {
        ///*Вывод заголовка Pause
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+200, 0));
        SetScal(QVector3D(256, 50, 0));
        ManagerSprite::getInstance()->GetValue(id_header)->Bind(256, 50, 0, 2);
        ManagerSprite::getInstance()->GetValue(id_header)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_header)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                        Setting::GetProjection() *
                                                                                        ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                        this->GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_header)->GetMesh()->GetCountVertex());
        ManagerSprite::getInstance()->GetValue(id_header)->UnBind();
        //Вывод заголовка Pause*/


        ///*Вывод кнопки Continue
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()+80, 0));
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
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY(), 0));
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
        SetPos(QVector3D(Setting::GetViewPort().width()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosX(), Setting::GetViewPort().height()/2+ManagerCamera::getInstance()->GetCurrentCamera()->GetPosY()-80, 0));
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
