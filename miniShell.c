#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define ARGSIZE 100

char* cmd=NULL;  //pointer for command string, global
char** args;  //pointer array for each arguments in command, global

void cleanup(void){ //free global malloc variables
	free(cmd);
	for(int i=0; i<ARGSIZE; i++)
		free(args[i]);
	free(args);
}

int main(){
	char* ptr;	
	char path[100];

	size_t size;
	ssize_t cmdread; //related to cmd reading error
	pid_t pid;

	int i;
	int cmp; //related to 'quit'

	atexit(cleanup);

	size = 100;
	arg = (char**)malloc(sizeof(char*) * ARGSIZE);

	do{
		//getline error handling
		if((cmdread = getline(&cmd, &size, stdin)) == -1) 
			perror("command reading error"), exit(1);
		cmd[strlen(cmd)-1] = '\0';

		//quit
		if((cmp = strcmp("quit",cmd))==0){
			//if parent has no child, then wait() returns -1 right away
			//parent waits all possible child processes then quit
			while(true){
				if((pid = wait(NULL)) == -1) break;
			}		
			exit(0);
		}	
		//cmd parsing -> args
		i = 0;
		ptr = strtok(cmd, " ");
		while(ptr != NULL){
			args[i++] = ptr;
			ptr = strtok(NULL, " ");
			}
		args[i] == NULL;

		//path
		sprintf(path, "/bin/%s", args[0]);
		
		//if child, then execute the cmd
		if(fork() == 0){
			int exe;
			if((exe = execv(path, args)) == -1){
				perror("command executing error");
				exit(1);
			}else{
				exit(0);
			}	
		}
		else //if parent, wait until child process ends
		{ 
			wait(NULL);
		}	
			 
				

	}while(true);
	
	

	exit(0);
}
