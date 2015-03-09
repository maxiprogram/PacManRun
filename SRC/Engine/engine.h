#ifndef ENGINE_H
#define ENGINE_H


#include <QObject>
#include <QString>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMatrix4x4>
#include <QVector3D>
#include <QDebug>

#include "Engine/fps.h"
#include "Engine/managerkeyboard.h"
#include "Engine/managermouse.h"

#include "Engine/transformer.h"
#include "Engine/gameobject.h"
#include "Engine/creatorgameobject.h"



//#include "Engine/camera.h"
//#include "Engine/gamescene.h"
//#include "Engine/geometry.h"
//#include "Engine/layer.h"
//#include "Engine/managercamera.h"
//#include "Engine/managergameobject.h"
//#include "Engine/managermesh.h"
//#include "Engine/managershader.h"
//#include "Engine/managersprite.h"
//#include "Engine/managertexture.h"
//#include "Engine/mesh.h"
//#include "Engine/object3d.h"
//#include "Engine/setting.h"
//#include "Engine/shader.h"
//#include "Engine/sprite.h"
//#include "Engine/texture.h"
//#include "Engine/tilemap.h"

namespace QtEngineGL
{
    class Fps;
    class ManagerKeyboard;
    class ManagerMouse;
    class Transformer;
    class GameObject;
    class CreatorGameObject;
}


#endif // ENGINE_H
