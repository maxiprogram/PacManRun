#include "managerfont.h"

ManagerFont* ManagerFont::instance = 0;

ManagerFont::ManagerFont()
{
}

ManagerFont::~ManagerFont()
{
    Clear();
    qDebug()<<"~ManagerFont";
}

ManagerFont* ManagerFont::getInstance()
{
    if (!instance)
        instance = new ManagerFont();
    return instance;
}

void ManagerFont::Add(QString key, Font* value)
{
    hash_tab.insert(key, value);
}

void ManagerFont::Delete(QString key)
{
    Font* sprite = GetValue(key);
    delete sprite;
    hash_tab.remove(key);
}

Font* ManagerFont::GetValue(QString key)
{
    return hash_tab.value(key);
}

void ManagerFont::Clear()
{
    QHash<QString, Font*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerFont::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}

