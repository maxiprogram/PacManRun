#ifndef PAUSEGAME_H
#define PAUSEGAME_H

//#include "Engine/gamescene.h"
//#include "Engine/managerkeyboard.h"
//#include "Engine/fps.h"
//#include "Engine/font.h"
#include "Engine/resources.h"

#include "playprofile.h"
#include "statusgame.h"

class PauseGame:public GameObject
{
public:
    PauseGame();
    ~PauseGame();
    void Init(QHash<QString, QString> property);
    void Update(float dt=1);
    void Draw();
private:
    int id_header;
    int id_button;
    int id_blood;
    int time_pause_dead;
};

#endif // PAUSEGAME_H
