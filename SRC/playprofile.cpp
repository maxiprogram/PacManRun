#include "playprofile.h"

int PlayProfile::last_level = 1;
int PlayProfile::score = 0;

PlayProfile::PlayProfile()
{
}

bool PlayProfile::Load()
{
    bool flag = false;
    QFile f("profile.data");
    flag = f.open(QIODevice::ReadOnly);
    if (!flag)
    {
        last_level = 1;
        score = 0;
        flag = f.open(QIODevice::WriteOnly);
        if (!flag)
            return flag;
        f.write((char*)&last_level, sizeof(int));
        f.write((char*)&score, sizeof(int));
        flag = true;
    }else
    {
        f.read((char*)&last_level, sizeof(int));
        f.read((char*)&score, sizeof(int));
        flag = true;
    }
    f.close();
    return flag;
}

bool PlayProfile::Save()
{
    QFile f("profile.data");
    if (!f.open(QIODevice::WriteOnly))
        return false;
    f.write((char*)&last_level, sizeof(int));
    f.write((char*)&score, sizeof(int));
    f.close();
    return true;
}
