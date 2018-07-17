#include <stdio.h>
#include <stdlib.h>
#include "ternarytree.h"
#include "selection.h"
#include "linklist.h"

/* Kenny Lee 801361 3/9/17 */

int
main(int argc, char *argv[]){

/* similar to autocomplete1.c */
    char *datafile, *outputfile, *prefix;
    prefix = argv[3];
    outputfile = argv[2];
    datafile = argv[1];

    if(outputfile == NULL || datafile == NULL || prefix == NULL){
        printf("STDIN FAILURE\n");
        exit(EXIT_FAILURE);
    }

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

    char *word;
    word = malloc(MAXCHAR*sizeof(char));
    if(word == NULL){
        printf("MALLOC FAILURE\n");
        exit(EXIT_FAILURE);

    }

    struct node *pNode = NULL;
    int weight;

    while(fscanf(ifp, "%d;%250[^\n]", &weight, word) != EOF){
        pNode = insert(pNode, word, weight);

    }

    fprintf(ofp, "Prefix:  %s\n", prefix);

    struct link_list *list = NULL;
    list = find_and_traverse(pNode, prefix, ofp);

/* sorting the list while returning the weight comparisons */
    int weight_comparison;
    weight_comparison = selection(list);

    if(list != NULL){
        while(list->next != NULL){
            fprintf(ofp, "key:  %s%s ---> weight:  %d\n", prefix, list->buffer,
            list->weight);
            list = list->next;
            weight_comparison++;

        }
        fprintf(ofp, "key:  %s%s ---> weight:  %d\n", prefix, list->buffer,
        list->weight);
        weight_comparison++;

    }

    printf("Selection Sort: %d weight comparisons\n", weight_comparison);

    fclose(ifp);
    fclose(ofp);

    return 0;
}
