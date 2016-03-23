#include "mainform.h"

CreatorObject* MainForm::CreateObject = 0;

MainForm::MainForm(QWindow *parent) :
    QWindow(parent),
    m_update_pending(false),
    m_animating(false),
    m_context(0),
    m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);


    GameScene* main_menu = new GameScene();
    GameScene* level = new GameScene();
    Resources::GAMESCENE()->Add("MainMenu", main_menu);
    Resources::GAMESCENE()->Add("Level", level);
}

MainForm::~MainForm()
{

    delete m_device;
}

void MainForm::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void MainForm::initialize()
{
    ///*Настройки экрана
    QMatrix4x4 proj;
    proj.setToIdentity();
    proj.ortho(0, this->width(), 0, this->height(), -10, 10);
    Setting::SetProjection(proj);
    Setting::SetViewPort(QRectF(0, 0, this->width(), this->height()));
    //Настройки экрана*/

    MainForm::CreateObject = new CreatorObject();
    ///*Загрузка главного меню
    if (!Resources::GAMESCENE()->GetValue("MainMenu")->Load("Resources/main_menu.xml", MainForm::CreateObject))
        qDebug()<<"Not Load MainMenu";
    //Загрузка главного меню*/

    //Таймер обновления логики игры win=40fps lin=30fps
    id_timer = this->startTimer(1000/40);

}

