#ifndef PLAYER_H
#define PLAYER_H

#include <QMessageBox>

#include "Engine/gamescene.h"
#include "Engine/managerkeyboard.h"
#include "Engine/fps.h"
#include "Engine/font.h"

#include "SFML/Audio.hpp"

#include "playprofile.h"
#include "statusgame.h"
#include "portal.h"
#include "bullet.h"
#include "particle.h"

class Player:public GameObject
{
public:
    Player();
    ~Player();
    void Init(QHash<QString, QString> property);
    void Update(float dt=1);
    void Draw();
    QRectF GetBoundBox();
    void SetJolt(bool flag);
    int score;
private:
    enum _Status {OnGround, Jump, Down} Status;
    bool flag_jolt;
    int id_sprite;
    int id_close;
    float frame;
    QVector2D direction;
    float speed_x, speed_y;
    float accel_x, accel_y;
    int count_bonus;
    int count_bonus_shoot;
    int y_sprite;
    float rotation_shoot;
    sf::SoundBuffer buffer_jump;
    sf::Sound sound_jump;
    sf::SoundBuffer buffer_spring;
    sf::Sound sound_spring;
    sf::SoundBuffer buffer_bonus;
    sf::Sound sound_bonus;
    sf::SoundBuffer buffer_kill;
    sf::Sound sound_kill;
    sf::SoundBuffer buffer_score;
    sf::Sound sound_score;
};

#endif // PLAYER_H
