#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX 250

struct node {
    char data;
    int weight;
    int end_of_key;
    struct node *left;
    struct node *equal;
    struct node *right;

};

struct node *insert(struct node *pNode, char *word, int weight);
void traverse(struct node* pNode, char *prefix, char *buffer, int depth);
void find_and_traverse(struct node *pNode, char *prefix);

int
main(int argc, char *argv[]){
    struct node *pNode = NULL;
    char *word;
    int weight;

    word = malloc(MAX*sizeof(char));
    if(word == NULL){
        printf("MALLOC FAIL\n");
        exit(EXIT_FAILURE);

    }

    while(scanf("%d;%250[^\n]", &weight, word) != EOF){
        pNode = insert(pNode, word, weight);
    }

    find_and_traverse(pNode, "Me");

    return 0;
}

struct node
*new_node(char *word){
    struct node *new;

    new = malloc(sizeof(struct node));
    if(new == NULL){
        printf("Malloc Failure!\n");
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
        pNode->left = insert(pNode->left, word, weight);

    }else if(*word == pNode->data){
        if(*(word+1) == '\0'){
            pNode->end_of_key = TRUE;
            pNode->weight = weight;

        }else {
            pNode->equal = insert(pNode->equal, word+1, weight);

        }

    }else {
        pNode->right = insert(pNode->equal, word, weight);

    }

    return pNode;
}

void
find_and_traverse(struct node *pNode, char *prefix){
    char *buffer = malloc(MAX*sizeof(char));
    char *secondPrefix = malloc(MAX*sizeof(char));

    strcpy(secondPrefix, prefix);

    while(*prefix != '\0' && pNode != NULL){

        if(*prefix < (pNode->data)){
            pNode = pNode->left;
            continue;

        }

        if(*prefix > pNode->data){
            pNode = pNode->right;
            continue;

        }

        if(*prefix == pNode->data){
            pNode = pNode->equal;
            prefix = prefix+1;
            continue;

        }
    }

    if(pNode != NULL){
        if(pNode->end_of_key == TRUE){
            buffer[strlen(prefix)+1] = '\0';
            printf("%s", secondPrefix);
            printf("%s\n", buffer);

        }

        traverse(pNode, secondPrefix, buffer, strlen(prefix));
    }

    return;
}

void
traverse(struct node *pNode, char *secondPrefix, char *buffer, int depth){

    if(pNode == NULL){
        return;

    }

    traverse(pNode->left, secondPrefix, buffer, depth);

    buffer[depth] = pNode->data;

    if(pNode->end_of_key == TRUE){

        buffer[depth+1] = '\0';
        printf("%s", secondPrefix);
        printf("%s\n", buffer);

    }

    traverse(pNode->equal, secondPrefix, buffer, depth+1);
    traverse(pNode->right, secondPrefix, buffer, depth);

    return;
}
