#include<stdio.h>
char monocipher_encr(char);

char str[20];
int main() {
    char str[20], str2[20];
    int i;
    printf("\n Enter String:");
    fgets(str, sizeof(str), stdin);
    for (i = 0; str[i] != '\0'; i++) {
        str2[i] = monocipher_encr(str[i]);
    }
    str2[i] = '\0';
    printf("\n Before encryption:%s", str);
    printf("\n After encryption:%s\n", str2);
}
char monocipher_encr(char a) {
    int i;
    char a1[53] ="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char a2[53]="lqsakjpdmetnfgruwhuizyeoxbLQSAKJPDMETNFGRUWHUIZYEOXB";
    if (a == ' ' || a == '\t') {
        return a;
    }
    for (int i = 0; i<52; i++) {
        if(a==a1[i]){
        	return a2[i];
		}
    }
    return a;
}
