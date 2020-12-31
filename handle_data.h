//log in
#ifndef HANDLE_DATA_H
#define HANDLE_DATA_H

#include<iostream>

int fo_login(int& p_ind);
//account handle
int choice_acc();
void add_acc();
int check_account(std::ifstream&,char*,char*,int& p_ind,int same_name);

#endif
