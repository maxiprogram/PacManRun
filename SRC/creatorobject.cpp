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
    case MainMenuObject:
    {
        return new MainMenu();
        break;
    }
    case PauseObject:
    {
        return new PauseGame();
        break;
    }
    case PortalObject:
    {
        return new Portal();
        break;
    }
    case GhostObject:
    {
        return new Ghost();
        break;
    }
    case BackGroundObject:
    {
        return new BackGround();
        break;
    }

    default:{return 0;break;}
    }
}
