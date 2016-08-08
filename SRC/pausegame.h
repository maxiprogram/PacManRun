#ifndef PAUSEGAME_H
#define PAUSEGAME_H

#include <QMessageBox>

#include "Engine/resources.h"

#include <SFML/Audio.hpp>

#include "playprofile.h"
#include "statusgame.h"
#include "player.h"

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
    int id_cherry;
    int time_pause_dead;
    sf::Music background_music;
    sf::Music background_music1;
};

#endif // PAUSEGAME_H
