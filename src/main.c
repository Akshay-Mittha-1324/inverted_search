/**
 * @file    main.c
 * @author  Akshay Ravikiran Mittha
 * @date    09/07/2026
 * @brief   Entry point of the Inverted Search Program. Handles user interaction and menu-driven operations.
 * 
 * @details 
 * Functions Performed:
 * - main() : Entry point of the Inverted Search program. Handles user interaction and menu-driven operations.
 */

#include "../include/inverted_search.h"

int main(int argc, char *argv[])
{
    Slist *head = NULL;
    /* Check if files are passed as command line arguments */
    if(argc <= 1)
    {
        printf(RED "\nINFO: Usage: ./inverted_search file1 file2 ...\n" RESET);
        return FAILURE;
    }

    /* Validate inputs and store files in linked list */
    printf(YELLOW "Validating Files...\n" RESET);
    for(int i  = 1; i < argc; i++)
    {
        /* Validate and store */
        if(validate_inputs_n_store_files(argv[i], &head) == FAILURE)
            continue;
        
        printf(GREEN "\nINFO: Successfull: inserting %s File Name in the List\n" RESET, argv[i]);
    }
    if(head == NULL)
    {
        printf(RED "\nINFO: No Files were Inserted In the List\n" RESET);
        return FAILURE;
    }

    print_filename_list(head);

    /* Initializing Hash Table */
    hash_t arr[HASH_SIZE];
    for(int i = 0; i < HASH_SIZE; i++)
    {
        arr[i].index = i;
        arr[i].main_link = NULL;
    }
    
    char opr, word[30], file_name[30], database_file[30];
    short int is_create_done = 0, is_update_done = 0;
    do
    {
        printf(MAGENTA "\nMain Menu:\n"
                "1. Create Database\n"
                "2. Display Database\n"
                "3. Search Database\n"
                "4. Update Database\n"
                "5. Save Database\n"
                "6. Exit\n"
                "Enter your Choice: " RESET);
        scanf("%hhd",&opr);
        switch(opr)
        {
            case 1:
                if(is_create_done)
                {
                    printf(RED "\nINFO: Database Is Already Created\n" RESET);
                    break;
                }   
                create_database(arr, head);
                is_create_done = 1;
                break;
            case 2:
                if(!is_create_done && !is_update_done)
                {
                    printf(RED "\nINFO: Database Is Not Created\n" RESET);
                    break;
                }
                display_database(arr);
                break;
            case 3:
                if(!is_create_done && !is_update_done)
                {
                    printf(RED "\nINFO: Database Is Not Created\n" RESET);
                    break;
                }
                printf(CYAN "Enter the word to search: " RESET);
                scanf("%29s", word);
                search_database(arr, word);
                break;
            case 4:
                printf(CYAN "Enter the Database File: " RESET);
                scanf("%29s", database_file);
                if(update_database(arr, &head, database_file) == FAILURE)
                    printf(RED "\nINFO: Database Update Failed in %s File\n" RESET, database_file);
                else
                {
                    printf(GREEN "\nINFO: Database Updated in %s File\n" RESET, database_file);
                    is_update_done = 1;
                }
                break;
            case 5:
                if(!is_create_done && !is_update_done)
                {
                    printf(RED "\nINFO: Database Is Not Created\n" RESET);
                    break;
                }
                printf(CYAN "Enter the File Name to save Database: " RESET);
                scanf("%29s", file_name);
                if(save_database(arr, file_name) == FAILURE)
                    printf(RED "\nINFO: Database Save Failed in %s File\n" RESET, file_name);
                else
                    printf(GREEN "\nINFO: Database Saved in %s File\n" RESET, file_name);
                break;
            case 6:
                printf(GREEN "\nINFO: Exiting...\n" RESET);
                break;
            default:
                printf(RED "\nINFO: ERROR: Please Enter valid Operation\n" RESET);
                break;
        }
    } while (opr != 6);
    
    return SUCCESS;
}