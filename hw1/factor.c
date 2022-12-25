#include <stdio.h>
#include <stdlib.h>

int isPrime(int num){
    int i;
    for(i=2; i<num; i++){
        if(num%i == 0){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    int num = atoi(argv[1]);
    while(num != 1){
        for(int curNum = 2; curNum <= num; curNum++){
            if(isPrime(curNum) && num%curNum == 0){
                printf("%d ", curNum);
                num /= curNum;
                break;
            }
        }
    }
    return 0;
}