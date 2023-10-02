#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

dictionary_t *create_dictionary() {
    dictionary_t *dict = malloc(sizeof(dictionary_t));
    if (dict == NULL) {
        return NULL;
    }
    dict->root = NULL;
    dict->size = 0;
    return dict;
}

void dict_insert_helper(node_t* root, char *word) {
    if(root == NULL) {
        node_t *node = (node_t*) malloc(sizeof(node_t));
        node->left = node->right = NULL;
        strcpy(node->word,word);
        root = node;
    }
}

int dict_insert(dictionary_t *dict, const char *word) {
    // TODO Not yet implemented
    if (word == NULL) {
        return -1; // Invalid input
    }
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    

    strcpy(new_node->word, word);
    //new_node->word[MAX_WORD_LEN - 1] = '\0'; //null terminator in case of overflow


    node_t *current = dict->root;
    node_t *parent = NULL;


    while (current != NULL) {
        parent = current;
        int cmp = strcmp(word, current->word);

        if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (parent == NULL) {
        dict->root = new_node;
    }
    else {
        int cmp = strcmp(word, parent->word);
        if (cmp < 0) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
    }

    dict->size++;
    return 0;
}

int dict_find_helper(const node_t *node, const char *word) {
    if (node == NULL) {
        return 1; 
    }
    int cmp = strcmp(word, node->word);

    if (cmp == 0) {
        return 0; 
    } else if (cmp < 0) {
        return dict_find_helper(node->left, word); 
    } else {
        return dict_find_helper(node->right, word); 
    }
}

int dict_find(const dictionary_t *dict, const char *word) {
    if (dict == NULL || dict->root == NULL || word == NULL) {
        return -1; 
    }

    return dict_find_helper(dict->root, word);
}
void dict_print_helper(node_t* node) {
    if(node == NULL) {
        return;
    }
    dict_print_helper(node->left);
    printf("%s\n", node->word);
    dict_print_helper(node->right);
    //Inorder traversal
}

void dict_print(const dictionary_t *dict) {
    if (dict == NULL || dict->root == NULL) {
        return;
    }
    dict_print_helper(dict->root);
    
}

void dict_free_helper(node_t* node) {
    if(node == NULL) {
        return;
    }
    dict_free_helper(node->left);
    dict_free_helper(node->right);
    
    //free(node->word);
    free(node);

}


void dict_free(dictionary_t *dict) {
    if (dict == NULL) {
        //free(dict);
        return;
    }
    
    dict_free_helper(dict->root);
    free(dict);
}

dictionary_t *read_dict_from_text_file(const char *file_name) {
    dictionary_t *dict = create_dictionary();
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    char word[MAX_WORD_LEN];
    
    while(fscanf(file, "%s", word) != EOF) {
        dict_insert(dict, word);
    }

    fclose(file);
    return dict;
}
void write_dict_text_helper(node_t* node, FILE *file_name) {
    //FILE *file = fopen(file_name, "w");
    if(node == NULL) {
        return;
    }
    fprintf(file_name, "%s\n", node->word);
    write_dict_text_helper(node->left, file_name);
    write_dict_text_helper(node->right, file_name);
    //preorder traversal
}

int write_dict_to_text_file(const dictionary_t *dict, const char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    else if (dict == NULL) {
        printf("Invalid input(save)");
        return -1;
    }
    else if(dict->root == NULL) {
        printf("Empty Dictionary");
        return -1;
    }
    
    write_dict_text_helper(dict->root, file);
    fclose(file);
    return 0;

}
