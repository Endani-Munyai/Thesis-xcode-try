//
//  graph_adjency_list.h
//  Thesis xcode try
//
//  Created by Endani Munyai on 2024. 03. 07..
//https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Graphs.html

#ifndef graph_adjency_list_h
#define graph_adjency_list_h

#include <stdio.h>

/* basic directed graph type */

typedef struct graph *p_Graph;
// Graph refers to a pointer (not the actual structure) to a GraphStruct structure.

/* create a new graph with n vertices labeled 0..n-1 and no edges */
p_Graph graph_create(int nodes);

/* free all space used by graph */
void graph_destroy(p_Graph);

/* add an edge to an existing graph */
/* doing this more than once may have unpredictable results */
void graph_add_edge(p_Graph,
                    int source,
                    int sink);

/* return the number of vertices/edges in the graph */
int graph_vertex_count(p_Graph);
int graph_edge_count(p_Graph);

/* return the out-degree of a vertex */
int graph_out_degree(p_Graph,
                     int source);

/* return 1 if edge (source, sink) exists), 0 otherwise */
int graph_has_edge(p_Graph,
                   int source,
                   int sink);

/* invoke f on all edges (u,v) with source u */
/* supplying data as final parameter to f */
/* no particular order is guaranteed */
void graph_foreach(p_Graph g,
                   int source,
                   void (*f)(p_Graph g, int source, int sink, void *data),
                   void *data);

#endif /* graph_adjency_list_h */
