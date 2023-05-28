#include "graph.h"

int main() {
    // Reads the number of vertex and edges
    int num_vertices, num_edges;
    scanf("%d %d", &num_vertices, &num_edges);

    Graph* graph = createGraph(num_vertices);

    // Reads the edges source and destination
    for (int i = 0; i < num_edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    // Get the number of strongly connected components and store all of them in a matrix
    int** strongly_connected_components = (int**)malloc(num_vertices * sizeof(int*));
    if (strongly_connected_components == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for the strongly_connected_components array\n");
        freeGraph(graph);
        return EXIT_FAILURE;
    }
    int num_components = countStronglyConnectedComponents(graph, &strongly_connected_components);

    // Print the number of components
    printf("%d\n", num_components);

    // Sort the components and print each one of them in a line
    sortComponents(strongly_connected_components, num_components);
    printComponents(strongly_connected_components, num_components);

    // Free the memory
    for (int i = 0; i < num_components; i++) {
        free(strongly_connected_components[i]);
    }
    free(strongly_connected_components);
    freeGraph(graph);

    return 0;
}