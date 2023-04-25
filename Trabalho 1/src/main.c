#include "eulerianCycle.h"

int main() {
    
    // Reads the file name with the graph informations and open it
    char arq[20];
    fgets(arq, 20, stdin);
    FILE *f = fopen(arq , "r");

    int numVertex, numEdges;
    // Read the number of vertex and edges of the graph
    fscanf(f ,"%d %d\n", &numVertex, &numEdges);

    // Create a graph with "numVertex" vertex and "numEdges" edges
    Graph *g = createGraph(numVertex, numEdges);

    // Read the vertex and edges and put them in the graph
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        fscanf(f, "%d %d\n", &src, &dest);
        g->edge[src][dest] = g->edge[dest][src] = true;
    }

    // Check if the graph has an eurelian Cycle
    if (!hasEulerianCycle(g)) {
        printf("Não\n");
    } else {
        printf("Sim\n");
        // Print the Eurelian Cycle path
        printEulerianCycle(g);
    }

    freeGraph(g);
    fclose(f);
}