#include<iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<cstring>
#include"report.h"
#include"user_interface.h"

using namespace std;

void show_guest()
{
    system("cls");
    char temp[50];
    ifstream in("guest history.txt");


    cout<<"guest history\n";
    cout<<"-----------------\n";
    cout<<"1. standard  2.deluxe  3.president\n\n";
    if(!in)
        cout<<"there is no guest";

    else
    {
        while(!(in.eof()))
        {
            in.getline(temp,50);
            if(strcmp(temp,"->")==0)
            {
                cout<<"\n--------------------\n";
                continue;
            }
            cout<<temp<<endl;
        }
    }

    getch();
}

void guest_data(guest*& gst)
{
    ofstream save_data("guest history.txt",ios::app);

    save_data<<"name        : "<<gst->first_name<<" "<<gst->last_name<<endl;
    save_data<<"nationality : "<<gst->country<<endl;
    save_data<<"id          : "<<gst->pas_id<<endl;
    save_data<<"room type   : "<<gst->room_type<<endl;
    save_data<<"room no     : "<<gst->room_num<<endl;
    save_data<<"extra bed   : "<<gst->ext_bed<<endl;
    save_data<<"night       : "<<gst->_stay<<endl;
    save_data<<"->"<<endl;
    save_data.close();
}
