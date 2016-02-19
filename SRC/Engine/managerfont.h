#ifndef MANAGERFONT_H
#define MANAGERFONT_H

#include "font.h"

class ManagerFont
{
public:
    ManagerFont();
    ~ManagerFont();
    static ManagerFont* getInstance();
    void Add(QString key, Font* value);
    void Delete(QString key);
    Font* GetValue(QString key);
    void Clear();
    void Destroy();

private:
    static ManagerFont* instance;
    QHash<QString, Font*> hash_tab;
};

#endif // MANAGERFONT_H
