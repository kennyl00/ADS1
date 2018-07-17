#ifndef LINKLISTH
#define LINKLISTH
#include "ternarytree.h"

/* Kenny Lee 801361 3/9/17 */

struct link_list {
    int weight;
    char buffer[MAXCHAR];
    struct link_list *next;

};

struct link_list *new_link_list(int weight, char *buffer);
struct link_list *insert_link_list(struct link_list *list, char *buffer,
    int weight);

#endif
