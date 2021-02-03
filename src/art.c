#include <stdlib.h>
#include <stdio.h>

int main()
{
    char message[101];
    int e;
    scanf("%[^\n]%n", message, &e);
    if(e % 2 == 0) {
        printf("Error");
        exit(1);
    }
    int s=0;
    while(s < e) {
        for(int i=0;i<s;i++){
            printf("%c", 32);
        }
        for(int i=s; i<e; i++){
            printf("%c",message[i]);
        }
        printf("\n");
        s++;
        e--;
    }
    e+=2;s-=2;
    while(s>=0) {
        for(int i=0;i<s;i++){
            printf("%c", 32);
        }
        for(int i=s; i<e; i++){
            printf("%c",message[i]);
        }
        printf("\n");
        s--;
        e++;
    }

    return 0;
}
