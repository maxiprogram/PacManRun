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
    id_main_menu = property.value("id_main_menu").toInt();
    id_level_menu1 = property.value("id_level_menu1").toInt();
    id_item_back = property.value("id_item_back").toInt();
    id_item_lock = property.value("id_item_lock").toInt();
    SetPivot(QVector3D(0.5, 0.5, 0));
    SetPos(QVector3D(0, 0, 0));
}

void MainMenu::Update(float dt)
{
    int m_x = Resources::MOUSE()->GetX();
    int m_y = Setting::GetViewPort().height()-Resources::MOUSE()->GetY();

    ///*Если сейчас в главном меню
    if (CurrentStatusGame==Main_Menu)
    {
        ///*Если нажата мышка
        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            ///*Если нажата на Play
            if (m_x>(Setting::GetViewPort().width()/2-279/2) && m_x<(Setting::GetViewPort().width()/2+279/2))
            {
                if (m_y>Setting::GetViewPort().height()/2+100-72/2 && m_y<Setting::GetViewPort().height()/2+100+72/2)
                {
                    CurrentStatusGame = Level_Menu1;
                    PlayProfile::last_level = 2; //УБРАТЬ ЭТО ДЛЯ ТЕСТА
                    Resources::MOUSE()->Update(Resources::MOUSE()->GetEvent(),false);
                }
            }
            //Если нажата на Play*/
        }
        //Если нажата мышка*/
    }
    //Если сейчас в главном меню*/

    ///*Если сейчас в меню1 выбора уровня
    if (CurrentStatusGame==Level_Menu1)
    {
        ///*Если нажата мышка
        if (Resources::MOUSE()->GetButton()==Qt::LeftButton)
        {
            CurrentStatusGame = Play;
        }
        //Если нажата мышка*/
    }
    //Если сейчас в меню1 выбора уровня*/
}

void MainMenu::Draw()
{
    ///*Если сейчас в главном меню
    if (CurrentStatusGame==Main_Menu)
    {
        SetScal(QVector3D(279, 72, 0));
        ///*Вывод кнопки Play
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2+100, 0));
        Resources::SPRITE()->GetValue(id_main_menu)->Bind(GetScalX(), GetScalY(), 0, 3);
        Resources::SPRITE()->GetValue(id_main_menu)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_main_menu)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_main_menu)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_main_menu)->UnBind();
        //Вывод кнопки Play*/

        ///*Вывод кнопки Setting
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2, 0));
        Resources::SPRITE()->GetValue(id_main_menu)->Bind(GetScalX(), GetScalY(), 0, 2);
        Resources::SPRITE()->GetValue(id_main_menu)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_main_menu)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_main_menu)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_main_menu)->UnBind();
        //Вывод кнопки Setting*/

        ///*Вывод кнопки Author
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2-100, 0));
        Resources::SPRITE()->GetValue(id_main_menu)->Bind(GetScalX(), GetScalY(), 0, 1);
        Resources::SPRITE()->GetValue(id_main_menu)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_main_menu)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_main_menu)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_main_menu)->UnBind();
        //Вывод кнопки Author*/

        ///*Вывод кнопки Exit
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2-200, 0));
        Resources::SPRITE()->GetValue(id_main_menu)->Bind(GetScalX(), GetScalY(), 0, 0);
        Resources::SPRITE()->GetValue(id_main_menu)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_main_menu)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_main_menu)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_main_menu)->UnBind();
        //Вывод кнопки Exit*/
    }
    //Если сейчас в главном меню*/

    ///*Если сейчас в меню1 выбора уровня
    if (CurrentStatusGame==Level_Menu1)
    {
        SetScal(QVector3D(800, 600, 0));
        ///*Вывод Уровней
        SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2, 0));
        Resources::SPRITE()->GetValue(id_level_menu1)->Bind(GetScalX(), GetScalY());
        Resources::SPRITE()->GetValue(id_level_menu1)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_level_menu1)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_level_menu1)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_level_menu1)->UnBind();
        //Вывод Уровней*/

        ///*Вывод стрелки назад к главному меню
        SetScal(QVector3D(Resources::SPRITE()->GetValue(id_item_back)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(id_item_back)->GetTexture()->GetHeight(), 0));
        SetPos(QVector3D(75, 50, 0));
        Resources::SPRITE()->GetValue(id_item_back)->Bind(GetScalX(), GetScalY());
        Resources::SPRITE()->GetValue(id_item_back)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_item_back)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                               Setting::GetProjection() *
                                                                               Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                               this->GetMatrix()
                                                                               );
        glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_item_back)->GetMesh()->GetCountVertex());
        Resources::SPRITE()->GetValue(id_item_back)->UnBind();
        //Вывод стрелки назад к главному меню*/


        ///*Вывод заблокированных уровней
        SetScal(QVector3D(Resources::SPRITE()->GetValue(id_item_lock)->GetTexture()->GetWidth(), Resources::SPRITE()->GetValue(id_item_lock)->GetTexture()->GetHeight(), 0));

        for (int i=PlayProfile::last_level; i<9; i++)
        {
            int tmp_x = (i%3)*240+133;
            int tmp_y = 600-((i/3)*180+120);
            SetPos(QVector3D(tmp_x, tmp_y, 0));
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
    //Если сейчас в меню1 выбора уровня*/
}
