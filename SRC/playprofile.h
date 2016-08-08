#ifndef PLAYPROFILE_H
#define PLAYPROFILE_H

#include <QFile>

class PlayProfile
{
public:
    PlayProfile();
    static bool Load();
    static bool Save();
    static int last_level;
    static int score_plan[27];
    static int score[27];
    static int current_level;
    static int setting_fullscreen;
    static int setting_sound;
private:
    static void ResetScorePlan();
};

#endif // PLAYPROFILE_H
