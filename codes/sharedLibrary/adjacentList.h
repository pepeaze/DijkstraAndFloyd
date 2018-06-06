#ifndef ADJACENTLIST_H_   /* Include guard */
#define ADJACENTLIST_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define new_node (t_graph*)malloc(sizeof(t_graph))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

extern char graph_folder[60];
extern char data_structure_type[3];

struct type_graph{
    int vertex;
    int cost;
    struct type_graph *prox;
};

struct type_path{
    int src;
    int dest;
};

typedef struct{
    int *distancia;
    int *anterior;
}t_graph_info;

typedef struct type_graph t_graph;
typedef struct type_path t_path;

int get_graph_size(FILE *f, char **argv);
t_graph **get_adjacent_list(t_graph ** adjacent_list, int graph_size, FILE *f, char **argv);
t_graph** add_to_list_undir(t_graph **adjacent_list, int u, int v, int w);
void readParameters (int argc, char **argv);
void show_time_spent (double time_spent);

#endif // ADJACENTLIST_H_
