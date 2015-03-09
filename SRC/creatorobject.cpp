#include "creatorobject.h"

CreatorObject::CreatorObject()
{
}

GameObject* CreatorObject::CreateGameObject(uint type)
{
    type = (Type_GameObject)type;
    switch (type)
    {
    case Hero:
    {
        return new Player();
        break;
    }

    default:{return 0;break;}
    }
}
