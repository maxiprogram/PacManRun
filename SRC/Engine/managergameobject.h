#ifndef MANAGERGAMEOBJECT_H
#define MANAGERGAMEOBJECT_H

#include <QHash>
#include <QDebug>
#include "gameobject.h"

class ManagerGameObject
{
public:
    ManagerGameObject();
    ~ManagerGameObject();
    static ManagerGameObject* getInstance();
    QMultiHash<QString,GameObject*>::iterator Add(QString key, GameObject* value);
    GameObject* GetValue(QString key);
    QList<GameObject*> GetValues(QString key);
    QMultiHash<QString, GameObject*>* GetHashTab();
    void Clear();
    void Destroy();

private:
    static ManagerGameObject* instance;
    QMultiHash<QString, GameObject*> hash_tab;
};

#endif // MANAGERGAMEOBJECT_H
