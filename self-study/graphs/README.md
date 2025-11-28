# Graph Data Structures and Algorithms - Training Ground

A comprehensive collection of graph implementations and algorithms based on Aho's "Data Structures and Algorithms" (Chapters 6 & 7). This directory follows the same systematic pattern as `adt_list_mania` and `tree` for consistent practice.

## Directory Structure

```
graphs/
├── graph.h                  # Type definitions for all graph structures
├── adjacency_matrix.h/.c    # Matrix representation (Aho Section 6.2)
├── adjacency_list.h/.c      # List representation (Aho Section 6.2)
├── graph_algorithms.h/.c    # All major graph algorithms
├── main.c                   # Test driver (to be implemented)
└── README.md                # This file
```

## File Organization Pattern

Following the established pattern:

1. **graph.h** - Shared type definitions
   - Both graph representations (matrix and list)
   - Traversal data structures
   - Shortest path structures
   - MST structures
   - Union-find for Kruskal

2. **adjacency_matrix.h/.c** - Matrix implementation
   - O(1) edge lookup
   - O(n²) space
   - Best for dense graphs

3. **adjacency_list.h/.c** - List implementation
   - O(|V| + |E|) space
   - Best for sparse graphs
   - Efficient neighbor iteration

4. **graph_algorithms.h/.c** - All algorithms
   - DFS, BFS
   - Dijkstra, Floyd-Warshall
   - Prim, Kruskal
   - Topological sort, SCCs, etc.

5. **main.c** - Testing framework (create this)
   - Test each representation
   - Test each algorithm
   - Compare matrix vs list

## Graph Representations

### 1. Adjacency Matrix (`adjacency_matrix.h/.c`)
**Based on:** Aho Section 6.2

**Structure:** n × n matrix where entry [i][j] = edge weight (or INFINITY if no edge)

**Advantages:**
- ✅ O(1) time to check if edge exists
- ✅ Simple implementation
- ✅ Good for dense graphs (e ≈ n²)

**Disadvantages:**
- ❌ O(n²) space even for sparse graphs
- ❌ O(n²) time to initialize
- ❌ Inefficient to iterate through neighbors

**Operations:**
- `addEdgeMatrix(G, u, v, weight)` - Add edge
- `hasEdgeMatrix(G, u, v)` - Check edge existence
- `firstMatrix(G, v)` - Get first neighbor
- `nextMatrix(G, v, i)` - Get next neighbor

---

### 2. Adjacency List (`adjacency_list.h/.c`)
**Based on:** Aho Section 6.2

**Structure:** Array of linked lists - each vertex has list of adjacent vertices

**Advantages:**
- ✅ O(|V| + |E|) space - proportional to graph size
- ✅ Efficient neighbor iteration
- ✅ Good for sparse graphs (e << n²)

**Disadvantages:**
- ❌ O(degree(v)) time to check specific edge
- ❌ Slightly more complex implementation

**Operations:**
- `addEdgeList(G, u, v, weight)` - Add edge
- `hasEdgeList(G, u, v)` - Check edge (O(degree))
- `firstList(G, v)` - Get first neighbor
- `nextList(G, v, edge)` - Get next neighbor

**When to use List vs Matrix:**
- **Sparse graph (e << n²):** Use adjacency list
- **Dense graph (e ≈ n²):** Use adjacency matrix
- **Frequent edge checks:** Use matrix
- **Iterate neighbors frequently:** Use list

---

## Graph Algorithms

### 1. Depth-First Search (DFS)
**Based on:** Aho Section 6.5 (directed), 7.3 (undirected)

**Purpose:** Systematically explore graph by going as deep as possible

**Key Operations:**
- `dfsListFromVertex(G, source, result)` - DFS from single vertex
- `dfsListAll(G, result)` - DFS entire graph (handles disconnected)

**Algorithm:**
```
mark[v] := VISITED
for each neighbor w of v:
    if mark[w] = UNVISITED:
        parent[w] := v
        dfs(w)
```

**Time:** O(e) with adjacency lists, O(n²) with matrix

**Applications:**
- Finding connected components
- Detecting cycles
- Topological sorting
- Finding strongly connected components

**Edge Types (Directed Graphs):**
- **Tree edges:** To unvisited vertices
- **Back edges:** To ancestors (indicates cycle!)
- **Forward edges:** To proper descendants
- **Cross edges:** Between non-ancestor/descendant

---

### 2. Breadth-First Search (BFS)
**Based on:** Aho Section 7.3

**Purpose:** Explore graph level by level (shortest paths in unweighted graphs!)

**Key Operations:**
- `bfsListFromVertex(G, source, result)` - BFS from single vertex
- `bfsListAll(G, result)` - BFS entire graph

**Algorithm:**
```
mark[source] := VISITED
enqueue(Q, source)
while Q not empty:
    v := dequeue(Q)
    for each neighbor w of v:
        if mark[w] = UNVISITED:
            mark[w] := VISITED  // BEFORE enqueue!
            parent[w] := v
            enqueue(Q, w)
```

