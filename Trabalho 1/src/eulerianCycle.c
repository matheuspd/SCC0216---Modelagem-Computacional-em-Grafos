#include "eulerianCycle.h"

// Create a graph as a square matrix of "numVertex" order and initializaes the boolean values as false 
Graph *createGraph(int numVertex, int numEdges) {
    Graph *g = malloc(sizeof(Graph));
    if(g != NULL) {
        g->numVertex = numVertex;
        g->numEdges = numEdges;
        g->edge = (bool **)malloc(sizeof(bool*)*numVertex);
        if(g->edge == NULL) {
            free(g);
            return NULL;
        } else {
            for(int i = 0; i < numVertex; i++) {
                g->edge[i] = (bool *)malloc(sizeof(bool)*numVertex);
                if(g->edge[i] == NULL) {
                    free(g->edge);
                    free(g);
                    return NULL;
                } else {
                    for(int j = 0; j < numVertex; j++) {
                        g->edge[i][j] = false;
                    }
                }
            }
            return g;
        }
    }
    return NULL;
}

// Delete the graph
void freeGraph(Graph *g) {
    for(int i = 0; i < g->numVertex; i++) {
        free(g->edge[i]);
    }
    free(g->edge);
    free(g);
}

/*
    Check for an Eurelian Cycle in the graph.
    The graph will have an Eurelian Cycle only if all the vertex have an even degree.
*/
bool hasEulerianCycle(Graph *g) {
    // Check the degrees of all vertex
    for (int i = 0; i < g->numVertex; i++) {
        int degree = 0;
        for (int j = 0; j < g->numVertex; j++) {
            if(i == j) {    // Dont check for connections for the same vertex
                continue;
            }
            if (g->edge[i][j] == true) {
                degree++;
            }
        }
        if (degree % 2 != 0) {
            return false;
        }
    }
    return true;
}

// Print the path of the Eurelian Cycle
void printEulerianCycle(Graph *g) {
    // Initialize array to keep track of the visited edges
    bool visited[g->numVertex][g->numVertex];
    for(int i = 0; i < g->numVertex; i++) {
        for(int j = 0; j < g->numVertex; j++) {
            visited[i][j] = false;
        }
    }

    // Stack to keep track of the visited vertex in the path
    int stack[g->numEdges+1];
    /*  
        Initialize stack with the first vertex (0).
        If the last edge of the path was already visited, 
        this prevents garbage from being stored at the last position of the stack, that is, 
        the last vertex of the path (which is the same as the initial - the vertex 0).
    */
    for(int i = 0; i <= g->numEdges; i++) {
      stack[i] = 0;
    }
    // Starts at vertex 0
    int top = 0;

    while (top >= 0) {
        int v = stack[top];
        bool foundNext = false;

        // Find an unvisited edge
        for (int i = 0; i < g->numVertex; i++) {
            if (g->edge[v][i] && !visited[v][i]) {
                // Visit the edge and push the next vertex onto the stack
                visited[v][i] = visited[i][v] = true;
                top++;
                stack[top] = i;
                foundNext = true;
                break;
            }
        }

        if (!foundNext) {
            // All edges from this vertex were already visited, so pop it from the stack
            top--;
        }
    }

    // Print the final cycle path
    for(int i = 0; i <= g->numEdges; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}