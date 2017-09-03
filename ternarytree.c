#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ternarytree.h"

/* Creating a new node while initialising its variables */
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

/* Creating a ternary tree by moving each character left, right or down
depending on its value */
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
int
find_and_traverse(struct node *pNode, char *prefix, FILE *ofp){
    char *buffer = NULL;
    char *secondPrefix = prefix;
    int comparisons = 0;

    buffer = malloc(250*sizeof(char));
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

            /* buffer is a placeholder for the prefix, it adds an extra nul
            char at the end for the next function*/
            buffer[strlen(prefix)+1] = '\0';
            fprintf(ofp, "key:  %s%s --> weight:  %d\n", secondPrefix,
            buffer, pNode->weight);


        }
    }

    if(pNode == NULL){
        if(*prefix != '\0'){
            fprintf(ofp, "NOTFOUND\n");

        }

    }else{
        traverse(pNode, secondPrefix, buffer, strlen(prefix), ofp);

    }



    return comparisons;
}

/* moves through the tree and collects the characters that are
after the prefix */
void
traverse(struct node *pNode, char *secondPrefix, char *buffer, int depth,
    FILE *ofp){


    if(pNode == NULL){
        return;

    }

    traverse(pNode->left, secondPrefix, buffer, depth, ofp);

    /* the nul char that was added before gets replaced by the new char */
    buffer[depth] = pNode->data;

    if(pNode->end_of_key == TRUE){


        /* since that new character that was added formed a word a new nul
        char is added at the end of the buffer placeholder */
        buffer[depth+1] = '\0';
        fprintf(ofp, "key:  %s%s --> weight:  %d\n", secondPrefix,
        buffer, pNode->weight);

    }

    traverse(pNode->equal, secondPrefix, buffer, depth+1, ofp);
    traverse(pNode->right, secondPrefix, buffer, depth, ofp);

    return;
}
