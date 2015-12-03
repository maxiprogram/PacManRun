#ifndef FONT_H
#define FONT_H

#include "sprite.h"

class Font:public Sprite
{
public:
    void SetWidthChar(int width);
    void SetHeightChar(int height);
    int GetWidthChar();
    int GetHeightChar();
    void DrawText(QString text, int x = 0, int y = 0);
private:
    int width_char;
    int height_char;
};

#endif // FONT_H
