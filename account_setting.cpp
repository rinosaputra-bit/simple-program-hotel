#include<conio.h>
#include<windows.h>
#include<fstream>
#include"handle_data.h"
#include"account_setting.h"

using namespace std;

void m_con(int& get_ind)
{
    int chg;
    int get_suc;

    chg=choosen();

    system("cls");
    print_head();
    cout<<"You Must Log In First....\n";
    Sleep(1000);

    get_suc=fo_login(get_ind);

    if(get_suc)
    {
        cout<<"\n\nLog In Success....\n";
        Sleep(1000);
        system("cls");
        print_head();

        if(chg==1 || chg==0)
            chg_data(chg,get_ind);

        if(chg==3)
            return;

        else if(chg==2)
        {
            chg_phone(get_ind);
            return;
        }
    }

    else
        cout<<"you dont have account....\n";
    //cin.get();
}

void chg_data(int user_inp, int& get_ind)
{
    char get_pw_id[20];
    char temp_pasw[20];
    char buffer[50];
    int i_con=0;
    int sep_buffer;
    int pas_value=get_ind;

    ifstream in("user.txt",ios::app);
    ofstream out("user temp.txt");

    if(out)
        out.ios::trunc;
    else
        out.ios::app;

    while(in)//to find indeks line to change and assign to buffer
    {
        in.getline(buffer,50);
        if(i_con==get_ind)
            break;
        i_con++;
    }
    i_con=0;//reset control

    system("cls");
    print_head();

    for(int i=0;i<strlen(buffer);i++)//to binary buffer into id and pw
    {
        if(buffer[i]=='~')
        {
            sep_buffer=i+1;
            break;
        }
    }

    in.clear();
    in.seekg(ios::beg);//line 129 back to eof

    while(1)
    {

        char to_stop;
        char buffer_temp[50];
        strcpy(buffer_temp,buffer);

        system("cls");
        print_head();

        if(user_inp)
        {
            int i=0;
            int j=0;
            cout<<"New ID   :";
            cin>>get_pw_id;

            j=0;
            for(i=sep_buffer-1;i<strlen(buffer_temp);i++)//assign pw in buffer in file to temp variable
            {
                temp_pasw[j]=buffer_temp[i];
                j++;
            }
            temp_pasw[j]='\0';
            memset(buffer_temp,0,50);
            strcpy(buffer_temp,get_pw_id);//assign new id to buffer

            j=0;
            i=0;
            for(i=strlen(buffer_temp);i<((strlen(buffer_temp)-1)+strlen(temp_pasw));i++)//assign pw from temp variable to buffer
            {
                buffer_temp[i]=temp_pasw[j];
                j++;
            }
        }

        else
        {
            cout<<"New Pasword  :";
            cin>>get_pw_id;

            for(int i=0;i<strlen(get_pw_id);i++)
            {
                buffer_temp[sep_buffer]=get_pw_id[i];
                sep_buffer+=1;
            }
            buffer_temp[sep_buffer]='\0';
        }

        int check_same;
        check_same=check_account(in,get_pw_id," ",pas_value,1);//make file direction into eof

        if(check_same)
        {
            cout<<"\nName already exist try another name....\n\n";
            system("pause");
        }

        else
        {
            memset(buffer,0,50);
            strcpy(buffer,buffer_temp);
            in.clear();
            in.seekg(ios::beg);
            break;
        }

        label_pw:
        if(i_con==4)
        {
            system("cls");
            print_head();
            cout<<"New ID   :"<<get_pw_id;
            cout<<"\n\nEnter N/n to exit or any key to continue...?";
            to_stop=getch();
            if(to_stop=='N' || to_stop=='n')
                return;
            i_con=0;
        }
        memset(temp_pasw,0,20);
        memset(buffer_temp,0,50);
        i_con++;
    }i_con=0;


    char temp_file[50];
    int indeks_ch=-1;
    while(!in.eof())
    {
        in.getline(temp_file,50);
        indeks_ch++;
    }
    in.clear();
    in.seekg(ios::beg);
    memset(temp_file,0,50);

    while(!in.eof())//copy data to user tmp with with add data
    {
        in.getline(temp_file,50);
        if(i_con==indeks_ch)
        {
            if(get_ind!=indeks_ch)
                out<<temp_file;
            else
                out<<buffer;
            i_con++;
            break;
        }

        if(i_con==get_ind)
        {
            out<<buffer<<endl;
            i_con++;
            continue;
        }
        out<<temp_file<<endl;
        i_con++;
    }i_con=0;

    memset(buffer,0,50);
    in.close();
    out.close();
    in.open("user temp.txt",ios::app);
    out.open("user.txt");

    if(out)
        out.ios::trunc;

    else
        out.ios::app;

    while(!in.eof())//copy data to user file from temp user file which have mod
    {
        in.getline(buffer,50);

        if(i_con==indeks_ch)
        {
            out<<buffer;
            break;
        }

        else
        {
            out<<buffer<<endl;
            i_con++;
        }
    }
    in.ios::trunc;
    in.close();
    out.close();
    out.open("user temp.txt",ios::trunc);
    out.close();

    system("cls");
    print_head();
    if(user_inp)
        cout<<"Username has succesfullly change!\n\n";
    else
        cout<<"Pasword has succesfully change!\n\n";
    //system("pause");
}

void chg_phone(int& get_ind)
{
    cout<<"sorry";
}

int choosen()
{
    char choice_set[4][20]={"Change Pasword","Change Username","Change Number Phone","Exit"};
    int indeks=0;
    char control;
    char* arrow_="->";
    char* _arrow="<-";
    while(control!=0x0D)
    {
        print_head();
        for(int i=0;i<4;i++)
        {
            cout<<"  ";
            if(indeks==i)
                cout<<arrow_<<choice_set[i]<<_arrow<<endl<<endl;
            else
                cout<<choice_set[i]<<endl<<endl;
        }

        control=getch();
        if(control=='s')
            indeks+=1;
        else if(control=='w')
            indeks-=1;

        if(indeks<0)
            indeks=0;
        else if(indeks>3)
            indeks=3;
        system("cls");
    }
    return indeks;
}

void print_head()
{
    cout<<"     ACCOUNT SETTING     \n";
    cout<<"-------------------------\n\n";
}
