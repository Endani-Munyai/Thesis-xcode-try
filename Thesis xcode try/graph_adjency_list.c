//
//  graph_adjency_list.c
//  Thesis xcode try
//
//  Created by Endani Munyai on 2024. 03. 07..
//https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Graphs.html
#include <stdlib.h>

#include "graph_adjency_list.h"

/* basic directed graph type */
/* the implementation uses adjacency lists
 * represented as variable-length arrays */

/* these arrays may or may not be sorted: if one gets long enough
 * and you call graph_has_edge on its source, it will be */

struct graph {
	int nodes;              /* number of vertices */
	int edges;              /* number of edges */
	
	struct successors { // declaration of structure to be used
		int relations;          /* number of successors */
		int len;        /* number of slots in array */
		char is_sorted; /* true if list is already sorted */
		int list[1];}    /* actual list of successors */
	*alist[1]; // declaration of array of pointers to a structure objects
};

/* create a new graph with (nodes) vertices labeled 0..n-1 and no edges */
p_Graph
graph_create(int nodes)
{
	p_Graph g;
	
	g = malloc(sizeof(struct graph) + sizeof(struct successors *) * (nodes-1));
	
	// -> is the . operator for struct pointers
	g->nodes = nodes;
	g->edges = 0;
	// initialising number of nodes and zeroing number of edges
	
	for(int i = 0; i < nodes; i++) {
		g->alist[i] = malloc(sizeof(struct successors));
		g->alist[i]->relations = 0;
		g->alist[i]->len = 1;
		g->alist[i]->is_sorted= 1;}
	
	return g;
}

/* free all space used by graph */
void
graph_destroy(p_Graph g)
{
	int i;
	
	for(i = 0; i < g->nodes; i++)
		free(g->alist[i]);
	// clearing relation pointer
	
	free(g);
}

/* add an edge to an existing graph */
void
graph_add_edge(p_Graph g, int u, int v)
{
	
	/* do we need to grow the list? */
	while(g->alist[u]->relations >= g->alist[u]->len) {
		g->alist[u]->len *= 2;
		g->alist[u] =
		realloc(g->alist[u],
				sizeof(struct successors) + sizeof(int) * (g->alist[u]->len - 1));
	}
	
	/* now add the new sink */
	g->alist[u]->list[g->alist[u]->relations++] = v;
	g->alist[u]->is_sorted = 0;
	
	/* bump edge count */
	g->edges++;
}

/* return the number of vertices in the graph */
int
graph_vertex_count(p_Graph g)
{
	return g->nodes;
}

/* return the number of vertices in the graph */
int
graph_edge_count(p_Graph g)
{
	return g->edges;
}

/* return the out-degree of a vertex */
int
graph_out_degree(p_Graph g, int source)
{
	
	return g->alist[source]->relations;
}

/* when we are willing to call bsearch */
#define BSEARCH_THRESHOLD (10)

static int
intcmp(const void *a, const void *b)
{
	return *((const int *) a) - *((const int *) b);
}

/* return 1 if edge (source, sink) exists), 0 otherwise */
int
graph_has_edge(p_Graph g, int source, int sink)
{
	int i;
	
	if(graph_out_degree(g, source) >= BSEARCH_THRESHOLD) {
		/* make sure it is sorted */
		if(! g->alist[source]->is_sorted) {
			qsort(g->alist[source]->list,
				  g->alist[source]->relations,
				  sizeof(int),
				  intcmp);
		}
		
		/* call bsearch to do binary search for us */
		return
		bsearch(&sink,
				g->alist[source]->list,
				g->alist[source]->relations,
				sizeof(int),
				intcmp)
		!= 0;
	} else {
		/* just do a simple linear search */
		/* we could call lfind for this, but why bother? */
		for(i = 0; i < g->alist[source]->relations; i++) {
			if(g->alist[source]->list[i] == sink) return 1;
		}
		/* else */
		return 0;
	}
}

/* invoke f on all edges (u,v) with source u */
/* supplying data as final parameter to f */
void
graph_foreach(p_Graph g, int source,
			  void (*f)(p_Graph g, int source, int sink, void *data),
			  void *data)
{
	int i;
	
	for(i = 0; i < g->alist[source]->relations; i++) {
		f(g, source, g->alist[source]->list[i], data);
	}
}

/* test main
 static void
 match_sink(Graph g, int source, int sink, void *data)
 {
	 assert(data && sink == *((int *) data));
 }

 int main(int argc, const char * argv[]) {
	 Graph g;
	 int i;
	 int j;
	 
	 g = graph_create(TEST_SIZE);
	 
	 assert(graph_vertex_count(g) == TEST_SIZE);
	 
	 // check it's empty
	 for(i = 0; i < TEST_SIZE; i++) {
		 for(j = 0; j < TEST_SIZE; j++) {
			 assert(graph_has_edge(g, i, j) == 0);
		 }
	 }
	 
	 //
	 for(i = 0; i < TEST_SIZE; i++) {
		 assert(graph_out_degree(g, i) == 0);
		 graph_foreach(g, i, match_sink, 0);
	 }
	 
	 // check edge count
	 assert(graph_edge_count(g) == 0);
	 
	 // fill in the diagonal
	 for(i = 0; i < TEST_SIZE; i++) {
		 graph_add_edge(g, i, i);
	 }
	 
	 //check
	 assert(graph_edge_count(g) == TEST_SIZE);
	 
	 for(i = 0; i < TEST_SIZE; i++) {
		 for(j = 0; j < TEST_SIZE; j++) {
			 assert(graph_has_edge(g, i, j) == (i == j));
		 }
	 }
	 
	 for(i = 0; i < TEST_SIZE; i++) {
		 assert(graph_out_degree(g, i) == 1);
		 graph_foreach(g, i, match_sink, &i);
	 }
	 
	 
	 // fill in all the entries
	 for(i = 0; i < TEST_SIZE; i++) {
		 for(j = 0; j < TEST_SIZE; j++) {
			 if(i != j) graph_add_edge(g, i, j);
		 }
	 }
	 
	 // test they are all there
	 assert(graph_edge_count(g) == TEST_SIZE * TEST_SIZE);
	 
	 for(i = 0; i < TEST_SIZE; i++) {
		 assert(graph_out_degree(g, i) == TEST_SIZE);
		 for(j = 0; j < TEST_SIZE; j++) {
			 assert(graph_has_edge(g, i, j) == 1);
		 }
	 }
	 int flag;
	 putchar('0');
	 flag = getchar();
	 // free it 
	 graph_destroy(g);
	 
	 return 0;
 }

 
 */
