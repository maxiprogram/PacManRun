#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMessageBox>

#include "Engine/resources.h"
#include "Engine/font.h"

#include "SFML/Audio.hpp"

#include "statusgame.h"
#include "playprofile.h"

class MainMenu:public GameObject
{
public:
    MainMenu();
    ~MainMenu();
    void Init(QHash<QString, QString> property);
    void Update(float dt);
    void Draw();
private:
    int id_button;
    int id_header;
    int id_level_menu1;
    int id_level_menu2;
    int id_level_menu3;
    int id_item_back;
    int id_item_next;
    int id_item_lock;
    int id_player;
    int id_button_apply;
    int id_header_menu;
    int id_checkbox;
    float flag_header;
    float pos_y_header;
    float frame_player;
    float pos_x_player;
    QVector2D mas_pos[9];
    int current_level_menu;
    float pos_y_author;
    int checkbox_fullscreen;
    int checkbox_sound;
    sf::Music background_music;

};

#endif // MAINMENU_H
