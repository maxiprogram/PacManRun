#ifndef GHOST_H
#define GHOST_H

#include "Engine/gamescene.h"

class Ghost: public GameObject
{
public:
    Ghost();
    ~Ghost();
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();

private:
    int id_sprite;
    float frame;
    float radius;
    float speed_x;
    float speed_y;
    QVector2D start_pos;
    QVector2D direction;
};

#endif // GHOST_H
