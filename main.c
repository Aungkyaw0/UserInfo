
#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
int strLen(char *p);
int cmpStr(char *p1, char *p2);
int scan_int();
void scanStr(char *p);
void insertData();
int idAdding();
void findData();
void updateData();
char ScanfCharHandling();
struct data
{
    char username[SIZE];
    char password[SIZE];
    int id, amount, age;
    char location[SIZE];
};

int main()
{
    int op;

    while(1)
    {
        printf("Welcome From The Database\n----------------------------\n1. Insert Data\n2. Find Data\n3. Update Data\n4. Exit\n");
        printf("Enter the operation number ::> ");
        op = scan_int();
        
        switch (op)
        {
        case 1:
            insertData();
            break;
        case 2:
            findData();
            break;
        case 3:
            updateData();
            break;
        case 4:
            exit(1);
            break;
        default:
            break;
        }
           
    }


}
int strLen(char *p)// User for StringLength
{
    int c =0;
    while(*p != '\0')
    {
        c++;
        p++;
    }

    return c;

}
int cmpStr(char *p1, char *p2)//Used For The String Compare// Need StrLen Function
{
    int i = 1;
    char *x,*y;
    if(strLen(p1) < strLen(p2))
    {
        x = p2;
        y = p1;
    }
    else
    {
        x = p1;
        y = p2;
    }

    while(*x)
    {

        if( *x == *y)
        {
            i =1;
        }
        else if( *x != *y)
        {
            i =0;
            break;
        }
        x++;
        y++;
    }

    return i;
}

int scan_int()// Use for hadling invalid input for INT
{
    int inp = 0;
    int status = scanf("%d", &inp);
    if(status != 1)
    {
        scanf( "%*[^\n]" );
        inp = 0;
    }
    return  inp;

}
void insertData()
{
    struct data tmp;
    FILE *inp;
    if( (inp = fopen("UserDb1.txt", "a+")) == NULL)
    {
        printf("Sorry Can't Open FIle ");
        exit(1);
    }
    tmp.id = idAdding();
    printf("Enter the username ::> ");
    scanStr(tmp.username);
    printf("Enter the password ::> ");
    scanStr(tmp.password);
    printf("Enter the Location ::> ");
    scanStr(tmp.location);
    printf("Enter the amount ::> ");
    tmp.amount = scan_int();
    printf("Enter the age ::> ");
    tmp.age = scan_int();  

    fprintf(inp,"%d | %s | %s | %s | %d | %d | ", tmp.id, tmp.username, tmp.password, tmp.location, tmp.amount,tmp.age);
    fclose(inp);
}
void scanStr(char *p)// Use for the scanf to avoid stream error
{
    
    char tmp[SIZE];
    char *p1 = tmp;
    while(getchar() != '\n');
    scanf("%[^\n]s", tmp);
    while(*p1 != '\0')
    {
        *p++ = *p1++;
    }
    *p = '\0';
}
int idAdding()
{
    int counter = 1;
    FILE *d;
    int c = 0;
    d = fopen("UserDb1.txt", "r");
    
    if(!d)
    {
        printf("Sorry Can't Open the file");
        exit(1);
    }

    struct data tmp;
    tmp.id = 0;
    //fscanf(d,"%d | %[^|] | %[^|] | %[^|] | %d | %d | ", &tmp.id, tmp.username, tmp.password, tmp.location, &tmp.amount, &tmp.age);
    //counter++;
    while(1)
    {
        if(feof(d))
        {
            break;
        }
        fscanf(d,"%d | %[^|] | %[^|] | %[^|] | %d | %d | ", &tmp.id, tmp.username, tmp.password, tmp.location, &tmp.amount, &tmp.age);
        counter++;
    }
    fclose(d);
    if(tmp.id == 0)
    {
        return tmp.id + 1;
    }
    tmp.id++;
    return tmp.id;


    //while(!feof(F))
}
void findData()
{
    int c = 0, n_status =0;
    char name[SIZE];char *n = name;
    char pass[SIZE];char *p = pass;
    FILE *data;
    printf("Finding Data in Database\n------------------------\nEnter the username ::> ");
    scanStr(name);
    while(*n++);
    n--;*n = ' ';n++; *n = '\0';
    data = fopen("UserDb1.txt", "r");
    if(!data)
    {
        printf("Can't Open the file!!!");
        exit(1);
    }
    struct data tmp;
    while(1)
    {
        if(feof(data))
        {
            break;
        }
        fscanf(data,"%d | %[^|]| %[^|]| %[^|]| %d | %d | ", &tmp.id, tmp.username, tmp.password, tmp.location, &tmp.amount, &tmp.age);   
        c++;
        if(cmpStr(tmp.username, name) == 1)
        {
            n_status = 1;
            break;
        }
        
    }
    fclose(data);
    if(c == 0)
    {
        printf("!!!There is no data in the DataBase!!! ");
    }
    else
    {
        if(n_status == 1)
        {
            printf("Enter password for %s ::> ", name);
            scanStr(pass);
            while(*p++);
            p--;*p = ' ';p++; *p = '\0';
            if(cmpStr(tmp.password, pass) == 1)
            {
                printf("\n!!!Password Correct!!!\n");
                printf("Information for %s\n------------------------\n", name);
                printf("Username ::> %s\n", tmp.username);
                printf("Password ::> %s\n", tmp.password);
                printf("Location ::> %s\n", tmp.location);
                printf("Amount ::> %d\n", tmp.amount);
                printf("User Age ::> %d\n", tmp.age);
            }
            else
            {
                printf("\n!!PASSWORD IS INCORRECT!!\n");
            }

        }
        else
        {
            printf("\n!!!Sorry there is  no data for %s!!!\n", name);
        }
    }
    
    

}

