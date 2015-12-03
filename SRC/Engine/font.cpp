#include "font.h"

void Font::SetWidthChar(int width)
{
    width_char = width;
}

void Font::SetHeightChar(int height)
{
    height_char = height;
}

int Font::GetWidthChar()
{
    return width_char;
}

int Font::GetHeightChar()
{
    return height_char;
}

void Font::DrawText(QString text, int x, int y)
{

}
