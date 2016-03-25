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
    void SetCountFrame(int count);
private:
    int id_sprite;
    float atlas_x, atlas_y;
    int width, height;

    float frame;
    int count_frame;
};

#endif // DECOR_H
