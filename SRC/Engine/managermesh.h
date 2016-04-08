#ifndef MANAGERMESH_H
#define MANAGERMESH_H

#include "mesh.h"

class ManagerMesh
{
public:
    ManagerMesh();
    ~ManagerMesh();
    static ManagerMesh* getInstance();
    void Add(int key, Mesh* value);
    void Delete(int key);
    Mesh* GetValue(int key);
    QHash<int, Mesh*>* GetHash();
    void Clear();
    void Destroy();

private:
    static ManagerMesh* instance;
    QHash<int, Mesh*> hash_tab;
};

#endif // MANAGERMESH_H
