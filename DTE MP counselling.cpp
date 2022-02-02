//***************************************************************
//   PROJECT NAME : DIRECTORATE TECHNICAL EDUCATION GOVERNMENT OF MADHYA PRADESH
//****************************************************************
#include<iostream>
#include<process.h>
#include<fstream>
#include<iomanip>
#include<conio.h>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
class student
{
    private:
    string name,dob,gen,add,email,pno,crse;
    public:
    float marks;
    int application;
    void getdata()
    {
        cout<<"\tStudent Name:              ";
        cin.ignore();
        getline(cin,name);
        cout<<"\n\tDate Of Birth(DD/MM/YYYY): ";
        getline(cin,dob);
        cout<<"\n\tGender:                    ";
        getline(cin,gen);
        cout<<"\n\tAddress:                   ";
        getline(cin,add);
        cout<<"\n\tEmail:                     ";
        getline(cin,email);
        cout<<"\n\tPhone Number:              ";
        getline(cin,pno);
        cout<<"\n\tMarks:                     ";
        cin>>marks;
        cout<<"\n\tCourse Name:               ";
        cin>>crse;
    }
    void showdata()
    {
        cout<<"\n\t_________________________________________________________________";
        cout<<"\n\t Student Name:  "<<name<<endl;
        cout<<"\n\t Date Of Birth: "<<dob<<endl;
        cout<<"\n\t Gender:        "<<gen<<endl;
        cout<<"\n\t Address:       "<<add<<endl;
        cout<<"\n\t Email:         "<<email<<endl;
        cout<<"\n\t Phone Number:  "<<pno<<endl;
        cout<<"\n\t Marks:         "<<marks<<endl;
        cout<<"\n\t Course Name:   "<<crse<<endl;
        cout<<"\n\t_________________________________________________________________";
    }
};

//**********global declaration for stream object, object*********
fstream fs;
student s;

//***************************************************************
//      function to write in file
//****************************************************************
void write_student()
{
    fs.open("student.dat",ios::binary | ios::app);
        s.getdata();
        srand(s.marks);
        s.application=rand();
        cout<<"\n\t"<<"Your Application no. is : "<<s.application;
        fs.write((char*)&s,sizeof(s));
        getch();
        cout<<"\n\n\t***REGISTRATION DONE***";
        getch();
    fs.close();
}

//***************************************************************
//      function to read all records from file
//****************************************************************
void display()
{
    fs.seekg(0);
    fs.open("student.dat",ios::binary | ios::in);
    if(!fs)
    {
        cout<<"Error in file opening";
    }
    else
    {
        cout<<"\n\nOutput\n\n";
        while(fs.read((char*)&s, sizeof(s)))
        {
            s.showdata();
            cout<<"\n\n====================================\n";
        }
    }
    fs.close();
}

//***************************************************************
//      function to read specific record from file
//****************************************************************
void status()
{
    int num,flag=0;
    system("cls");
    cout<<"\n\n\tPlease Enter The Application number: ";
    cin>>num;
    cout<<"\n\n\t\t\t\tGET STATUS\n";
    fs.open("student.dat",ios::binary | ios::in);
    if(!fs)
    {
        cout<<"\nError in opening file\n";
    }
    else
    {
        while(fs.read((char*)&s, sizeof(s)))
        {
            if(s.application == num)
            {
                system("cls");
                s.showdata();
                flag=1;
            }
        }
        fs.close();
        if(flag==0)
        cout<<"\n\nrecord not exist";
    }
    cout<<"\n\n\n\n\t\t\t\t\tREGISTRATION CONFIRMED\n";
}

