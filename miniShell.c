#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define ARGSIZE 100

void cleanup(void){
	free(cmd);
	for(int i=0; i<ARGSIZE; i++)
		free(args[i]);
	free(args);
}

int main(){
	char* cmd=NULL;
	char* ptr;
	char** args;
	char path[100];

	size_t size;
	ssize_t cmdread;//related to cmd reading error
	
	int i;
	int cmpresult;//related to 'quit'
	
	size = 100;
	arg = (char**)malloc(sizeof(char*) * ARGSIZE);

	do{	//getline error handling
		if((cmdread = getline(&cmd, &size, stdin)) == -1) break;
		cmd[strlen(cmd)-1] = '\0';

		//quit
		if((cmpresult = strcmp("quit",cmd))==0) break;
		
		//cmd parsing -> args
		i = 0;
		ptr = strtok(cmd, " ");
		while(ptr != NULL){
			args[i++] = ptr;
			ptr = strtok(NULL, " ");
			}
		//path
		sprintf(path, "/bin/%s", args[0]);
		

	}while(1);
	
	//later -> atexit() !!!
	free(args);
	free(cmd);
	return 0;
}
