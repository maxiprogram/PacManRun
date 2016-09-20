#ifndef GOAL_H
#define GOAL_H

#include "Engine/gamescene.h"

class Goal: public GameObject
{
public:
    Goal();
    ~Goal();
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();

public:
    QString list_x;
    QString list_y;
    int value_tile;

private:
    int id_sprite;

};

#endif // GOAL_H
