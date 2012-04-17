#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "directory.h"

typedef struct{
	Directory *currentDir;
	int umask;
	int time;
}Funix;

void init(Funix *funix, Directory *new){


	funix->currentDir=new;
	funix->currentDir->time=funix->time;
}

void cd(Funix *funix, char name1[80], char extra[80]){

	int dNum=funix->currentDir->subN, i;

	if(strlen(extra)>0){

		printf("usage: cd directoryName\n");
		return ;
	}
	if(strcmp("..",name1)==0){

		if(funix->currentDir->previousDir==NULL){}		
		else{

			init(funix,funix->currentDir->previousDir);
		}
	}
	else if(dNum==0)printf("%s: no such directory.\n", name1);
	else{

		for(i=0;i<dNum;i++){

			if(strcmp(name1,funix->currentDir->subDir[i]->name)==0){

				init(funix,funix->currentDir->subDir[i]);
				break;
			}
			else{ 
				if(i==dNum-1)printf("%s: No such directories.\n", name1);
			}

		}
	}

}

int eXit(Funix *funix, char extra[80]){

	if(strlen(extra)>0){

		printf("usage: exit\n");
		return 0;
	}
	exit(0);
	return 0;
}

void writePrompt(Funix *funix){

	Directory *temp;
	int i=0,j;
	char path[20][50];
	temp=(Directory *)malloc(sizeof(Directory));
	temp=funix->currentDir;
	strcpy(path[1],"");
	while(1){

		strcpy(path[i],temp->name);

		if(temp->previousDir!=NULL){
			temp=temp->previousDir;
		}
		else break;
		i++;
	
	}

	for(j=i;j>=0;j--){

		if(j==i){

			printf("/");
		
		}
		else printf("%s/",path[j]);
	}
	
	printf(" # ");

}

void getCommand(Funix *funix, char command1[80], char command2[80], char command3[80]){

	char input[80], commandF1[80]="\0", commandF2[80]="\0", commandF3[80]="\0";
		
	fgets(input, 79, stdin);

	int i, c1=0, t=0;
	for(i=0;i<strlen(input)-1;i++){

		if(input[i]==' '){

			c1++;
			t=i+1;
			if(input[i-1]==' '||i==0)c1--;
		}

		if(input[i]=='\0')break;

		if(input[i]!=' '&&c1==0){

			commandF1[i-t]=input[i];
		}

		if(input[i]!=' '&&c1==1){

			commandF2[i-t]=input[i];
		}

		if(input[i]!=' '&&c1==2){
			
			commandF3[i-t]=input[i];
		}
		

	}
	strcpy(command1, commandF1);
	strcpy(command2, commandF2);
	strcpy(command3, commandF3);


}


void ls(Funix *funix, char command1[80], char extra[80]){

	if(strlen(extra)>0){

		printf("usage: ls [-l]\n");
		return ;
	}

	int i;
	char *octal[]={"rwx", "rw-", "r-x", "r--", "-wx", "-w-", "--x", "---"};

	for(i=0;i<funix->currentDir->subN;i++){

		if(strlen(command1)==0)printf("%s	", funix->currentDir->subDir[i]->name);
		else if(strcmp(command1,"-l")==0)printf("%s	%d	%s	\n",octal[funix->currentDir->subDir[i]->umask->perm], funix->currentDir->subDir[i]->time,funix->currentDir->subDir[i]->name);
		else{ 
			
			printf("%s : Command not found.\n", command1);
			return ;
		}
	}
	if(strlen(command1)==0) printf("\n");
					

}