**IMPORTANT:** Mark vertices BEFORE enqueuing to avoid duplicates!

**Time:** O(e) with adjacency lists

**Applications:**
- Shortest paths (unweighted graphs)
- Level-order traversal
- Testing connectivity

---

### 3. Dijkstra's Algorithm
**Based on:** Aho Section 6.3

**Purpose:** Single-source shortest paths with **non-negative** weights

**Key Operation:**
- `dijkstraMatrix(G, source, result)` - Find shortest paths from source

**Algorithm:**
```
S := {source}  // Vertices with known shortest paths
dist[source] := 0
for each vertex v:
    dist[v] := direct cost from source

repeat n-1 times:
    choose w in V-S with minimum dist[w]
    add w to S
    for each v in V-S:
        dist[v] := min(dist[v], dist[w] + cost[w][v])
```

**Time:**
- O(n²) with adjacency matrix
- O(e log n) with adjacency list + priority queue

**CRITICAL:** Requires **non-negative edge weights!** Fails with negative weights.

**Returns:** Distance and predecessor for path reconstruction

---

### 4. Floyd-Warshall Algorithm
**Based on:** Aho Section 6.4

**Purpose:** **All-pairs** shortest paths

**Key Operation:**
- `floydWarshall(G, result)` - Find shortest paths between all pairs

**Algorithm:**
```
// Initialize
for i, j: A[i][j] := cost[i][j]

// Dynamic programming
for k := 1 to n:  // Intermediate vertex
    for i := 1 to n:
        for j := 1 to n:
            A[i][j] := min(A[i][j], A[i][k] + A[k][j])
```

**Invariant:** After k iterations, A[i][j] = shortest path using vertices ≤ k

**Time:** O(n³)

**Comparison with Dijkstra:**
- Floyd: O(n³) for all pairs
- Dijkstra × n: Also O(n³) with matrix, O(ne log n) with lists
- **Use Floyd for dense graphs, Dijkstra for sparse**

**Advantage:** Can handle **negative weights** (but not negative cycles)

---

### 5. Prim's Algorithm
**Based on:** Aho Section 7.2

**Purpose:** Minimum Spanning Tree for **undirected** graphs

**Key Operation:**
- `primMatrix(G, result)` - Find MST

**Algorithm:**
```
U := {1}  // Start with vertex 1
for each v not in U:
    LOWCOST[v] := cost from 1 to v
    CLOSEST[v] := 1

repeat n-1 times:
    find k with minimum LOWCOST[k] among V-U
    add edge (k, CLOSEST[k]) to MST
    add k to U
    for each v in V-U:
        if cost[k][v] < LOWCOST[v]:
            LOWCOST[v] := cost[k][v]
            CLOSEST[v] := k
```

**Time:** O(n²)

**When to use:** Dense graphs (e ≈ n²)

**MST Property:** Greedy choice is always safe - adding cheapest edge connecting tree to non-tree vertex

---

### 6. Kruskal's Algorithm
**Based on:** Aho Section 7.2

**Purpose:** Minimum Spanning Tree using edge sorting

**Key Operation:**
- `kruskal(G, result)` - Find MST

**Algorithm:**
```
1. Sort all edges by weight
2. Initialize union-find: each vertex in own set
3. For each edge (u,v) in sorted order:
       if FIND(u) ≠ FIND(v):  // Doesn't create cycle
           add (u,v) to MST
           MERGE(u, v)
```

**Time:** O(e log e) - dominated by sorting

**When to use:** Sparse graphs (e << n²)

**Uses Union-Find:**
- `FIND(x)` - Find set containing x (with path compression)
- `MERGE(x, y)` - Merge sets containing x and y (union by rank)

---

### 7. Topological Sort
**Based on:** Aho Section 6.6

**Purpose:** Linear ordering of vertices in DAG

**Key Operation:**
- `topologicalSort(G, ordering, size)` - Get topological order

**Algorithm:**
```
1. DFS on entire graph
2. Output vertices in reverse order of finish times
3. If back edge found, graph has cycle (not a DAG)
```

**Result:** If u → v is an arc, u appears before v in ordering

**Time:** O(e)

**Applications:** Task scheduling, course prerequisites, build systems

---

### 8. Strongly Connected Components
**Based on:** Aho Section 6.7

**Purpose:** Find maximal sets of mutually reachable vertices (directed graphs)

**Key Operation:**
- `findSCC(G, components)` - Find all SCCs

**Algorithm:**
```
1. DFS on G, record finish times
2. Create reverse graph G^R (reverse all arcs)
3. DFS on G^R in decreasing finish time order
4. Each tree in second DFS is one SCC
```

**Time:** O(e) - two DFS passes

**Property:** Vertices u and v are in same SCC iff path exists u→v AND v→u

---

### 9. Articulation Points & Biconnectivity
**Based on:** Aho Section 7.4

**Purpose:** Find vertices whose removal disconnects graph

**Key Operation:**
- `findArticulationPoints(G, artPoints)` - Find all articulation points

