#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"
#include "ternarytree.h"

/* Kenny Lee 801361 3/9/17 */

/* creating a new link list, similar to the ternary tree */
struct link_list
*new_link_list(int weight, char *buffer){
    struct link_list *new;

    new = malloc(sizeof(struct link_list));
    if(new == NULL){
        printf("MALLOC FAILURE\n");
        exit(EXIT_FAILURE);

    }

    new->weight = weight;
    strcpy(new->buffer, buffer);
    new->next = NULL;

    return new;

}

struct link_list
*insert_link_list(struct link_list *list, char *buffer, int weight){

    if(list == NULL){
        list = new_link_list(weight, buffer);

    }else{
        list->next = insert_link_list(list->next, buffer, weight);

    }

    return list;
}
