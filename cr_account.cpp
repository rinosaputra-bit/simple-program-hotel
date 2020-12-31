#include<iostream>
#include<fstream>
#include<cstring>
#include<conio.h>

using namespace std;

int if_id_same(char* check_id)
{
    char buffer[50];
    int indeks;
    int control=0;

    ifstream in("user.txt");

    while(!in.eof())
    {
        in.getline(buffer,50);

        for(int i=0;i<strlen(buffer);i++)
        {

            if(buffer[i]=='~')
                control=1;

            if(control)
                buffer[i]='\0';
        }

        control=0;
        if(strlen(buffer)==strlen(check_id))
        {
            for(int i=0;i<strlen(buffer);i++)
            {
                if(buffer[i]==check_id[i])
                    control=1;

                else
                    control=0;
            }
        }
        if(control)
            break;

    }
    in.close();
    return control;
}

int chec_empty()
{
    ifstream in("user.txt",ios::app);
    in.seekg(0,ios::end);
    if(in.tellg()==0)
        return 0;
    else
        return 1;
}




