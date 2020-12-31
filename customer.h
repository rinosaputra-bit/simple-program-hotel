#ifndef CUSTOMER_H
#define CUSTOMER_H

class guest{

protected:
    char first_name[20];
    char last_name[20];
    char country[20];
    int date;
    int month;
    int year;

    int room_num;
    int room_type;

    guest* next_guest;

public:
    void search_guest();
    void add_guest();
    void delete_guest();

};


#endif
