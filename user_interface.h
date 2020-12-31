#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include"front_office.h"

class _user :public room{

private:
    char menu[4][20];
    char* arrow;
    char* arrow2;

public:
    _user();
    void init();
    void display();
    int show_menu();
};

#endif // USER_INTERFACE_H
