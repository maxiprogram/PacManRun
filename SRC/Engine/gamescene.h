#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

#include "resources.h"
#include "creatorgameobject.h"

class GameScene
{
public:
    GameScene();
    bool Load(QString filename, CreatorGameObject* creator);
    void Update(float dt=1);
    void Draw();
    void Draw(QRectF rect);
    void Clear();
private:
    QHash<QString, GameObject*> hash_tab;
};

#endif // GAMESCENE_H
