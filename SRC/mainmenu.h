#ifndef MAINMENU_H
#define MAINMENU_H

#include "Engine/resources.h"

class MainMenu:public GameObject
{
public:
    MainMenu();
    ~MainMenu();
    void Init(QHash<QString, QString> property);
    void Update(float dt);
    void Draw();
private:
    int id_sprite;
};

#endif // MAINMENU_H
