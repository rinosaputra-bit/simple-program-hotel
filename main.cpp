#include<iostream>
#include<fstream>
#include<windows.h>
#include"user_interface.h"
#include"handle_data.h"
using namespace std;

void init();

int main()
{
    _user u;

    ifstream in("user.txt");
    if(!in)
        init();
    in.clear();
    in.close();

    u.display();

    return 0;
}

void init()
{
    ifstream infile("user.txt",ios::app);
    ifstream infilea("user temp.txt",ios::app);
    ifstream infileb("phone.txt",ios::app);
    infile.close();
    infilea.close();
    infileb.close();

    cout<<"Please make account first\n\n";
    system("pause");
    system("cls");
    add_acc();
    cin.get();
}




















