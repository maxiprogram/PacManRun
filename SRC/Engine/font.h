#ifndef FONT_H
#define FONT_H

#include "sprite.h"
#include "transformer.h"
#include "setting.h"
#include "managercamera.h"

class Font:public Sprite
{
public:
    Font();
    ~Font();
    void SetWidthChar(int width);
    void SetHeightChar(int height);
    int GetWidthChar();
    int GetHeightChar();
    void Draw(QString text, int x = 0, int y = 0, int z = 1);
private:
    int width_char;
    int height_char;
};

#endif // FONT_H
