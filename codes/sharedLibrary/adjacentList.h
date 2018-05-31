#ifndef ADJACENTLIST_H_   /* Include guard */
#define ADJACENTLIST_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define new_node (t_graph*)malloc(sizeof(t_graph))

struct type_graph{
    int vertex;
    int cost;
    struct type_graph *prox;
};

struct type_path{
    int src;
    int dest;
};

typedef struct type_graph t_graph;
typedef struct type_paph t_path;

int get_graph_size(FILE *f);
t_graph **get_adjacent_list(t_graph ** adjacent_list, int graph_size, FILE *f);
t_graph** add_to_list_undir(t_graph **adjacent_list, int u, int v, int w);

#endif // ADJACENTLIST_H_
