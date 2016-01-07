#ifndef MAINFORM_H
#define MAINFORM_H

#include <QCoreApplication>
#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QTime>

#include "Engine/resources.h"

#include "creatorobject.h"
#include "statusgame.h"
#include "playprofile.h"

#include "Engine/font.h"

class MainForm : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MainForm(QWindow *parent = 0);
    ~MainForm();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();
    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent* key);
    void keyReleaseEvent(QKeyEvent* key);

    void timerEvent(QTimerEvent* t);

private:
    bool m_update_pending;
    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;

    GameScene level;
    GameScene main_menu;
    static CreatorObject* CreateObject;

    QTime time;
    int id_timer;

    Font f;
};

#endif // MAINFORM_H
