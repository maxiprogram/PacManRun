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
        CharInfo buf_charinfo;
        f.read((char*)&buf_char, sizeof(buf_char));
        f.read((char*)&buf, sizeof(buf));
        buf_charinfo.x = buf;
        f.read((char*)&buf, sizeof(buf));
        buf_charinfo.y = buf;
        f.read((char*)&buf, sizeof(buf));
        buf_charinfo.width = buf;
        f.read((char*)&buf, sizeof(buf));
        buf_charinfo.height = buf;
        f.read((char*)&buf, sizeof(buf));
        buf_charinfo.x_offset = buf;
        f.read((char*)&buf, sizeof(buf));
        buf_charinfo.y_offset = buf;
        hash.insert(buf_char, buf_charinfo);
        //qDebug()<<"char="<<(QChar)buf_char<<"x="<<buf_charinfo.x<<"y="<<buf_charinfo.y<<"width="<<buf_charinfo.width<<"height="<<buf_charinfo.height<<"x_offset="<<buf_charinfo.x_offset<<"y_offset="<<buf_charinfo.y_offset;
    }

    return true;
}

void Font::Draw(QString text, int x, int y, int z)
{
    int frameX, frameY;
    for (int i=0; i<text.length(); i++)
    {
        CharInfo char_info = hash.value(text.at(i));
        //qDebug()<<"char="<<text.at(i)<<"x="<<char_info.x<<"y="<<char_info.y<<"width="<<char_info.width<<"height="<<char_info.height<<"x_offset="<<char_info.x_offset<<"y_offset="<<char_info.y_offset;
        Transformer tr;
        tr.SetPivot(QVector3D((float)char_info.x_offset/char_info.width, 1+(float)char_info.y_offset/char_info.height, 0));
        tr.SetPos(QVector3D(x, y, z));
        tr.SetScal(QVector3D(char_info.width, char_info.height, 1));

        Bind(char_info.width, char_info.height, char_info.x, char_info.y, true);
        GetShader()->setUniformValue(GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix()*tr.GetMatrix());
        glDrawArrays(GL_TRIANGLES, 0, GetMesh()->GetCountVertex());
        UnBind();

        x+=char_info.width+kerning;
    }

}