//***************************************************************
//      function to modify record of file
//****************************************************************
void modify_data()
{
    int no,found=0;
    system("cls");
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Application number of student";
    cin>>no;
    fs.open("student.dat",ios::binary | ios::in | ios::out);
    fs.seekg(0);
    while(fs.read((char*)&s, sizeof(s)))
    {
        if(s.application==no)
        {
            s.showdata();
            cout<<"\nPlease Enter The New Details of student"<<endl;
            s.getdata();
            fs.seekp(-sizeof(s),ios::cur);
            fs.write((char*)&s,sizeof(s));
            cout<<"\n\n\nRecord Updated";
            found=1;
        }
    }fs.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
}

//***************************************************************
//      function to select course
//****************************************************************
void course()
{
    int wish;
    {
        cout<<"\n\t1.Graduate programme\t2.Post-Graduate programme\t3.Exit\n";
        cout<<"\tEnter Choice: ";
        cin>>wish;
        switch(wish)
        {
            case 1:
                int op;
                {
                    cout<<"\n\t1.Bachelor of Architecture\t2.Bachelor of Technology\t3.Exit\n";
                    cout<<"\tEnter Choice: ";
                    cin>>op;
                    switch(op)
                    {
                        case 1:write_student();
                               status();
                            break;
                        case 2:write_student();
                               status();
                            break;
                        default:cout<<"\n\tInvalid Choice! Select right option\n";
                    }
                }
                break;
            case 2:
                int ch;
                {
                    cout<<"\n\t1.Master of Business Administration\t2.Master of Computer Application\t3.Exit\n";
                    cout<<"\n\tEnter Choice: ";
                    cin>>ch;
                    cout<<"\n\t***Apply for Counselling***\n\n";
                    switch(ch)
                    {
                        case 1:write_student();
                               status();
                               cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\t\t***YOUR REGISTRATION PROCESS COMPLETED***\n";
                            break;
                        case 2:write_student();
                               status();
                            break;
                        default:cout<<"\n\tInvalid Choice! Select right option\n";
                    }
                }
                break;
            default:cout<<"\n\tInvalid Choice! Select right option\n";
        }
    }
}

//***************************************************************
//      function to delete specific record from file
//****************************************************************
void delet()
{
    int num,flag=0;
    system("cls");
    cout<<"\n\n\tPlease Enter The Application number: ";
    cin>>num;
    fs.open("student.dat",ios::binary | ios::in | ios::out);
    fstream fs1;
    fs1.open("temp1.dat",ios::binary | ios::out);
    fs.seekg(0,ios::beg);
    if(!fs)
    {
        cout<<"\nError in opening file\n";
    }
    else
    {
        while(fs.read((char*)&s, sizeof(s)))
        {
            if(s.application!=num )
            {
               fs1.write((char*)&s,sizeof(s));
                flag=1;
            }
        }
        fs.close();
        fs1.close();
        remove("student.dat");
        rename("temp1.dat","student.dat");
        if(flag==0)
        {
            cout<<"\n\nrecord not exist";
        }
    }
    cout<<"\n\n\n\n\t\t\t\t\tREGISTRATION DELETED\n";
}

