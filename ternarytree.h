#ifndef TERNARYTREEH
#define TERNARYTREEH

#define TRUE 1
#define FALSE 0
#define MAXCHAR 250


struct node {
    char data;
    int weight;
    int end_of_key;
    struct node *left;
    struct node *equal;
    struct node *right;

};


struct node *insert(struct node *pNode, char *word, int weight);
void traverse(struct node* pNode, char *prefix, char *buffer, int depth,
    FILE *ofp);
int find_and_traverse(struct node *pNode, char *prefix, FILE *ofp);



#endif
