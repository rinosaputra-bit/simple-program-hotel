#ifndef FRONT_OFFICE_H
#define FRONT_OFFICE_H

#include"customer.h"
//#include"user_interface.h"

//class _user;
class room : public guest{

protected:

    int r_std[40];//standard room is 40
    int r_deluxe[20];//deluxe room is 20
    int r_president[5];//president room is 5
    char chose_prog[7][29];
    int full;

public:
    room();
    int display_room();
    void add_room(int type,int num);
    void delete_room(guest*& gst);
    void search_room(guest*& gst,int type,int num);//direction to see data guest in room with input not with list of room
    void check_room(guest*& gst);//show list type  and operate
    void change_room(guest*& gst,int chose);

    void init_room();
    int get_prog();
    void show_room(guest*& gst ,int& type);//show all room
    //friend class _user;
};

void print_prog();
#endif
