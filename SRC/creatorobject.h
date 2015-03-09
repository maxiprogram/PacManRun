#ifndef CREATOROBJECT_H
#define CREATOROBJECT_H

#include "Engine/creatorgameobject.h"

#include "player.h"

enum Type_GameObject {Hero=0};

class CreatorObject:public CreatorGameObject
{
public:
    CreatorObject();
    GameObject* CreateGameObject(uint type);
};

#endif // CREATOROBJECT_H