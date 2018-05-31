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

void readParameters (int argc, char **argv){

    if(argc != 4){
        printf("Parametros incorretos!\n");
        printf("./dijkstra < -d :distanceGraph or -t :timeTravelGraph > < -NY || -COL || -FLA || -BAY || -TES (test) instances> < -l for list >\n");
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

    graph_size = get_graph_size(f);

    if(strcmp(data_structure_type, "-l") == 0){
        adjacent_list = get_adjacent_list(adjacent_list, graph_size, f);
        distance = dijkstra_list (adjacent_list, graph_size, 1);
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
