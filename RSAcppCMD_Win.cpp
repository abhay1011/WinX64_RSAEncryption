/*Program for Command line RSA encryption i.e converting char into ascii and performing
the RSAencryption on numerical data and saving the data into a file */
//This is windows version
#include<windows.h>//For Sleep(milliseconds)#include<iostream>#include<stdlib.h>#include<fstream>
#include<cstring>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;using namespace std;
namespace mp = boost::multiprecision;
typedef mp::number<mp::cpp_int_backend<4096, 4096, mp::signed_magnitude, mp::unchecked, void> >  int4096_t;//***********classSection*************************class Users{private:
    int64_t p,q,n,phiN,e,d;
    int4096_t temp,ct,msg;    int64_t pvtkey;    char uname[20],pwd[20];    void credential();    int authenticate();
    int64_t gcd(int64_t a,int64_t b);
    int64_t getE();
    int64_t getD(double phiN,double e);
    int4096_t power(int4096_t x,int4096_t y);
    void genKeys();public:    void login();    void signUp();
    int exitProg();
    void rsaFileEncrypt();
    int rsaEncrypt();
    int rsaDecrypt();
    void goBack();};
void Users::goBack(){
    char ch;
    cout<<"Further Continue? Y/N:";
    here:
    cin>>ch;
    if(ch=='y'||ch=='Y')
        return;
    else if(ch=='n'||ch=='N')
        exitProg();
    else{
        cout<<"Invalid Choice"<<endl;
        goto here;
    }

}
//********encryption**Program****/
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
int64_t Users::getD(double phiN,double e){
 double d,flag,i=1;
 int64_t temp;
 do{
    d=((phiN*i)+1)/e;
    temp=d;
    //cout<<"Temp:"<<temp<<endl;
    //cout<<"D :"<<d<<endl;
    flag=d-temp;
    //cout<<"flag: "<<flag<<endl<<endl;
    i++;
 }while(flag!=0.0);
return d;
}
int4096_t Users::power(int4096_t x,int4096_t y){

    int i;
    int4096_t res=1;
    for(i=0;i<y;i++){
        res=res*x;
    }
    return res;
}
void Users::genKeys(){
 system("cls");
 cout<<"Enter the first prime No. P: ";
 cin>>p;
 cout<<"Enter the second prime NO. Q:";
 cin>>q;
 n=p*q;
// cout<<"The N is : "<<n<<endl;//n=p*q
 phiN=(p-1)*(q-1);
// cout<<"The phi(n) is : "<<phiN<<endl;//phiN =(p-1)*(q-1)
 e=getE();
 //cout<<"The e is : "<<e<<endl;
 d=getD(phiN,e);
// cout<<"The d is : "<<d<<endl;
}
/*void Users::rsaFileEncrypt(){
 genKeys();
 system("cls");
 char ch;
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
 goBack();
}*/
int Users::rsaEncrypt(){
 genKeys();
 system("cls");
 string str;
 char name[18];
 char ch;
 int i=0;
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
 cout<<"Save This Data to File Y/N:";
 cin>>ch;
 if(ch=='Y'||ch=='y'){
    cout<<"Save File as :";
    cin>>name;
    rename("encrypted.dat",name);
 }
 goBack();
}
int Users::rsaDecrypt(){
    system("cls");
    fstream myFile("encrypted.dat",ios_base::in);
    fstream decFile("decrypted.dat",ios_base::out);
    int a;
    char ch;
    while (myFile >> a)
    {   ct=a;
        temp=power(ct,d);
        msg=temp%n;
        decFile<<msg<<' ';
    }
    myFile.close();
    decFile.close();
    fstream msgFile("decrypted.dat",ios_base::in);
    cout<<"The Decrypted data"<<endl;
    while(msgFile>>a){
        cout<<(char)a;
    }
    cout<<endl;
    goBack();
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
  char p[20],u[20]; //read uname,pwd,pvtkey from file and match with obeject ifstream rd("credential.dat",ios::in);
 if(!rd){
    cout<<"The credential Data failed to load";
    exit(0);
 }
 while(true){
     rd.getline(u,20,'#');//For reading Username
     rd.getline(p,20,'#');//For reading Password
   //red.getline(pk,20,'#');//For Reading Private key
     if((strcmp(u,uname)==0)&&(strcmp(p,pwd)==0))
      return 1;
     if(rd.tellg()==0||rd.tellg()==-1)
        break;

 }
 cout<<"Login failed!"<<endl<<"Try Again"<<endl;
 Sleep(1500); return 0;}//***********credentialInput**********************void Users::credential(){system("cls"); cout<<"Enter Your Details..."<<endl; cout<<" Username : ";cin>>uname; cout<<" Password : ";cin>>pwd;}//**********user login****************************void Users::login(){ int choice,flag=0; credential();
 cin.clear();
 cin.ignore(10,'\n'); flag=authenticate(); if(flag==1){    system("cls");    cout<<"Login Successfull!"<<endl;    Sleep(1000);    do{
        cout<<"Welcome "<<uname<<endl;        cout<<" 1>List All files."<<endl;        //Always show the encypted data to console!        cout<<" 2>Encrypt Data from Keyboard."<<endl;        cout<<" 3>Encrypt a Text File."<<endl;        //Show Data to the console and also Save to file        cout<<" 4>Decrypt Your Data."<<endl;        cout<<" 5>Switch"<<endl;        cout<<" 6>Exit"<<endl;        cout<<"Choice : ";cin>>choice;        switch(choice){            case 1:system("cls");                   cout<<"The under current directory!"<<endl;                   system("dir *.*");                   cout<<endl<<"*********************"<<endl;                break;            case 2:rsaEncrypt();//keyEncrypt();                break;            case 3:                break;            case 4:rsaDecrypt();//decData();                break;            case 5:                break;            case 6:exitProg();            default:system("cls");                    cout<<"Invalid Input!"<<endl;                break;    }    }while(true); } else{ cout<<"Invalid Username or Password!"; } }//**********user Sign up**************************void Users::signUp(){ system("cls"); string temp; here: credential(); cout<<" Re-enter Password : ";cin>>temp;
 ofstream out("credential.dat",ios::app); if(!out){    cout<<"Failed to create ofstream object!";    exit(-1);    } out<<uname<<'#'<<pwd<<'#'; if(temp!=pwd){    cout<<"Password Did not match!"<<endl;    Sleep(2000);    goto here;    } else{    cout<<"Account Successfully Created"<<endl;    cout<<"Your Private Key is :"<<endl;//Generate Private key here    cout<<"Going Back to main menu..."<<endl;    Sleep(3000);}}//******************dataEncryption****************int main(){ int choice,i=0; Users u1; do{    system("cls");
    cout<<"*************RSA encrption*************"<<endl;    cout<<"Choose any of option:"<<endl;    cout<<" 1>Login"<<endl;    cout<<" 2>SignUp"<<endl;    cout<<" 3>Exit"<<endl;    cout<<"Choice: ";    cin>>choice;
    cin.clear();//It clear cin error flag which stops further input
    cin.ignore(1000,'\n');/*It ignores 1000 char and stop on encountering newline char
     avoid infinite loop on entering non-int and avoid parse failure*/    switch(choice){        case 1:u1.login();            break;        case 2:u1.signUp();            break;        case 3:u1.exitProg();            break;        default:system("cls");
                cout<<"Choose a valid option!\n";
                cout<<i++;                Sleep(1000);            break;    } }while(true); return 0;}