#ifndef MAINMENU_H
#define MAINMENU_H

#include "Engine/resources.h"
#include "Engine/font.h"

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
    float flag_header;
    float pos_y_header;
    float frame_player;
    float pos_x_player;
    QVector2D mas_pos[9];
    int current_level_menu;
    float pos_y_author;

    ///*Тестирование Font УБРАТЬ
    int id_font;
    QString path_font;
    Font font;
    //Тестирование Font УБРАТЬ*/

};

#endif // MAINMENU_H