//***************************************************************
//             FUNCTION OF USER MANUAL
//****************************************************************
void user_manual()
{
    system("cls");
    cout<<"\n\n\t________________________________________________________________________________________________________________________________________________________";
    cout<<"\n\t\t\t\tUSER MANUAL FOR CANDIDATES REGISTRATION PROCESS DTECOUNSELLING (2022-23)";
    cout<<"\n\t________________________________________________________________________________________________________________________________________________________";
    cout<<"\n\n\t1) Log-in to https://dte.mponline.gov.in\n\tLog in to:-  https://dte.mponline.gov.in";
    cout<<"\n\t Select course and click on Apply for Counselling link. ";
    cout<<"\n\n\t2) At course page, click on Click Here button for Registration. ";
    cout<<"\n\n\t3) Select basis of Registration and click on Continue button. ";
    cout<<"\n\n\t4) Fill Entrance Test Roll Number and DOB and proceed for registration. ";
    cout<<"\n\n\t5) Ist Tab : Fill Personal details on the Personal Details Tab ";
    cout<<"\n\n\t6) IInd Tab: Fill Details of Domicile, Category, Class and other certificate details.";
    cout<<"\n\n\t7) IIIrd Tab : Fill Qualifying Exam Details ";
    cout<<"\n\n\t8) IVth Tab: Fill bank account details.";
    cout<<"\n\n\t9) Vth Tab: Fill Loan requirement details.";
    cout<<"\n\n\t10) VIth Tab: Preview and Lock Registration Details - Upload required documents.";
    cout<<"\n\n\tIMP: Choose documents file and click on Upload Document button.";
    cout<<"\n\tThumbnails of documents will be visible and by clicking on View button check the uploaded document.";
    cout<<"\n\t(Document format/size – .jpeg max. 100 KB) ";
    cout<<"\n\tRead the instruction and click OK and then click on Lock and Confirm button. ";
    cout<<"\n\t11) Print Registration Receipt";
    cout<<"\n\n\t-: Utilities For Candidate :-";
    cout<<"\n\tI. Registration Cancellation facility before choice filling payment.";
    cout<<"\n\tII. Check Candidate Status on the portal.";
    cout<<"\n\tIII. Search counselling Roll no. from personal details";
    cout<<"\n\tIV. Receipt Reprint [Registration/Choice filing]";
    cout<<"\n\tV. Resend Temporary Password";
    cout<<"\n\tVI. Forgot/Change Password";
    cout<<"\n\tVII. List of Help Centers";
    cout<<"\n\tDTE Counselling Cell – 0755-2660441\n\tHelp-Desk Contact No. 0755-6720205\n";
    cout<<"\n\n\t\t\t\t***********************************************************************";
}

//***************************************************************
//              FUNCTION OF STUDENT
//****************************************************************
void student()
{
    int choice;
    do
    {
        system("cls");
        cout<<"\n\n\t____________________________________________________________________________________________________";
        cout<<"\n\t| 1.Select Course For Counselling | 2.Data Update | 3.User Manual | 4.Delete registration | ";
        cout<<"5.Exit |\n";
        cout<<"\t____________________________________________________________________________________________________";
        cout<<"\n\n\tSelect Your Choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:course();
                break;
            case 2:modify_data();
                break;
            case 3:user_manual();
                break;
            case 4:delet();
                break;
            default:cout<<"\nInvalid Choice!\nSelect right option\n";
        }
        cout<<"\nCONTINUE WITH STUDENT MENU? ";
        cin>>choice;
    }while(choice!=5);
}

//***************************************************************
//              FUNCTION OF ADMIN
//****************************************************************
void admin()
{
    int b;
    int a=12345;
    cout<<"\n\tEnter the password: ";
    cin>>b;
    if(b==a)
    {
        display();
    }
    else
    {
        cout<<"\n\tYOU ENTERED WRONG PASSWORD\n\n";
        cout<<"\tTRY AGAIN!";
    }
}

//***************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main()
{
    int choice1;
    char ch;
    cout<<"\n\n\n\n\n\t\t\t\t\t\t*****Directorate Technical Education Government Of Madhya Pradesh*****\n";
    getchar();
    cout<<"\n\n\t\t\t\t\t\t\t\t*****Welcome To Counselling Portal*****\n";
    getchar();
    do
    {
        system("cls");
        cout<<"\n\n\t\t\t\t\t\t1.Admin\t\t2.Student\t\t3.Exit";
        cout<<"\n\n\t\t\t\t\t\tSelect Your Category: ";
        cin>>choice1;
        switch(choice1)
        {
            case 1:admin();
                break;
            case 2:student();
                break;
            default:cout<<"\nInvalid Choice!\nSelect right option\n";
        }
        cout<<"\nCONTINUE WITH MAIN MENU? ";
        cin>>choice1;
    }while(choice1!=3);
    return 0;
}
//***************************************************************
//                      END OF PROGRAM
//****************************************************************
