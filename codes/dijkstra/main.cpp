#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <limits.h>


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
#define new_node (t_graph*)malloc(sizeof(t_graph))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
using namespace std;

char graph_folder[60];
char *path_folder;
char data_structure_type[3];

int* alloc_array (int graph_size){
    int *a;
    a = (int*)malloc(graph_size*sizeof(int));
    return a;
}

int* dijkstra (t_graph** adjacent_list, int graph_size, int vertex_ini){

    int *distancia, *fechado, *aberto, *anterior, v_ini = vertex_ini, abertos, k, inf = INT_MAX/2, maior = INT_MAX, custo;
    distancia = alloc_array (graph_size);
    fechado = alloc_array (graph_size);
    aberto = alloc_array (graph_size);
    anterior = alloc_array (graph_size);

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            distancia[i] = 0;
        else
            distancia[i] = inf;
    }

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            fechado[i] = 1;
        else
            fechado[i] = 0;
    }

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            aberto[i] = 0;
        else
            aberto[i] = 1;
    }
    abertos = 1;

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            anterior[i] = 0;
        else
            anterior[i] = 0;
    }

    while (abertos != graph_size){
        if(abertos==1)
            k=v_ini;
        else{
            for (int i=0; i<graph_size; i++){
                if(aberto[i]==1 && distancia[i]<maior){
                    maior = distancia[i];
                    k=i;
                }
            }
        }
        if(abertos!=1){
            aberto[k] = 0;
            fechado[k] = 1;
        }

        for(t_graph* p = adjacent_list[k]; p!=NULL; p = p->prox){
            if(aberto[p->vertex]!=0){
                custo = MIN (distancia[p->vertex], (distancia[k]+p->cost));
                if(custo < distancia[p->vertex]){
                    distancia[p->vertex] = custo;
                    anterior[p->vertex] = k;
                }
            }
        }
        abertos ++;
        maior = INT_MAX;
    }

    for(int j=0;j<graph_size;j++)
        cout<<distancia[j]<<" ";
    getchar();

    return (distancia);
}

void print_list(t_graph *graph){
    for(t_graph *p=graph; p!=NULL; p=p->prox){
        printf("%d|%d\t", p->vertex, p->cost);
    }

}

t_graph** add_to_list_undir(t_graph **adjacent_list, int u, int v, int w){
    //printf("%d %d %d\n", u,v,w);
    t_graph *c, *d, *p;
    c = new_node;
    c->vertex = v;
    c->cost = w;
    c->prox = NULL;

    if(adjacent_list[u] == NULL){
        adjacent_list[u] = c;
    }
    else{
        p = adjacent_list[u];
        while ( p -> prox != NULL ){
            p = p -> prox;
        }
        p -> prox = c;
    }
    d = new_node;
    d->vertex = u;
    d->cost = w;
    d->prox = NULL;
    if(adjacent_list[v] == NULL){
        adjacent_list[v] = d;
    }
    else{
        p = adjacent_list[v];
        while ( p -> prox != NULL ){
            p = p -> prox;
        }
        p -> prox = d;
    }

    return (adjacent_list);
}

t_graph **get_adjacent_list(t_graph ** adjacent_list, int *graph_size){
    char lixo[100];
    char l;
    int l1;
    int cont = 0;
    int u, v, w, i;
    FILE *f;

    f = fopen (graph_folder, "r");
    if(f==NULL){
        printf("Fail to read file!");
        exit(0);
    }

    while (cont <= 3){
        fgets(lixo,100,f);
        cont++;
    }
    fscanf(f, "%c %s %d %d\n", lixo, lixo, graph_size, &l1);
    fgets(lixo,100,f);
    fscanf(f, "%c\n", &l);


    printf("Graph Vertexes: %d\n", *graph_size);
    adjacent_list = (t_graph**)malloc((*graph_size)*sizeof(t_graph*));
    for(i=0; i<*graph_size;i++){
        adjacent_list[i] = NULL;
    }

    while (fscanf(f, "%c %d %d %d\n", &l, &u, &v, &w) != EOF){
        adjacent_list = add_to_list_undir(adjacent_list, u, v, w);
    }

    return adjacent_list;
}

void readParameters (int argc, char **argv){

    if(argc != 4){
        printf("Parametros incorretos!\n");
        printf("./dijkstra < -d :distance graph or -t :time travel graph > < -NY or -COL or -FLA or -BAY road network> < -m for matrix or -l for list >\n");
        exit(0);
    }

    if(strcmp(argv[1],"-d")==0){
        if(strcmp(argv[2],"-NY")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/USA-road-d.NY.gr");
        else if(strcmp(argv[2],"-COL")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/USA-road-d.COL.gr");
        else if(strcmp(argv[2],"-FLA")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/USA-road-d.FLA.gr");
        else if(strcmp(argv[2],"-BAY")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/USA-road-d.BAY.gr");
    }

    else if(strcmp(argv[1],"-t")==0){
        if(strcmp(argv[2],"-NY")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/USA-road-t.NY.gr");
        else if(strcmp(argv[2],"-COL")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/USA-road-t.COL.gr");
        else if(strcmp(argv[2],"-FLA")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/USA-road-t.FLA.gr");
        else if(strcmp(argv[2],"-BAY")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/USA-road-t.BAY.gr");
    }

    strcpy(data_structure_type, argv[3]);
}

int main(int argc, char **argv){

    readParameters(argc, argv);
    int graph_size;
    int path_size;

    t_graph **adjacent_list;
    t_path *path;

    int **distance_matrix;
    int *distance;

    int u, v, w, i, op=2;

    if(strcmp(data_structure_type, "-l") == 0){
        adjacent_list = get_adjacent_list(adjacent_list, &graph_size);
    }

    /*f = fopen ("graphDir2.txt", "r");
    fscanf(f, "%d", &graph_size);
    printf("Graph Vertexes: %d\n", graph_size);
    adjacent_list = (t_graph**)malloc(graph_size*sizeof(t_graph*));
    for(i=0; i<graph_size;i++){
        adjacent_list[i] = NULL;
    }
    distance_matrix = (int**)malloc(graph_size*sizeof(int*));
    for(int i=0;i<graph_size;i++)
        distance_matrix[i] = (int*)malloc(graph_size*sizeof(int));

    if(op==1){
        while (fscanf(f, "%d %d %d", &u, &v, &w) == 3){
            adjacent_list = add_to_list_undir(adjacent_list, u, v, w);
        }
    }
    else if(op==2){
        while (fscanf(f, "%d %d %d", &u, &v, &w) == 3){
            adjacent_list = add_to_list_dir(adjacent_list, u, v, w);
        }
    }

    for(int i=0; i<graph_size;i++){
        printf("Vertex %d\t", i);
        print_list(adjacent_list[i]);
        printf("\n");
    }

    for(int i=0; i<graph_size; i++){
        distance = dijkstra (adjacent_list, graph_size, i);
        for(int j=0;j<graph_size;j++)
            distance_matrix[i][j] = distance[j];
        free(distance);

    }
    printf("\n");

    for(int i=0;i<graph_size;i++){
        for(int j=0;j<graph_size;j++){
            cout<<distance_matrix[i][j]<<"\t";
        }
        cout<<"\n";
    }*/


}
