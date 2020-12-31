#include<iostream>
#include<conio.h>
#include<cstring>
#include<windows.h>

#include"front_office.h"
using namespace std;

room::room()
{
    init_room();
}

void room::display_room()
{
    int get;
    while(1)
    {
        get=get_prog();

        if(get==2)
            check_room();
    }
}

int room::get_prog()
{
    system("cls");
    char* arrows="<-";
    char control;
    int indeks=0;

    while(1)
    {
        print_prog();
        cout<<endl;
        for(int i=0;i<7;i++)
        {
            if(indeks==i)
                cout<<i+1<<". "<<chose_prog[i]<<arrows<<endl<<endl;
            else
                cout<<i+1<<". "<<chose_prog[i]<<endl<<endl;

        }

        control=getch();

        if(control=='s' && (indeks<6 && indeks>=0))
            indeks++;
        else if(control=='w' && (indeks>0 && indeks<=6))
            indeks--;

        if(control==0x0D)
            break;

        system("cls");
    }

    return indeks;
}

void room::init_room()
{
    full=0;
    r_std[40]={0};
    r_deluxe[20]={0};
    r_president[5]={0};

    char temp[7][25]={"manage room","check in","get available room","search customer",
                      "check out room","guest summary report","exit"};
    for(int i=0;i<7;i++)
        strcpy(chose_prog[i],temp[i]);
}

void room::check_room()
{
    int i;

    for(i=0;i<40;i++)//check standar room available with value 1 is there is guest and 0 is empty
    {
        if(r_std[i]==1)
    }
}

void print_prog()
{
    cout<<"Front Office Program\n";
    cout<<"------------------------\n";
}


















