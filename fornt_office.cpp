#include<iostream>
#include<conio.h>
#include<cstring>
#include<windows.h>
#include<iomanip>
#include<cstdio>
#include"front_office.h"
#include"report.h"

using namespace std;

int co_st=0;
int cons_co=0;

room::room()
{
    init_room();
}

int room::display_room()
{
    int get;
    while(1)
    {
        get=get_prog();

        if(get>=0 && get<7)
            return get;
    }
}

void room::add_room(int type , int num)
{
    num-=1;
    if(type==1)
    {
        for(int i=0;i<40;i++)
        {
            if(i==num)
                r_std[i]=1;
        }
    }

    else if(type==2)
    {
        for(int i=0;i<20;i++)
        {
            if(i==num)
                r_deluxe[i]=1;
        }
    }

    else if(type==3)
    {
        for(int i=0;i<5;i++)
        {
            if(i==num)
                r_president[i]=1;
        }
    }

    else
    {
        cout<<"invalid type\n";
        cin.clear();
        system("pause");
    }
}

void room::change_room(guest*& gst,int chose)
{
    switch(chose)
    {
        case 0:
        {
            int r_typ;
            int r_num;
            int r_night;

            int* p_num;
            int all_room;

            cout<<"\treservation"<<endl;
            cout<<"\t-------------"<<endl;
            cout<<"\n\troom type to book    :";
            cin>>r_typ;
            cout<<"\n\tnumber room to book  :";
            cin>>r_num;
            cout<<"\n\tcount of night       :";
            cin>>r_night;

            if(r_typ==1)
            {
                p_num=r_std;
                all_room=40;
            }
            else if(r_typ==2)
            {
                p_num=r_deluxe;
                all_room=20;
            }
            else if(r_typ==3)
            {
                p_num=r_president;
                all_room=5;
            }
            else
            {
                cout<<"\n\tinvalid type";
                Sleep(2000);
                return;
            }

            for(int i=0;i<=all_room;i++)
            {
                if(i==r_num)
                {
                    if(p_num[i-1]==1)
                    {
                        cout<<"\n\troom is stay can not book";
                        break;
                    }
                    else
                    {
                        cout<<"\n\tbooking success";
                        break;
                    }
                }
            }
        }
        break;

        case 1:
        {
            guest* help=gst;
            int by=0;
            int rom_num,rom_num_2;
            int rom_typ,rom_typ_2;
            int ch_type;
            int* p_num;
            int* p_numm;
            int status=0;
            int to_check=0;
            char room_name[10],room_name_2[10];

            system("cls");
            cout<<"change room\n";
            cout<<"-------------------\n\n";
            cout<<"room type 1.standard 2.deluxe 3.president\n\n";
            cout<<"choose type 1 2 3?:";
            cin>>rom_typ;
            cout<<"\nroom number    :";
            cin>>rom_num;
            /////////////////////////////
            if(rom_typ==1)
            {
                ch_type=40;
                p_num=r_std;
            }
            else if(rom_typ==2)
            {
                ch_type=20;
                p_num=r_deluxe;
            }
            else if(rom_typ==3)
            {
                ch_type=5;
                p_num=r_president;
            }

            for(int i=0;i<=ch_type;i++)//to check empty or not
            {
                if(i==rom_num)
                {
                    if(p_num[rom_num-1]==1)
                    {
                        to_check=1;
                        break;
                    }
                }
            }

            /////////////////

            cons_co=1;
            if(to_check)
            {
                to_check=0;
                search_room(help,rom_typ,rom_num);

                if(help->room_type==1)
                    strcpy(room_name,"standard");

                else if(help->room_type==2)
                    strcpy(room_name,"deluxe");

                else if(help->room_type==3)
                    strcpy(room_name,"president");
            }

            else
            {
                cout<<"room is empty\n";
                Sleep(2000);
                return;
            }


            cout<<"\n\nMove To....\n\n";
            cout<<"room type 1.standard 2.deluxe 3.president\n";
            cout<<"choose type 1 2 3?:";
            cin>>rom_typ_2;
            cout<<"\nroom number    :";
            cin>>rom_num_2;

             /////////////////////////////
            if(rom_typ_2==1)
            {
                ch_type=40;
                p_numm=r_std;
            }
            else if(rom_typ_2==2)
            {
                ch_type=20;
                p_numm=r_deluxe;
            }
            else if(rom_typ_2==3)
            {
                ch_type=5;
                p_numm=r_president;
            }

            for(int i=0;i<=ch_type;i++)//to check empty or not
            {
                if(i==rom_num_2)
                {
                    if(p_numm[rom_num_2-1]==1)
                    {
                        to_check=1;
                        status=1;
                        break;
                    }
                    else
                    {
                        help->room_num=i;
                        help->room_type=rom_typ_2;
                        p_num[rom_num-1]=0;
                        p_numm[rom_num_2-1]=1;
                    }
                }
            }
            /////////////////
            guest* room_dest=gst;
            if(to_check)
                search_room(room_dest,rom_typ_2,rom_num_2);
            /////////////////////////
            if(rom_typ_2==1)
                strcpy(room_name_2,"standard");

            else if(rom_typ_2==2)
                strcpy(room_name_2,"deluxe");

            else if(rom_typ_2==3)
                strcpy(room_name_2,"president");
            system("cls");

            cout<<"change room\n";
            cout<<"-------------------\n\n";
            cout<<room_name<<" room no. "<<help->room_num<<"-->move to "<<room_name_2<<" room no. "<<rom_num_2<<endl;

            if(status)
                cout<<"\nstatus : failed room destination is stay";
            else
                cout<<"\nstatus : sucess to change";

        }
        break;
    }
    cons_co=0;
    getch();
}

