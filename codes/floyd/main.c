#include "../sharedLibrary/adjacentList.h"
#include "vector.h"

char coord_folder[60];
char visited_coordinates_folder[60];
char path_coordinates_folder[60];
char graph_folder[60];
char *path_folder;
char data_structure_type[3];

int* alloc_array (int graph_size){
    int *a;
    a = (int*)calloc(graph_size,sizeof(int));
    return a;
}

int **alloc_matrix (int graph_size){
    int **m;
    int i;
    m = (int**)malloc(graph_size*sizeof(int*));
    for (i=0; i<graph_size; i++){
        m[i] = (int*)calloc(graph_size,sizeof(int));
    }
    return m;
}

void save_distance_and_anterior_file (int **distancia, int **anterior, int graph_size){
    FILE *f, *f1;
    int i, j;

    f = fopen("rome.anterior.matrix.txt", "w");
    f1 = fopen("rome.distancia.matrix.txt", "w");

    for(i=0; i<graph_size; i++){
        for(j=0; j<graph_size; j++){
            fprintf(f, "%d ", anterior[i][j]);
            fprintf(f1, "%d ", distancia[i][j]);
        }
        fprintf(f, "\n");
        fprintf(f1, "\n");
    }
    fclose(f);
    fclose(f1);
}

void save_distance_and_anterior_file_vector (vector distancia, vector anterior, int graph_size){
    FILE *f, *f1;
    int i, j;

    f = fopen("rome.anterior.matrix.vec.txt", "w");
    f1 = fopen("rome.distancia.matrix.vec.txt", "w");

    for(i=0; i<graph_size; i++){
        for(j=0; j<graph_size; j++){
            fprintf(f, "%d ", vector_get(&anterior, i*graph_size + j));
            fprintf(f1, "%d ", vector_get(&distancia, i*graph_size + j));
        }
        fprintf(f, "\n");
        fprintf(f1, "\n");
    }
    fclose(f);
    fclose(f1);
}

void floyd_matrix(t_graph** adjacent_list, int graph_size, int vertex_ini, int vertex_fin)
{
    int i, j, k, *p;
    int inf = INT_MAX/2;
    int **distanceMatrix; // shortest path cost between nodes
    int **adjacentMatrix; // adjacent matrix
    int *path; // shortest path from initial to final node
    int currentVertex = 0;
    t_graph *v; // vertex in adjacent_list

    distanceMatrix = alloc_matrix(graph_size);
    adjacentMatrix = alloc_matrix(graph_size);
    path = alloc_array(graph_size);

    /* Initializes every node's path to itself to 0 and the remaining combinations to infinite */
    for (i = currentVertex; i < graph_size; i++)
    {
        for (j = currentVertex; j < graph_size; j++)
        {
            if (i == j)
                distanceMatrix[i][j] = 0;
            else
                distanceMatrix[i][j] = inf;
        }
    }

    /* Initializes every next node to -1. -1 means vertices are not adjacent */
    for (i = currentVertex; i < graph_size; i++)
    {
        for (j = currentVertex; j < graph_size; j++)
        {
            adjacentMatrix[i][j] = -1;
        }
    }

    /* Asigns weights to adjacent vertices and fill adjacent matrix */
    for (i = currentVertex; i < graph_size; i++)
    {
        for (v = adjacent_list[i]; v != NULL; v = v->prox)
        {
            distanceMatrix[i][v->vertex] = v->cost;
            adjacentMatrix[i][v->vertex] = v->vertex;
        }
    }

    /* Algorithm calculation */
    for (k = currentVertex; k < graph_size; k++)
    {
        for (i = currentVertex; i < graph_size; i++)
        {
            for (j = currentVertex; j < graph_size; j++)
            {
                if (distanceMatrix[i][j] > (distanceMatrix[i][k] + distanceMatrix[k][j]) )
                {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    adjacentMatrix[i][j] = adjacentMatrix[i][k];
                }
            }
        }
    }

	save_distance_and_anterior_file(distanceMatrix, adjacentMatrix, graph_size);
}

int *floyd_vector(t_graph **adjacent_list, int graph_size, int vertex_ini, int vertex_fin)
{
    int i, j, k;
    int inf = INT_MAX/2;
    t_graph *v; // vertex in adjacent list
    vector adjacentVector, distanceVector;

    vector_init(&adjacentVector);
    vector_init(&distanceVector);

    /* Initializes every node's path to itself to 0 and the remaining combinations to infinite */
    for (i = 0; i <= graph_size*graph_size; i++)
    {
        if (i == 0 || i % (graph_size + 1) == 0)
            vector_add(&distanceVector, 0);
        else
            vector_add(&distanceVector, inf);
    }

    /* Initializes every next node to -1. -1 means vertices are not adjacent */
    for (i = 0; i < graph_size*graph_size; i++)
    {
        vector_add(&adjacentVector, -1);
    }

    /* Asigns weights to adjacent vertices and fill adjacent matrix */
    for (i = 0; i < graph_size; i++)
    {
        for (v = adjacent_list[i]; v != NULL; v = v->prox)
        {
            vector_set(&distanceVector, i*graph_size + v->vertex, v->cost);
            vector_set(&adjacentVector, i*graph_size + v->vertex, v->vertex);
        }
    }

    /* Algorithm calculation */
    for (k = 0; k < graph_size; k++)
    {
        for (i = 0; i < graph_size; i++)
        {
            for (j = 0; j < graph_size; j++)
            {
                if ( vector_get(&distanceVector, i*graph_size + j) >
                    (vector_get(&distanceVector, i*graph_size + k) + vector_get(&distanceVector, k*graph_size + j)) )
                {
                    vector_set(&distanceVector, i*graph_size + j, vector_get(&distanceVector, i*graph_size + k) + vector_get(&distanceVector, k*graph_size + j));
                    vector_set(&adjacentVector, i*graph_size + j, vector_get(&adjacentVector, i*graph_size + k));
                }
            }
        }
    }

    save_distance_and_anterior_file_vector(distanceVector, adjacentVector, graph_size);

    vector_free(&adjacentVector);
    vector_free(&distanceVector);
}

void print_list(t_graph *graph){
    t_graph *p;
    for(p=graph; p!=NULL; p=p->prox){
        printf("%d|%d\t", p->vertex, p->cost);
    }

}

int main(int argc, char **argv)
{

    readParameters(argc, argv);
    int graph_size;
    int path_size;

    t_graph **adjacent_list;
    t_path *path;

    int **adjacent_matrix;

    int **distance_matrix;
    int *distance;
    int i;

    FILE *f;

    f = fopen (graph_folder, "r");
    if (f == NULL)
    {
        printf("Fail to read file!\n");
        exit(0);
    }

    graph_size = get_graph_size(f, argv);

    if (strcmp(data_structure_type, "-m") == 0)
    {
        adjacent_list = get_adjacent_list(adjacent_list, graph_size, f, argv);
        clock_t begin = clock();
        floyd_matrix(adjacent_list, graph_size, 0, 6);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        show_time_spent(time_spent);
    }
    else if (strcmp(data_structure_type, "-v") == 0)
    {
        adjacent_list = get_adjacent_list(adjacent_list, graph_size, f, argv);
        clock_t begin = clock();
        floyd_vector(adjacent_list, graph_size, 0, 6);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        show_time_spent(time_spent);
    }
}
