#ifndef PORTAL_H
#define PORTAL_H

#include <Engine/resources.h>

class Portal: public GameObject
{
public:
    Portal();
    ~Portal();
    void Init(QHash<QString, QString> property);
    void Update(float dt=1);
    void Draw();
    QVector2D GetPosStart();
    QVector2D GetPosFinish();

private:
    QVector2D pos_start;
    QVector2D pos_finish;
};

#endif // PORTAL_H
