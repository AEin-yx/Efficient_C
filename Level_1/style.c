#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[argc+1]){
    puts("Hello World");
    if(argc>1){
        while(true){
            puts("some program never stop");
        }
    } else {
        do{
            puts("but this one does");
        }while(false);
    }
    return EXIT_SUCCESS;
}