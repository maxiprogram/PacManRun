#ifndef DECOR_H
#define DECOR_H

#include "Engine/resources.h"

class Decor : public GameObject
{
public:
    Decor();
    ~Decor();
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();

private:
    int id_sprite;
};

#endif // DECOR_H
