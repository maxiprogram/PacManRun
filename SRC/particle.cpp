#include "particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
    qDebug()<<"Destroy ~Particle";
}

void Particle::Init(QHash<QString, QString> property)
{
    id_sprite = property.value("id_sprite").toInt();
    time_life = property.value("time_life").toFloat();
    velocity.setX(property.value("vel_x").toFloat());
    velocity.setY(property.value("vel_y").toFloat());

    time.start();
}

void Particle::Update(float dt)
{
    if (time_life<0)
    {
        Resources::GAMESCENE()->GetValue("Level")->DeleteGameObject(this);
    }else
    {
        this->MovePos(velocity);
        time_life -= time.elapsed();
    }
}

void Particle::Draw()
{
    glDepthMask(false);
    ///*Вывод Particle
    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(this->GetScalX(), this->GetScalY());
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
    //Вывод Particle*/
    glDepthMask(true);
}
