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

    graph_size = get_graph_size(f, argv);
    path[0].src = 0;
    path[0].dest = (graph_size-(graph_size*0.85))-1;
    path[1].src = 0;
    path[1].dest = (graph_size/2)-1;
    path[2].src = 0;
    path[2].dest = graph_size-1;
    adjacent_list = get_adjacent_list(adjacent_list, graph_size, f, argv);

    if(strcmp(data_structure_type, "-v") == 0){
        printf("dijkstra_array\n");
        for(i=0;i<3;i++){
            clock_t begin = clock();
            dijkstra_results = dijkstra_array (adjacent_list, graph_size, path[i].src, path[i].dest);
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Distance from %d to %d vertex: %d\n", path[i].src+1, path[i].dest+1,dijkstra_results.distancia[path[i].dest]);
            show_time_spent(time_spent);

        }
    }

    if(strcmp(data_structure_type, "-h") == 0){
        //printf("dijkstra_heap\n");
        //for(i=0;i<3;i++){
            clock_t begin = clock();
            dijkstra_results = dijkstra_heap (adjacent_list, graph_size, 1, 10);
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            //printf("Distance from %d to %d vertex: %d\n", path[i].src+1, path[i].dest+1,dijkstra_results.distancia[path[i].dest]);
            int maior = 0;
            int medio = 0;
            int menor = 0;
            int diameter_vertex = 0;
            int center_vertex = 0;
            int min_vertex = 0;
            int i;
            for (i=0; i<graph_size; i++){
                if(maior<dijkstra_results.distancia[i]){
                    maior = dijkstra_results.distancia[i];
                    diameter_vertex = i;
                }
            }
            for (i=0; i<graph_size; i++){
                if(dijkstra_results.distancia[i] >= (maior/2)-100 && dijkstra_results.distancia[i] <= (maior/2)+100){
                    //maior = dijkstra_results.distancia[i];
                    medio = dijkstra_results.distancia[i];
                    center_vertex = i;
                }
            }

            for (i=0; i<graph_size; i++){
                if(dijkstra_results.distancia[i] >= (medio/2)-100 && dijkstra_results.distancia[i] <= (medio/2)+100){
                    //maior = dijkstra_results.distancia[i];
                    menor = dijkstra_results.distancia[i];
                    min_vertex = i;
                }
            }
            printf("Facil: 1 X %d vertex\n", min_vertex+1);
            printf("Medio: 1 X %d vertex\n", center_vertex+1);
            printf("Dificil: 1 X %d vertex\n", diameter_vertex+1);


            show_time_spent(time_spent);
        //}
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
