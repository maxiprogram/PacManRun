#include "managershader.h"

ManagerShader* ManagerShader::instance = 0;

ManagerShader::ManagerShader()
{
}

ManagerShader::~ManagerShader()
{
    Clear();
    qDebug()<<"~ManagerShader";
}

ManagerShader* ManagerShader::getInstance()
{
    if (!instance)
        instance = new ManagerShader();
    return instance;
}

void ManagerShader::Add(int key, Shader* value)
{
    hash_tab.insert(key, value);
}

void ManagerShader::Delete(int key)
{
    Shader* shader = GetValue(key);
    delete shader;
    hash_tab.remove(key);
}

Shader* ManagerShader::GetValue(int key)
{
    return hash_tab.value(key);
}

QHash<int, Shader*>* ManagerShader::GetHash()
{
    return &hash_tab;
}

void ManagerShader::Clear()
{
    QHash<int, Shader*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerShader::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}
