#ifndef FONT_H
#define FONT_H

#include <QFile>

#include "sprite.h"
#include "transformer.h"
#include "setting.h"
#include "managercamera.h"

class Font:public Sprite
{
public:
    Font();
    ~Font();
    void SetKerning(int kerning);
    int GetKerning();
    bool Load(QString filename);
    void Draw(QString text, int x = 0, int y = 0, int z = 1);
private:
    QHash<QChar, QRect> hash;
    int kerning;
};

#endif // FONT_H
