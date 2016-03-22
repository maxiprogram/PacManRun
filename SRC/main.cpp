#include <QApplication>
#include "mainform.h"

#include "playprofile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat surface;
    surface.setDepthBufferSize(24);

    MainForm w;
    w.setFormat(surface);

    ///*Загрузка информации об пройденных уровнях и очках
    PlayProfile::Load();
    //Загрузка информации об пройденных уровнях и очках*/

    if (PlayProfile::setting_fullscreen==0)
    {
        w.resize(800, 600);
        w.setMaximumSize(QSize(800, 600));
        w.setMinimumSize(QSize(800, 600));
        w.show();
    }else
    {
        w.showFullScreen();
    }

    //w.setAnimating(true);

    return a.exec();
}
