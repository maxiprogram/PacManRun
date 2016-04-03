#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/gamescene.h"
#include "Engine/managerkeyboard.h"
#include "Engine/fps.h"
#include "Engine/font.h"

#include "playprofile.h"
#include "statusgame.h"
#include "portal.h"
#include "bullet.h"
#include "particle.h"

class Player:public GameObject
{
public:
    Player();
    ~Player();
    void Init(QHash<QString, QString> property);
    void Update(float dt=1);
    void Draw();
    QRectF GetBoundBox();
    void SetJolt(bool flag);
    int score;
private:
    enum _Status {OnGround, Jump, Down} Status;
    bool flag_jolt;
    int id_sprite;
    int id_close;
    float frame;
    QVector2D direction;
    float speed_x, speed_y;
    float accel_x, accel_y;
    int count_bonus;
    int count_bonus_shoot;
    int y_sprite;
    float rotation_shoot;
};

#endif // PLAYER_H
