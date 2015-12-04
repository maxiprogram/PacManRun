#include "font.h"

Font::Font()
{
    width_char = height_char = 32;
}

Font::~Font()
{

}

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

void Font::Draw(QString text, int x, int y)
{
    int frameX, frameY;
    for (int i=0; i<text.length(); i++)
    {
        ushort s = text.at(i).unicode();
        if ((s>=32 && s<=122) || (s>=1040 && s<=1103))
        {
            frameX = s-31;
            int count_col = texture->GetWidth()/width_char;
            frameY = frameX/count_col;
            frameX = frameX%(frameY*count_col);
            qDebug()<<"Font frameX="<<frameX-1<<"frameY="<<frameY;
            //Bind(width_char, height_char, frameX, frameY);
        }
    }

}
