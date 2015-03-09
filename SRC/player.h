#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/gamescene.h"
#include "Engine/managerkeyboard.h"
#include "Engine/fps.h"

class Player:public GameObject
{
public:
    Player();
    ~Player();
    void Init(QHash<QString, QString> property);
    void Update(float dt=1);
    void Draw();
    QRectF GetBoundBox();
private:
    int id_sprite;
    float frame;
    QVector2D direction;
    float speed_x, speed_y;
    float accel_x, accel_y;
    enum _Status {OnGround, Jump, Down, Dead} Status;
};

#endif // PLAYER_H
