#include <stdio.h>
#include <stdbool.h>

int main(){
    int a[6] = {1,2,3};
    int b[3] = {2,5,6};
    bool flag = false;
    for( int i =0; i<3; i++){
        int x;
        for(int j =0 ; j<3+i;j++){
            if(b[i]==a[j]){
                flag = true;
                i++;
            }
            else{
                flag = false;
            }
            x=j;
        }
        if(flag==false){
            a[x+1]=b[i];
        }
    }
    for( int i =0; i<6; i++){
        printf("%d\n",a[i]);
    }
}