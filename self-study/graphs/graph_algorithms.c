#include "graph_algorithms.h"

// ============================================================================
// DEPTH-FIRST SEARCH (Section 6.5, 7.3)
// ============================================================================

void dfsListFromVertex(AdjList *G, Vertex source, TraversalData *result) {
    int currentIndex = source;
    result->mark[currentIndex] = VISITED;

    static int time = 0;
    result->discoveryTime[currentIndex] = time++;

    Edge current = G->adjList[currentIndex];
    while (current != NULL) {
        int neighborIndex = current->dest;
        if (result->mark[neighborIndex] == UNVISITED) {
            result->parent[neighborIndex] = currentIndex;
            dfsListFromVertex(G, neighborIndex, result);
        }
        current = current->next;
    }

    result->mark[currentIndex] = FINISHED;
    result->finishTime[currentIndex] = time++;
}

void dfsMatrixFromVertex(AdjMatrix *G, Vertex source, TraversalData *result) {
    int currentIndex = source;
    result->mark[currentIndex] = VISITED;

    static int time = 0;
    result->discoveryTime[currentIndex] = time++;

    for (int i = 0; i < G->numVertices; i++) {
        if (G->adjMatrix[currentIndex][i] != INFINITY && G->adjMatrix[currentIndex][i] != 0) {
            if (result->mark[i] == UNVISITED) {
                result->parent[i] = currentIndex;
                dfsMatrixFromVertex(G, i, result);
            }
        }
    }

    result->mark[currentIndex] = FINISHED;
    result->finishTime[currentIndex] = time++;
}

void dfsListAll(AdjList *G, TraversalData *result) {
    for (int i = 0; i < G->numVertices; i++) {
        if (result->mark[i] == UNVISITED) {
            dfsListFromVertex(G, i, result);
        }
    }
}

void dfsMatrixAll(AdjMatrix *G, TraversalData *result) {
    for (int i = 0; i < G->numVertices; i++) {
        if (result->mark[i] == UNVISITED) {
            dfsMatrixFromVertex(G, i, result);
        }
    }
}

EdgeType classifyEdge(Vertex u, Vertex v, TraversalData *data) {
    if (data->mark[v] == UNVISITED) {
        return TREE_EDGE;
    }

    if (data->discoveryTime[v] < data->discoveryTime[u] &&
        data->finishTime[u] < data->finishTime[v]) {
        return BACK_EDGE;
    }

    if (data->discoveryTime[u] < data->discoveryTime[v] &&
        data->finishTime[v] < data->finishTime[u]) {
        return FORWARD_EDGE;
    }

    return CROSS_EDGE;
}

// ============================================================================
// BREADTH-FIRST SEARCH (Section 7.3)
// ============================================================================

void bfsListFromVertex(AdjList *G, Vertex source, TraversalData *result) {
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    result->mark[source] = VISITED;
    result->distance[source] = 0;
    queue[rear++] = source;

    while (front < rear) {
        int current = queue[front++];

        Edge currentEdge = G->adjList[current];
        while (currentEdge != NULL) {
            int neighbor = currentEdge->dest;
            if (result->mark[neighbor] == UNVISITED) {
                result->mark[neighbor] = VISITED;
                result->distance[neighbor] = result->distance[current] + 1;
                result->parent[neighbor] = current;
                queue[rear++] = neighbor;
            }
            currentEdge = currentEdge->next;
        }
    }
}

void bfsMatrixFromVertex(AdjMatrix *G, Vertex source, TraversalData *result) {
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    result->mark[source] = VISITED;
    result->distance[source] = 0;
    queue[rear++] = source;

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < G->numVertices; i++) {
            if (G->adjMatrix[current][i] != INFINITY && G->adjMatrix[current][i] != 0) {
                if (result->mark[i] == UNVISITED) {
                    result->mark[i] = VISITED;
                    result->distance[i] = result->distance[current] + 1;
                    result->parent[i] = current;
                    queue[rear++] = i;
                }
            }
        }
    }
}

void bfsListAll(AdjList *G, TraversalData *result) {
    for (int i = 0; i < G->numVertices; i++) {
        if (result->mark[i] == UNVISITED) {
            bfsListFromVertex(G, i, result);
        }
    }
}

