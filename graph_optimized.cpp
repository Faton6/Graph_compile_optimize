#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <omp.h>

struct Node {
    int id;
    std::vector<int> neighbors;
};

void bfs(const std::vector<Node>& graph, int start_node) {
    size_t n = graph.size();
    std::vector<int> visited(n, 0);
    std::queue<int> q;

    visited[start_node] = 1;
    q.push(start_node);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        const auto& neighbors = graph[current].neighbors;
        size_t neighbor_count = neighbors.size();

        std::vector<int> new_nodes;
        new_nodes.reserve(neighbor_count);

        #pragma omp simd
        for (size_t i = 0; i < neighbor_count; ++i) {
            int neighbor = neighbors[i];
            if (visited[neighbor] == 0) {
                visited[neighbor] = 1;
                new_nodes.push_back(neighbor); 
            }
        }

        std::vector<int> temp_new_nodes(neighbor_count);
        size_t new_count = 0;

        #pragma omp simd
        for (size_t i = 0; i < neighbor_count; ++i) {
            int neighbor = neighbors[i];
            if (visited[neighbor] == 0) {
                visited[neighbor] = 1;
                temp_new_nodes[i] = neighbor;
            } else {
                temp_new_nodes[i] = -1;
            }
        }

        for (size_t i = 0; i < neighbor_count; ++i) {
            if (temp_new_nodes[i] != -1) {
                q.push(temp_new_nodes[i]);
            }
        }
    }
}

int main() {
    int num_nodes = 20000000;
    std::vector<Node> graph(num_nodes);

    for (int i = 0; i < num_nodes; ++i) {
        graph[i].id = i;
        if (i + 1 < num_nodes) {
            graph[i].neighbors.push_back(i + 1);
        }
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    bfs(graph, 0);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Время выполнения: " << duration.count() << " мс" << std::endl;

    return 0;
}