#include "../sharedLibrary/adjacentList.h"
#include "dijkstra_array.h"
#include "dijkstra_heap.h"

char graph_folder[60];
char *path_folder;
char data_structure_type[3];

void print_list(t_graph *graph){
    t_graph *p;
    for(p=graph; p!=NULL; p=p->prox){
        printf("%d|%d\t", p->vertex, p->cost);
    }

}

void readParameters (int argc, char **argv){

    if(argc != 4){
        printf("Parametros incorretos!\n");
        printf("./dijkstra < -d :distanceGraph or -t :timeTravelGraph > < -NY || -COL || -FLA || -BAY || -TES (test) instances> < -v for array or -h for heap\n");
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
    t_path path[3];

    int **adjacent_matrix;

    int **distance_matrix;
    t_graph_info dijkstra_results;
    //int *distance;
    int i;

    FILE *f;

    f = fopen (graph_folder, "r");
    if(f==NULL){
        printf("Fail to read file!\n");
        exit(0);
    }

    graph_size = get_graph_size(f);
    path[0].src = 0;
    path[1].src = 0;
    path[2].src = 0;
    path[0].dest = (graph_size-(graph_size*0.85))-1;
    path[1].dest = (graph_size/2)-1;
    path[2].dest = graph_size-1;
    adjacent_list = get_adjacent_list(adjacent_list, graph_size, f);

    if(strcmp(data_structure_type, "-v") == 0){
        for(i=0;i<3;i++){
            dijkstra_results = dijkstra_array (adjacent_list, graph_size, path[i].src, path[i].dest);
            printf("Distance from %d to %d vertex: %d\n", path[i].src+1, path[i].dest+1,dijkstra_results.distancia[path[i].dest]);
        }
    }

    if(strcmp(data_structure_type, "-h") == 0){
        for(i=0;i<3;i++){
            dijkstra_results = dijkstra_heap (adjacent_list, graph_size, path[i].src, path[i].dest);
            printf("Distance from %d to %d vertex: %d\n", path[i].src+1, path[i].dest+1,dijkstra_results.distancia[path[i].dest]);
        }
    }

    if(strcmp(argv[2],"-TES")==0){
        for(i=0;i<graph_size;i++){
            printf("%d\t",dijkstra_results.anterior[i]);
        }
        printf("\n");
    }

   /*else{
        printf("Distance from 1 to %d vertex:\n", 50);
        for(i=0;i<50;i++){
            printf("%d\t",dijkstra_results.distancia[i]);
        }
        printf("\n");
        printf("Distance from 1 to %d vertex: %d\n", 50,dijkstra_results.distancia[50-1]);
    }*/




}
