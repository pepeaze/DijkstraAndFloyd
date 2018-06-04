#include "dijkstra_array.h"

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

t_graph_info dijkstra_array (t_graph** adjacent_list, int graph_size, int vertex_ini, int vertex_end){
    printf("dijkstra_array\n");
    t_graph_info r;
    int *fechado, *aberto, v_ini = vertex_ini, abertos, k, inf = INT_MAX/2, maior = INT_MAX, custo, i, j;
    r.distancia = alloc_array (graph_size);
    fechado = alloc_array (graph_size);
    aberto = alloc_array (graph_size);
    r.anterior = alloc_array (graph_size);
    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            r.distancia[i] = 0;
        else
            r.distancia[i] = inf;
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
            r.anterior[i] = 0;
        else
            r.anterior[i] = 0;
    }

    //while (abertos != graph_size){
    while (k!=vertex_end){
        if(abertos==1)
            k=v_ini;
        else{
            for (i=0; i<graph_size; i++){
                if(aberto[i]==1 && r.distancia[i]<maior){
                    maior = r.distancia[i];
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
                custo = MIN (r.distancia[p->vertex], (r.distancia[k]+p->cost));
                if(custo < r.distancia[p->vertex]){
                    r.distancia[p->vertex] = custo;
                    r.anterior[p->vertex] = k;
                }
            }
        }
        abertos ++;
        maior = INT_MAX;
    }

    /*for(j=0;j<graph_size;j++)
        cout<<distancia[j]<<" ";
    getchar();*/

    return (r);
}
