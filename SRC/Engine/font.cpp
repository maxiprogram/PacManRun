#include "font.h"

Font::Font()
{
    kerning = 0;
}

Font::~Font()
{
    qDebug()<<"~Font";
}

void Font::SetKerning(int kerning)
{
    this->kerning = kerning;
}

int Font::GetKerning()
{
    return kerning;
}

bool Font::Load(QString filename)
{
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly))
        return false;
    int count = 0;
    f.read((char*)&count, sizeof(count));

    for(int i=0; i<count; i++)
    {
        int buf_char, buf;
        QRect buf_rect;
        f.read((char*)&buf_char, sizeof(buf_char));
        f.read((char*)&buf, sizeof(buf));
        buf_rect.setX(buf);
        f.read((char*)&buf, sizeof(buf));
        buf_rect.setY(buf);
        f.read((char*)&buf, sizeof(buf));
        buf_rect.setWidth(buf);
        f.read((char*)&buf, sizeof(buf));
        buf_rect.setHeight(buf);
        hash.insert(buf_char, buf_rect);
        //qDebug()<<"char="<<(QChar)buf_char<<"x="<<buf_rect.x()<<"y="<<buf_rect.y()<<"width="<<buf_rect.width()<<"height="<<buf_rect.height();
    }

    return true;
}

void Font::Draw(QString text, int x, int y, int z)
{
    int frameX, frameY;
    for (int i=0; i<text.length(); i++)
    {
        QRect rect = hash.value(text.at(i));
        Transformer tr;
        tr.SetScal(QVector3D(rect.width(), rect.height(), 1));
        tr.SetPos(QVector3D(x, y, z));

        Bind(rect.width(), rect.height(), rect.x(), rect.y(), true);
        GetShader()->setUniformValue(GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix()*tr.GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, GetMesh()->GetCountVertex());
        UnBind();

        x+=rect.width()+kerning;
    }

}
