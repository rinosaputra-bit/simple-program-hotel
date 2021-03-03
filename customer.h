#ifndef CUSTOMER_H
#define CUSTOMER_H

class guest{

public:
    char first_name[20];
    char last_name[20];
    char country[20];
    unsigned long pas_id;

    int room_num;
    int room_type;

    int _stay;
    char ext_bed;

    guest();
    guest* next_guest;

};


#endif