void room::delete_room(guest*& gst)//sorting room type and num
{
    guest* help=gst;
    int by=0;
    int rom_num;
    int rom_typ;

    system("cls");
    cout<<"check out room\n";
    cout<<"-------------------\n\n";
    cout<<"room type 1.standard 2.deluxe 3.president\n\n";
    cout<<"choose type 1 2 3?:";
    cin>>rom_typ;
    cout<<"\nroom number    :";
    cin>>rom_num;

    cons_co=1;
    search_room(help,rom_typ,rom_num);

    if(co_st)
    {
        system("cls");

        char s;
        char* arrow="->";
        char w[2][10]={"yes","no"};
        while(1)
        {
            cout<<"check out room\n";
            cout<<"-------------------\n\n";
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
            cout<<"\nare sure to check out room "<<help->room_num<<" ?\n";
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
    }

    else
        return;


    if(by)
        return;
    else
    {
        guest_data(help);

        int to_empty;
        switch(help->room_type)
        {
            case 1:
                to_empty=40;
                break;
            case 2:
                to_empty=20;
                break;
            case 3:
                to_empty=5;
                break;
        }

        int i;
        for(i=0;i<=to_empty;i++)
            if(i==help->room_num)
                break;
        i-=1;
        if(help->room_type==1)
            r_std[i]=0;
        else if(help->room_type==2)
            r_deluxe[i]=0;
        else if(help->room_type==3)
            r_president[i]=0;

        cout<<"\nsucessfull check out room number "<<help->room_num<<endl;
        Sleep(2000);

        if(help==gst)
        {
            gst=gst->next_guest;
            delete help;
        }
        else
        {
            guest* bef_help=gst;
            while(bef_help->next_guest != help )
                bef_help=bef_help->next_guest;

            if(help->next_guest ==  NULL)
            {
                bef_help->next_guest=NULL;
                delete help;
            }
            else
            {
                bef_help->next_guest=help->next_guest;
                help->next_guest=NULL;
                delete help;
            }
        }
    }

    co_st=0;
    cons_co=0;
}

void room::search_room(guest*& gst,int type,int num)
{
    int rom_typ;
    int rom_num;
    guest* help=gst;
    guest* temp;

    if(type>=0 && num>=0)
    {
        rom_typ=type;
        rom_num=num;
        system("cls");
        goto ch_rom;
    }

    system("cls");
    cout<<"search room\n";
    cout<<"-------------------\n\n";

    cout<<"room type 1.standard 2.deluxe 3.president\n\n";
    cout<<"choose type 1 2 3?:";
    cin>>rom_typ;
    cout<<"\nroom number    :";
    cin>>rom_num;

    ch_rom:

    if(help==NULL)
        cout<<"room is empty\n";
    else
    {
        while(help->next_guest!=NULL)
        {
            if(help->room_type==rom_typ && help->room_num==rom_num)
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

                co_st=1;
                temp=help;
            }

            help=help->next_guest;
        }
        if(help->room_type==rom_typ && help->room_num==rom_num)
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

             co_st=1;
             temp=help;
        }

        else
            cout<<"room is empty\n";
    }

    if(cons_co)
        gst=temp;
    system("pause");
}

