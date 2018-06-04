#include "dijkstra_heap.h"


/*
** Creates an empty Heap, returns pointer to the heap
*/
Heap *createHeap(){

	Heap *h = malloc(sizeof(Heap));
	assert(h);

	h->n = 0;
	h->size = 1;
	h->size_map = 1;
	h->map = (uint *)malloc(sizeof(uint) * h->size_map);
	assert(h->map);
	h->H = (HeapItem *)malloc(sizeof(HeapItem) * h->size);
	assert(h->H);

	return h;
}

/*
** Inserts a HeapItem into a heap
** Returns HEAP_SUCESS if insertion is successful,otherwise HEAP_FAIL
*/
int insert(Heap *h, uint dataIndex, float key){
	if(h == NULL){
		return HEAP_FAIL;
	}
	//makes sure there is enough space
	if(dataIndex > h->size_map){
		h->size_map = dataIndex + 1;
		h->map = (uint *)realloc(h->map,sizeof(uint) * h->size_map);
		if(!(h->map)){
			return HEAP_FAIL;
		}

	}
	if(h->n == h->size){
		h->size *= 2;
		h->H = (HeapItem *)realloc(h->H, sizeof(HeapItem) * h->size);
		if(!(h->H)){
			return HEAP_FAIL;
		}
	}

	// insert data item at the bottom of the heap
	h->H[h->n].key = key;
    h->H[h->n].dataIndex = dataIndex;
	h->map[dataIndex] = h->n;
	h->n++;

	// find the correct position i.e. sift up
	//parent of A[i] in A[(i-1)/2]

	siftUp(h,h->n - 1,key);
	return HEAP_SUCCESS;
}


/*
** Swaps two elements in the heap
*/
void
swap(Heap *h, uint pos_child, uint pos_parent){
	assert(h);
	if(h->n == 1){
		return;
	}
	//change map
	uint child_dataIndex = h->H[pos_child].dataIndex;
	h->map[child_dataIndex] = pos_parent;
	uint parent_dataIndex = h->H[pos_parent].dataIndex;
	h->map[parent_dataIndex] = pos_child;

	// change HeapItem array
	HeapItem child = h->H[pos_child];
	h->H[pos_child] = h->H[pos_parent];
	h->H[pos_parent] = child;

}

/*
**returns dataIndex of the root
*/
uint peek(Heap *h){
	assert(h);
	assert(h->n>0);
	//root has position = 0

	return h->H[0].dataIndex;

}

/*
** returns the key of the root dataIndex in heap
*/
float peekKey(Heap *h){
	assert(h);
	assert(h->n>0);
	//root has position = 0

	return h->H[0].key;
}



/*
** Changes the key of the HeapItem with dataIndex to delta
*/
void changeKey(Heap *h, uint dataIndex, float delta){
	assert(h);
	uint n = h->map[dataIndex];
	h->H[n].key = delta;

	// no elements in Heap, or only one
	if(h->n <= 1){
		return;
	}
	siftUp(h,n,h->H[n].key);

}

void
siftUp(Heap *h, int N,float key){
	assert(h);
	int pos_child = N;
	//single element in heap
	if(pos_child == 0){
		return;
	}
	int pos_parent = (pos_child - 1)/2;
	float parent_key = h->H[pos_parent].key;
	while(pos_child > 0 && key < parent_key){
		swap(h,pos_child,pos_parent);
		pos_child = pos_parent;
		pos_parent = (pos_child - 1)/2;
		parent_key = h->H[pos_parent].key;
	}
}

/*
** re-heapifies the min heap
** takes O(n) time
*/
void
siftDown(Heap *h, int N, float key){
	assert(h);
	int pos_parent = N;
	// if last HeapItem
	if(h->n <= 1 ){
		return;
	}
	// till we reach end of the heap
	while((pos_parent * 2 + 1) <= h->n-1){
		int pos_child= 2 * pos_parent + 1;
		// if parent has a second child, which has minimum value of the two children
		if((pos_child + 1 <= h->n-1) && (h->H[pos_child + 1].key < h->H[pos_child].key)){
			pos_child += 1;
		}
		if(key > h->H[pos_child].key){
			swap(h,pos_child,pos_parent);
			pos_parent = pos_child;
		}
		else{
			return;
		}
	}

}

/*
** Frees any space allocated for Heap
*/
void destroyHeap(Heap *h){
	if(h == NULL){
		return;
	}
	if(h->size > 0){
		free(h->map);
		free(h->H);
	}
	free(h);
}

/*
** removes the root element of the heap
** then re-heapifies
** returns the dataIndex of the removed root element
*/
uint removeMin(Heap *h){
	assert(h);
	uint old_dataIndex = peek(h);
	swap(h,h->n-1,0);
	h->n--;
	siftDown(h,0,h->H[0].key);
	return old_dataIndex;

}

/*
** Prints the Heap
*/
void
print_heap(Heap *h){
	assert(h);
	if(h == NULL){
		printf("heap empty\n");
		return;
	}
	uint n = h->n;
	printf("Key: ");
	uint i;
	for(i = 0; i < n; i++){
		printf("%.2f ",h->H[i].key);
	}

	printf("\n-----------------------\n");
	printf("DataIndex -> Map: ");
	for(i = 0; i < n; i++){
		printf("%d -> %d ",h->H[i].dataIndex, h->map[h->H[i].dataIndex]);
	}

	printf("\n");

}

t_graph_info dijkstra_heap (t_graph** adjacent_list, int graph_size, int vertex_ini, int vertex_end){
    printf("dijkstra_heap\n");
    t_graph_info r;
    int *fechado, *aberto, v_ini = vertex_ini, abertos, k, inf = INT_MAX/2, maior = INT_MAX, custo, i, j;
    int dist_v1,dist_k,edge_weight;
    r.distancia = alloc_array (graph_size);
    r.anterior = alloc_array (graph_size);
    //initialise heap with dist values
	Heap *h = createHeap();
	insert(h,vertex_ini,0);

	for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            r.distancia[i] = 0;
        else
            r.distancia[i] = inf;
    }

    for(i = 0; i<graph_size; i++){
        if(i == v_ini)
            r.anterior[i] = 0;
        else
            r.anterior[i] = 0;
    }

	// set all dist values to infinity
	for(i = 0; i < graph_size; i++){
		if(i != vertex_ini){
			insert(h,i,inf);
		}
	}

	//while heap is not empty
	while (k!=vertex_end){
	//while(h->n != 0){
        k = removeMin(h);
		t_graph* p;
        for(p = adjacent_list[k]; p!=NULL; p = p->prox){

			dist_v1 = h->H[h->map[p->vertex]].key;
			dist_k = h->H[h->map[k]].key;
			edge_weight = p->cost;

			if(dist_v1 > (dist_k + edge_weight)){
				dist_v1 = dist_k + edge_weight;
				r.distancia[p->vertex] = dist_v1;
                r.anterior[p->vertex] = k;
				changeKey(h,h->H[h->map[p->vertex]].dataIndex,dist_v1);
			}
		}
	}
	//free heap
	destroyHeap(h);

    return (r);
}
