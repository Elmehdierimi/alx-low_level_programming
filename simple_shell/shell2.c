#ifndef SHELL_H
#define SHELL_H

#include <string.h> /*strtok*/
#include <stdio.h> /* library of printf*/
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h> /* fork & execve*/
#include <errno.h> /*errno & perror */
#include <signal.h> /*signal management*/
#include <sys/types.h> /*type pid */
#include <sys/wait.h> /*wait*/
#include <sys/stat.h> /*stat function*/
#include <fcntl.h> /* for open files*/

/************* MACROS **************/

#include "macros.h"

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized
 * @env: environ
 * @alias_list: array of pointers
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	char **tokens;
	char **env;
	char **alias_list;
	int exec_counter;
	int file_descriptor;
} data_of_program;

/**
 * struct builtins - it shows the struct for the builtins
 * @builtin: name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	int (*function)(data_of_program *data);
	char *builtin;
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/


int _getline(data_of_program *data);


int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/*======== execute.c ========*/

int execute(data_of_program *data);

/*======== expansions.c ========*/

void expand_variables(data_of_program *data);

void expand_alias(data_of_program *data);

/*it append str to the end of buf*/
int buffer_add(char *buffer, char *str_to_add);

/*===--===== builtins_list.c ==---======*/

int builtins_list(data_of_program *data);

/*======== find_in_path.c ========*/

char **tokenize_path(data_of_program *data);

/* Search for program in path */
int find_program(data_of_program *data);

/*======== str_tok.c ========*/
char *_strtok(char *line, char *delim);
void tokenize(data_of_program *data);

/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* it Change the current directory */
int builtin_cd(data_of_program *data);

/* it Close the shell */
int builtin_exit(data_of_program *data);

/*unset& set&show alias */
int builtin_alias(data_of_program *data);

/* it set the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* it shows help*/
int builtin_help(data_of_program *data);

/*======== builtins_env.c ========*/

/* it delete a var of environ*/
int builtin_unset_env(data_of_program *data);

/* it Shows the environ where the shell goes */
int builtin_env(data_of_program *data);

/* it create or override a var */
int builtin_set_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* it Gets the value of the value of the environ */
char *env_get_key(char *name, data_of_program *data);

/* it Removes a key from the environ */
int env_remove_key(char *key, data_of_program *data);

/* it Overwrite the value of the environ variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* it prints the current environ */
void print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* it prints a str in the standard error */
int _print_error(int errorcode, data_of_program *data);

/* it prints str in the output */
int _print(char *string);

/* it prints a str in the stdr error */
int _printe(char *string);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/*it Counts num of chars of a str */
int str_length(char *string);

/* it Duplicates string */
char *str_duplicate(char *string);

/* it Concatenates 2 strings */
char *str_concat(char *string1, char *string2);

/* it Compares 2 strings */
int str_compare(char *string1, char *string2, int number);

/* Reverse string */
void str_reverse(char *string);

/*======== alias_management.c ========*/

/* print the alias list*/
int print_alias(data_of_program *data, char *alias);

/* set the name of the alias*/
int set_alias(char *alias_string, data_of_program *data);

/*get the name of the alias */
char *get_alias(data_of_program *data, char *alias);

/*======== helpers_numbers.c ========*/

/* Cast from int to str */
void long_to_string(long number, char *string, int base);

/* it count coincidences of char in str */
int count_characters(char *string, char *character);

/* it convert str to num*/
int _atoi(char *s);

#endif
