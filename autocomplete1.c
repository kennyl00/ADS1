#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAXCHAR 250

/* global variable to keep track of the number of output keys */
int key_found = 0;

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
int find_and_traverse(struct node *pNode, char *prefix, FILE *ofp);

int
main(int argc, char *argv[]){

/* Checking if the datafile, outputfile and prefix is not NULL */
    char *datafile, *outputfile, *prefix;
    prefix = argv[3];
    outputfile = argv[2];
    datafile = argv[1];

    if(prefix == NULL || outputfile == NULL || datafile == NULL){
        printf("STDIN FAILURE\n");
        exit(EXIT_FAILURE);
    }

/* Opening datafile and output file to read and write */
    FILE *ifp, *ofp;

    ifp = fopen(datafile, "r");
    if(ifp == NULL){
        fprintf(stderr, "INPUT FILE FAIL\n");
        exit(EXIT_FAILURE);
    }

    ofp = fopen(outputfile, "w");
    if(ofp == NULL){
        fprintf(stderr, "OUTPUT FILE FAIL\n");
        exit(EXIT_FAILURE);
    }

/* Creating a space for words that form the ternary tree */
    char *word;
    word = malloc(MAXCHAR*sizeof(char));
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
    int comparisons;
    fprintf(ofp, "Prefix:  %s\n", prefix);
    comparisons = find_and_traverse(pNode, prefix, ofp);

/* stdout the number of comparisons done to find the key prefix */
    printf("Prefix:  %s found with %d char comparisons\n", prefix,
    comparisons);

    if(!key_found){
        fprintf(ofp, "NOTFOUND\n");

    }

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

/* Finding the end of the prefix. If the key is true, it's a
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

        traverse(pNode, secondPrefix, buffer, strlen(prefix), ofp);

    }

    return comparisons;
}

/* Moves through the tree and collects the characters that are
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
        key_found++;

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
