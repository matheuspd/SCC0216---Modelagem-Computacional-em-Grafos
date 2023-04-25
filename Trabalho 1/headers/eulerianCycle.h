#ifndef __EULERIAN_CYCLE__
#define __EULERIAN_CYCLE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Graph matrix ADT
struct graph {
    int numVertex;
    int numEdges;
    bool **edge;
};
typedef struct graph Graph;

// Graph functions
Graph *createGraph(int numVertex, int numEdges);
void freeGraph(Graph *g);
bool hasEulerianCycle(Graph *g);
void printEulerianCycle(Graph *g);

#endif