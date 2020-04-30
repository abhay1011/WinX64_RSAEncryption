/*Program for Command line RSA encryption i.e converting char into ascii and performing
the RSAencryption on numerical data and saving the data into a file */
//This is windows 64 bit version
#include<windows.h>//For Sleep(milliseconds)#include<iostream>
#include<conio.h>#include<stdlib.h>#include<fstream>
#include<cstring>
#include <boost/multiprecision/cpp_int.hpp> //For using larger integer numbers
using namespace boost::multiprecision;using namespace std;
namespace mp = boost::multiprecision;
//For Using the int4096_t data type
typedef mp::number<mp::cpp_int_backend<4096, 4096, mp::signed_magnitude, mp::unchecked, void> >  int4096_t;//***********classSection*************************
class Users{private:
    int64_t p,q,n,phiN,e,d;
    char ch,name[20];
    int4096_t temp,ct,msg;    char uname[20],pwd[20];    void credential();    int authenticate();
    int64_t gcd(int64_t a,int64_t b);
    int64_t getE();
    int64_t getD(double phiN,double e);
    int4096_t power(int4096_t x,int4096_t y);
    void genKeys();
    void saveFile();public:    void login();    void signUp();
    int exitProg();
    void rsaFileEncrypt();
    int rsaEncrypt();
    void rsaDecrypt();
    void pressKey();};
