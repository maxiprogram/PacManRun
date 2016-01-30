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
    static int score;
    static int current_level;
    static int setting_fullscreen;
};

#endif // PLAYPROFILE_H
