#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define EMPTY '\0'


struct node {
    char data;
    int weight;
    int end_of_key;
    struct *node left;
    struct *node equal;
    struct *node right;

};


struct node
*new_node(char word){
    struct node *new;

    new = malloc(sizeof(struct node));
    new->left = NULL;
    new->equal = NULL;
    new->right = NULL;
    new->data = word;

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

    if(!pNode){
        pNode = new_node(word);

    }

    if(word < pNode->data){
        pNode->left = insert(pNode->left, word, weight);

    }else if(word == pNode->data){
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

    while( *prefix != '\0 ' && pNode != NULL){

        if(prefix < pNode->data){
            find_and_traverse(pNode->left, prefix);
            continue;

        }

        if(prefix > pNode->right){
            find_and_traverse(pNode->right, prefix);
            continue;

        }

        if(prefix == pNode->equal){
            find_and_traverse(pNode->equal, prefix+1);
            continue;

        }

    }

    if(pNode){
        if(pNode->end_of_key == TRUE){
            buffer[strlen(prefix)+1] = '\0';
            printf("%s\n", buffer);

        }

        traverse(pNode, buffer, strlen(prefix));
    }

    return;
}

/* This function traverses through the tree for a given prefix and a buffer
that holds a prefix and finds if there is a word that is equivalent to that
prefix and 1 char more at each recursion. It then prints out every different
word that exist since it checks for the flags */

void
traverse(struct node* pNode, char *buffer, int depth){

    if(!pNode) return;

    traverse(pNode->left, buffer, depth);

    buffer[depth] = pNode->data;

    if(pNode->end_of_key == TRUE){
        buffer[depth+1] = '\0';
        printf("%s\n", buffer);

    }

    /* Depth is basically the next character of the prefix and
    it would be going down from the tree */
    traverse(pNode->equal, buffer, depth+1);


    traverse(pNode->right, buffer, depth);

    return;
}



int
main(int argc, char *argv[]){







    return 0;
}
