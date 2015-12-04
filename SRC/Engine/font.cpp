#include "font.h"

Font::Font()
{
    width_char = 30;
    height_char = 39;
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

void Font::Draw(QString text, int x, int y, int z)
{
    int frameX, frameY;
    for (int i=0; i<text.length(); i++)
    {
        ushort s = text.at(i).unicode();
        if ((s>=32 && s<=122) || (s>=1040 && s<=1103))
        {
            if (s>=32 && s<=122)
                frameX = s-31;
            if (s>=1040 && s<=1103)
                frameX = s-1039;
            int count_col = texture->GetWidth()/width_char;
            int count_row = texture->GetHeight()/height_char;
            frameY = frameX/count_col;
            frameX = frameX%count_col;
            if (frameX==0)
            {
                frameX = count_col;
                frameY--;
            }
            qDebug()<<"Font frameX="<<frameX-1<<"frameY="<<frameY<<"key"<<s;
            Transformer tr;
            tr.SetScal(QVector3D(30, 39, 1));
            tr.SetPos(QVector3D(x, y, z));

            Bind(width_char, height_char, frameX-1, frameY);
            GetShader()->setUniformValue(GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix()*tr.GetMatrix());
            glDrawArrays(GL_TRIANGLES, 0, GetMesh()->GetCountVertex());
            UnBind();
            x+=30;
        }
    }

}