void room::check_room(guest*& gst)
{
    char room_list[4][12]={"standard","deluxe","president","exit"};
    int ind=0;
    char t;
    char* arrow="->";

    while(1)
    {
        system("cls");
        cout<<"room status\n";
        cout<<"-----------------\n\n";

        for(int i=0;i<4;i++)
        {
            if(i==ind)
                cout<<'\t'<<arrow<<room_list[i]<<endl<<endl;
            else
                cout<<'\t'<<room_list[i]<<endl<<endl;
        }

        t=getch();

        if(t=='s' && (ind>=0 && ind<3))
            ind+=1;
        else if(t=='w' && (ind>0 && ind<=3))
            ind-=1;

        if(t==0x0D && (ind>=0 && ind<3))
            show_room(gst,ind);
        else if(t==0x0D && ind==3)
            break;
    }
}

void room::show_room(guest*& gst ,int& type)
{
    int line_std=4;

    int limit;//0 is can left direction.1 to right,2 to up.3 to down
    int ang;
    char dir;
    int dir_ind=0;
    char* arrow1="->";

    system("cls");

    switch(type)
    {
        case 0:
        {
            int l[8]={4,8,12,16,20,24,28,32};
            int r[8]={7,11,15,19,23,27,31,35};
            int t[2]={1,2};
            int b[2]={37,38};
            while(1)
            {

                cout<<"\t\t\t\t\tStandard room\n";
                cout<<"\t     -----------------------------------------------------------------------\n";
                cout<<"\t     "<<"room"<<"\t\t     "<<"status"<<"\t\t     "<<"room"<<"\t\t     "<<"status"<<endl;
                cout<<"\t     "<<"-----"<<"\t\t     "<<"------"<<"\t\t     "<<"-----"<<"\t\t     "<<"------"<<endl<<endl;
                for(int i=0;i<40;i++)
                {
                    if(i==line_std)
                    {
                        cout<<endl<<endl;
                        line_std+=4;
                    }

                    if(dir_ind==i)
                    {

                        if(r_std[i]==1)
                            cout<<"\t     "<<arrow1<<i+1<<" "<<"stay/U"<<"\t     ";
                        else
                            cout<<"\t     "<<arrow1<<i+1<<" "<<"empty"<<"\t     ";
                        continue;
                    }

                    if(r_std[i]==1)
                        cout<<"\t     "<<i+1<<" "<<"stay/U"<<"\t     ";
                    else
                        cout<<"\t     "<<i+1<<" "<<"empty"<<"\t     ";
                }

                cout<<"\n\n\t\tpress enter to see room detail . . .";
                cout<<"\n\n\t\tpress space to exit. . .";

                line_std=4;
                dir=getch();

                for(int k=0;k<8;k++)
                {
                    if(l[k]==dir_ind)
                    {
                        limit=0;
                        break;
                    }
                    else if(r[k]==dir_ind)
                    {
                        limit=1;
                        break;
                    }

                }

                for(int k=0;k<2;k++)
                {
                    if(t[k]==dir_ind)
                    {
                        limit=2;
                        break;
                    }
                    else if(b[k]==dir_ind)
                    {
                        limit=3;
                        break;
                    }
                }

                if(dir_ind==0)
                    ang=0;
                else if(dir_ind==3)
                    ang=1;
                else if(dir_ind==36)
                    ang=2;
                else if(dir_ind==39)
                    ang=3;

                if(dir=='s' && (limit!=3 && ang!=2) && ang!=3)
                    dir_ind+=4;
                else if(dir=='w' && ((limit!=2 && ang!=0) && ang!=1))
                    dir_ind-=4;
                else if(dir=='d' && (limit!=1 && ang!=1) && ang!=3)
                    dir_ind+=1;
                else if(dir=='a' && (limit!=0 && ang!=0) && ang!=2)
                    dir_ind-=1;
                else if(dir==0x0D)
                    search_room(gst,type+1,dir_ind+1);
                else if(dir==0x20)
                    break;

                limit=-1;
                ang=-1;
                system("cls");
            }
        }break;

        case 1:
        {
            int l[4]={4,8,12};
            int r[4]={7,11,15};
            int t[2]={1,2};
            int b[2]={17,18};
            while(1)
            {

                cout<<"\t\t\t\t\tDeluxe room\n";
                cout<<"\t     -----------------------------------------------------------------------\n";
                cout<<"\t     "<<"room"<<"\t\t     "<<"status"<<"\t\t     "<<"room"<<"\t\t     "<<"status"<<endl;
                cout<<"\t     "<<"-----"<<"\t\t     "<<"------"<<"\t\t     "<<"-----"<<"\t\t     "<<"------"<<endl<<endl;
                for(int i=0;i<20;i++)
                {
                    if(i==line_std)
                    {
                        cout<<endl<<endl;
                        line_std+=4;
                    }

                    if(dir_ind==i)
                    {

                        if(r_deluxe[i]==1)
                            cout<<"\t     "<<arrow1<<i+1<<" "<<"stay/U"<<"\t     ";
                        else
                            cout<<"\t     "<<arrow1<<i+1<<" "<<"empty"<<"\t     ";
                        continue;
                    }

                    if(r_deluxe[i]==1)
                        cout<<"\t     "<<i+1<<" "<<"stay/U"<<"\t     ";
                    else
                        cout<<"\t     "<<i+1<<" "<<"empty"<<"\t     ";
                }

                cout<<"\n\n\t\tpress enter to see room detail . . .";
                cout<<"\n\n\t\tpress space to exit. . .";

                line_std=4;
                dir=getch();

                for(int k=0;k<4;k++)
                {
                    if(l[k]==dir_ind)
                    {
                        limit=0;
                        break;
                    }
                    else if(r[k]==dir_ind)
                    {
                        limit=1;
                        break;
                    }

                }

                for(int k=0;k<2;k++)
                {
                    if(t[k]==dir_ind)
                    {
                        limit=2;
                        break;
                    }
                    else if(b[k]==dir_ind)
                    {
                        limit=3;
                        break;
                    }
                }

                if(dir_ind==0)
                    ang=0;
                else if(dir_ind==3)
                    ang=1;
                else if(dir_ind==16)
                    ang=2;
                else if(dir_ind==19)
                    ang=3;

                if(dir=='s' && (limit!=3 && ang!=2) && ang!=3)
                    dir_ind+=4;
                else if(dir=='w' && ((limit!=2 && ang!=0) && ang!=1))
                    dir_ind-=4;
                else if(dir=='d' && (limit!=1 && ang!=1) && ang!=3)
                    dir_ind+=1;
                else if(dir=='a' && (limit!=0 && ang!=0) && ang!=2)
                    dir_ind-=1;
                else if(dir==0x0D)
                    search_room(gst,type+1,dir_ind+1);
                else if(dir==0x20)
                    break;

                limit=-1;
                ang=-1;
                system("cls");
            }
        }break;

        case 2:
        {
            while(1)
            {

                cout<<"\t\t\t\t\tPresident room\n";
                cout<<"\t     -----------------------------------------------------------------------\n";
                cout<<"\t     "<<"room"<<"\t\t     "<<"status"<<"\t\t     "<<"room"<<"\t\t     "<<"status"<<endl;
                cout<<"\t     "<<"-----"<<"\t\t     "<<"------"<<"\t\t     "<<"-----"<<"\t\t     "<<"------"<<endl<<endl;
                for(int i=0;i<5;i++)
                {
                    if(i==line_std)
                    {
                        cout<<endl<<endl;
                        line_std+=4;
                    }

                    if(dir_ind==i)
                    {

                        if(r_president[i]==1)
                            cout<<"\t     "<<arrow1<<i+1<<" "<<"stay/U"<<"\t     ";
                        else
                            cout<<"\t     "<<arrow1<<i+1<<" "<<"empty"<<"\t     ";
                        continue;
                    }

                    if(r_president[i]==1)
                        cout<<"\t     "<<i+1<<" "<<"stay/U"<<"\t     ";
                    else
                        cout<<"\t     "<<i+1<<" "<<"empty"<<"\t     ";
                }

                cout<<"\n\n\t\tpress enter to see room detail . . .";
                cout<<"\n\n\t\tpress space to exit. . .";

                line_std=4;
                dir=getch();

                if(dir=='a' && (dir_ind!=0 && dir_ind!=4))
                    dir_ind-=1;
                else if(dir=='d' && (dir_ind!=3 && dir_ind!=4))
                    dir_ind+=1;
                else if(dir=='w' && (dir_ind!=0 && dir_ind!=3) && (dir_ind!=1 && dir_ind!=2))
                    dir_ind-=4;
                else if(dir=='s' && dir_ind!=4)
                    dir_ind=4;
                else if(dir==0x0D)
                    search_room(gst,type+1,dir_ind+1);
                else if(dir==0x20)
                    break;

                system("cls");
            }
        }
    }
}

void room::init_room()
{
    full=0;
    int i;

    for(i=0;i<40;i++)
        r_std[i]=0;

    for(i=0;i<20;i++)
        r_deluxe[i]=0;

    for(i=0;i<5;i++)
        r_president[i]=0;

    char temp[7][25]={"manage room","check in","get available room","search",
                      "check out room","guest summary report","exit"};
    for(int i=0;i<7;i++)
        strcpy(chose_prog[i],temp[i]);
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


void print_prog()
{
    cout<<"Front Office Program\n";
    cout<<"------------------------\n";
}


















