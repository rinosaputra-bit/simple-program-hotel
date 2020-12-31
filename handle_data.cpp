
//login function
#include<iostream>
#include<fstream>
#include<cstring>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
#include"handle_data.h"
#include"cr_account.h"
//0 is dont have account and dont make account
using namespace std;

int fo_login(int& p_ind)
{
    char temp_id[20];
    char id[20];
    char pw[20];

    repeat:
    system("cls");
    cout<<"LOG IN\n";
    cout<<"------------------\n\n";
    cout<<"User name/ID :";
    cin.getline(id,20);
    cout<<"\nPasword      :";
    cin.getline(pw,20);
    cout<<endl;

    ifstream in;
    in.open("user.txt",ios::app);
    in.seekg(0,ios::end);//put cursor end of file
    int chec=in.tellg();//find cursor position

    if(chec==0)
    {

        if(choice_acc()==0)
        {
            add_acc();
            system("cls");
            goto repeat;
        }
        else
        {
            in.close();
            return 0;
        }
    }

    else
    {
        int rtrn;
        in.seekg(0,ios::beg);
        rtrn=check_account(in,id,pw,p_ind,0);

        if(rtrn==0)
            goto repeat;

        else if(rtrn==1)
        {
            in.close();
            return 1;
        }

        else if(rtrn==2)
        {

            system("cls");
            cout<<"\nSeem you dont have account....\n\n";
            if(choice_acc()==0)
                add_acc();
            else
            {
                in.close();
                return 0;
            }
        }
    }
}

int check_account(ifstream& infile,char* get_id, char* get_pw,int& p_ind,int same_name)
{
    static int make_account=0;
    static int wrong_one=0;

    char temp_word[50];
    char word_file[50];
    int i;

    char temp_id[20];
    char ch;
    int j;
    int id_same=0;
    int pw_same=0;

    for(i=0;i<(strlen(get_id));i++)
        temp_word[i]=get_id[i];

    temp_word[i]='~';

    for(j=0;j<strlen(get_pw);j++)
    {
        i++;
        temp_word[i]=get_pw[j];
    }

    i++;
    temp_word[i]='\0';
    p_ind=0;

    while(!infile.eof())//if username and pasword is correct
    {
        infile.getline(word_file,50);
        if(strcmp(word_file,temp_word)==0)
            return 1;
        p_ind++;
    }
    infile.clear();
    infile.seekg(0,ios::beg);

    i=0;
    int con=0;
    while(!infile.eof())
    {
        infile.get(ch);

        if(ch=='\n')
        {
            i=0;
            con=0;
            if(strcmp(temp_id,get_pw)==0)
                pw_same=1;
            memset(temp_id,0,20);
            continue;
        }

        if(con)
        {
            temp_id[i]=ch;
            i++;
            continue;
        }

        if(ch=='\~')//compare two string or strcmp
        {
            temp_id[i]='\0';
            con=1;
            if( strlen(temp_id)>strlen(get_id) || strlen(temp_id)<strlen(get_id))
            {
                memset(temp_id,0,20);
                i=0;
                continue;
            }
            else
            {
                for(j=0;j<strlen(temp_id);j++)
                {
                    if(temp_id[j]==get_id[j])
                        id_same=1;

                    else if(temp_id[j]!=get_id[j])
                    {
                        id_same=0;
                        break;
                    }
                }
            }
            memset(temp_id,0,20);
            i=0;

            if(id_same)
                break;

            continue;
        }

        temp_id[i]=ch;
        i++;

    }

    if(same_name && id_same)
        return 1;

    else if(same_name && id_same==0)
        return 0;

    else
    {
        if( id_same && pw_same )
            pw_same=0;

        if( id_same && pw_same==0)
        {
            cout<<"\n\nPasword is incorrect....\n";
            wrong_one++;
        }

        else if( id_same==0 && pw_same==0)
        {
            cout<<"\n\nThere is no account....\n";
            make_account++;
        }

        else
        {
            cout<<"\n\nUsername is incorrect....\n";
            wrong_one++;
        }

        getch();
        if(make_account==2 || wrong_one==4)
        {
            make_account=0;
            wrong_one=0;
            return 2;
        }

        return 0;
    }
}

void add_acc()//write karakter and store in text file
{
    char temp_create[40];
    char create[20];
    char temp_id[20];
    int is_num=0;
    int same=0;
    int is_null;

    is_null=chec_empty();

    ofstream out("user.txt",ios::app);
    ofstream out_ph("phone.txt",ios::app);
    while(1)
    {
        char stop;
        label_a:
        cout<<"     CREATE ACCOUNT\n";
        cout<<"----max 20 character----\n\n";

        cout<<"Id/username   :";
        cin.getline(temp_create,40);

        same=if_id_same(temp_create);

        if(strlen(temp_create)>=20 || same)
        {
            if(same)
                cout<<"\nName already exist try another name....\n\n";
            else
                cout<<"\n\nUsername more than 20 character,try again\n\n";

            Sleep(1000);
            same=0;
            memset(temp_create,0,40);
            system("cls");
            goto label_a;
        }

        strcpy(create,temp_create);
        strcpy(temp_id,create);

        if(is_null)
            out<<endl<<create;

        else
            out<<create;

        out<<'~';
        memset(create,0,20);
        memset(temp_create,0,40);

        label_b:
        cout<<"\nPasword       :";
        cin.getline(temp_create,40);

        if(strlen(temp_create)>=20)
        {
            cout<<"\n\nPasword more than 20 character,try again\n\n";
            Sleep(1000);
            memset(temp_create,0,40);
            system("cls");

            cout<<"     CREATE ACCOUNT\n";
            cout<<"----max 20 character----\n\n";
            cout<<"Id/username   :";
            cout<<temp_id<<endl;

            goto label_b;
        }

        strcpy(create,temp_create);
        out<<create;
        //out<<'\n';
        memset(temp_create,0,40);

        label_c:
        cout<<"\nPhone No      :";
        cin>>temp_create;

        for(int i=0;i<strlen(temp_create);i++)
        {
            if(temp_create[i]<0x30 || temp_create[i]>0x39)
            {
                is_num=1;
                break;
            }
        }

        if(strlen(temp_create)>12 || is_num)
        {
            if(is_num)
                cout<<"Number is invalid....\n\n";
            else
                cout<<"Number more than 13 digit\n\n";

            is_num=0;
            memset(temp_create,0,40);
            goto label_c;
        }

        if(is_null)
            out_ph<<endl<<temp_create;
        else
            out_ph<<temp_create;

        memset(temp_create,0,40);

        cout<<"\n\nAccount has been created\n\n";
        cout<<"Press enter to continue...\n\n";
        stop=getch();
        system("cls");

        if(stop==0x0D)
            break;
    }
    out.close();
    out_ph.close();
}

int choice_acc()
{
    char choice[2][4]={"yes","no"};
    int ind=0;
    char con;
    char* arrow="->";
    while(con!=0x0D)
    {
        cout<<"\n\naccount has not found\n";
        cout<<"do you want create new account?\n\n";
        for(int i=0;i<2;i++)
        {
            cout<<"\t\t";
            if(ind==i)
                cout<<arrow<<choice[i]<<endl<<endl;
            else
                cout<<choice[i]<<endl<<endl;
        }

        con=getch();
        if(con=='s')
            ind+=1;
        else if(con=='w')
            ind-=1;

        if(ind<0)
            ind=0;
        else if(ind>1)
            ind=1;
        system("cls");
    }
    return ind;
}













