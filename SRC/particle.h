#ifndef PARTICLE_H
#define PARTICLE_H

#include <QTime>

#include "Engine/resources.h"

class Particle : public GameObject
{
public:
    Particle();
    ~Particle();
    void Init(QHash<QString, QString> property);
    void Update(float dt = 1);
    void Draw();

private:
    int id_sprite;
    float time_life;
    QVector3D velocity;
    QTime time;
};

#endif // PARTICLE_H
