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
    ///*Глобальные Mesh и Shader
    Resources::MESH()->Add(0, new Mesh());
    Resources::MESH()->GetValue(0)->Create();
    Resources::SHADER()->Add(0, new Shader());
    //Глобальные Mesh и Shader*/

    MainForm::CreateObject = new CreatorObject();
    ///*Загрузка главного меню
    if (!main_menu.Load("Resources/main_menu.xml", MainForm::CreateObject))
        qDebug()<<"Not Load MainMenu";
    //Загрузка главного меню*/

    ///*Загрузка уровня
    if (!level.Load("Resources/level0_0.xml", MainForm::CreateObject))
        qDebug()<<"Not Load Level";
    //Загрузка уровня*/

    QMatrix4x4 proj;
    proj.setToIdentity();
    proj.ortho(0, this->width(), 0, this->height(), -1, 1);
    Setting::SetProjection(proj);
    Setting::SetViewPort(QRectF(0, 0, this->width(), this->height()));

    //Таймер обновления логики игры win=40fps lin=30fps
    id_timer = this->startTimer(1000/40);

}

void MainForm::timerEvent(QTimerEvent *t)
{
    m_context->makeCurrent(this);

    //Явный FPS
    this->setTitle("FPS="+QString::number(Resources::FPS()->GetFps()) +
                   " X="+QString::number(Resources::MOUSE()->GetX()) +
                   " Y="+QString::number(Setting::GetViewPort().height()-Resources::MOUSE()->GetY())
                   );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch(CurrentStatusGame)
    {
        case Main_Menu:
        {
            main_menu.Update();
            main_menu.Draw();
            break;
        }
        case Level_Menu1:
        {
            main_menu.Update();
            main_menu.Draw();
            break;
        }
        case Play:
        {
            level.Update(/*Fps::getInstance()->GetFps()/1000.0*/);
            Resources::TILEMAP()->Draw(Resources::CAMERA()->GetCurrentCamera()->GetRect());
            level.Draw(Resources::CAMERA()->GetCurrentCamera()->GetRect());
            break;
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

void MainForm::resizeEvent(QResizeEvent * event)
{

}
