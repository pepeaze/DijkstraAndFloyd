#ifndef DIJKSTRA_ARRAY_H_   /* Include guard */
#define DIJKSTRA_ARRAY_H_
#include "../sharedLibrary/adjacentList.h"
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int* alloc_array (int graph_size);
int **alloc_matrix (int graph_size);
t_graph_info dijkstra_array (t_graph** adjacent_list, int graph_size, int vertex_ini, int vertex_end);

#endif
