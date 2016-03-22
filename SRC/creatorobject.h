#ifndef CREATOROBJECT_H
#define CREATOROBJECT_H

#include "Engine/creatorgameobject.h"

#include "player.h"
#include "mainmenu.h"
#include "pausegame.h"
#include "portal.h"
#include "ghost.h"
#include "background.h"

enum Type_GameObject {Hero=0, MainMenuObject=1, PauseObject=2, PortalObject=3, GhostObject=4, BackGroundObject=5};

class CreatorObject:public CreatorGameObject
{
public:
    CreatorObject();
    GameObject* CreateGameObject(uint type);
};

#endif // CREATOROBJECT_H
