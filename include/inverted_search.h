/**
 * @file    inverted_search.h
 * @author  Akshay Ravikiran Mittha
 * @date    09/07/2026
 * @brief   Contains the declarations of all the functions and structures used in the Inverted Search program.
 * 
 * @details 
 * Functions Performed:
 * - validate_inputs_n_store_files() : Validates the input arguments and stores the file names in the linked list.
 * - insert_at_last() : Inserts the file name at the end of the linked list.
 * - delete_file_from_list() : Deletes the file name from the linked list.
 * - file_exists() : Checks if the file name exists in the linked list.
 * - insert_last() : Inserts the word and file name in the hash table.
 * - print_filename_list() : Prints the file names in the linked list.
 * - get_hash() : Returns the hash index for the given character.
 * - create_database() : Creates the database by processing the file names and storing the words and file names in the hash table.
 * - display_database() : Displays the database.
 * - search_database() : Searches for a word in the database.
 * - save_database() : Saves the database to a file.
 * - update_database() : Updates the database by processing the file names and storing the words and file names in the hash table.
 */

#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

/* Include the necessary header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Define the return values */
#define SUCCESS 0
#define FAILURE 1

/* Define the colors for the output messages */
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define HASH_SIZE 27

/* Define the structure for a node in the linked list */
typedef struct file_node
{
    char file_name[30];
    struct file_node *link;
}Slist;

/* Define the Structure for Sub Node */
typedef struct _subNode
{
    char file_name[30];
    int word_count;
    struct _subNode *link;
}subnode_t;

/* Define the Structure for Main Node */
typedef struct _mainNode
{
    int file_count;
    char word[30];
    subnode_t *sub_link;
    struct _mainNode *link;
}mainnode_t;

/* Define the Structure for Hash Table */
typedef struct _hash_T
{
    short int index;
    mainnode_t *main_link;
}hash_t;

/* Validation Functions */
int validate_inputs_n_store_files(char *argv, Slist **head);

/* File Operation Functions */
int insert_at_last(Slist **head, char *file_name);
void delete_file_from_list(Slist **head, char *file_name);

/* Helper Functions */
int file_exists(Slist *head, char *file_name);
int insert_last(hash_t *arr, char *word, char *filename);

/* Print Function for FileList */
void print_filename_list(Slist *head);

/* Hash Function */
int get_hash(char ch);

/* Database Operation Functions */
int create_database(hash_t *arr, Slist *head);
void display_database(hash_t *arr);
int search_database(hash_t *arr, char *word);
int save_database(hash_t *arr, char *file_name);
int update_database(hash_t *arr, Slist **head, char *file_name);

#endif /* INVERTED_SEARCH_H */