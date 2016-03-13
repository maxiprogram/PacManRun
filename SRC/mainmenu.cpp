#include "mainmenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
    qDebug()<<"Destroy ~MainMenu";
}

void MainMenu::Init(QHash<QString, QString> property)
{
    id_button = property.value("id_button").toInt();
    id_header = property.value("id_header").toInt();
    id_level_menu1 = property.value("id_level_menu1").toInt();
    id_level_menu2 = property.value("id_level_menu2").toInt();
    id_level_menu3 = property.value("id_level_menu3").toInt();
    id_item_back = property.value("id_item_back").toInt();
    id_item_next = property.value("id_item_next").toInt();
    id_item_lock = property.value("id_item_lock").toInt();
    id_player = property.value("id_player").toInt();
    id_button_apply = property.value("id_button_apply").toInt();
    id_header_menu = property.value("id_header_menu").toInt();
    id_checkbox = property.value("id_checkbox").toInt();

    SetPivot(QVector3D(0.5, 0.5, 0));
    SetPos(QVector3D(0, 0, 0));

    mas_pos[0].setX(206);
    mas_pos[0].setY(463);
    mas_pos[1].setX(398);
    mas_pos[1].setY(463);
    mas_pos[2].setX(591);
    mas_pos[2].setY(463);

    mas_pos[3].setX(206);
    mas_pos[3].setY(300);
    mas_pos[4].setX(398);
    mas_pos[4].setY(300);
    mas_pos[5].setX(591);
    mas_pos[5].setY(300);

    mas_pos[6].setX(206);
    mas_pos[6].setY(138);
    mas_pos[7].setX(398);
    mas_pos[7].setY(138);
    mas_pos[8].setX(591);
    mas_pos[8].setY(138);

    flag_header= 0;
    pos_y_header = Setting::GetViewPort().height()+62;
    frame_player = 0;
    pos_x_player = -200;
    pos_y_author = -200;

    checkbox_fullscreen = 1;
    checkbox_sound = 1;

    current_level_menu = 1;
}

