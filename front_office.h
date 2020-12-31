#ifndef FRONT_OFFICE_H
#define FRONT_OFFICE_H

#include"customer.h"
//#include"user_interface.h"

//class _user;
class room : public guest{

protected:

    int r_std[40];//standard room are 40
    int r_deluxe[20];//deluxe room is 20
    int r_president[5];//president room is 5
    char chose_prog[7][29];
    int full;

public:
    room();
    void display_room();
    void add_room();//add
    void delete_room();//pop
    void search_room();//direction to see data guest in room
    void check_room();
    void change_room();

    void init_room();
    int get_prog();
    //friend class _user;
};

void print_prog();
#endif
