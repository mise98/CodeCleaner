

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
#include "clean.h"




/*
delete_comments removes comments from a file which name is given as a parameter.
*/
char *delete_comments(char *input) {
	size_t koko = strlen(input);
	char *tau = malloc(koko + 100);
	int a = 0;
	int b = 0;
	int c = 0;
	for (int i = 0; i < koko; i++) {
		if ((input[i] == '/') && (input[i + 1] == '*')) {
			a = 1;
		}
		else if ((input[i] == '*') && (input[i + 1] == '/')&&(a==1)) {
			a = 0;
			i += 1;
		}
		else if ((input[i] == '/') && (input[i + 1] == '/')) {
			c = 1;
		}
		else if ((input[i] == '\n')&&(c==1)) {
			c = 0;
		}
		else if ((a == 0)&&(c==0)) {
			tau[b] = input[i];
			b += 1;
		}
	}
	tau[b] = 0;
	free(input);
	return tau;
}


/*
delete_empty_lines removes empty lines from a file which name is given as a parameter.
*/
char *delete_empty_lines(char *input){
size_t koko = strlen(input);
	char *tau = malloc(koko + 100);
	int b = 0;
	for (int i = 0; i < koko; i++) {
		if((input[i] == '\n') && (input[i + 1] == '\n')){			
		}
		else{
		tau[b] = input[i];
		b += 1;
		}
	}
	tau[b] = 0;
	free(input);
	return tau;

}


/*
read_file reads the file to *char which name is given as a parameter.
Returns char* or NULL if reading file fails.
*/
char *read_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return NULL;

    char *buf = NULL;
    unsigned int count = 0;
    const unsigned int ReadBlock = 100;
    unsigned int n;
    do {
        buf = realloc(buf, count + ReadBlock + 1);
        n = fread(buf + count, 1, ReadBlock, f);
        count += n;
    } while (n == ReadBlock);

    buf[count] = 0;

    fclose(f);
    return buf;
}


/*
write_file writes char *input that is given as a parameter to the file which namr is given as a parameter.
Returns 1 if reading is successful and if it fails returns 0.
*/
int write_file(const char *filename, char *input){
FILE *fileAddress;
   fileAddress = fopen(filename, "w");
   int i;
   int len = strlen(input);
   if (fileAddress != NULL) {
	for (i = 0; i < len; i++) {
	   fputc (input[i], fileAddress);
	}
	fclose(fileAddress);
    return 1;		
   }
   else {
    return 0;
   }
}


/*
clean_file removes comments and empty lines from file which name is given as a parameter, 
and write clean version of the file to the file named 'filename.clean'.
Returns name of clean file or NULL if cleaning fails.
*/
char *clean_file( char *filename){
	char *m = read_file(filename);
	
	if(m==NULL){
		return NULL;
	}
	else{
	char* j= delete_comments(m);
	char* k = delete_empty_lines(j);

	char* new_name = strcat(filename,".clean");
	int check =write_file(new_name,k);
	if(check==0){
		return NULL;
	}
	else{
	return new_name;
	}
	}
}



 /*
Log writes message given as a parameter to the file which name is given as a parameter.
 */
int Log (char *message, char *filename)
{
FILE *fileAddress;
   fileAddress = fopen(filename, "a+");
   if (fileAddress != NULL) {
	
	   fprintf( fileAddress,"%s", message);
   
	fclose(fileAddress);
    return 1;		
   }
   else {
    return 0;
   } 
	
}


/*
timeforlog writes time at the moment to the logfile which name is given as a parameter.
*/
int timeforlog(char *filename){
	FILE *fileAddress;
   fileAddress = fopen(filename, "a+");
   if (fileAddress != NULL) {
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
	Log("-------------------\n",filename);
	fprintf(fileAddress,"%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fclose(fileAddress);
    return 1;		
   }
   else {
    return 0;
   } 
	
}


 
