
//
// Created by Mikko Seppi on 20.10.2019.
//
/*
delete_comments removes comments from a file which name is given as a parameter.
*/
char *delete_comments(char *input);


/*
delete_empty_lines removes empty lines from a file which name is given as a parameter.
*/
char *delete_empty_lines(char *input);


/*
read_file reads the file to *char which name is given as a parameter.
Returns char* or NULL if reading file fails.
*/
char *read_file(const char *filename);


/*
write_file writes char *input that is given as a parameter to the file which namr is given as a parameter.
Returns 1 if reading is successful and if it fails returns 0.
*/
int write_file(const char *filename, char *input);


/*
clean_file removes comments and empty lines from file which name is given as a parameter, 
and write clean version of the file to the file named 'filename.clean'.
Returns name of clean file or NULL if cleaning fails.
*/
char *clean_file( char *filename);


/*
Log writes message given as a parameter to the file which name is given as a parameter.
 */
int Log (char *message, char *filename);


/*
Defines that program will end by signal given as a parameter
*/
void sigint_handler(int sig);


/*
Writes time at the moment to the logfile
*/
int timeforlog(char *filename);