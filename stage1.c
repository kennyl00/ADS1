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
void traverse(struct node* pNode, char *buffer, int depth);
void find_and_traverse(struct node *pNode, char *prefix);

int
main(int argc, char *argv[]){
    struct node *pNode = NULL;
    char *word;
    int weight;
    int i = 0;

    word = malloc((MAX+1)*(sizeof(char)));

    if(word == NULL){
        printf("Malloc Failure!\n");
        exit(EXIT_FAILURE);

    }


    /* seg fault in the while loop, gets cut off by
    the terminal while running */
    while(scanf("%d;%250s[^\n]", &weight, word) != EOF){
        pNode = insert(pNode, word, weight);

         if(i = 93826){
             printf("weight = %d, word = %s\n", weight, *word);
         }
        i++;
    }




    find_and_traverse(pNode, "Chi");

    return 0;
}


/* Function that creates a new node and returns a pointer to that new node */
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

    return new;

}

/* The insert function takes in a pointer to node, a pointer to a word,
and a weight. If the node is empty create a new node. If the word is less,
equal or greater than the current word in pNode, then recursively call the
function to the left, equal or greater. If the word is equal, it also checks
the next word to see if it's nul, then define whether it's end of key or move
on with the next char of the word */

struct node
*insert(struct node *pNode, char *word, int weight){

    if(pNode == NULL){
        pNode = new_node(word);

    }

    if(*word < pNode->data){
        pNode->left = insert(pNode->left, word, weight);

    }else if(*word == pNode->data){
        if((*word+1) == '\0'){
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

/* The function takes the pointer to a node and a pointer to an input prefix
if the prefix is not nul nor NULL, then the loop would initiate the
traversing of the tree to the end of the prefix char. At the end of the prefix
char, a traverse function is used to print out all the characters that have
the prefix */

void
find_and_traverse(struct node *pNode, char *prefix){
    char *buffer = NULL;
    printf("check");

    while(*prefix != '\0' && pNode != NULL){

        if(*prefix < (pNode->data)){
            find_and_traverse(pNode->left, prefix);
            continue;

        }

        if(*prefix > pNode->data){
            find_and_traverse(pNode->right, prefix);
            continue;

        }

        if(*prefix == pNode->data){
            find_and_traverse(pNode->equal, prefix+1);
            continue;

        }

    }

    if(pNode != NULL){
        if(pNode->end_of_key == TRUE){

            /* buffer is a placeholder for the prefix, it adds an extra nul
            char at the end for the next function*/
            buffer[strlen(prefix)+1] = '\0';
            printf("%s \n", buffer);

        }


        traverse(pNode, buffer, strlen(prefix));
    }

    return;
}

/* This function traverses through the tree for a given prefix
 * It looks at the left most node and then adds it to the prefix. If the flag
 * is raised, it would be printed out as a word, else it would keep adding.
 * It adds 1 char more at each recursion.
 * It then traverses further in the order of a word */

void
traverse(struct node *pNode, char *buffer, int depth){

    /* if pNode is empty that means there are no further words that
    have the prefix */
    if(pNode == NULL){

        return;
    }

    traverse(pNode->left, buffer, depth);

    /* the nul char that was added before gets replaced by the new char */
    buffer[depth] = pNode->data;

    if(pNode->end_of_key == TRUE){

        /* since that new character that was added formed a word a new nul
        char is added at the end of the buffer placeholder */
        buffer[depth+1] = '\0';
        printf("%s\n", buffer);

    }

    /* Depth is the length of the prefix and at each iteration it
    would add 1 more to check if a word exist at that length */
    traverse(pNode->equal, buffer, depth+1);
    traverse(pNode->right, buffer, depth);

    return;
}
