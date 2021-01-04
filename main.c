
//
// Created by Mikko Seppi on 20.10.2019.
//
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "clean.c"

pid_t p; 
int run = 1;
char logfile[100]= "log.txt"; //Defines logfile name

void sigint_handler(int sig)  //Defines that program will end by signal given as a parameter
{    
        printf("\nProgram ends\n");
        Log("program ends because ctr+c\n",logfile);
	    kill(p,sig);
        exit(0);
        run = 0;

} 

int main() 
{ 
        signal(SIGINT, sigint_handler); // Defines that program will end with ctrl+c

        timeforlog(logfile); // writes time when program start to the logfile

  while(run){ 
        char input[100]; 
        Log("Asking files that needs cleaning\n",logfile);
        printf("Enter filenames separated by ',' or end program with empty input: "); //asks name of files that need cleaning
        fgets(input, sizeof input, stdin); 
        if(input[0]=='\n' ){ // checks if user wants to end program
        run = 0;
        printf("program ends\n");
        Log("Program ends because empty input\n", logfile);
        }

    else{
        int len=strlen(input); 

    if(input[len-1]=='\n'){//deletes newline from input string
        input[len-1]='\0';
    }
         
        const char s[2] = ",";
        char *filename;
        filename = strtok(input, s);//takes one file from the input string
    
    while( filename != NULL ) { //Makes while loop to clean all files from input stream
        
    int fd[2];  
    

    if (pipe(fd)==-1) //opens pipe and check if it failed
    { 
        printf("Pipe Failed\n"); 
        Log("Pipe Failed\n",logfile);
        return 1; 
    } 
  
        Log("Making fork\n" ,logfile);
        
    p = fork(); // makes child process
     
  
    if (p < 0) //checks if fork failed
    { 
        printf("fork Failed\n" ); 
        Log("fork Failed\n" ,logfile);
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        close(fd[0]);  // Close reading of the pipe
        write(fd[1], filename, strlen(filename)+1); // writes filename to the child trought the pipe
        Log("Parent process sends filename to child\n" ,logfile);
        close(fd[1]); 
        Log("Parent is waiting that child process ends\n" ,logfile);
        wait(NULL); // Waits for child 
        }
  
    // child process 
    else
    { 
        signal(SIGINT, SIG_IGN); // makes child to ignore signal SIGINT
        close(fd[1]);  // Close writing of pipe 
        char str2[100]; 
        char orig[100];
        read(fd[0], str2, 100); // reads filename from parent
        Log("Child receive filename\n",logfile);
        strcat(orig,str2); // saves original file name to str2
        char *new_name = clean_file(str2); // cleans the file
        Log("Child cleans the file\n",logfile);

        if(new_name==NULL){ // checks if cleaning failed 
        printf("Failed to clean file %s\n",str2);
        Log("Child failed to clean the file\n",logfile);
        }

        else{
        printf("File %s is now clean in file ",orig); 
        printf("%s\n",new_name);
        Log("cleaning succeed\n",logfile);
        }

        close(fd[0]); //  Close reading of pipe
        Log("Child dies\n",logfile);
        exit(0);  // kills child
        }

        filename = strtok(NULL, s); // takes another filename from the input string

        }
        }
    }
}
    

    
  
    
    