void updateData()
{
    int op = 0;
    FILE *fptr;
    int c = 0;
    int status = 0; 
    char name[SIZE];char *n = name;
    char pass[SIZE];char *p = pass;
    struct data st;
    printf("Welcome From Updateing Data\n--------------------------\n");
    printf("!!!To Update The Data You Need To Login First!!!\n");
    printf("Enter Username ::> ");
    scanStr(name);
    printf("Enter Password ::> ");
    scanStr(pass);
    while(*n++);
    n--;*n = ' ';n++; *n = '\0';
    while(*p++);
    p--;*p = ' ';p++; *p = '\0';
    fptr = fopen("UserDb1.txt", "r");

    if(!fptr)
    {
        printf("Can't open FIle");
        exit(1);
    }
    struct data tmp;
    while(1)
    {
        if(feof(fptr))
        {
            break;
        }
        //fgets(tmp.username, SIZE, fptr);
        fscanf(fptr,"%d | %[^|]| %[^|]| %[^|]| %d | %d | ", &tmp.id, tmp.username, tmp.password, tmp.location, &tmp.amount, &tmp.age);   

        printf("Username ::>  %s\n", tmp.username);
        if(cmpStr(tmp.username, name) == 1)
        {
            if(cmpStr(tmp.password, pass) == 1)
            {
                //fprintf(inp," %s | %s | %s | %d | %d | ", tmp.username, tmp.password, tmp.location, tmp.amount,tmp.age);
                //fgets("TEST",7 , fptr);
                st = tmp;
                status = 1;
                break;
            }
            else
            {
                printf("\nYour Password is incorrect!!!\n");
                break;
            }
        }
        c++;
        
    }
    fclose(fptr);
    if(status == 1)
    {
        char opt;
        fptr = fopen("UserDb1.txt", "r+");
        if(!fptr)
        {
            exit(1);
        }
        
        for(int i =0; i < c; i++)
        {
            fscanf(fptr,"%d | %[^|]| %[^|]| %[^|]| %d | %d | ", &tmp.id, tmp.username, tmp.password, tmp.location, &tmp.amount, &tmp.age);   
            printf("Name ::> %s", tmp.username);
        }
        
        while(1)
        {
            char *p = NULL;
            printf("Changing Information For %s\n---------------\n", name);
            printf("1. Password\n2. Location\n3. Amount\n4. Mark\nEnter the number ::> ");
            op = scan_int();
            if(op == 1)
            {
                p = st.password;
                printf("Enter new password ::> ");
                scanStr(st.password);
                while(*p++);
                p--;*p = ' ';p++; *p = '\0';

            }
            else if(op == 2)
            {
                
                printf("Eneter new location ::> ");
                scanStr(st.location);
                

            }
            else if(op == 3)
            {
                st.amount = scan_int();
            }
            else if(op == 4)
            {
                st.age = scan_int();
            }
            else
            {
                printf("please enter 1 - 4 only");
            }
            printf("Do you want to add more (y,n) ::> ");
            opt = ScanfCharHandling();
            if(opt != 'y' || opt != 'n')
            {
                break;
            }
        }
        fprintf(fptr,"%d | %s | %s | %s | %d | %d | ", st.id, st.username, st.password, st.location,  st.amount, st.age);

        
        fclose(fptr);      
    }


}

char ScanfCharHandling()
{
    char inp;

    scanf(" %c", &inp);
    if(inp == 'y' || inp == 'Y')
    {
        scanf( "%*[^\n]" );
        return 'y';
    }
    else if(inp == 'n' || inp == 'N')
    {
        scanf( "%*[^\n]" );
        return 'n';
    }
    else
    {
        scanf( "%*[^\n]" );
        return 'a';
    }
}
