#include "portal.h"

Portal::Portal()
{
}

Portal::~Portal()
{
    qDebug()<<"Destroy ~Portal";
}

QVector2D Portal::GetPosStart()
{
    return pos_start;
}

QVector2D Portal::GetPosFinish()
{
    return pos_finish;
}

void Portal::Init(QHash<QString, QString> property)
{
    pos_start.setX(property.value("pos_i_start").toInt());
    pos_start.setY(property.value("pos_j_start").toInt());
    pos_finish.setX(property.value("pos_i_finish").toInt());
    pos_finish.setY(property.value("pos_j_finish").toInt());
}

void Portal::Update(float dt)
{

}

void Portal::Draw()
{

}
