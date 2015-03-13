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
    id_sprite = property.value("id_sprite").toInt();
    SetScal(QVector3D(279, 72, 0));
    SetPivot(QVector3D(0.5, 0.5, 0));
    SetPos(QVector3D(0, 0, 0));
}

void MainMenu::Update(float dt)
{

}

void MainMenu::Draw()
{
    ///*Вывод кнопки Play
    SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2+100, 0));
    Resources::SPRITE()->GetValue(id_sprite)->Bind(GetScalX(), GetScalY(), 0, 3);
    Resources::SPRITE()->GetValue(id_sprite)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                           Setting::GetProjection() *
                                                                           Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                           this->GetMatrix()
                                                                           );
    glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    Resources::SPRITE()->GetValue(id_sprite)->UnBind();
    //Вывод кнопки Play*/

    ///*Вывод кнопки Setting
    SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2, 0));
    Resources::SPRITE()->GetValue(id_sprite)->Bind(GetScalX(), GetScalY(), 0, 2);
    Resources::SPRITE()->GetValue(id_sprite)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                           Setting::GetProjection() *
                                                                           Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                           this->GetMatrix()
                                                                           );
    glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    Resources::SPRITE()->GetValue(id_sprite)->UnBind();
    //Вывод кнопки Setting*/

    ///*Вывод кнопки Author
    SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2-100, 0));
    Resources::SPRITE()->GetValue(id_sprite)->Bind(GetScalX(), GetScalY(), 0, 1);
    Resources::SPRITE()->GetValue(id_sprite)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                           Setting::GetProjection() *
                                                                           Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                           this->GetMatrix()
                                                                           );
    glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    Resources::SPRITE()->GetValue(id_sprite)->UnBind();
    //Вывод кнопки Author*/

    ///*Вывод кнопки Exit
    SetPos(QVector3D(Setting::GetViewPort().width()/2, Setting::GetViewPort().height()/2-200, 0));
    Resources::SPRITE()->GetValue(id_sprite)->Bind(GetScalX(), GetScalY(), 0, 0);
    Resources::SPRITE()->GetValue(id_sprite)->GetShader()->setUniformValue(Resources::SPRITE()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                           Setting::GetProjection() *
                                                                           Resources::CAMERA()->GetCurrentCamera()->GetMatrix() *
                                                                           this->GetMatrix()
                                                                           );
    glDrawArrays(GL_TRIANGLES, 0, Resources::SPRITE()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    Resources::SPRITE()->GetValue(id_sprite)->UnBind();
    //Вывод кнопки Exit*/
}
