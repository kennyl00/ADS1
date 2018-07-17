#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ternarytree.h"
#include "linklist.h"

/* Kenny Lee 801361 3/9/17 */

/* Creating a ternary tree */
struct node
*new_node(char *word){
    struct node *new;

    new = malloc(sizeof(struct node));
    if(new == NULL){
        printf("MALLOC FAILURE\n");
        exit(EXIT_FAILURE);

    }
    new->left = NULL;
    new->equal = NULL;
    new->right = NULL;
    new->data = *word;
    new->end_of_key = FALSE;
    new->weight = 0;

    return new;
}

struct node
*insert(struct node *pNode, char *word, int weight){

    if(pNode == NULL){
        pNode = new_node(word);

    }

    if(*word < pNode->data){
        pNode->left= insert(pNode->left, word, weight);

    }else if(*word == pNode->data){
        if(*(word+1) == '\0'){
            pNode->end_of_key = TRUE;
            pNode->weight = weight;


        }else {
            pNode->equal= insert(pNode->equal, word+1, weight);

        }

    }else {
        pNode->right = insert(pNode->right, word, weight);

    }

    return pNode;
}

/* finding the end of the prefix. If the flag is true, it's a
word and it gets printed out */
struct link_list
*find_and_traverse(struct node *pNode, char *prefix, FILE *ofp){
    char *buffer = NULL;
    char *second_prefix = prefix;
    int comparisons = 0;
    struct link_list *list = NULL;

    buffer = malloc(MAXCHAR*sizeof(char));
    if(buffer == NULL){
        printf("MALLOC FAILURE\n");
        exit(EXIT_FAILURE);

    }

    while(*prefix != '\0' && pNode != NULL){

        if(*prefix < (pNode->data)){
            pNode = pNode->left;
            comparisons ++;
            continue;

        }

        if(*prefix > pNode->data){
            pNode = pNode->right;
            comparisons ++;
            continue;

        }

        if(*prefix == pNode->data){
            pNode = pNode->equal;
            prefix = prefix+1;
            comparisons ++;
            continue;

        }

    }

    if(pNode != NULL){
        if(pNode->end_of_key == TRUE){

            buffer[strlen(prefix)+1] = '\0';
            list = insert_link_list(list, buffer, pNode->weight);


        }
    }

    if(pNode == NULL){
        if(*prefix != '\0'){
            fprintf(ofp, "NOTFOUND\n");

        }

    }else{
        list = traverse(pNode, second_prefix, buffer, strlen(prefix),
        ofp, list);

    }

    printf("Prefix:  %s found with %d char comparisons\n",
    second_prefix, comparisons);

    return list;
}

/* moves around the tree and prints out if it's a word */
struct link_list
*traverse(struct node *pNode, char *second_prefix, char *buffer,
    int depth, FILE *ofp, struct link_list *list){


    if(pNode == NULL){
        return list;

    }

    list = traverse(pNode->left, second_prefix, buffer, depth, ofp,
        list);

    buffer[depth] = pNode->data;

    if(pNode->end_of_key == TRUE){
        buffer[depth+1] = '\0';

        list = insert_link_list(list, buffer, pNode->weight);

    }

    list = traverse(pNode->equal, second_prefix, buffer, depth+1, ofp,
        list);
    list = traverse(pNode->right, second_prefix, buffer, depth, ofp,
        list);

    return list;
}
