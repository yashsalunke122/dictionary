#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

#define MAX_CMD_LEN 128

// A helper function to spell check a specific file
// 'file_name': Name of the file to spell check
// 'dict': A dictionary containing correct words
int spell_check_file(const char *file_name, const dictionary_t *dict) {
    // TODO Not yet implemented
    return 0;
}


/*
 * This is in general *very* similar to the list_main file seen in lab
 */
int main(int argc, char **argv) {
    
    dictionary_t *dict = create_dictionary();
    char cmd[MAX_CMD_LEN];

    

    printf("CSCI 2021 Spell Check System\n");
    printf("Commands:\n");
    printf("  add <word>:              adds a new word to dictionary\n");
    printf("  lookup <word>:           searches for a word\n");
    printf("  print:                   shows all words currently in the dictionary\n");
    printf("  load <file_name>:        reads in dictionary from a file\n");
    printf("  save <file_name>:        writes dictionary to a file\n");
    printf("  check <file_name>: spell checks the specified file\n");
    printf("  exit:                    exits the program\n");

    while (1) {
        printf("spell_check> ");
        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        else if (strcmp("exit", cmd) == 0) {
            break;
        }
        // TODO Add cases for the other commands
        // Read in the command and any additional arguments (where needed)

        else if (strcmp("add", cmd) == 0) {
            scanf("%s", cmd);
            
            if(strlen(cmd)> 127) {
                printf("Input too large. 127 Character limit\n");
            }
            else {
                if(dict_insert(dict, cmd)!=0) {
                    printf("Error, word not added. Invalid dictionary or word\n");
                }

            }

        }
        else if(strcmp("lookup", cmd)==0)  {
            scanf("%s", cmd);
            if(dict_find(dict, cmd)==0) {
                printf(" '%s' present in dictionary\n", cmd);
            }
            
            else {
                printf(" '%s' not found\n", cmd);
            }
        }

        else if(strcmp("print", cmd)==0) {
            dict_print(dict);
        }
        else if(strcmp("load", cmd)==0) {
            scanf("%s", cmd);
            dict = read_dict_from_text_file(cmd);
            printf("Dictionary successfully read from text file\n");
            
        }
        else if(strcmp("save", cmd)==0) {
            scanf("%s", cmd);
            write_dict_to_text_file(dict, cmd);
        }
        else if(strcmp("check", cmd)==0) {
            scanf("%s", cmd);
            spell_check_file(cmd, dict);
        }

        else {
            printf("Unknown command %s\n", cmd);
        }
        
    }


    dict_free(dict);
    return 0;
}
