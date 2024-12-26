#include<stdio.h>
#include<stdlib.h>
 int main(){
	int i=0;
	char c;
	char s[5];
	for(i=0;i<5;i++){
		scanf("%c",&s[i]); 
		c = s[i];
		printf("%c %c\n",s[i],c);
	} 
	return 0;
 } 
