#include "../sharedLibrary/adjacentList.h"

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

int *floyd_list(t_graph** adjacent_list, int graph_size, int vertex_ini, int vertex_fin)
{
    int i, j, k, *p;
    int inf = INT_MAX/2;
    int **minDistanceMatrix; // shortest path cost between nodes
    int **nextVertexMatrix; // adjacent matrix
    int *path; // shortest path from initial to final node
    int currentVertex = 0;
    t_graph *v; // vertex in adjacent_list

    minDistanceMatrix = alloc_matrix(graph_size);
    nextVertexMatrix = alloc_matrix(graph_size);
    path = alloc_array(graph_size);

    /* Initializes every node's path to itself to 0 and the remaining combinations to infinite */
    for (i = currentVertex; i < graph_size; i++)
    {
        for (j = currentVertex; j < graph_size; j++)
        {
            if (i == j)
                minDistanceMatrix[i][j] = 0;
            else
                minDistanceMatrix[i][j] = inf;
        }
    }

    /* Initializes every next node to -1. -1 means vertices are not adjacent */
    for (i = currentVertex; i < graph_size; i++)
    {
        for (j = currentVertex; j < graph_size; j++)
        {
            nextVertexMatrix[i][j] = -1;
        }
    }

    /* Asigns weights to adjacent vertices and fill adjacent matrix */
    for (i = currentVertex; i < graph_size; i++)
    {
        for (v = adjacent_list[i]; v != NULL; v = v->prox)
        {
            minDistanceMatrix[i][v->vertex] = v->cost;
            nextVertexMatrix[i][v->vertex] = v->vertex;
        }
    }

    /* Algorithm calculation */
    for (i = currentVertex; i < graph_size; i++)
    {
        for (j = currentVertex; j < graph_size; j++)
        {
            for (k = currentVertex; k < graph_size; k++)
            {
                if (minDistanceMatrix[i][j] > (minDistanceMatrix[i][k] + minDistanceMatrix[k][j]) )
                {
                    minDistanceMatrix[i][j] = minDistanceMatrix[i][k] + minDistanceMatrix[k][j];
                    nextVertexMatrix[i][j] = nextVertexMatrix[i][k];
                }
            }
        }
    }

    // printf("Adjacent Matrix:\n");
    // /* print matrix */
    // for (i = currentVertex; i < graph_size; i++)
    // {
    //     for (j = currentVertex; j < graph_size; j++)
    //     {
    //         printf("%2d ", nextVertexMatrix[i][j]);
    //     }

    //     printf("\n");
    // }
    // printf("\n");

    /* Path reconstruction */
    if (nextVertexMatrix[vertex_ini][vertex_fin] == -1)
        return;

    i = 0;
    path[i] = vertex_ini;
    i++;
    int size = 1;

    while (vertex_ini != vertex_fin)
    {
        vertex_ini = nextVertexMatrix[vertex_ini][vertex_fin];
        path[i] = vertex_ini;
        i++;
        size++;
    }

    // printf("Path:\n");
    // /* Print path */
    // for (i = 0; i < size; i++)
    // {
    //     printf("%d\t", path[i]);
    // }
    // printf("\n\n");

    // printf("Distance Matrix:\n");
    // /* print matrix */
    // for (i = currentVertex; i < graph_size; i++)
    // {
    //     for (j = currentVertex; j < graph_size; j++)
    //     {
    //         printf("%2d ", minDistanceMatrix[i][j]);
    //     }

    //     printf("\n");
    // }
    // printf("\n");

    printFile(minDistanceMatrix, graph_size);

    return path;
}

void print_list(t_graph *graph){
    t_graph *p;
    for(p=graph; p!=NULL; p=p->prox){
        printf("%d|%d\t", p->vertex, p->cost);
    }

}

int main(int argc, char **argv){

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
    if(f==NULL){
        printf("Fail to read file!\n");
        exit(0);
    }

    graph_size = get_graph_size(f, argv);

    if(strcmp(data_structure_type, "-l") == 0){
        adjacent_list = get_adjacent_list(adjacent_list, graph_size, f, argv);
        clock_t begin = clock();
        distance = floyd_list(adjacent_list, graph_size, 0, 6);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        show_time_spent(time_spent);
    }


        //for(int j=0;j<graph_size;j++)
          //  distance_matrix[i][j] = distance[j];
        //free(distance);

    //}
    //printf("\n");
    // if(strcmp(argv[2],"-TES")==0){
    //     for(i=0;i<graph_size;i++){
    //         printf("%d\t",distance[i]);
    //     }
    //     printf("\n");
    // }
}