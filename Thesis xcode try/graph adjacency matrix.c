//
//  graph adjacency matrix.c
//  Thesis xcode try
//
//  Created by Endani Munyai on 2024. 03. 15..
//

#include <stdlib.h>
#include "graph adjacency matrix.h"

struct GraphNode
{
	// number of relations origniating from node
	int numberRelations;
	int lengthRelatedArray;
	//
	int relationIDs[1];
	int relationStrength[1];
};

struct GraphMatrixStruct
{
	int numberNodes;
	int numberEdges;
	struct GraphNode *Nodes[1];
};

p_graph_matrix graph_create(int nodes)
{
	p_graph_matrix graph;
	
	graph = malloc(sizeof(struct GraphMatrixStruct) + sizeof(struct GraphNode) * (nodes-1));
	
	graph->numberNodes = nodes;
	graph->numberEdges = 0;
	
	for (int i=0; i<nodes; i++)
	{
		graph->Nodes[i] = malloc(sizeof(struct GraphNode));
		graph->Nodes[i]->numberRelations = 0;
		graph->Nodes[i]->lengthRelatedArray = 1;
	}
	
	return graph;
}