**Algorithm:**
```
DFS with tracking:
- dfnumber[v] = discovery time
- low[v] = lowest dfnumber reachable from subtree at v

v is articulation point if:
- v is root with > 1 DFS child, OR
- v has child w with low[w] ≥ dfnumber[v]
```

**Time:** O(e)

**Biconnected:** Graph with no articulation points

---

## Algorithm Complexity Summary

| Algorithm | Time (List) | Time (Matrix) | Space | Notes |
|-----------|-------------|---------------|-------|-------|
| **DFS** | O(e) | O(n²) | O(n) | Traversal |
| **BFS** | O(e) | O(n²) | O(n) | Shortest paths (unweighted) |
| **Dijkstra** | O(e log n)* | O(n²) | O(n) | Non-negative weights only |
| **Floyd-Warshall** | O(n³) | O(n³) | O(n²) | All pairs, handles negatives |
| **Prim** | O(n²) | O(n²) | O(n) | MST, good for dense |
| **Kruskal** | O(e log e) | O(e log e) | O(n) | MST, good for sparse |
| **Topological** | O(e) | O(n²) | O(n) | DAGs only |
| **SCC** | O(e) | O(n²) | O(n) | Directed graphs |

*With priority queue

**Key:**
- n = number of vertices
- e = number of edges
- Sparse: e << n²
- Dense: e ≈ n²

---

## Critical Notes from Aho

### 1. Dijkstra Requires Non-Negative Weights
❌ **FAILS with negative weights!**

If you have negative weights, use Floyd-Warshall instead.

### 2. Mark BEFORE Enqueue in BFS
```c
// WRONG ❌
enqueue(Q, w);
mark[w] := VISITED;  // TOO LATE! May enqueue duplicates

// CORRECT ✅
mark[w] := VISITED;  // Mark FIRST
enqueue(Q, w);       // Then enqueue
```

### 3. MST Algorithms Only for Undirected Graphs
Prim and Kruskal work on **undirected graphs only**!

For directed graphs, the problem is different (minimum spanning arborescence).

### 4. Matrix vs List Performance

**Use Matrix when:**
- Graph is dense (e ≈ n²)
- Frequently checking "does edge (u,v) exist?"
- Implementing Floyd-Warshall

**Use List when:**
- Graph is sparse (e << n²)
- Frequently iterating through neighbors
- Implementing DFS, BFS, or most algorithms

### 5. Greedy Algorithms
Not all greedy approaches work! Dijkstra and Kruskal work because of special properties:

- **Dijkstra:** Optimal substructure + non-negative weights
- **Kruskal/Prim:** MST property (safe greedy choice)

---

## Implementation Strategy

### Phase 1: Representations
1. **Adjacency Matrix** - simpler, start here
2. **Adjacency List** - more complex but essential
3. Test both with same operations

### Phase 2: Traversals
4. **DFS** - fundamental, used by many algorithms
5. **BFS** - shortest paths, level-order
6. Compare DFS vs BFS behavior

### Phase 3: Shortest Paths
7. **Dijkstra** - single-source, non-negative
8. **Floyd-Warshall** - all-pairs

### Phase 4: Spanning Trees
9. **Prim** - grow from single vertex
10. **Kruskal** - sort edges, use union-find

### Phase 5: Advanced
11. **Topological Sort** - uses DFS
12. **SCCs** - two DFS passes
13. **Articulation Points** - DFS with low values

---

## Common Patterns

### Graph Traversal Template
```c
// DFS
void dfs(v) {
    mark[v] = VISITED;
    for each neighbor w of v:
        if mark[w] = UNVISITED:
            dfs(w);
}

// BFS
void bfs(source) {
    mark[source] = VISITED;
    enqueue(Q, source);
    while Q not empty:
        v = dequeue(Q);
        for each neighbor w of v:
            if mark[w] = UNVISITED:
                mark[w] = VISITED;  // BEFORE enqueue!
                enqueue(Q, w);
}
```

### Iterating Neighbors
```c
// Matrix
for (int w = 0; w < n; w++) {
    if (G->adjMatrix[v][w] != INFINITY) {
        // w is neighbor of v
    }
}

// List
Edge e = G->adjList[v];
while (e != NULL) {
    Vertex w = e->dest;
    // w is neighbor of v
    e = e->next;
}
```

---

## Testing Your Implementations

Create test graphs:
- Empty graph
- Single vertex
- Single edge
- Disconnected graph
- Complete graph
- Cyclic graph
- DAG
- Tree
- Dense graph
- Sparse graph

Test edge cases:
- Source = destination (Dijkstra)
- No path exists
- Negative weights (Floyd)
- Graph with cycles (topological sort should fail)

---

## Next Steps

1. **Implement main.c** with menu system
2. Start with **adjacency matrix** (simpler)
3. Implement **DFS** (foundation for many algorithms)
4. Move to **adjacency list**
5. Implement algorithms systematically
6. Test each with sample graphs
7. Compare performance of matrix vs list

---

**Happy Graph Exploring!** 📊
