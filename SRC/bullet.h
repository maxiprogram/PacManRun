#ifndef BULLET_H
#define BULLET_H

#include "Engine/resources.h"

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
    float frame;
    float x, y;
    float speed;
    float distance;
    QVector3D start;
};

#endif // BULLET_H
