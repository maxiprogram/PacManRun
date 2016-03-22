#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Engine/resources.h"

class BackGround : public GameObject
{
public:
    BackGround();
    ~BackGround();
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();
private:
    int id_sprite;
};

#endif // BACKGROUND_H
