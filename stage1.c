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





void
find_and_traverse(struct node *pNode, char *prefix){



    return;
}

void
traverse(struct node* pNode, char *buffer, int depth)



int
main(int argc, char *argv[]){







    return 0;
}
