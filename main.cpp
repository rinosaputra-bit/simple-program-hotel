#include<iostream>
#include<fstream>
#include<windows.h>
#include<cstring>
#include<cstdlib>
#include<conio.h>
#include"user_interface.h"
#include"handle_data.h"
#include"customer.h"
#include"report.h"
using namespace std;

int room_con;

class main_operate{
public:
    void init();
////////
    void search_guest_name(guest*& gst, _user& user);
    void add_guest(guest*& gst , _user& user);
    void delete_guest(guest*& gst, _user& user);
    ////////////////////////
    void manage_room(guest*& gst, _user& user);
};
/////////////////
int srch();

int main()
{
    main_operate main_o;
    ifstream in("user.txt");
    if(!in)
        main_o.init();
    in.clear();
    in.close();

    _user u;
    guest* head;

    head=NULL;//head

    int val;
    extern int end_exec;
    u.display();

    while(end_exec!=3)
    {
        for(;;)
        {
            if(room_con==0)
                main_o.manage_room(head,u);

            else if(room_con==1)
            {
                main_o.add_guest(head,u);
                cin.get();
            }

            else if(room_con==2)
                u.check_room(head);

            else if(room_con==3)
            {
                system("cls");

                if(srch())
                    u.search_room(head,-1,-1);

                else
                    main_o.search_guest_name(head,u);
            }

            else if(room_con==4)
                main_o.delete_guest(head,u);

            else if(room_con==5)
                show_guest();

            else if(room_con==6)
                break;

            room_con=u.display_room();
        }

        system("cls");
        u.display();
    }

    return 0;
}

void main_operate::manage_room(guest*& gst, _user& user)
{
    int by=0;
    char s;
    char* arrow="->";
    char w[2][15]={"reservation"," change rooms"};
    system("cls");

    while(1)
    {
        cout<<'\t'<<"manage room\n";
        cout<<'\t'<<"-------------\n\n";
        for(int i=0;i<2;i++)
        {
            if(by==i)
                cout<<'\t'<<arrow<<w[i]<<endl<<endl;
            else
                cout<<'\t'<<w[i]<<endl<<endl;
        }

        s=getch();

        if(s=='w')
            by-=1;
        else if(s=='s')
            by+=1;
        if(by>1)
            by=0;
        else if(by<0)
            by=1;

        system("cls");
        if(s==0x0D)
            break;
    }

    user.change_room(gst,by);
}

void main_operate::delete_guest(guest*& gst, _user& user)
{
    guest* help=gst;
    if(help==NULL)
        cout<<"room is empty";

    else
        user.delete_room(gst);
}

void main_operate::search_guest_name(guest*& gst, _user& user)
{

    guest* help=gst;
    char guest_name[20];

    system("cls");
    cout<<"guest data\n";
    cout<<"----------------\n\n";
    cout<<"input first or last guest name?:";
    cin>>guest_name;
    cout<<'\n';
    if(help==NULL)
        cout<<"all room is empty, there is no guest\n";
    else
    {
        while(help->next_guest!=NULL)
        {
            if(strcmp(guest_name,help->first_name)==0 || strcmp(guest_name,help->last_name)==0)
            {
                cout<<"name         :"<<"Mr/Mrs "<<help->first_name<<" "<<help->last_name<<endl;
                cout<<"natinality   :"<<help->country<<endl;
                cout<<"pasport id   :"<<help->pas_id<<endl;
                cout<<"room type    :";

                if(help->room_type==1)
                    cout<<"standard\n";

                else if(help->room_type==2)
                    cout<<"deluxe\n";

                else if(help->room_type==3)
                    cout<<"president\n";

                cout<<"room number  :"<<help->room_num<<endl;
                cout<<"night        :"<<help->_stay<<endl;
                cout<<"extra bed    :"<<help->ext_bed<<endl;
            }

            cout<<endl;
            help=help->next_guest;

        }

        if(strcmp(guest_name,help->first_name)==0 || strcmp(guest_name,help->last_name)==0)
        {
            cout<<"name         :"<<"Mr/Mrs "<<help->first_name<<" "<<help->last_name<<endl;
            cout<<"natinality   :"<<help->country<<endl;
            cout<<"pasport id   :"<<help->pas_id<<endl;
            cout<<"room type    :";

            if(help->room_type==1)
                cout<<"standard\n";

            else if(help->room_type==2)
                cout<<"deluxe\n";

            else if(help->room_type==3)
                cout<<"president\n";

            cout<<"room number  :"<<help->room_num<<endl;
            cout<<"night        :"<<help->_stay<<endl;
            cout<<"extra bed    :"<<help->ext_bed<<endl;
        }
    }
    cout<<'\n';
    system("pause");
}

void main_operate::add_guest(guest*& gst , _user& user)
{
    system("cls");
    guest* help;
    help=gst;

    guest* add=new guest;

    cout<<"check in guest\n";
    cout<<"------------------\n\n";

    cout<<"first name\t:";
    cin>>add->first_name;
    cout<<"\nlast name\t:";
    cin>>add->last_name;
    cout<<"\nnationality\t:";
    cin.ignore();
    cin.getline(add->country,20);
    cout<<"\npasport id\t:";
    cin>>add->pas_id;

    cout<<"\nroom type 123?\t:";
    cin>>add->room_type;
    cout<<"\nroom number\t:";
    cin>>add->room_num;

    cout<<"\nhave extra bed y/n?:";
    cin>>add->ext_bed;
    cout<<"\nlong to stay\t:";
    cin>>add->_stay;

    user.add_room(add->room_type, add->room_num);

    if(help==NULL)
    {
       add->next_guest=help;
       gst=add;
    }

    else
    {
        while(help->next_guest != NULL){
            help=help->next_guest;}

        add->next_guest=help->next_guest;
        help->next_guest=add;
    }
}
void main_operate::init()
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

int srch()
{
    int by=0;
    char s;
    char* arrow="->";
    int blank=1;
    char w[2][10]={"by name","bye room"};
    while(1)
    {
        cout<<"search->";
        for(int i=0;i<2;i++)
        {
            if(by==i)
            {
                if(blank&&i==0)
                    cout<<arrow<<w[i]<<endl<<endl;
                else if(blank&& i==1)
                    cout<<"      "<<arrow<<w[i]<<endl<<endl;

            }
            else
            {
                if(blank && i==1)
                    cout<<"      "<<w[i]<<endl<<endl;
                else
                    cout<<w[i]<<endl<<endl;
            }
        }

        s=getch();

        if(s=='w')
            by-=1;
        else if(s=='s')
            by+=1;
        if(by>1)
            by=0;
        else if(by<0)
            by=1;

        if(s==0x0D)
            return by;

        system("cls");
    }
}


















