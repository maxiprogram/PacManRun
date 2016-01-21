#ifndef FONT_H
#define FONT_H

#include <QFile>

#include "sprite.h"
#include "transformer.h"
#include "setting.h"
#include "managercamera.h"

struct CharInfo
{
    int x;
    int y;
    int width;
    int height;
    int x_offset;
    int y_offset;
};

class Font:public Sprite
{
public:
    Font();
    ~Font();
    void SetKerning(int kerning);
    int GetKerning();
    bool Load(QString filename);
    void Draw(QString text, int x = 0, int y = 0, int z = 0);
private:
    QHash<QChar, CharInfo> hash;
    int kerning;
};

#endif // FONT_H
