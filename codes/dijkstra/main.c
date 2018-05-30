#include <stdio.h>
#include <string.h>
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

int* dijkstra_matrix (int** adjacent_matrix, int graph_size, int vertex_ini){
    int *distancia, *fechado, *aberto, *anterior, v_ini = vertex_ini, abertos, k, inf = INT_MAX/2, maior = INT_MAX, custo, i, j, askZero = 0;;
    distancia = alloc_array (graph_size);
    fechado = alloc_array (graph_size);
    aberto = alloc_array (graph_size);
    anterior = alloc_array (graph_size);
    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            distancia[i] = 0;
        else
            distancia[i] = inf;
    }

    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            fechado[i] = 1;
        else
            fechado[i] = 0;
    }

    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            aberto[i] = 0;
        else
            aberto[i] = 1;
    }
    abertos = 1;

    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            anterior[i] = 0;
        else
            anterior[i] = 0;
    }

    while (abertos != graph_size){
        if(abertos==1)
            k=v_ini;
        else{
            for (i=0; i<graph_size; i++){
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

        for(j=0; j<graph_size; j++){
            if(adjacent_matrix[k][j]!=0){
                if(aberto[j]!=0){
                    custo = MIN (distancia[j], (distancia[k]+adjacent_matrix[k][j]));
                    if(custo < distancia[j]){
                        distancia[j] = custo;
                        anterior[j] = k;
                    }
                }
            }
            else{
                askZero++;
            }
        }
        abertos ++;
        maior = INT_MAX;
    }

    /*for(j=0;j<graph_size;j++)
        cout<<distancia[j]<<" ";
    getchar();*/
    printf("Ignorou %d posicoes\n", askZero);
    return (distancia);

}

int* dijkstra_list (t_graph** adjacent_list, int graph_size, int vertex_ini){

    int *distancia, *fechado, *aberto, *anterior, v_ini = vertex_ini, abertos, k, inf = INT_MAX/2, maior = INT_MAX, custo, i, j;
    distancia = alloc_array (graph_size);
    fechado = alloc_array (graph_size);
    aberto = alloc_array (graph_size);
    anterior = alloc_array (graph_size);
    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            distancia[i] = 0;
        else
            distancia[i] = inf;
    }

    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            fechado[i] = 1;
        else
            fechado[i] = 0;
    }

    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            aberto[i] = 0;
        else
            aberto[i] = 1;
    }
    abertos = 1;

    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            anterior[i] = 0;
        else
            anterior[i] = 0;
    }

    while (abertos != graph_size){
        if(abertos==1)
            k=v_ini;
        else{
            for (i=0; i<graph_size; i++){
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

        t_graph* p;

        for(p = adjacent_list[k]; p!=NULL; p = p->prox){
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

    /*for(j=0;j<graph_size;j++)
        cout<<distancia[j]<<" ";
    getchar();*/

    return (distancia);
}

void print_list(t_graph *graph){
    t_graph *p;
    for(p=graph; p!=NULL; p=p->prox){
        printf("%d|%d\t", p->vertex, p->cost);
    }

}

int **get_adjacent_matrix(int **adjacent_matrix, int graph_size, FILE *f){
    int u, v, w;
    char l;

    while (fscanf(f, "%c %d %d %d\n", &l, &u, &v, &w) != EOF){
        adjacent_matrix[u][v] = w;
    }
    return adjacent_matrix;

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

    return (adjacent_list);
}

t_graph **get_adjacent_list(t_graph ** adjacent_list, int graph_size, FILE *f){

    int u, v, w, i;
    char l;

    adjacent_list = (t_graph**)malloc((graph_size)*sizeof(t_graph*));
    for(i=0; i<graph_size;i++){
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
        printf("./dijkstra < -d :distanceGraph or -t :timeTravelGraph > < -NY || -COL || -FLA || -BAY || -TES (test) instances> < -m for matrix or -l for list >\n");
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
        else if(strcmp(argv[2],"-TES")==0)
            strcpy(graph_folder,"../../instances/teste/graph.gr");
    }

    else if(strcmp(argv[1],"-t")==0){
        if(strcmp(argv[2],"-NY")==0)
            strcpy(graph_folder,"../../instances/travelTimeGraphs/USA-road-t.NY.gr");
        else if(strcmp(argv[2],"-COL")==0)
            strcpy(graph_folder,"../../instances/travelTimeGraphs/USA-road-t.COL.gr");
        else if(strcmp(argv[2],"-FLA")==0)
            strcpy(graph_folder,"../../instances/travelTimeGraphs/USA-road-t.FLA.gr");
        else if(strcmp(argv[2],"-BAY")==0)
            strcpy(graph_folder,"../../instances/travelTimeGraphs/USA-road-t.BAY.gr");
        else if(strcmp(argv[2],"-TES")==0)
            strcpy(graph_folder,"../../instances/teste/graph.gr");
    }

    strcpy(data_structure_type, argv[3]);
}

int get_graph_size(FILE *f){
    char lixo[100];
    char l;
    int l1;
    int cont = 0;
    int graph_size;

    while (cont <= 3){
        fgets(lixo,100,f);
        cont++;
    }
    fscanf(f, "%c %s %d %d\n", lixo, lixo, &graph_size, &l1);
    fgets(lixo,100,f);
    fscanf(f, "%c\n", &l);
    printf("Graph Vertexes: %d\n", graph_size);

    return graph_size;
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
        printf("Fail to read file!");
        exit(0);
    }

    graph_size = get_graph_size(f);

    if(strcmp(data_structure_type, "-l") == 0){
        adjacent_list = get_adjacent_list(adjacent_list, graph_size, f);
        distance = dijkstra_list (adjacent_list, graph_size, 1);
    }

    else if(strcmp(data_structure_type, "-m") == 0){
        adjacent_matrix = alloc_matrix(graph_size);
        adjacent_matrix = get_adjacent_matrix(adjacent_matrix, graph_size, f);
        distance = dijkstra_matrix (adjacent_matrix, graph_size, 1);
    }


        //for(int j=0;j<graph_size;j++)
          //  distance_matrix[i][j] = distance[j];
        //free(distance);

    //}
    //printf("\n");
    if(strcmp(argv[2],"-TES")==0){
        for(i=0;i<graph_size;i++){
            printf("%d\t",distance[i]);
        }
        printf("\n");
    }



}
