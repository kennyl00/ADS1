#ifndef TERNARYTREEH
#define TERNARYTREEH

/* Kenny Lee 801361 3/9/17 */

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

struct node *new_node(char *word);
struct node *insert(struct node *pNode, char *word, int weight);
struct link_list *traverse(struct node* pNode, char *prefix,
    char *buffer, int depth, FILE *ofp, struct link_list *list);
struct link_list *find_and_traverse(struct node *pNode, char *prefix,
    FILE *ofp);

#endif
