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
typedef struct type_path t_path;
#define new_node (t_graph*)malloc(sizeof(t_graph))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

char graph_folder[60];
char *path_folder;
char data_structure_type[3];