void bfsMatrixAll(AdjMatrix *G, TraversalData *result) {
    for (int i = 0; i < G->numVertices; i++) {
        if (result->mark[i] == UNVISITED) {
            bfsMatrixFromVertex(G, i, result);
        }
    }
}

// ============================================================================
// DIJKSTRA'S ALGORITHM (Section 6.3)
// ============================================================================

void dijkstraMatrix(AdjMatrix *G, Vertex source, ShortestPathData *result) {
    for (int i = 0; i < G->numVertices; i++) {
        result->dist[i] = G->adjMatrix[source][i];
        result->pred[i] = (G->adjMatrix[source][i] != INFINITY) ? source : NIL;
        result->inSet[i] = false;
    }

    result->dist[source] = 0;
    result->pred[source] = NIL;
    result->inSet[source] = true;

    for (int i = 1; i < G->numVertices; i++) {
        int minDist = INFINITY;
        int w = -1;

        for (int j = 0; j < G->numVertices; j++) {
            if (!result->inSet[j] && result->dist[j] < minDist) {
                minDist = result->dist[j];
                w = j;
            }
        }

        if (w == -1) break;

        result->inSet[w] = true;

        for (int v = 0; v < G->numVertices; v++) {
            if (!result->inSet[v] && G->adjMatrix[w][v] != INFINITY) {
                if (result->dist[w] + G->adjMatrix[w][v] < result->dist[v]) {
                    result->dist[v] = result->dist[w] + G->adjMatrix[w][v];
                    result->pred[v] = w;
                }
            }
        }
    }
}

void dijkstraList(AdjList *G, Vertex source, ShortestPathData *result) {
    for (int i = 0; i < G->numVertices; i++) {
        result->dist[i] = INFINITY;
        result->pred[i] = NIL;
        result->inSet[i] = false;
    }

    result->dist[source] = 0;
    result->inSet[source] = true;

    Edge current = G->adjList[source];
    while (current != NULL) {
        result->dist[current->dest] = current->weight;
        result->pred[current->dest] = source;
        current = current->next;
    }

    for (int i = 1; i < G->numVertices; i++) {
        int minDist = INFINITY;
        int w = -1;

        for (int j = 0; j < G->numVertices; j++) {
            if (!result->inSet[j] && result->dist[j] < minDist) {
                minDist = result->dist[j];
                w = j;
            }
        }

        if (w == -1) break;

        result->inSet[w] = true;

        Edge currentEdge = G->adjList[w];
        while (currentEdge != NULL) {
            int v = currentEdge->dest;
            if (!result->inSet[v]) {
                if (result->dist[w] + currentEdge->weight < result->dist[v]) {
                    result->dist[v] = result->dist[w] + currentEdge->weight;
                    result->pred[v] = w;
                }
            }
            currentEdge = currentEdge->next;
        }
    }
}

void printShortestPath(ShortestPathData *data, Vertex source, Vertex dest) {
    if (dest == source) {
        printf("%d", source);
        return;
    }

    if (data->pred[dest] == NIL) {
        printf("No path exists");
        return;
    }

    printShortestPath(data, source, data->pred[dest]);
    printf(" -> %d", dest);
}

bool hasPath(ShortestPathData *data, Vertex dest) {
    return data->dist[dest] != INFINITY;
}

// ============================================================================
// FLOYD-WARSHALL ALGORITHM (Section 6.4)
// ============================================================================

void floydWarshall(AdjMatrix *G, AllPairsData *result) {
    for (int i = 0; i < G->numVertices; i++) {
        for (int j = 0; j < G->numVertices; j++) {
            result->dist[i][j] = G->adjMatrix[i][j];
            result->path[i][j] = NIL;
        }
        result->dist[i][i] = 0;
    }

    for (int k = 0; k < G->numVertices; k++) {
        for (int i = 0; i < G->numVertices; i++) {
            for (int j = 0; j < G->numVertices; j++) {
                if (result->dist[i][k] != INFINITY && result->dist[k][j] != INFINITY) {
                    if (result->dist[i][k] + result->dist[k][j] < result->dist[i][j]) {
                        result->dist[i][j] = result->dist[i][k] + result->dist[k][j];
                        result->path[i][j] = k;
                    }
                }
            }
        }
    }
}

void printFloydPath(AllPairsData *data, Vertex u, Vertex v) {
    if (data->path[u][v] == NIL) {
        printf("%d -> %d", u, v);
        return;
    }

    int k = data->path[u][v];
    printFloydPath(data, u, k);
    printf(" -> ");
    printFloydPath(data, k, v);
}

