#ifndef BULLET_H
#define BULLET_H

#include "Engine/resources.h"

#include "player.h"

class Bullet : public GameObject
{
public:
    Bullet();
    ~Bullet();
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();
private:
    int id_sprite;
    int id_sprite_fire;
    float frame, frame_y;
    float x, y;
    float speed;
    float distance;
    QVector3D start;
    bool flag_move;
};

#endif // BULLET_H
