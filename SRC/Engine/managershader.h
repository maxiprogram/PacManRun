#ifndef MANAGERSHADER_H
#define MANAGERSHADER_H

#include "shader.h"

class ManagerShader
{
public:
    ManagerShader();
    ~ManagerShader();
    static ManagerShader* getInstance();
    void Add(int key, Shader* value);
    void Delete(int key);
    Shader* GetValue(int key);
    QHash<int, Shader*>* GetHash();
    void Clear();
    void Destroy();

private:
    static ManagerShader* instance;
    QHash<int, Shader*> hash_tab;
};

#endif // MANAGERSHADER_H