// ============================================================================
// WARSHALL'S ALGORITHM (Section 6.4)
// ============================================================================

void warshall(AdjMatrix *G, bool closure[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < G->numVertices; i++) {
        for (int j = 0; j < G->numVertices; j++) {
            closure[i][j] = (G->adjMatrix[i][j] != INFINITY && i != j);
        }
    }

    for (int k = 0; k < G->numVertices; k++) {
        for (int i = 0; i < G->numVertices; i++) {
            for (int j = 0; j < G->numVertices; j++) {
                closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
            }
        }
    }
}

// ============================================================================
// PRIM'S ALGORITHM (Section 7.2)
// ============================================================================

void primMatrix(AdjMatrix *G, MSTResult *result) {
    int lowcost[MAX_VERTICES];
    int closest[MAX_VERTICES];
    bool inU[MAX_VERTICES];

    for (int i = 0; i < G->numVertices; i++) {
        inU[i] = false;
    }

    inU[0] = true;
    for (int i = 1; i < G->numVertices; i++) {
        lowcost[i] = G->adjMatrix[0][i];
        closest[i] = 0;
    }

    result->numEdges = 0;
    result->totalCost = 0;

    for (int i = 1; i < G->numVertices; i++) {
        int minCost = INFINITY;
        int k = -1;

        for (int j = 1; j < G->numVertices; j++) {
            if (!inU[j] && lowcost[j] < minCost) {
                minCost = lowcost[j];
                k = j;
            }
        }

        if (k == -1) break;

        result->edges[result->numEdges].u = closest[k];
        result->edges[result->numEdges].v = k;
        result->edges[result->numEdges].weight = lowcost[k];
        result->numEdges++;
        result->totalCost += lowcost[k];

        inU[k] = true;

        for (int j = 1; j < G->numVertices; j++) {
            if (!inU[j] && G->adjMatrix[k][j] < lowcost[j]) {
                lowcost[j] = G->adjMatrix[k][j];
                closest[j] = k;
            }
        }
    }
}

void primList(AdjList *G, MSTResult *result) {
    int lowcost[MAX_VERTICES];
    int closest[MAX_VERTICES];
    bool inU[MAX_VERTICES];

    for (int i = 0; i < G->numVertices; i++) {
        lowcost[i] = INFINITY;
        inU[i] = false;
    }

    inU[0] = true;
    Edge current = G->adjList[0];
    while (current != NULL) {
        lowcost[current->dest] = current->weight;
        closest[current->dest] = 0;
        current = current->next;
    }

    result->numEdges = 0;
    result->totalCost = 0;

    for (int i = 1; i < G->numVertices; i++) {
        int minCost = INFINITY;
        int k = -1;

        for (int j = 1; j < G->numVertices; j++) {
            if (!inU[j] && lowcost[j] < minCost) {
                minCost = lowcost[j];
                k = j;
            }
        }

        if (k == -1) break;

        result->edges[result->numEdges].u = closest[k];
        result->edges[result->numEdges].v = k;
        result->edges[result->numEdges].weight = lowcost[k];
        result->numEdges++;
        result->totalCost += lowcost[k];

        inU[k] = true;

        Edge currentEdge = G->adjList[k];
        while (currentEdge != NULL) {
            int neighbor = currentEdge->dest;
            if (!inU[neighbor] && currentEdge->weight < lowcost[neighbor]) {
                lowcost[neighbor] = currentEdge->weight;
                closest[neighbor] = k;
            }
            currentEdge = currentEdge->next;
        }
    }
}

// ============================================================================
// KRUSKAL'S ALGORITHM (Section 7.2)
// ============================================================================

int compareEdges(const void *a, const void *b) {
    MSTEdge *edgeA = (MSTEdge *)a;
    MSTEdge *edgeB = (MSTEdge *)b;
    return edgeA->weight - edgeB->weight;
}

