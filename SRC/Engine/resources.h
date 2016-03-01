#ifndef RESOURCES_H
#define RESOURCES_H

#include "fps.h"
#include "managerkeyboard.h"
#include "managermouse.h"
#include "managermesh.h"
#include "managershader.h"
#include "managertexture.h"
#include "managersprite.h"
#include "managerfont.h"
#include "tilemap.h"
#include "managergameobject.h"
#include "managergamescene.h"
#include "managercamera.h"


class Resources
{
public:
    Resources();
    static Fps* FPS();
    static ManagerKeyboard* KEYBOARD();
    static ManagerMouse* MOUSE();
    static ManagerMesh* MESH();
    static ManagerShader* SHADER();
    static ManagerTexture* TEXTURE();
    static ManagerSprite* SPRITE();
    static ManagerFont* FONT();
    static TileMap* TILEMAP();
    static ManagerGameObject* GAMEOBJECT();
    static ManagerGameScene* GAMESCENE();
    static ManagerCamera* CAMERA();

    static void DestroyResources();
};

#endif // RESOURCES_H
