#include "managertexture.h"

ManagerTexture* ManagerTexture::instance = 0;

ManagerTexture::ManagerTexture()
{
}

ManagerTexture::~ManagerTexture()
{
    Clear();
    qDebug()<<"~ManagerTexture";
}

ManagerTexture* ManagerTexture::getInstance()
{
    if (!instance)
        instance = new ManagerTexture();
    return instance;
}

void ManagerTexture::Add(int key, Texture* value)
{
    hash_tab.insert(key, value);
}

void ManagerTexture::Delete(int key)
{
    Texture* texture = GetValue(key);
    delete texture;
    hash_tab.remove(key);
}

Texture* ManagerTexture::GetValue(int key)
{
    return hash_tab.value(key);
}

QHash<int, Texture*>* ManagerTexture::GetHash()
{
    return &hash_tab;
}

void ManagerTexture::Clear()
{
    QHash<int, Texture*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerTexture::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}