void Users::pressKey(){
    cout<<"\n*****************************************"<<endl;
    cout<<"Press any key to continue..."<<endl;
    getch();
}
//GCD function
int64_t Users::gcd(int64_t a,int64_t b){
    int64_t temp;
    while(1){
        temp=a%b;
        if(temp==0)
        return b;
        a=b;
        b=temp;
    }
}
//For calculating e(Private key) for encryption
int64_t Users::getE(){
    int64_t retE=2;
    while(retE<phiN)
    {
        if(gcd(retE,phiN)==1)
            break;
        retE++;
    }
return retE;
}
//For calculating d (public Key) for decryption
int64_t Users::getD(double phiN,double e){
 double d,flag,i=1;
 int64_t temp;
 do{
    d=((phiN*i)+1)/e;
    temp=d;
    flag=d-temp;
    i++;
 }while(flag!=0.0);
return d;
}
//For find powers of BigIntegers
int4096_t Users::power(int4096_t x,int4096_t y){

    int i;
    int4096_t res=1;
    for(i=0;i<y;i++){
        res=res*x;
    }
    return res;
}
//For generating all RSA variables
void Users::genKeys(){
 cout<<"Enter PRIME no. Between 10 & 30"<<endl;
 cout<<"e.g[11,13,17,19,23,29]"<<endl;
 cout<<" 1st Prime No. : ";cin>>p;
 cout<<" 2nd Prime No. : ";cin>>q;
 n=p*q;
 phiN=(p-1)*(q-1);
 e=getE();
 d=getD(phiN,e);
}
void Users::saveFile(){
 while(true){
     cout<<"Save This Data to File Y/N:";
     cin>>ch;
     if(ch=='Y'||ch=='y'){
        cout<<"Save File as :";
        cin>>name;
        if(rename("encrypted.dat",name)==0){
            cout<<"File Saved!"<<endl;
            Sleep(2000);
            break;
        }
        else{
            cout<<"FIle NOT saved"<<endl;
            cout<<"Try Again!"<<endl;
        }
     }
     else if(ch=='n'||ch=='N'){
        break;
     }
     else{
        cout<<"Enter Correct Input"<<endl;
     }
 }
}
void Users::rsaFileEncrypt(){
 system("cls");
 cout<<"Please name file to encrypt : ";
 cin>>name;
 ofstream out("encrypted.dat",ios::out);
 fstream  rdChar(name,ios::in); if(!out){    cout<<"Failed to create ofstream object!";    exit(-1);    }

 if(!rdChar){
    cout<<" File not Found!"<<endl;
    cout<<" Enter valid name with extension!"<<endl;
    pressKey();
    return;
 }
 else{
    cout<<" Found the File!"<<endl;
    cout<<"Now enter your private key : ";
    cin>>e;
 }
 cout<<"Encrypting Data!"<<endl;
 while(rdChar.get(ch)){
    int m=ch;
    temp=power(m,e);
    ct=temp%n;
    out<<ct<<' ';
    cout<<ct;
 }
 cout<<"\nData Encryption Complete !"<<endl;
 rdChar.close();
 out.close();
 saveFile();
}
int Users::rsaEncrypt(){
 system("cls");
 string str;
 int i=0;
 cout<<"Please enter your private key : ";
 cin>>e;
 cout<<"Now enter the message :";
 cin.ignore(10,'\n');
 getline(cin,str);
 ch=str[i];
 ofstream out("encrypted.dat",ios::out); if(!out){    cout<<"Failed to create ofstream object!";    exit(-1);    }
    cout<<"Encrypting Data!"<<endl;
 while(ch!='\0'){
    int m=ch;
    temp=power(m,e);
    ct=temp%n;
    out<<ct<<' ';
    cout<<ct;
    i++;
    ch=str[i];
 }
 cout<<"\nData Encryption Complete !"<<endl;
 out.close();
 saveFile();
}
void Users::rsaDecrypt(){
    system("cls");
    int a;
    cout<<"Name the File.extension to Decrypt"<<endl;
    cin>>name;
    fstream encInt(name,ios::in);
    if(!encInt){
        cout<<"The file You have entered not found!"<<endl;
        pressKey();
        return;
    }
    cout<<"Now enter your public key : ";
    cin>>d;
    //Saving the dec into decrypted.dat
    fstream decFile("decrypted.dat",ios_base::out);
    while (encInt >> a)
    {   ct=a;
        temp=power(ct,d);
        msg=temp%n;
        decFile<<msg<<' ';
    }
    encInt.close();
    decFile.close();
    fstream msgFile("decrypted.dat",ios_base::in);//for Reading decInt
    fstream txtFile("originalTxt.dat",ios_base::out);//For saving char
    cout<<"The Decrypted data"<<endl;
    while(msgFile>>a){
        cout<<(char)a;
        txtFile<<char(a);
    }
    msgFile.close();
    txtFile.close();
    while(true){
        cout<<"\nSave The Data? Y/N :";
        cin>>ch;
        if(ch=='y'||ch=='Y'){
            cout<<"Please name the file:";
            cin>>name;
            if(rename("originalTxt.dat",name)==0)
                cout<<"File Saved Successfully!"<<endl;
            else
                cout<<"Failed to Save the file"<<endl;
            break;
        }
        else if(ch=='n'||ch=='N')
        {   cout<<"Going back to previous menu"<<endl;
            //delete both files decrypted.dat and originalTxt.dat
            break;
            }
        else
        {   cout<<"Invalid Option! Try Again!"<<endl;
        }
    }
}
//******to Close The Program**********************
int Users::exitProg(){
 char choice;
 cout<<"Exit The Program (Y/N) :";
 cin>>choice;
 cin.clear();
 cin.ignore(20,'\n');
 if(choice=='Y'||choice=='y')
    exit(0);
 else if(choice=='n'||choice=='N'){
    cout<<"Cancelled!"<<endl;
    Sleep(1000);
 }
 else{
    cout<<"Please press Y or N"<<endl;
    Sleep(1000);
 }
return 1;
}//***********AuthenticatingCredential.dat*********int Users::authenticate(){
  char psw[20],u[20]; //read uname,pwd,pvtkey from file and match with obeject ifstream rd("credential.dat",ios::in);
 if(!rd){
    cout<<"The credential Data failed to load";
    exit(0);
 }
 while(true){
     rd.getline(u,20,'#');//For reading Username
     rd.getline(psw,20,'#');//For reading Password
     rd>>p;
     rd>>q;
   //red.getline(pk,20,'#');//For Reading Private key
     if((strcmp(u,uname)==0)&&(strcmp(psw,pwd)==0))
      {   n=p*q;
          return 1;
          }
     if(rd.tellg()==0||rd.tellg()==-1)
        break;

 }
 cout<<"Check username and password!"<<endl<<" Try Again!"<<endl;
 pressKey(); return 0;}//***********credentialInput**********************void Users::credential(){system("cls"); cout<<"Enter Your Details..."<<endl; cout<<" Username : ";cin>>uname; cout<<" Password : ";cin>>pwd;}//**********user_login****************************void Users::login(){ int choice,flag=0; credential(); flag=authenticate(); if(flag==1){    cout<<"Login Successfull!"<<endl;    Sleep(1000);    do{ system("cls");
        cout<<"Welcome "<<uname<<endl;        cout<<" 1>List All files."<<endl;        //Always show the encypted data to console!        cout<<" 2>Encrypt Data from Keyboard."<<endl;        cout<<" 3>Encrypt a Text File."<<endl;        //Show Data to the console and also Save to file        cout<<" 4>Decrypt Your Data."<<endl;        cout<<" 5>Switch User"<<endl;        cout<<" 6>Exit"<<endl;        cout<<"Choice : ";
        cin.clear();
        cin.ignore(100,'\n');
        cin>>choice;        switch(choice){            case 1:system("cls");                   cout<<"Files under current directory!"<<endl;                   system("dir *.*");                   cout<<endl<<"*********************"<<endl;
                   cout<<"Press any key to continue.."<<endl;
                   getch();                break;            case 2:rsaEncrypt();//keyEncrypt();                break;            case 3:rsaFileEncrypt();                break;            case 4:rsaDecrypt();//decData();                break;            case 5:return;                break;            case 6:exitProg();            default:system("cls");                    cout<<"Invalid Input!"<<endl;                break;    }    }while(true); } }//**********user Sign up**************************void Users::signUp(){ system("cls"); string temp; here: credential(); cout<<" Re-enter Password : ";
 cin>>temp; if(temp!=pwd){    cout<<"Password Did not match!"<<endl;
    pressKey();    goto here;    }
 else if(strlen(pwd)<8){
    cout<<"Password should be of at least of 8 character!"<<endl;
    pressKey();
    goto here;
 } else{
    ofstream out("credential.dat",ios::app);    if(!out){    cout<<"Failed to create ofstream object!";    exit(-1);    }
    genKeys();    out<<uname<<'#'<<pwd<<'#'<<'\n';
    out<<p<<' '<<q;    cout<<"Account Successfully Created"<<endl;    cout<<"\nNote Down Your Keys:"<<endl;
    cout<<"  Private Key : "<<e<<endl;
    cout<<"  Public Key : "<<d<<endl;    pressKey();}}//******************dataEncryption****************int main(){ int choice,i=0; Users u1; do{    system("cls");
    cout<<"*************RSA encrption*************"<<endl;    cout<<"Choose any of option:"<<endl;    cout<<" 1>Login"<<endl;    cout<<" 2>SignUp"<<endl;    cout<<" 3>Exit"<<endl;    cout<<"Choice: ";    cin>>choice;
    cin.clear();//It clear cin error flag which stops further input
    cin.ignore(1000,'\n');/*It ignores 1000 char and stop on encountering newline char
     avoid infinite loop on entering non-int and avoid parse failure*/    switch(choice){        case 1:u1.login();            break;        case 2:u1.signUp();            break;        case 3:u1.exitProg();            break;        default:system("cls");
                cout<<"Choose a valid option!\n";
                cout<<i++;                Sleep(1000);            break;    } }while(true); return 0;}