//
//  graph original adjacency list.c
//  Thesis xcode try
//
//  Created by Endani Munyai on 2024. 03. 08..
//	https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Graphs.html

#include <stdlib.h>
#include "graph original adjacency list.h"

// structure that defines each node
struct GraphNode
{
	int numberRelations;
	int lengthArray;
	char sorted; // true when equal to length of array + 1
	int realtationIdentifiers[1];
};

//structure that defines entire graph
struct GraphStruct
{
	int numberNodes;
	int numberEdges;
	struct GraphNode *Nodes[1];
};

// function that creates and initiallises a graph of n nodes and returns the pointer to said graph
// commented out because of clashing definitions
/*p_graph graph_create(int nodes)
{
	p_graph g;
	
	g = malloc(sizeof(struct GraphStruct) + sizeof(struct GraphNode) * (nodes-1));
	
	g->numberNodes = nodes;
	g->numberEdges = 0;
	
	for (int i=0; i<nodes; i++)
	{
		g->Nodes[i] = malloc(sizeof(struct GraphNode));
		g->Nodes[i]->numberRelations = 0;
		g->Nodes[i]->lengthArray = 1;
	}
	
	return g;
}

// function that destroys a graph via said graphs pointer
void graph_destroy(p_graph g)
{
	// destroys nodes
	for(int i=0; i <g->numberNodes; i++)
		free (g->Nodes[i]);
	
	free(g);
	return;
}*/

int graph_is_sorted (p_graph g,
					 int sourceNodeID)
{
	if (g->Nodes[sourceNodeID]->sorted == g->Nodes[sourceNodeID]->lengthArray + 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void graph_add_edge(p_graph g,
					int u,
					int v)
{
	while(g->Nodes[u]->numberRelations >= g->Nodes[u]->lengthArray)
	{
		g->Nodes[u]->lengthArray *=2;
		g->Nodes[u] = realloc(g->Nodes[u],sizeof(struct GraphNode) + sizeof(int) * (g->Nodes[u]->lengthArray-1));
	}
	g->Nodes[u]->realtationIdentifiers[g->Nodes[u]->numberRelations++]=v;
	g->numberEdges++;
}

int graph_node_number (p_graph g)
{
	return g->numberNodes;
}

int graph_edge_number (p_graph g)
{
	return g->numberEdges;
}

int graph_node_relation_count (p_graph g,
				  int nodeID)
{
	return g->Nodes[nodeID]->numberRelations;
}

static int intcmp (const void *a,
				   const void *b)
{
	return *((const int *) a) - *((const int *) b);
}

# define BSEARCH_THRESHOLD (10)

int graph_edge_exists (p_graph g,
					   int sourceNodeID,
					   int sinkNodeID)
{
	if (! graph_is_sorted(g,sourceNodeID))
	{
		qsort (g->Nodes[sourceNodeID]->realtationIdentifiers,
			   g->Nodes[sourceNodeID]->numberRelations,
			   sizeof(int),
			   intcmp);
	}
	if (graph_node_relation_count(g,sourceNodeID) >= BSEARCH_THRESHOLD)
	{
		return bsearch(&sinkNodeID,
					   g->Nodes[sourceNodeID]->realtationIdentifiers,
					   g->Nodes[sourceNodeID]->numberRelations,
					   sizeof(int),
					   intcmp)
		!= 0;
	}
	else
	{
		for (int i=0; i<g->Nodes[sourceNodeID]->numberRelations; i++)
		{
			if (g->Nodes[sourceNodeID]->realtationIdentifiers[i]==sinkNodeID)
			{
				return 1;
			}
		}
	}
	return 0;
}

void graph_for_each (p_graph g,
					 int sourceNodeID,
					 void (*f)(p_graph g,
							   int sourceNodeID,
							   int sinkNodeID,
							   void *data),
					 void *data)
{
	for (int i=0; i<g->Nodes[sourceNodeID]->numberRelations; i++)
	{
		f(g, sourceNodeID, g->Nodes[sourceNodeID]->realtationIdentifiers[i], data);
	}
}
