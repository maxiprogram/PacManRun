#ifndef MAINMENU_H
#define MAINMENU_H

#include "Engine/resources.h"

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
    int id_main_menu;
    int id_level_menu1;
    int id_item_back;
    int id_item_lock;
};

#endif // MAINMENU_H
