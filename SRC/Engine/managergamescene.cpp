#include "managergamescene.h"

ManagerGameScene* ManagerGameScene::instance = 0;

ManagerGameScene::ManagerGameScene()
{
}

ManagerGameScene::~ManagerGameScene()
{
    Clear();
    qDebug()<<"~ManagerGameScene";
}

ManagerGameScene* ManagerGameScene::getInstance()
{
    if (!instance)
        instance = new ManagerGameScene();
    return instance;
}

void ManagerGameScene::Add(QString key, GameScene* value)
{
    hash_tab.insert(key, value);
}

void ManagerGameScene::Delete(QString key)
{
    GameScene* scene = GetValue(key);
    scene->Clear();
    delete scene;
    hash_tab.remove(key);
}

GameScene* ManagerGameScene::GetValue(QString key)
{
    return hash_tab.value(key);
}

QHash<QString, GameScene*>* ManagerGameScene::GetHashTab()
{
    return &hash_tab;
}

void ManagerGameScene::Clear()
{
    QHash<QString, GameScene*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerGameScene::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}
