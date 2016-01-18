//define vertex
typedef struct vertex{
   int val;
   int visited;
   struct vertex *next;
   struct vertex *down;
} vtx, *vtx_ptr;

//function prototypes
vtx_ptr add_to_graph(vtx_ptr, vtx_ptr, vtx_ptr);
vtx_ptr add_to_back(vtx_ptr, vtx_ptr);
void print_adj_list(vtx_ptr);
void free_graph(vtx_ptr);
void unvisit_all_vertices(vtx_ptr);
int mark_vertex(vtx_ptr, vtx_ptr, int, int);
