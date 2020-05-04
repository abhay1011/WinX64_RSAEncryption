/*RSA algorithm program
STEPS:
1.Choose 2 prime number p and q.
2.Compute n=p*q
3.Calculate phi=(p-1)*(q-1).
4.Choose integer e such that 1<e<phi(n) and gcd of e and phi(n) is 1.(They are co-prime)
5.
*/
#include<iostream>
#include<math.h>
#include<conio.h>
#include<boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
using namespace std;
//Note msg shoud be smaller tha n i.e p*q
//src: https://crypto.stackexchange.com/questions/15021/rsa-problem-if-i-choose-two-specific-small-prime-numbers
int64_t gcd(int64_t a,int64_t b){
    int64_t temp;
    while(1){
        temp=a%b;
        if(temp==0)
        return b;
        a=b;
        b=temp;
    }
}
int64_t getE(int64_t phiN){
    int64_t e=2;
    while(e<phiN)
    {
        if(gcd(e,phiN)==1)
            break;
        e++;
    }
return e;
}
int64_t getD(double phiN,double e){
 double d,flag,i=1;
 int64_t temp;
 do{
    d=((phiN*i)+1)/e;
    temp=d;
    cout<<"Temp:"<<temp<<endl;
    cout<<"D :"<<d<<endl;
    flag=d-temp;
    cout<<"flag: "<<flag<<endl<<endl;
    i++;
 }while(flag!=0.0);
return d;
}
int1024_t power(int1024_t x,int1024_t y){
    int i;
    int1024_t res=1;
    for(i=0;i<y;i++){
        res=res*x;
    }
    return res;
}
int main(){
 int64_t p,q,n,phiN,e,d;
 int1024_t temp,ct,msg;
 cout<<"Enter the first prime No. P: ";
 cin>>p;
 cout<<"Enter the second prime NO. Q:";
 cin>>q;
 n=p*q;
 cout<<"The N is : "<<n<<endl;//n=p*q
 phiN=(p-1)*(q-1);
 cout<<"The phi(n) is : "<<phiN<<endl;//phiN =(p-1)*(q-1)
 e=getE(phiN);
 cout<<"The e is : "<<e<<endl;
 d=getD(phiN,e);
 cout<<"The d is : "<<d<<endl;
 cout<<"Now enter the message :";
 cin>>msg;
 temp=power(msg,e);
 cout<<"power msg^e : "<<temp<<endl;
 ct=temp%n;
 cout<<"THe cipher text ct%n: "<<ct<<endl;
 temp=power(ct,d);
 cout<<"ct^d "<<temp<<endl;
 msg=temp%n;
 cout<<"Original message is :"<<msg<<endl;
 getch();
 return 0;
}
