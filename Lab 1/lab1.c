/*	Sameh Saleh
	10/21/12
	CS 367
	Lab1
*/
#include <stdio.h>
#include <stdlib.h>
#include "lab1.h"

/*Words Used Interchangeably:
Vertex = Node
Graph = Network (made of vertex list and represented as adjacency list)
Top = Head = Front (depending on context)
*/

//add to graph based on an adacency list
vtx_ptr add_to_graph(vtx_ptr list, vtx_ptr vertex, vtx_ptr connectTo) {
	vtx_ptr top = list;
	vertex->next = NULL;
	vertex->down = NULL;
	//if list is empty, add node and add directed edge to connectTo
	if(list == NULL){
		vertex->next = connectTo;
		connectTo->next = NULL;
		return vertex;
	}
	//if the vertex should be ordered as the first node in list, add to top
	else if(vertex->val < top->val){
		vertex->down = top;
		vertex->next = connectTo;
		connectTo->next = NULL;
		top = vertex;
	}
	//iteratively search list until placement is found
	else{
		//if the vertex already exists in the graph and is the first in the vertex list
		if(list->val == vertex->val){
			add_to_back(list, connectTo);
			//free vertex since it is not needed given that the node already exists in the graph
			free(vertex);
		}
		else{
			while((list->down != NULL) && (vertex->val)>((list->down)->val)){
				list = list->down;
			}
			//if at end of vertex list, add the node to the back of vertex list
			if(list->down == NULL){
				list->down = vertex;
				vertex->next = connectTo;
				connectTo->next = NULL;
			}
			//Since node already exists in vertex list/graph, add connectTo to back of adjacency list of node
			else if(vertex->val==((list->down)->val)){
				add_to_back(list->down, connectTo);
				//free vertex since it is not needed given that the node already exists in the graph
				free(vertex);
			}
			//if node doesn't exist in vertex list, add to vertex list in the correct order
			else{
				vertex->down = list->down;
				list->down = vertex;
				vertex->next = connectTo;
				connectTo->next = NULL;
			}
		}
	} 
	return top;
}

//add the node at the back of the list of neighbors of the head node
vtx_ptr add_to_back(vtx_ptr list, vtx_ptr connectTo) {
   vtx_ptr front = list;
   connectTo->next = NULL;
   while (list->next != NULL ) {
     list = list->next;
   } 
   list->next = connectTo;
   return front;
}

//prints the adjacency list form of the graph 
void print_adj_list(vtx_ptr list) {
	vtx_ptr adjlist;
	while (list) {
		adjlist = list;
		while(adjlist){
			printf("%d  ",adjlist->val);
			adjlist = adjlist->next;
		}
		printf("\n");
		list = list->down;
        }   
}

//frees the pointers of the current graph to set up next graph
void free_graph(vtx_ptr list) {
    vtx_ptr tmp1, tmp2, adjlist;
    while (list) {
    	adjlist = list->next;
    	while(adjlist){
    		tmp1=adjlist->next;
    		free(adjlist);
    		adjlist = tmp1;
    	}
    	tmp2 = list->down;
        free(list);
        list = tmp2;
    }
}

//reset visit/mark of all vertices for next query
void unvisit_all_vertices(vtx_ptr list){
	while(list){
		list->visited = 0;
		list = list->down;
	}
}

int mark_vertex(vtx_ptr list, int current, int TTL){
	vtx_ptr current_ptr = (vtx_ptr) malloc(sizeof(vtx));
	current_ptr->val = current;
	vtx_ptr head = list;
	
	//if current node matches the first node
	if(list->val == current_ptr->val){
		list->visited = 1;
		free(current_ptr);
		current_ptr = list;
	}
	else{//checks the correct order of where the current_ptr should be in the down list
		while((list->down != NULL) && (current_ptr->val)>((list->down)->val)){
			list = list->down;
		}
		//if current node matches the next node in the down list, set visited to 1 and set the current_ptr to that node
		if(current_ptr->val==((list->down)->val)){
			(list->down)->visited = 1;
			free(current_ptr);
			current_ptr = list->down;
		}
		//node not in graph (i.e. invalid query)
		else{
			return 0;
		}
	}	
	
	if(TTL!=0){
		while(current_ptr->next){
			mark_vertex(head, current_ptr->next->val, TTL-1);
			current_ptr = current_ptr->next;
		}
	}
	return 1;
}

main(int argc, char **argv) {
	int querynum = 0;
	int numConnect = -1;
	while(numConnect!=0){
		vtx_ptr head = NULL;
		int TTL = 0;
		int startvtx = 0;
		int queriesleft = 1;
		
		scanf("%d", &numConnect);
		//printf("Connections: %d\n",numConnect);
		int decrement = numConnect;
		while(decrement>0){
			/*four nodes, two for each vertex in added edge, where one node contributes to the down vertices list
			and one for adjacency list for each vertex in adjacency list for other vertex*/
			vtx_ptr vtxA = (vtx_ptr) malloc(sizeof(vtx));
			vtx_ptr vtxB = (vtx_ptr) malloc(sizeof(vtx));
			vtx_ptr connectA = (vtx_ptr) malloc(sizeof(vtx));
			vtx_ptr connectB = (vtx_ptr) malloc(sizeof(vtx));
			
			//initialize values in vertex struct
			vtxA->next = NULL;
			vtxB->next = NULL;
			vtxA->down = NULL;
			vtxB->down = NULL;
			vtxA->val = 0;
			vtxB->val = 0;
			vtxA->visited = 0;
			vtxB->visited = 0;
			
			//get input and set values of vertices pointers
			scanf("%d %d", &(vtxA->val), &(vtxB->val));
			connectA->val = vtxA->val;
			connectB->val = vtxB->val;
			
			//add vertices to adjacency list form of graph (undirected)
			head = add_to_graph(head, vtxA, connectB);
			head = add_to_graph(head, vtxB, connectA);
			decrement--;
		}
		
		//contiue with queries until queriesleft is set to 0 when both the start vtx and TTL equal 0
		while(queriesleft!=0){
			//input for startvtx and TTL
			scanf("%d %d", &startvtx, &TTL);
			if(startvtx == 0 && TTL == 0) queriesleft = 0;
			else{
				querynum++;
				//marks all the vertices visited from the start vtx based on the TTL
				int valid = mark_vertex(head, startvtx, TTL);
				//ensures the query is present in the network
				if(valid = 0) printf("Invalid query.\n");
				int counter = 0;
				vtx_ptr list = head;
				//look through list of vertices and see which one is unmarked (unvisited) and add to counter
				while(list){
					if(list->visited == 0){
						counter++;
					}
					list = list->down;
				}
				printf("%d  -  %d nodes not reachable from node %d with TTL = %d.\n", querynum, counter, startvtx, TTL);
				//reset visit/mark of all vertices for next query
				unvisit_all_vertices(head);
			}
		}
		
		//print_adj_list(head);
		//frees the pointers of the current graph to set up next graph
		free_graph(head);
	
	}
	
	return 0;
}