void kruskal(AdjMatrix *G, MSTResult *result) {
    MSTEdge edges[MAX_VERTICES * MAX_VERTICES];
    int edgeCount = 0;

    for (int i = 0; i < G->numVertices; i++) {
        for (int j = i + 1; j < G->numVertices; j++) {
            if (G->adjMatrix[i][j] != INFINITY && G->adjMatrix[i][j] != 0) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = G->adjMatrix[i][j];
                edgeCount++;
            }
        }
    }

    qsort(edges, edgeCount, sizeof(MSTEdge), compareEdges);

    UnionFind uf;
    initUnionFind(&uf, G->numVertices);

    result->numEdges = 0;
    result->totalCost = 0;
    int ncomp = G->numVertices;

    for (int i = 0; i < edgeCount && ncomp > 1; i++) {
        int ucomp = find(&uf, edges[i].u);
        int vcomp = find(&uf, edges[i].v);

        if (ucomp != vcomp) {
            result->edges[result->numEdges] = edges[i];
            result->numEdges++;
            result->totalCost += edges[i].weight;
            unionSets(&uf, ucomp, vcomp);
            ncomp--;
        }
    }
}

void kruskalList(AdjList *G, MSTResult *result) {
    MSTEdge edges[MAX_VERTICES * MAX_VERTICES];
    int edgeCount = 0;

    for (int i = 0; i < G->numVertices; i++) {
        Edge current = G->adjList[i];
        while (current != NULL) {
            if (i < current->dest) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = current->dest;
                edges[edgeCount].weight = current->weight;
                edgeCount++;
            }
            current = current->next;
        }
    }

    qsort(edges, edgeCount, sizeof(MSTEdge), compareEdges);

    UnionFind uf;
    initUnionFind(&uf, G->numVertices);

    result->numEdges = 0;
    result->totalCost = 0;
    int ncomp = G->numVertices;

    for (int i = 0; i < edgeCount && ncomp > 1; i++) {
        int ucomp = find(&uf, edges[i].u);
        int vcomp = find(&uf, edges[i].v);

        if (ucomp != vcomp) {
            result->edges[result->numEdges] = edges[i];
            result->numEdges++;
            result->totalCost += edges[i].weight;
            unionSets(&uf, ucomp, vcomp);
            ncomp--;
        }
    }
}

void displayMST(MSTResult *mst) {
    printf("----- MST EDGES -----\n");
    for (int i = 0; i < mst->numEdges; i++) {
        printf("Edge %d: (%d, %d) weight %d\n",
               i + 1, mst->edges[i].u, mst->edges[i].v, mst->edges[i].weight);
    }
    printf("Total cost: %d\n", mst->totalCost);
}

// ============================================================================
// UNION-FIND DATA STRUCTURE
// ============================================================================

void initUnionFind(UnionFind *uf, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
}

int find(UnionFind *uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]);
    }
    return uf->parent[x];
}

void unionSets(UnionFind *uf, int x, int y) {
    int xroot = find(uf, x);
    int yroot = find(uf, y);

    if (xroot == yroot) return;

    if (uf->rank[xroot] < uf->rank[yroot]) {
        uf->parent[xroot] = yroot;
    } else if (uf->rank[xroot] > uf->rank[yroot]) {
        uf->parent[yroot] = xroot;
    } else {
        uf->parent[yroot] = xroot;
        uf->rank[xroot]++;
    }
}

bool sameSet(UnionFind *uf, int x, int y) {
    return find(uf, x) == find(uf, y);
}

// ============================================================================
// TOPOLOGICAL SORT (Section 6.6)
// ============================================================================

void topSortDFSHelper(AdjList *G, Vertex v, TraversalData *data, Vertex *ordering, int *orderSize, bool *hasCycle) {
    data->mark[v] = VISITED;

    Edge current = G->adjList[v];
    while (current != NULL) {
        if (data->mark[current->dest] == UNVISITED) {
            topSortDFSHelper(G, current->dest, data, ordering, orderSize, hasCycle);
        } else if (data->mark[current->dest] == VISITED) {
            *hasCycle = true;
        }
        current = current->next;
    }

    data->mark[v] = FINISHED;
    ordering[(*orderSize)++] = v;
}

bool topologicalSort(AdjList *G, Vertex *ordering, int *orderSize) {
    TraversalData data;
    initTraversalData(&data, G->numVertices);

    *orderSize = 0;
    bool hasCycle = false;

    for (int i = 0; i < G->numVertices; i++) {
        if (data.mark[i] == UNVISITED) {
            topSortDFSHelper(G, i, &data, ordering, orderSize, &hasCycle);
        }
    }

    if (hasCycle) return false;

    for (int i = 0; i < *orderSize / 2; i++) {
        Vertex temp = ordering[i];
        ordering[i] = ordering[*orderSize - 1 - i];
        ordering[*orderSize - 1 - i] = temp;
    }

    return true;
}

