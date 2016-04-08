#ifndef MANAGERTEXTURE_H
#define MANAGERTEXTURE_H

#include "texture.h"

class ManagerTexture
{
public:
    ManagerTexture();
    ~ManagerTexture();
    static ManagerTexture* getInstance();
    void Add(int key, Texture* value);
    void Delete(int key);
    Texture* GetValue(int key);
    QHash<int, Texture*>* GetHash();
    void Clear();
    void Destroy();

private:
    static ManagerTexture* instance;
    QHash<int, Texture*> hash_tab;
};

#endif // MANAGERTEXTURE_H