void MainForm::timerEvent(QTimerEvent *t)
{
    Q_UNUSED(t);
    m_context->makeCurrent(this);

    //Явный FPS
    this->setTitle("FPS="+QString::number(Resources::FPS()->GetFps()) +
                   " X="+QString::number(Resources::MOUSE()->GetX()) +
                   " Y="+QString::number(Setting::GetViewPort().height()-Resources::MOUSE()->GetY())
                   );

    ///*Альфа смешивание
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //*/
    //glEnable(GL_ALPHA_TEST);

    ///*Буфер глубины(QSurfaceFormat.setDepthBufferSize(24);)
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glDepthMask(GL_TRUE);
    //Буфер глубины(QSurfaceFormat.setDepthBufferSize(24);)*/

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch(CurrentStatusGame)
    {
        case Load_Main_Menu:
        {
            qDebug()<<"CurrentStatusGame Load_Main_Menu";

            Resources::GAMESCENE()->GetValue("Level")->Clear();
            Resources::MESH()->Clear();
            Resources::SHADER()->Clear();
            Resources::SPRITE()->Clear();
            Resources::FONT()->Clear();
            Resources::TEXTURE()->Clear();
            Resources::CAMERA()->Clear();
            Resources::TILEMAP()->Clear();

            if (!Resources::GAMESCENE()->GetValue("MainMenu")->Load("Resources/main_menu.xml", MainForm::CreateObject))
                qDebug()<<"Not Load MainMenu";

            Resources::CAMERA()->SetCurrentCamera("MainMenuCamera");
            CurrentStatusGame = Level_Menu;
            break;
        }
        case Main_Menu:
        {
            qDebug()<<"CurrentStatusGame Main_Menu";
            Resources::GAMESCENE()->GetValue("MainMenu")->Update();
           Resources::GAMESCENE()->GetValue("MainMenu")->Draw();
            break;
        }
        case Level_Menu:
        {
            qDebug()<<"CurrentStatusGame Level_Menu1";
            Resources::GAMESCENE()->GetValue("MainMenu")->Update();
            Resources::GAMESCENE()->GetValue("MainMenu")->Draw();
            break;
        }
        case Setting_Menu:
        {
            qDebug()<<"CurrentStatusGame Setting_Menu";
            Resources::GAMESCENE()->GetValue("MainMenu")->Update();
            Resources::GAMESCENE()->GetValue("MainMenu")->Draw();
            break;
        }
        case Update_Setting:
        {
            if (PlayProfile::setting_fullscreen==1)
            {
                this->resize(QApplication::desktop()->width(), QApplication::desktop()->height());
                this->setMaximumSize(QSize(QApplication::desktop()->width(), QApplication::desktop()->height()));
                this->setMinimumSize(QSize(0, 0));
                this->showFullScreen();
                ///*Настройки экрана
                QMatrix4x4 proj;
                proj.setToIdentity();
                proj.ortho(0, this->width(), 0, this->height(), -10, 10);
                Setting::SetProjection(proj);
                Setting::SetViewPort(QRectF(0, 0, this->width(), this->height()));
                //Настройки экрана*/
            }else
            {
                this->resize(800, 600);
                this->setMaximumSize(QSize(800, 600));
                this->setMinimumSize(QSize(800, 600));
                this->show();
                ///*Настройки экрана
                QMatrix4x4 proj;
                proj.setToIdentity();
                proj.ortho(0, this->width(), 0, this->height(), -10, 10);
                Setting::SetProjection(proj);
                Setting::SetViewPort(QRectF(0, 0, this->width(), this->height()));
                //Настройки экрана*/
            }
            CurrentStatusGame = Main_Menu;
            break;
        }
        case Author_Menu:
        {
            qDebug()<<"CurrentStatusGame Author_Menu";
            Resources::GAMESCENE()->GetValue("MainMenu")->Update();
            Resources::GAMESCENE()->GetValue("MainMenu")->Draw();
            break;
        }
        case Load_Level:
        {
            qDebug()<<"CurrentStatusGame Load_Level";

            Resources::GAMESCENE()->GetValue("MainMenu")->Clear();
            Resources::GAMESCENE()->GetValue("Level")->Clear();
            Resources::MESH()->Clear();
            Resources::SHADER()->Clear();
            Resources::SPRITE()->Clear();
            Resources::FONT()->Clear();
            Resources::TEXTURE()->Clear();
            Resources::CAMERA()->Clear();
            Resources::TILEMAP()->Clear();

            if (!Resources::GAMESCENE()->GetValue("Level")->Load("Resources/level"+QString::number(PlayProfile::current_level)+".xml", MainForm::CreateObject))
                qDebug()<<"Not Load Level";
            Resources::CAMERA()->SetCurrentCamera("MainCamera");
            CurrentStatusGame = Play;
            qDebug()<<"CurrentStatusGame Play";
            break;
        }
        case Play:
        {
            qDebug()<<"CurrentStatusGame Play";

            Resources::GAMESCENE()->GetValue("Level")->Update(/*Fps::getInstance()->GetFps()/1000.0*/);
            Resources::TILEMAP()->Draw("Main", Resources::CAMERA()->GetCurrentCamera()->GetRect());
            Resources::GAMESCENE()->GetValue("Level")->Draw(Resources::CAMERA()->GetCurrentCamera()->GetRect());
            Resources::TILEMAP()->Draw("Object", Resources::CAMERA()->GetCurrentCamera()->GetRect());

            break;
        }
        case Dead:
        {
            qDebug()<<"CurrentStatusGame Dead";

            Resources::TILEMAP()->Draw("Main", Resources::CAMERA()->GetCurrentCamera()->GetRect());
            Resources::GAMESCENE()->GetValue("Level")->Draw(Resources::CAMERA()->GetCurrentCamera()->GetRect());
            Resources::TILEMAP()->Draw("Object", Resources::CAMERA()->GetCurrentCamera()->GetRect());

            Resources::GAMEOBJECT()->GetValue("Pause")->Update();
            Resources::GAMEOBJECT()->GetValue("Pause")->Draw();

            break;
        }
        case Finish:
        {
            qDebug()<<"CurrentStatusGame Finish";

            Resources::TILEMAP()->Draw("Main", Resources::CAMERA()->GetCurrentCamera()->GetRect());
            Resources::GAMESCENE()->GetValue("Level")->Draw(Resources::CAMERA()->GetCurrentCamera()->GetRect());
            Resources::TILEMAP()->Draw("Object", Resources::CAMERA()->GetCurrentCamera()->GetRect());

            Resources::GAMEOBJECT()->GetValue("Pause")->Update();
            Resources::GAMEOBJECT()->GetValue("Pause")->Draw();

            break;
        }
        case Pause:
        {
            qDebug()<<"CurrentStatusGame Pause";

            Resources::TILEMAP()->Draw("Main", Resources::CAMERA()->GetCurrentCamera()->GetRect());
            Resources::GAMESCENE()->GetValue("Level")->Draw(Resources::CAMERA()->GetCurrentCamera()->GetRect());
            Resources::TILEMAP()->Draw("Object", Resources::CAMERA()->GetCurrentCamera()->GetRect());

            Resources::GAMEOBJECT()->GetValue("Pause")->Update();
            Resources::GAMEOBJECT()->GetValue("Pause")->Draw();

            break;
        }
        case Exit:
        {
            qDebug()<<"CurrentStatusGame Exit";

            QEvent event_exit(QEvent::Close);
            QCoreApplication::sendEvent(this, &event_exit);
            return;
        }
    }

    m_context->swapBuffers(this);
}

void MainForm::render()
{

    if (!m_device)
        m_device = new QOpenGLPaintDevice();

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);

}

void MainForm::renderLater()
{
    if (!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool MainForm::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        //renderNow();
        return true;
    case QEvent::Close:
        qDebug()<<"Close()";
        PlayProfile::Save();
        this->killTimer(id_timer);
        Resources::DestroyResources();
        return QWindow::event(event);
    default:
        return QWindow::event(event);
    }
}

void MainForm::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void MainForm::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context)
    {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();
        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize)
    {      
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}

void MainForm::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}

void MainForm::mouseMoveEvent(QMouseEvent *event)
{
    Resources::MOUSE()->Update(event, false);
}

void MainForm::mousePressEvent(QMouseEvent *event)
{
    Resources::MOUSE()->Update(event, true);
}

void MainForm::mouseReleaseEvent(QMouseEvent *event)
{
    Resources::MOUSE()->Update(event, false);
}

void MainForm::keyPressEvent(QKeyEvent *key)
{
    Resources::KEYBOARD()->Update(key);
}

void MainForm::keyReleaseEvent(QKeyEvent *key)
{
    Resources::KEYBOARD()->Update(key, false);
}
