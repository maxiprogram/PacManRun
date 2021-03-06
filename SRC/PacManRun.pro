#-------------------------------------------------
#
# Project created by QtCreator 2015-02-09T20:47:45
#
#-------------------------------------------------

QT       += core gui
LIBS     += -L./lib -lsfml-system -lsfml-audio

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PacManRun
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainform.cpp \
    Engine/camera.cpp \
    Engine/creatorgameobject.cpp \
    Engine/fps.cpp \
    Engine/gameobject.cpp \
    Engine/gamescene.cpp \
    Engine/geometry.cpp \
    Engine/layer.cpp \
    Engine/managercamera.cpp \
    Engine/managergameobject.cpp \
    Engine/managerkeyboard.cpp \
    Engine/managermesh.cpp \
    Engine/managermouse.cpp \
    Engine/managershader.cpp \
    Engine/managersprite.cpp \
    Engine/managertexture.cpp \
    Engine/mesh.cpp \
    Engine/object3d.cpp \
    Engine/setting.cpp \
    Engine/shader.cpp \
    Engine/sprite.cpp \
    Engine/texture.cpp \
    Engine/transformer.cpp \
    player.cpp \
    creatorobject.cpp \
    Engine/tilemap.cpp \
    Engine/resources.cpp \
    statusgame.cpp \
    mainmenu.cpp \
    playprofile.cpp \
    Engine/font.cpp \
    pausegame.cpp \
    portal.cpp \
    Engine/managerfont.cpp \
    ghost.cpp \
    Engine/managergamescene.cpp \
    bullet.cpp \
    background.cpp \
    decor.cpp \
    particle.cpp \
    goal.cpp

HEADERS  += \
    mainform.h \
    Engine/camera.h \
    Engine/creatorgameobject.h \
    Engine/fps.h \
    Engine/gameobject.h \
    Engine/gamescene.h \
    Engine/geometry.h \
    Engine/layer.h \
    Engine/managercamera.h \
    Engine/managergameobject.h \
    Engine/managerkeyboard.h \
    Engine/managermesh.h \
    Engine/managermouse.h \
    Engine/managershader.h \
    Engine/managersprite.h \
    Engine/managertexture.h \
    Engine/mesh.h \
    Engine/object3d.h \
    Engine/setting.h \
    Engine/shader.h \
    Engine/sprite.h \
    Engine/texture.h \
    Engine/transformer.h \
    player.h \
    creatorobject.h \
    Engine/tilemap.h \
    Engine/resources.h \
    statusgame.h \
    mainmenu.h \
    playprofile.h \
    Engine/font.h \
    pausegame.h \
    portal.h \
    Engine/managerfont.h \
    ghost.h \
    Engine/managergamescene.h \
    bullet.h \
    background.h \
    decor.h \
    particle.h \
    goal.h

FORMS    +=

RESOURCES += \
    resources.qrc
