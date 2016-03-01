#include "resources.h"

Resources::Resources()
{
}

Fps* Resources::FPS()
{
    return Fps::getInstance();
}

ManagerKeyboard* Resources::KEYBOARD()
{
    return ManagerKeyboard::getInstance();
}

ManagerMouse* Resources::MOUSE()
{
    return ManagerMouse::getInstance();
}

ManagerMesh* Resources::MESH()
{
    return ManagerMesh::getInstance();
}

ManagerShader* Resources::SHADER()
{
    return ManagerShader::getInstance();
}

ManagerTexture* Resources::TEXTURE()
{
    return ManagerTexture::getInstance();
}

ManagerSprite* Resources::SPRITE()
{
    return ManagerSprite::getInstance();
}

ManagerFont* Resources::FONT()
{
    return ManagerFont::getInstance();
}

TileMap* Resources::TILEMAP()
{
    return TileMap::getInstance();
}

ManagerGameObject* Resources::GAMEOBJECT()
{
    return ManagerGameObject::getInstance();
}

ManagerGameScene* Resources::GAMESCENE()
{
    return ManagerGameScene::getInstance();
}

ManagerCamera* Resources::CAMERA()
{
    return ManagerCamera::getInstance();
}

void Resources::DestroyResources()
{
    TileMap::getInstance()->Destroy();

    ManagerCamera::getInstance()->Destroy();
    ManagerGameScene::getInstance()->Destroy();
    ManagerGameObject::getInstance()->Destroy();

    ManagerFont::getInstance()->Destroy();
    ManagerSprite::getInstance()->Destroy();
    ManagerTexture::getInstance()->Destroy();
    ManagerMesh::getInstance()->Destroy();
    ManagerShader::getInstance()->Destroy();

    Fps::getInstance()->Destroy();
    ManagerKeyboard::getInstance()->Destroy();
    ManagerMouse::getInstance()->Destroy();
}