void mkdir(Funix *funix, char name1[80], char extra[80]){

	if(strlen(extra)>0){

		printf("usage: mkdir directoryName\n");
		return ;
	}

	int dNum=funix->currentDir->subN, i;

	if(strlen(name1)==0)printf("Missing file name.\n");
	else if(dNum<3){

		if(dNum==1&&strcmp(name1,funix->currentDir->subDir[0]->name)==0){
			printf("mkdir: cannot create directory '%s':File exists\n", name1);
		}
		else if(dNum==2&&(strcmp(name1,funix->currentDir->subDir[0]->name)==0)){
			printf("mkdir: cannot create directory '%s':File exists\n", name1);
		}
		else if(dNum==2&&(strcmp(name1,funix->currentDir->subDir[1]->name)==0)){
			printf("mkdir: cannot create directory '%s':File exists\n", name1);
		}			
		else{

			Directory *new;
			Permission *mask;
			new=(Directory *)malloc(sizeof(Directory));
			mask=(Permission *)malloc(sizeof(Directory));
			funix->currentDir->subDir[dNum]=new;
			funix->currentDir->subDir[dNum]->previousDir=funix->currentDir;
			funix->currentDir->subDir[dNum]->time=funix->time;
			funix->currentDir->subDir[dNum]->umask=mask;
			funix->currentDir->subDir[dNum]->umask->perm=funix->umask;
			strcpy(funix->currentDir->subDir[dNum]->name,name1);
			funix->currentDir->subN++;
			for(i=0;i<3;i++){

				new->subDir[i]=NULL;
			}
		}

	}
	else{

		printf("%s already the maximum number of directories.\n", funix->currentDir->name);
	}


}

void umask(Funix *funix, char command1[80], char extra[80]){


	int i, u, uIn, ifNum=0;

	char *commands[]={"0", "1", "2", "3", "4", "5", "6", "7","unknownInput"};


	for(i=0;i<=8;i++){

		if(strcmp(command1,commands[i])==0||i==8){

			break;
		}
	}

	char unknowns[10]={'0','1', '2', '3', '4','5', '6', '7','8','9'};

	if(strlen(extra)>0||i==8){

		for(u=0;u<strlen(command1);u++){

			for(uIn=0; uIn<10; uIn++){

				if(command1[u]==unknowns[uIn]){

					break;
				}
			}
			if(uIn==10){

				printf("usage: umask octal\n");
				return ;
			}
		}
		if(ifNum==0)printf("umask: octal must be between 0 and 7\n");
			
		return ;
	}
	else funix->umask=i;
		

}

int processCommand(Funix *funix, char command1[80]){



	int i;

	char *commands[]={"cd", "exit", "ls", "mkdir", "umask", "unknownInput"};


	for(i=0;i<=5;i++){

		if(strcmp(command1,commands[i])==0){

			break;
		}
	}
	


	return i;
}

void run(Funix *funix){

	printf(".....||===..||....||..| \\...||..||..\\\\...//.....\n");
	printf(".....||.....||....||..||\\\\..||..||...\\\\.//......\n");
	printf(".....||===..||....||..||.\\\\.||..||....)X(.......\n");
	printf(".....||.....\\\\____//..||..\\\\||..||...//.\\\\......\n");
	printf(".....||......\\____/...||...\\ |..||..//...\\\\.....\n");

	printf("                     v1.2 \n");
	printf("Creator: Wen Xi Zhang, Hiu Hong Yu \n");


	funix->time=0;
	Directory *root;
	root=(Directory *)malloc(sizeof(Directory));
	root->previousDir=NULL;
	strcpy(root->name, "/");
	root->subN=0;
	funix->currentDir=root;
	funix->umask=0;


	char command1[80]="\0", command2[80]="\0", command3[80]="\0";



	while(1){

		writePrompt(funix);
		getCommand(funix, command1, command2, command3);
		
		funix->time++;

		init(funix, funix->currentDir);


		switch(processCommand(funix, command1)){

			case 0:
				cd(funix, command2, command3);
				break;
			case 1:
				eXit(funix, command2);
				break;
			case 2:
				ls(funix, command2, command3);
				break;
			case 3:
				mkdir(funix, command2, command3);
				break;
			case 4:
				umask(funix, command2, command3);
				break;
			default:
				if(strcmp(command1,"")==0){}
				//else if(strcmp(command1, "rmdir")==0)printf("Funix does not support rmdir. Please donate to get more future updates.\n");
				else{					
					printf("%s: Command not found.\n", command1);
				}
				break;
		}

		
	}
	return ;
}



