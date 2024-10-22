#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

struct Node {
    int id;
    std::vector<int> neighbors;
};

void bfs(const std::vector<Node>& graph, int start_node) {
    size_t n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    visited[start_node] = true;
    q.push(start_node);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        const auto& neighbors = graph[current].neighbors;
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int neighbor = neighbors[i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
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