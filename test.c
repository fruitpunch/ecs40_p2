#include <stdio.h>
#include <string.h>

void a(char f[80]){

	strcpy(f,"dam");
	printf("run f %s\n",f);
}

int main(){

	char input[80], command[80]="\0", command2[80]="\0", command3[80]="\0";

	printf("EC:");
	fgets(input, 79, stdin);

	int i, c1=0, t=0;
	for(i=0;i<strlen(input);i++){

		if(input[i]==' '){

			printf("HH\n");
			c1++;
			t=i+1;
			if(input[i-1]==' '||i==0)c1--;
		}

		if(input[i]=='\0')break;

		if(input[i]!=' '&&c1==0){

			command[i-t]=input[i];
		}

		if(input[i]!=' '&&c1==1){
			printf("c2   t:%d  i:%d\n", t, i);
			command2[i-t]=input[i];
		}

		if(input[i]!=' '&&c1==2){
			
			command3[i-t]=input[i];
			printf("c3   t:%d  i:%d %c	\n", t, i, input[i]);
		}
		

	}

	a(command);

	printf("c1:%s c2:%s c3:%s   i:%d\n", command, command2, command3, i);
	return 0;
}