#include "playprofile.h"

int PlayProfile::last_level = 1;
int PlayProfile::current_level = 0;
int PlayProfile::setting_fullscreen = 1;
int PlayProfile::score_plan[27];
int PlayProfile::score[27];

PlayProfile::PlayProfile()
{
}

void PlayProfile::ResetScorePlan()
{
    score_plan[0] = 39;
    score_plan[1] = 0;
    score_plan[2] = 0;
    score_plan[3] = 0;
    score_plan[4] = 0;
    score_plan[5] = 0;
    score_plan[6] = 0;
    score_plan[7] = 0;
    score_plan[8] = 0;
    score_plan[9] = 0;
    score_plan[10] = 0;
    score_plan[11] = 0;
    score_plan[12] = 0;
    score_plan[13] = 0;
    score_plan[14] = 0;
    score_plan[15] = 0;
    score_plan[16] = 0;
    score_plan[17] = 0;
    score_plan[18] = 0;
    score_plan[19] = 0;
    score_plan[20] = 0;
    score_plan[21] = 0;
    score_plan[22] = 0;
    score_plan[23] = 0;
    score_plan[24] = 0;
    score_plan[25] = 0;
    score_plan[26] = 0;
}

bool PlayProfile::Load()
{
    bool flag = false;
    QFile f("profile.data");
    flag = f.open(QIODevice::ReadOnly);
    if (!flag)
    {
        last_level = 1;
        flag = f.open(QIODevice::WriteOnly);
        if (!flag)
            return flag;
        f.write((char*)&last_level, sizeof(int));
        f.write((char*)&setting_fullscreen, sizeof(bool));

        ResetScorePlan();
        for (int i=0; i<27; i++)
        {
            f.write((char*)&score_plan[i], sizeof(int));
        }

        for (int i=0; i<27; i++)
        {
            score[i] = 0;
            f.write((char*)&score[i], sizeof(int));
        }
        flag = true;
    }else
    {
        f.read((char*)&last_level, sizeof(int));
        f.read((char*)&setting_fullscreen, sizeof(bool));
        for (int i=0; i<27; i++)
        {
            f.read((char*)&score_plan[i], sizeof(int));
        }
        for (int i=0; i<27; i++)
        {
            f.read((char*)&score[i], sizeof(int));
        }
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
    f.write((char*)&setting_fullscreen, sizeof(bool));
    for (int i=0; i<27; i++)
    {
        f.write((char*)&score_plan[i], sizeof(int));
    }

    for (int i=0; i<27; i++)
    {
        f.write((char*)&score[i], sizeof(int));
    }
    f.close();
    return true;
}
