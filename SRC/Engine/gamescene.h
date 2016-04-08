#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

#include "managergameobject.h"
#include "managermesh.h"
#include "managershader.h"
#include "managertexture.h"
#include "managersprite.h"
#include "managerfont.h"
#include "tilemap.h"
#include "creatorgameobject.h"

class GameScene
{
public:
    GameScene();
    ~GameScene();
    void AddGameObject(GameObject* object);
    void DeleteGameObject(GameObject* object, bool scene=false);
    bool Load(QString filename, CreatorGameObject* creator);
    void Update(float dt=1);
    void Draw();
    void Draw(QRectF rect);
    void Clear();
private:
    QList <QMultiHash<QString, GameObject*>::iterator> list_it;

};

#endif // GAMESCENE_H
