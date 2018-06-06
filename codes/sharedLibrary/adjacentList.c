#include "adjacentList.h"

int get_graph_size(FILE *f, char **argv){
    char lixo[100];
    char l;
    int l1;
    int cont = 0;
    int graph_size;

    if(strcmp(argv[2],"-RO")==0){
        while (cont <= 13){
            fgets(lixo,100,f);
            cont++;
        }
        fscanf(f, "%c %s %d %d\n", lixo, lixo, &graph_size, &l1);
    }
    else{
        while (cont <= 3){
            fgets(lixo,100,f);
            cont++;
        }
        fscanf(f, "%c %s %d %d\n", lixo, lixo, &graph_size, &l1);
        fgets(lixo,100,f);
        fscanf(f, "%c\n", &l);
    }

    printf("Graph Vertexes: %d\n", graph_size);

    return graph_size;
}

t_graph **get_adjacent_list(t_graph ** adjacent_list, int graph_size, FILE *f, char **argv){

    int u, v, w, i;
    char l;

    adjacent_list = (t_graph**)malloc((graph_size)*sizeof(t_graph*));
    for(i=0; i<graph_size;i++){
        adjacent_list[i] = NULL;
    }

    if(strcmp(argv[2],"-RO")==0){
        while (fscanf(f, "%c %d %d %d\n", &l, &u, &v, &w) != EOF){
            adjacent_list = add_to_list_undir(adjacent_list, u-1, v-1, w);
            adjacent_list = add_to_list_undir(adjacent_list, v-1, u-1, w);
        }
    }
    else{
        while (fscanf(f, "%c %d %d %d\n", &l, &u, &v, &w) != EOF){
            adjacent_list = add_to_list_undir(adjacent_list, u-1, v-1, w);
        }
    }

    return adjacent_list;
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