void MainMenu::Update(float dt)
{
    int m_x = Resources::MOUSE()->GetX();
    int m_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();

    ///*Если сейчас в главном меню
    if (CurrentStatusGame==Main_Menu)
    {
        pos_y_header -= 1;
        if (pos_y_header<=(Setting::GetViewPort().height()-62))
        {
                pos_y_header = Setting::GetViewPort().height()-62;
                flag_header = 1;
        }

        if (flag_header==1)
        {
            frame_player += 0.09;
            if (frame_player>3)
                frame_player = 0;

            pos_x_player += 6;
            if (pos_x_player>(Setting::GetViewPort().width()+200))
                    pos_x_player = -200;
        }

        ///*Если нажата мышка
        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            ///*Если нажата на Play
            if (m_x>(Setting::GetViewPort().width()/2-279/2) && m_x<(Setting::GetViewPort().width()/2+279/2))
            {
                if (m_y>Setting::GetViewPort().height()/2+100-72/2 && m_y<Setting::GetViewPort().height()/2+100+72/2)
                {
                    CurrentStatusGame = Level_Menu;
                    //PlayProfile::last_level = 7; //УБРАТЬ ЭТО ДЛЯ ТЕСТА
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Play*/

            ///*Если нажата на Setting
            if (m_x>(Setting::GetViewPort().width()/2-279/2) && m_x<(Setting::GetViewPort().width()/2+279/2))
            {
                if (m_y>Setting::GetViewPort().height()/2-72/2 && m_y<Setting::GetViewPort().height()/2+72/2)
                {
                    checkbox_fullscreen = PlayProfile::setting_fullscreen;
                    CurrentStatusGame = Setting_Menu;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Setting*/

            ///*Если нажата на Author
            if (m_x>(Setting::GetViewPort().width()/2-279/2) && m_x<(Setting::GetViewPort().width()/2+279/2))
            {
                if (m_y>Setting::GetViewPort().height()/2-100-72/2 && m_y<Setting::GetViewPort().height()/2-100+72/2)
                {
                    pos_y_author = -200;
                    CurrentStatusGame = Author_Menu;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Author*/

            ///*Если нажата на Exit
            if (m_x>(Setting::GetViewPort().width()/2-279/2) && m_x<(Setting::GetViewPort().width()/2+279/2))
            {
                if (m_y>Setting::GetViewPort().height()/2-200-72/2 && m_y<Setting::GetViewPort().height()/2-200+72/2)
                {
                    CurrentStatusGame = Exit;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Exit*/
        }
        //Если нажата мышка*/
    }
    //Если сейчас в главном меню*/

    ///*Если сейчас в меню выбора уровня
    if (CurrentStatusGame==Level_Menu)
    {
        if (Resources::KEYBOARD()->GetKey(Qt::Key_Escape))
        {
            CurrentStatusGame = Main_Menu;
        }
        ///*Если нажата мышка
        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            int m_x = Resources::MOUSE()->GetX();
            int m_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();
            if (m_x<120 && m_y<80)
            {
                if (current_level_menu==1)
                {
                    CurrentStatusGame = Main_Menu;
                    Resources::KEYBOARD()->SetKey(Qt::Key_Escape, false);
                }else
                {
                    current_level_menu--;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }else
            if (m_x>Setting::GetViewPort().width()-120 && m_y<80)
            {
                if (current_level_menu!=3 && PlayProfile::last_level>(current_level_menu*9))
                {
                    current_level_menu++;
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }else
            {
                int start_lock = 0;
                int inc = 0;
                if (current_level_menu==1)
                {
                    inc = 0;
                    if (PlayProfile::last_level>=9)
                        start_lock = 9;
                    else
                        start_lock = PlayProfile::last_level;
                }
                if (current_level_menu==2)
                {
                    inc = 9;
                    if (PlayProfile::last_level>=18)
                        start_lock = 9;
                    else
                        start_lock = PlayProfile::last_level - 9;
                }
                if (current_level_menu==3)
                {
                    inc = 18;
                    if (PlayProfile::last_level>=27)
                        start_lock = 9;
                    else
                        start_lock = PlayProfile::last_level - 18;
                }

                bool flag = false;
                for (int i=0; i<start_lock; i++)
                {
                    int tmp_x = mas_pos[i].x()+(Setting::GetViewPort().width()-800)/2;
                    int tmp_y = mas_pos[i].y()+(Setting::GetViewPort().height()-600)/2;
                    if (m_x<tmp_x+50 && m_x>tmp_x-50 && m_y<tmp_y+51 && m_y>tmp_y-51)
                    {
                        flag = true;
                        PlayProfile::current_level = (i + inc);
                    }
                }
                if (flag)
                {
                    CurrentStatusGame = Load_Level;
                    qDebug()<<"SELECT LEVEL:"<<PlayProfile::current_level;
                }
            }
        }
        //Если нажата мышка*/
    }
    //Если сейчас в меню выбора уровня*/

    ///*Если сейчас в меню настроек
    if (CurrentStatusGame==Setting_Menu)
    {
        if (Resources::KEYBOARD()->GetKey(Qt::Key_Escape))
        {
            CurrentStatusGame = Main_Menu;
            Resources::KEYBOARD()->SetKey(Qt::Key_Escape, false);
        }
        ///*Если нажата мышка
        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            int m_x = Resources::MOUSE()->GetX();
            int m_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();
            if (m_x<120 && m_y<80) //Стрелка назад
            {
                CurrentStatusGame = Main_Menu;
                Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
            }else
            if (m_x>Setting::GetViewPort().width()-120 && m_y<80) //Apply
            {
                //ОБРАБОТАТЬ СОХРАНЕНИЕ НАСТРОЕК
                PlayProfile::setting_fullscreen = checkbox_fullscreen;

                CurrentStatusGame = Update_Setting;
                Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
            }else
            //checkbox_fullscreen click
            if (m_x>Setting::GetViewPort().width()/2+50 && m_x<Setting::GetViewPort().width()/2+50+72 && m_y>Setting::GetViewPort().height()/2+75 && m_y<Setting::GetViewPort().height()/2+75+78)
            {
                if (checkbox_fullscreen==0)
                    checkbox_fullscreen = 1;
                else
                    checkbox_fullscreen = 0;
                Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
            }else
            //checkbox_sound click
            if (m_x>Setting::GetViewPort().width()/2+50 && m_x<Setting::GetViewPort().width()/2+50+72 && m_y>Setting::GetViewPort().height()/2-75 && m_y<Setting::GetViewPort().height()/2-75+78)
            {
                if (checkbox_sound==0)
                    checkbox_sound = 1;
                else
                    checkbox_sound = 0;
                Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
            }
        }
    }
    //Если сейчас в меню настроек*/

    ///*Если сейчас в меню Author
    if (CurrentStatusGame==Author_Menu)
    {
        if (pos_y_author<(Setting::GetViewPort().height()-120))
            pos_y_author += 5;

        if (Resources::KEYBOARD()->GetKey(Qt::Key_Escape))
        {
            CurrentStatusGame = Main_Menu;
            Resources::KEYBOARD()->SetKey(Qt::Key_Escape, false);
        }
        ///*Если нажата мышка
        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            int m_x = Resources::MOUSE()->GetX();
            int m_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();
            if (m_x<120 && m_y<80) //Стрелка назад
            {
                CurrentStatusGame = Main_Menu;
                Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
            }
        }
    }
    //Если сейчас в меню Author*/
}

void MainMenu::Draw()
{

    ///*Если сейчас в главном меню
    if (CurrentStatusGame==Main_Menu)
    {
        SetScal(QVector3D(660, 124, 0));
        ///*Вывод заголовка Header
        SetPos(QVector3D(Setting::GetViewPort().width()/2, pos_y_header/*Setting::GetViewPort().height()-62*/, 0));
        Resources::SPRITE()->GetValue(id_header)->Bind(GetScalX(), GetScalY(), 0, qFloor(flag_header));
        Resources::SPRITE()->GetValue(id_header)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_header)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_header)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_header)->UnBind();
        //Вывод заголовка Header*/

        SetScal(QVector3D(48, 48, 0));
        ///*Вывод Player
        SetPos(QVector3D(pos_x_player, Setting::GetViewPort().height()-128, 0));
        Resources::SPRITE()->GetValue(id_player)->Bind(GetScalX(), GetScalY(), qFloor(frame_player), 1);
        Resources::SPRITE()->GetValue(id_player)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_player)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_player)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_player)->UnBind();
        //Вывод Player*/

        SetScal(QVector3D(279, 72, 0));
        ///*Вывод кнопки Play
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2+100, 0));
        Resources::SPRITE()->GetValue(id_button)->Bind(GetScalX(), GetScalY(), 0, 3);
        Resources::SPRITE()->GetValue(id_button)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_button)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_button)->UnBind();
        //Вывод кнопки Play*/

        ///*Вывод кнопки Setting
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2, 0));
        Resources::SPRITE()->GetValue(id_button)->Bind(GetScalX(), GetScalY(), 0, 2);
        Resources::SPRITE()->GetValue(id_button)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_button)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_button)->UnBind();
        //Вывод кнопки Setting*/

        ///*Вывод кнопки Author
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2-100, 0));
        Resources::SPRITE()->GetValue(id_button)->Bind(GetScalX(), GetScalY(), 0, 1);
        Resources::SPRITE()->GetValue(id_button)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_button)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_button)->UnBind();
        //Вывод кнопки Author*/

        ///*Вывод кнопки Exit
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2-200, 0));
        Resources::SPRITE()->GetValue(id_button)->Bind(GetScalX(), GetScalY(), 0, 0);
        Resources::SPRITE()->GetValue(id_button)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_button)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_button)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_button)->UnBind();
        //Вывод кнопки Exit*/
    }
    //Если сейчас в главном меню*/

    ///*Если сейчас в меню выбора уровня
    if (CurrentStatusGame==Level_Menu)
    {
        int id_level = id_level_menu1;
        if (current_level_menu==1)
            id_level = id_level_menu1;
        else
        if (current_level_menu==2)
            id_level = id_level_menu2;
        else
        if (current_level_menu==3)
            id_level = id_level_menu3;

        SetScal(QVector3D(800, 600, 0));
        ///*Вывод Уровней
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2, 0));
        Resources::SPRITE()->GetValue(id_level)->Bind(GetScalX(), GetScalY());
        Resources::SPRITE()->GetValue(id_level)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_level)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_level)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_level)->UnBind();
        //Вывод Уровней*/

        SetScal(QVector3D(418, 124, 0));
        ///*Вывод заголовка Header_menu
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()-48, 0));
        Resources::SPRITE()->GetValue(id_header_menu)->Bind(GetScalX(), GetScalY(), 0, 2);
        Resources::SPRITE()->GetValue(id_header_menu)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_header_menu)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_header_menu)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_header_menu)->UnBind();
        //Вывод заголовка Header_menu*/

        ///*Вывод стрелки назад к главному меню
        SetScal(QVector3D(Resources::SPRITE()->GetValue(id_item_back)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(id_item_back)->GetTexture()->GetHeight(), 0));
        SetPos(QVector3D(60, 40, 0));
        Resources::SPRITE()->GetValue(id_item_back)->Bind(GetScalX(), GetScalY());
        Resources::SPRITE()->GetValue(id_item_back)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_item_back)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_item_back)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_item_back)->UnBind();
        //Вывод стрелки назад к главному меню*/

        ///*Вывод стрелки вперед к главному меню
        if (current_level_menu!=3 && PlayProfile::last_level>(current_level_menu*9))
        {
            SetScal(QVector3D(Resources::SPRITE()->GetValue(id_item_next)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(id_item_next)->GetTexture()->GetHeight(), 0));
            SetPos(QVector3D(Setting::GetViewPort().width()-60, 40, 0));
            Resources::SPRITE()->GetValue(id_item_next)->Bind(GetScalX(), GetScalY());
            Resources::SPRITE()->GetValue(id_item_next)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_item_next)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                   Setting::GetProjection() *
                                                                                   Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                                   this->GetMatrix()
                                                                                   );
            glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_item_next)->GetMesh()->GetCountVertex());
            Resources::SPRITE()->GetValue(id_item_next)->UnBind();
        }
        //Вывод стрелки вперед к главному меню*/


        ///*Вывод заблокированных уровней
        SetScal(QVector3D(Resources::SPRITE()->GetValue(id_item_lock)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(id_item_lock)->GetTexture()->GetHeight(), 0));
        //SetPivot(QVector3D(0.5, 0.5, 0.0));

        int start_lock = 0;
        if (current_level_menu==1)
        {
            if (PlayProfile::last_level>=9)
                start_lock = 9;
            else
                start_lock = PlayProfile::last_level;
        }
        if (current_level_menu==2)
        {
            if (PlayProfile::last_level>=18)
                start_lock = 9;
            else
                start_lock = PlayProfile::last_level - 9;
        }
        if (current_level_menu==3)
        {
            if (PlayProfile::last_level>=27)
                start_lock = 9;
            else
                start_lock = PlayProfile::last_level - 18;
        }

        for (int i=start_lock; i<9; i++)
        {
            SetPos(QVector3D(mas_pos[i].x()+(Setting::GetViewPort().width()-800)/2, mas_pos[i].y()+(Setting::GetViewPort().height()-600)/2, 0));
            Resources::SPRITE()->GetValue(id_item_lock)->Bind(GetScalX(), GetScalY());
            Resources::SPRITE()->GetValue(id_item_lock)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_item_lock)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                   Setting::GetProjection() *
                                                                                   Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                                   this->GetMatrix()
                                                                                   );
            glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_item_lock)->GetMesh()->GetCountVertex());
            Resources::SPRITE()->GetValue(id_item_lock)->UnBind();
        }
        //Вывод заблокированных уровней*/
    }
    //Если сейчас в меню выбора уровня*/


    ///*Если сейчас в меню настроек
    if (CurrentStatusGame==Setting_Menu)
    {
        SetScal(QVector3D(Resources::SPRITE()->GetValue(9)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(9)->GetTexture()->GetHeight(), 0));
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2, 0));
        Resources::SPRITE()->GetValue(9)->Bind();
        Resources::SPRITE()->GetValue(9)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(9)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(9)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(9)->UnBind();

        SetScal(QVector3D(418, 124, 0));
        ///*Вывод заголовка Header_menu
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()-62, 0));
        Resources::SPRITE()->GetValue(id_header_menu)->Bind(GetScalX(), GetScalY(), 0, 1);
        Resources::SPRITE()->GetValue(id_header_menu)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_header_menu)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_header_menu)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_header_menu)->UnBind();
        //Вывод заголовка Header_menu*/

        SetPivot(QVector3D(0, 0, 0));
        SetScal(QVector3D(72, 78, 0));
        ///*Вывод checkbox_fullscreen и checkbox_sound
        SetPos(QVector3D(Setting::GetViewPort().width()/2+50, Setting::GetViewPort().height()/2+75, 0));
        Resources::SPRITE()->GetValue(id_checkbox)->Bind(GetScalX(), GetScalY(), checkbox_fullscreen, 0);
        Resources::SPRITE()->GetValue(id_checkbox)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_checkbox)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_checkbox)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_checkbox)->UnBind();
        //--
        SetPos(QVector3D(Setting::GetViewPort().width()/2+50, Setting::GetViewPort().height()/2-75, 0));
        Resources::SPRITE()->GetValue(id_checkbox)->Bind(GetScalX(), GetScalY(), checkbox_sound, 0);
        Resources::SPRITE()->GetValue(id_checkbox)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_checkbox)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_checkbox)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_checkbox)->UnBind();
        //Вывод checkbox_fullscreen и checkbox_sound*/
        SetPivot(QVector3D(0.5, 0.5, 0));

        ///*Вывод стрелки назад в меню настроек
        SetScal(QVector3D(Resources::SPRITE()->GetValue(id_item_back)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(id_item_back)->GetTexture()->GetHeight(), 0));
        SetPos(QVector3D(60, 40, 0));
        Resources::SPRITE()->GetValue(id_item_back)->Bind(GetScalX(), GetScalY());
        Resources::SPRITE()->GetValue(id_item_back)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_item_back)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_item_back)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_item_back)->UnBind();
        //Вывод стрелки назад в меню настроек*/

        ///*Вывод кнопки Apply в меню настроек
        SetScal(QVector3D(Resources::SPRITE()->GetValue(id_button_apply)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(id_button_apply)->GetTexture()->GetHeight(), 0));
        SetPos(QVector3D(Setting::GetViewPort().width()-60, 40, 0));
        Resources::SPRITE()->GetValue(id_button_apply)->Bind(GetScalX(), GetScalY());
        Resources::SPRITE()->GetValue(id_button_apply)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_button_apply)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_button_apply)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_button_apply)->UnBind();
        //Вывод кнопки Apply в меню настроек*/
    }
    //Если сейчас в меню настроек*/

    ///*Если сейчас в меню Author
    if (CurrentStatusGame==Author_Menu)
    {
        SetScal(QVector3D(418, 124, 0));
        ///*Вывод заголовка Header_menu
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()-62, 0));
        Resources::SPRITE()->GetValue(id_header_menu)->Bind(GetScalX(), GetScalY(), 0, 0);
        Resources::SPRITE()->GetValue(id_header_menu)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_header_menu)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_header_menu)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_header_menu)->UnBind();
        //Вывод заголовка Header_menu*/

        ///*Вывод стрелки назад в меню Author
        SetScal(QVector3D(Resources::SPRITE()->GetValue(id_item_back)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(id_item_back)->GetTexture()->GetHeight(), 0));
        SetPos(QVector3D(60, 40, 0));
        Resources::SPRITE()->GetValue(id_item_back)->Bind(GetScalX(), GetScalY());
        Resources::SPRITE()->GetValue(id_item_back)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_item_back)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_item_back)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_item_back)->UnBind();
        //Вывод стрелки назад в меню Author*/

        ///*Вывод текста Author
        Resources::FONT()->GetValue("orange")->Draw("Developer this game:", (Setting::GetViewPort().width()/2)-(295/2), pos_y_author);
        Resources::FONT()->GetValue("green")->Draw("Tihonov Maxim", (Setting::GetViewPort().width()/2)-(210/2), pos_y_author-30);

        Resources::FONT()->GetValue("orange")->Draw("My site:", (Setting::GetViewPort().width()/2)-(116/2), pos_y_author-90);
        Resources::FONT()->GetValue("green")->Draw("http://maxiprogram.net", (Setting::GetViewPort().width()/2)-(324/2), pos_y_author-120);

        Resources::FONT()->GetValue("orange")->Draw("My e-mail:", (Setting::GetViewPort().width()/2)-(140/2), pos_y_author-190);
        Resources::FONT()->GetValue("green")->Draw("maxiprogram@gmail.com", (Setting::GetViewPort().width()/2)-(356/2), pos_y_author-220);

        Resources::FONT()->GetValue("orange")->Draw("Thank you very much:", (Setting::GetViewPort().width()/2)-(310/2), pos_y_author-290);
        Resources::FONT()->GetValue("green")->Draw("bla-bla", (Setting::GetViewPort().width()/2), pos_y_author-320);

        Resources::FONT()->GetValue("orange")->Draw("Thank you:", (Setting::GetViewPort().width()/2)-(154/2), pos_y_author-390);
        Resources::FONT()->GetValue("green")->Draw("bla-bla", (Setting::GetViewPort().width()/2), pos_y_author-420);
        //Вывод текста Author*/
    }
    //Если сейчас в меню Author*/
}
