/*Generating the random sequence of number using the rand() and strand() function */
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<math.h>
//#include<typeinfo>
using namespace std;
int GetRandom(){
    srand(time(0));
    /*It set the seed different using the time
    If srand() is not called the seed is set srand(1) by default*/
    return rand();
}
//5,7,11,13,17,19,23,29,31,37
int main(){
 int arr[]={5,7,11,13,17,19,23,29,31,37};
 char ch='n';
 int n=0,p=0,q=0,i,j,rInt;
 cout<<"Generating Keys : ";
 do{
     //cout<<"\\\b"<<"|\b"<<"/\b";
     rInt=GetRandom();
     i=rInt%10;
    // cout<<i<<endl;
     rInt=GetRandom();
     j=rInt%10;
     //cout<<j<<endl;
     if(i!=j){
        p=arr[i];
        q=arr[j];
        n=p*q;
     }
 }while((n<127)||(n>700));
 cout<<"The p is "<<p<<endl;
 cout<<"THe q is "<<q<<endl;
 getch();
}
