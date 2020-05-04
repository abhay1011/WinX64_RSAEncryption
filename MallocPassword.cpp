#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
int main(){
int i=0;
char *u,ch;
u=(char *)calloc(4,sizeof(char));
for(i=0;i<4;i++){
    cin>>u[i];
}
cout<<u;
u=(char *)realloc(u,5);
for(i=4;i<8;i++){
    cin>>u[i];
}
u[8]='\0';
cout<<u;
return 0;
}
