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
void traverse(struct node* pNode, char *prefix, char *buffer, int depth, FILE *ofp);
void find_and_traverse(struct node *pNode, char *prefix, FILE *ofp);

int
main(int argc, char *argv[]){

/* Checking if the datafile, outputfile and prefix is not NULL */
    char *datafile, *outputfile, *prefix;
    prefix = argv[3];
    outputfile = argv[2];
    datafile = argv[1];

    if(prefix == NULL || outputfile == NULL || datafile == NULL){
        printf("STDIN FAIL\n");
        exit(EXIT_FAILURE);
    }

/* Opening datafile and output file to read and write */
    FILE *ifp, *ofp;

    ifp = fopen(datafile, "r");
    if(ifp == NULL){
        fprintf(stderr, "Can't open input file\n");
        exit(1);
    }

    ofp = fopen(outputfile, "w");
    if(ofp == NULL){
        fprintf(stderr, "Can't open output file\n");
        exit(1);
    }

/* Creating a space for words that form the ternary tree */
    char *word;
    word = malloc(MAX*sizeof(char));
    if(word == NULL){
        printf("MALLOC FAILURE\n");
        exit(EXIT_FAILURE);

    }

/* Reading the file into a ternary tree */
    struct node *pNode = NULL;
    int weight;

    while(fscanf(ifp, "%d;%250[^\n]", &weight, word) != EOF){
        pNode = insert(pNode, word, weight);

    }

/* Writing the results to the output file */
    fprintf(ofp, "Prefix:  %s\n", prefix);
    find_and_traverse(pNode, prefix, ofp);

    fclose(ifp);
    fclose(ofp);

    return 0;
}

/* Creating a new node while initialising its variables */
struct node
*new_node(char *word){
    struct node *new;

    new = malloc(sizeof(struct node));
    if(new == NULL){
        printf("MALLOC FAILURE\n");
        exit(1);

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

/* Finding the end of the prefix. If the key is true, it's a
word and it gets printed out */
void
find_and_traverse(struct node *pNode, char *prefix, FILE *ofp){
    char *buffer = NULL;
    char *secondPrefix = prefix;

    buffer = malloc(250*sizeof(char));
    if(buffer == NULL){
        printf("MALLOC FAILURE\n");
        exit(EXIT_FAILURE);

    }

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

            /* buffer is a placeholder for the prefix, it adds an extra nul
            char at the end for the next function*/
            buffer[strlen(prefix)] = '\0';
            fprintf(ofp, "key:  %s", secondPrefix);
            fprintf(ofp, "%s\n", buffer);

        }

        traverse(pNode, secondPrefix, buffer, strlen(prefix), ofp);
    }

    return;
}

/* Moves through the tree and collects the characters that are
after the prefix */
void
traverse(struct node *pNode, char *secondPrefix, char *buffer, int depth, FILE *ofp){

    if(pNode == NULL){
        return;

    }

    traverse(pNode->left, secondPrefix, buffer, depth, ofp);

    /* the nul char that was added before gets replaced by the new char */
    buffer[depth] = pNode->data;

    if(pNode->end_of_key == TRUE){

        /* since that new character that was added formed a word a new nul
        char is added at the end of the buffer placeholder */
        buffer[depth] = '\0';
        fprintf(ofp, "key:  %s", secondPrefix);
        fprintf(ofp, "%s\n", buffer);

    }

    traverse(pNode->equal, secondPrefix, buffer, depth+1, ofp);
    traverse(pNode->right, secondPrefix, buffer, depth, ofp);

    return;
}
