#include "graph.h"

// Create a new node with the given destination vertex
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Error: Memory allocation failed for creating a new node");
        exit(EXIT_FAILURE);
    }
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a new graph with the given number of vertices
Graph* createGraph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        perror("Error: Memory allocation failed for creating a new graph");
        exit(EXIT_FAILURE);
    }
    graph->num_vertices = num_vertices;
    graph->adj_list = (List*)malloc(num_vertices * sizeof(List));
    if (graph->adj_list == NULL) {
        perror("Error: Memory allocation failed for creating adjacency lists");
        free(graph);
        exit(EXIT_FAILURE);
    }

    // Initialize the adjacency lists as empty
    for (int i = 0; i < num_vertices; i++)
        graph->adj_list[i].head = NULL;

    return graph;
}

// Free the memory allocated for the graph
void freeGraph(Graph* graph) {
    if (graph) {
        if (graph->adj_list) {
            // Free the memory allocated for each node in the adjacency lists
            for (int i = 0; i < graph->num_vertices; i++) {
                Node* node = graph->adj_list[i].head;
                while (node != NULL) {
                    Node* next = node->next;
                    free(node);
                    node = next;
                }
            }
            free(graph->adj_list);
        }
        free(graph);
    }
}

// Add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    // Create a new node with the destination vertex
    Node* newNode = createNode(dest);
    // Add the new node at the beginning of the adjacency list for the source vertex
    newNode->next = graph->adj_list[src].head;
    graph->adj_list[src].head = newNode;
}

// Perform depth-first search and fill the order of vertices in the stack
void DFS(Graph* graph, int v, bool* visited, int* stack, int* stack_index) {
    visited[v] = true;

    Node* node = graph->adj_list[v].head;
    while (node != NULL) {
        int adj_vertex = node->dest;
        if (!visited[adj_vertex]) {
            DFS(graph, adj_vertex, visited, stack, stack_index);
        }
        node = node->next;
    }

    // Push the current vertex to the stack
    stack[(*stack_index)++] = v;
}

// Perform depth-first search traversal and store the vertices in a component
void auxDFS(Graph* graph, int v, bool* visited, int* components, int* component_index) {
    visited[v] = true;
    components[(*component_index)++] = v;

    Node* node = graph->adj_list[v].head;
    while (node != NULL) {
        int adj_vertex = node->dest;
        if (!visited[adj_vertex]) {
            auxDFS(graph, adj_vertex, visited, components, component_index);
        }
        node = node->next;
    }

    components[(*component_index)] = -1; // Set the last element as -1 to indicate the end of the component
}

// Get the reversed graph of a given graph
Graph* getReversedGraph(Graph* graph) {
    int num_vertices = graph->num_vertices;
    Graph* reversed_graph = createGraph(num_vertices);

    for (int v = 0; v < num_vertices; v++) {
        Node* node = graph->adj_list[v].head;
        while (node != NULL) {
            addEdge(reversed_graph, node->dest, v);  // Swap the source and destination vertices
            node = node->next;
        }
    }

    return reversed_graph;
}

// Compare two components based on the first element of each component
int compareComponents(const void* a, const void* b) {
    int* pa = *(int**)a;
    int* pb = *(int**)b;
    return pa[0] - pb[0];
}

// Compare two integers
int compareIntegers(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Count the number of strongly connected components in a graph and store them in a matrix
int countStronglyConnectedComponents(Graph* graph, int*** strongly_connected_components) {
    int num_vertices = graph->num_vertices;
    bool* visited = (bool*)calloc(num_vertices, sizeof(bool));
    if (visited == NULL) {
        perror("Error: Memory allocation failed for the 'visited' array");
        exit(EXIT_FAILURE);
    }
    int* stack = (int*)malloc(num_vertices * sizeof(int));
    if (stack == NULL) {
        perror("Error: Memory allocation failed for the 'stack' array");
        free(visited);
        exit(EXIT_FAILURE);
    }
    int stack_index = 0;
    int count = 0;

    // Fill the vertex stack order
    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i]) {
            DFS(graph, i, visited, stack, &stack_index);
        }
    }

    // Create the reversed graph
    Graph* reversed_graph = getReversedGraph(graph);

    // Set the visited array values to false
    for (int i = 0; i < num_vertices; i++)
        visited[i] = false;

    // Do the DFS in the reversed graph storing the components
    for (int i = stack_index - 1; i >= 0; i--) {
        int v = stack[i];
        if (!visited[v]) {
            int* components = (int*)malloc(num_vertices * sizeof(int));
            if (components == NULL) {
                perror("Error: Memory allocation failed for the 'components' array");
                free(visited);
                free(stack);
                freeGraph(reversed_graph);
                exit(EXIT_FAILURE);
            }
            int component_index = 0;
            auxDFS(reversed_graph, v, visited, components, &component_index);
            (*strongly_connected_components)[count] = components;
            count++;
        }
    }

    free(visited);
    free(stack);
    freeGraph(reversed_graph);
    return count;
}

// Print a strongly connected component
void printComponent(int* component) {
    for (int i = 0; component[i] != -1; i++) {
        printf("%d ", component[i]);
    }
    printf("\n");
}

// Print all the strongly connected components
void printComponents(int** strongly_connected_components, int num_components) {
    for (int i = 0; i < num_components; i++) {
        printComponent(strongly_connected_components[i]);
    }
}

// Sort the strongly connected components
void sortComponents(int** strongly_connected_components, int num_components) {   
    for (int i = 0; i < num_components; i++) {
        int* component = strongly_connected_components[i];
        int j;
        for (j = 0; component[j] != -1; j++) {}
        qsort(component, j, sizeof(int), compareIntegers);
    }
    qsort(strongly_connected_components, num_components, sizeof(int*), compareComponents);
}