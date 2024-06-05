#include<stdio.h>
int a=1;
void add(int b){
    
    (a+1)++;
    a++;
    printf("%d",a);
    return;
}
int main(){
    add(1);
    printf("%d",a);
    return 0;
}