#include "graph.h"

int main() {
    int num_vertices, num_edges;
    //printf("Digite o número de vértices: ");
    scanf("%d", &num_vertices);
    //printf("Digite o número de arestas: ");
    scanf("%d", &num_edges);

    Graph* graph = createGraph(num_vertices);

    //printf("Digite as arestas (origem e destino):\n");
    for (int i = 0; i < num_edges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    //printf("Componentes fortemente conexas:\n");

    int** strongly_connected_components = (int**)malloc(num_vertices * sizeof(int*));
    int num_components = countStronglyConnectedComponents(graph, &strongly_connected_components);

    //printf("Número de componentes fortemente conexas: %d\n", num_components);
    printf("%d\n", num_components);

    sortComponents(strongly_connected_components, num_components);
    printComponents(strongly_connected_components, num_components);

    for (int i = 0; i < num_components; ++i) {
        free(strongly_connected_components[i]);
    }
    free(strongly_connected_components);
    freeGraph(graph);

    return 0;
}