#ifndef MANAGERGAMESCENE_H
#define MANAGERGAMESCENE_H

#include <QHash>
#include "gamescene.h"

#include <QDebug>

class ManagerGameScene
{
public:
    ManagerGameScene();
    ~ManagerGameScene();
    static ManagerGameScene* getInstance();
    void Add(QString key, GameScene* value);
    void Delete(QString key);
    GameScene* GetValue(QString key);
    QHash<QString, GameScene*>* GetHashTab();
    void Clear();
    void Destroy();

private:
    static ManagerGameScene* instance;
    QHash<QString, GameScene*> hash_tab;
};

#endif // MANAGERGAMESCENE_H