bool isDAG(AdjList *G) {
    Vertex ordering[MAX_VERTICES];
    int orderSize;
    return topologicalSort(G, ordering, &orderSize);
}

// ============================================================================
// STRONGLY CONNECTED COMPONENTS (Section 6.7)
// ============================================================================

void sccDFS1(AdjList *G, Vertex v, TraversalData *data, Vertex *stack, int *stackTop) {
    data->mark[v] = VISITED;

    Edge current = G->adjList[v];
    while (current != NULL) {
        if (data->mark[current->dest] == UNVISITED) {
            sccDFS1(G, current->dest, data, stack, stackTop);
        }
        current = current->next;
    }

    stack[(*stackTop)++] = v;
}

void sccDFS2(AdjList *G, Vertex v, TraversalData *data, int componentNum, int components[MAX_VERTICES]) {
    data->mark[v] = VISITED;
    components[v] = componentNum;

    Edge current = G->adjList[v];
    while (current != NULL) {
        if (data->mark[current->dest] == UNVISITED) {
            sccDFS2(G, current->dest, data, componentNum, components);
        }
        current = current->next;
    }
}

int findSCC(AdjList *G, int components[MAX_VERTICES]) {
    TraversalData data;
    initTraversalData(&data, G->numVertices);

    Vertex stack[MAX_VERTICES];
    int stackTop = 0;

    for (int i = 0; i < G->numVertices; i++) {
        if (data.mark[i] == UNVISITED) {
            sccDFS1(G, i, &data, stack, &stackTop);
        }
    }

    AdjList reverseG;
    reverseG.numVertices = G->numVertices;
    reverseG.isDirected = true;
    reverseG.adjList = (Edge *)malloc(sizeof(Edge) * G->numVertices);

    for (int i = 0; i < G->numVertices; i++) {
        reverseG.adjList[i] = NULL;
    }

    for (int i = 0; i < G->numVertices; i++) {
        Edge current = G->adjList[i];
        while (current != NULL) {
            EdgeNode *newEdge = (EdgeNode *)malloc(sizeof(EdgeNode));
            newEdge->dest = i;
            newEdge->weight = current->weight;
            newEdge->next = reverseG.adjList[current->dest];
            reverseG.adjList[current->dest] = newEdge;
            current = current->next;
        }
    }

    initTraversalData(&data, G->numVertices);
    int componentNum = 0;

    for (int i = stackTop - 1; i >= 0; i--) {
        if (data.mark[stack[i]] == UNVISITED) {
            sccDFS2(&reverseG, stack[i], &data, componentNum, components);
            componentNum++;
        }
    }

    for (int i = 0; i < reverseG.numVertices; i++) {
        Edge current = reverseG.adjList[i];
        while (current != NULL) {
            Edge temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(reverseG.adjList);

    return componentNum;
}

bool isStronglyConnected(AdjList *G) {
    int components[MAX_VERTICES];
    int numComponents = findSCC(G, components);
    return numComponents == 1;
}

// ============================================================================
// CONNECTED COMPONENTS (Undirected Graphs - Section 7.3)
// ============================================================================

void ccDFS(AdjList *G, Vertex v, TraversalData *data, int componentNum, int components[MAX_VERTICES]) {
    data->mark[v] = VISITED;
    components[v] = componentNum;

    Edge current = G->adjList[v];
    while (current != NULL) {
        if (data->mark[current->dest] == UNVISITED) {
            ccDFS(G, current->dest, data, componentNum, components);
        }
        current = current->next;
    }
}

int findConnectedComponents(AdjList *G, int components[MAX_VERTICES]) {
    TraversalData data;
    initTraversalData(&data, G->numVertices);

    int componentNum = 0;

    for (int i = 0; i < G->numVertices; i++) {
        if (data.mark[i] == UNVISITED) {
            ccDFS(G, i, &data, componentNum, components);
            componentNum++;
        }
    }

    return componentNum;
}

bool isConnected(AdjList *G) {
    int components[MAX_VERTICES];
    int numComponents = findConnectedComponents(G, components);
    return numComponents == 1;
}

// ============================================================================
// ARTICULATION POINTS (Section 7.4)
// ============================================================================

void apDFS(AdjList *G, Vertex v, Vertex parent, TraversalData *data, int *dfnumber, int *low, Vertex artPoints[MAX_VERTICES], int *artCount, int *time) {
    int children = 0;
    dfnumber[v] = (*time)++;
    low[v] = dfnumber[v];
    data->mark[v] = VISITED;

    Edge current = G->adjList[v];
    while (current != NULL) {
        Vertex w = current->dest;

        if (data->mark[w] == UNVISITED) {
            children++;
            apDFS(G, w, v, data, dfnumber, low, artPoints, artCount, time);

            if (low[w] < low[v]) {
                low[v] = low[w];
            }

            if (parent != NIL && low[w] >= dfnumber[v]) {
                bool alreadyFound = false;
                for (int i = 0; i < *artCount; i++) {
                    if (artPoints[i] == v) {
                        alreadyFound = true;
                        break;
                    }
                }
                if (!alreadyFound) {
                    artPoints[(*artCount)++] = v;
                }
            }
        } else if (w != parent) {
            if (dfnumber[w] < low[v]) {
                low[v] = dfnumber[w];
            }
        }

        current = current->next;
    }

    if (parent == NIL && children > 1) {
        artPoints[(*artCount)++] = v;
    }
}

int findArticulationPoints(AdjList *G, Vertex artPoints[MAX_VERTICES]) {
    TraversalData data;
    initTraversalData(&data, G->numVertices);

    int dfnumber[MAX_VERTICES];
    int low[MAX_VERTICES];
    int artCount = 0;
    int time = 0;

    for (int i = 0; i < G->numVertices; i++) {
        if (data.mark[i] == UNVISITED) {
            apDFS(G, i, NIL, &data, dfnumber, low, artPoints, &artCount, &time);
        }
    }

    return artCount;
}

bool isBiconnected(AdjList *G) {
    if (!isConnected(G)) return false;

    Vertex artPoints[MAX_VERTICES];
    int artCount = findArticulationPoints(G, artPoints);
    return artCount == 0;
}

// ============================================================================
// CYCLE DETECTION
// ============================================================================

bool cycleDFSDirected(AdjList *G, Vertex v, TraversalData *data) {
    data->mark[v] = VISITED;

    Edge current = G->adjList[v];
    while (current != NULL) {
        if (data->mark[current->dest] == UNVISITED) {
            if (cycleDFSDirected(G, current->dest, data)) {
                return true;
            }
        } else if (data->mark[current->dest] == VISITED) {
            return true;
        }
        current = current->next;
    }

    data->mark[v] = FINISHED;
    return false;
}

bool hasCycleDirected(AdjList *G) {
    TraversalData data;
    initTraversalData(&data, G->numVertices);

    for (int i = 0; i < G->numVertices; i++) {
        if (data.mark[i] == UNVISITED) {
            if (cycleDFSDirected(G, i, &data)) {
                return true;
            }
        }
    }

    return false;
}

bool cycleDFSUndirected(AdjList *G, Vertex v, Vertex parent, TraversalData *data) {
    data->mark[v] = VISITED;

    Edge current = G->adjList[v];
    while (current != NULL) {
        if (data->mark[current->dest] == UNVISITED) {
            if (cycleDFSUndirected(G, current->dest, v, data)) {
                return true;
            }
        } else if (current->dest != parent) {
            return true;
        }
        current = current->next;
    }

    return false;
}

bool hasCycleUndirected(AdjList *G) {
    TraversalData data;
    initTraversalData(&data, G->numVertices);

    for (int i = 0; i < G->numVertices; i++) {
        if (data.mark[i] == UNVISITED) {
            if (cycleDFSUndirected(G, i, NIL, &data)) {
                return true;
            }
        }
    }

    return false;
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

void initTraversalData(TraversalData *data, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        data->parent[i] = NIL;
        data->distance[i] = INFINITY;
        data->discoveryTime[i] = 0;
        data->finishTime[i] = 0;
        data->mark[i] = UNVISITED;
    }
}

void printTraversalTree(TraversalData *data, int numVertices) {
    printf("----- DFS/BFS TREE -----\n");
    for (int i = 0; i < numVertices; i++) {
        printf("Vertex %d: parent = ", i);
        if (data->parent[i] == NIL) {
            printf("NIL");
        } else {
            printf("%d", data->parent[i]);
        }
        printf("\n");
    }
}
