#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ternarytree.h"
#include "linklist.h"
#include "selection.h"

/* Kenny Lee 801361 3/9/17 */

void
swap(struct link_list *a, struct link_list *b){
    int tmp_weight;
    char *tmp_buffer = NULL;
    tmp_buffer = malloc(MAXCHAR*sizeof(char));

    strcpy(tmp_buffer, a->buffer);
    tmp_weight = a->weight;

    strcpy(a->buffer, b->buffer);
    a->weight = b->weight;

    strcpy(b->buffer, tmp_buffer);
    b->weight = tmp_weight;

}

int
selection(struct link_list *list) {
    struct link_list *a = NULL;
    struct link_list *min = NULL;
    struct link_list *j = NULL;

    /* since it should count its own, and the loops misses that */
    int weight_comparison = 0;

    for(a = list; a != NULL && a->next != NULL ; a = a->next){
        min = a;
        for(j= a->next; j != NULL; j = j->next){
            if(j->weight > min->weight){
                min = j;


            }
            weight_comparison++;
        }

        if(min != a){
            swap(min, a);

        }
    }

    return weight_comparison;
}
