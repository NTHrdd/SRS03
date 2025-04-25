#include "graph_bfs.h"
#include <queue>
#include <fstream>
#include <algorithm>


std::vector<std::vector<int>> loadAdjacencyMatrix(const std::string& filename, int& n) {
    n = 0;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл: " << filename << std::endl;
        return {};
    }

    file >> n;
    if (file.fail() || n <= 0 || n > 1000) {
        std::cerr << "Ошибка: Некорректное количество городов или ошибка чтения n." << std::endl;
        file.close();
        n = 0;
        return {};
    }


    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(file >> matrix[i][j])) {
                std::cerr << "Ошибка: Не удалось прочитать элемент матрицы [" << i << "][" << j << "]." << std::endl;
                file.close();
                n = 0;
                return {};
            }
            if (matrix[i][j] != 0 && matrix[i][j] != 1) {
            std::cerr << "Ошибка: Некорректное значение в матрице [" << i << "][" << j << "]: " << matrix[i][j] << std::endl;
            file.close();
            n = 0;
            return {};
            }
        }
    }
    int dummy = 0;
    if (file >> dummy) {
    std::cerr << "Предупреждение: В файле есть лишние данные после матрицы." << std::endl;
    }

    file.close();
    return matrix;
}

std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    if (n == 0) {
        std::cerr << "Предупреждение: Попытка запуска BFS на пустом графе." << std::endl;
        return {};
    }
    if (start < 0 || start >= n) {
        std::cerr << "Ошибка: Некорректный индекс начального узла для BFS: " << start << ". Допустимый диапазон [0.." << n-1 << "]." << std::endl;
        return std::vector<int>(n, -1);
    }

    std::vector<int> dist(n, -1);
    std::queue<int> q(std::deque<int>{});

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int next = 0; next < n; ++next) {
            if (graph[current][next] == 1 && dist[next] == -1) {
                dist[next] = dist[current] + 1;
                q.push(next);
            }
        }
    }

    return dist;
}

std::vector<int> findCitiesWithTransfers(const std::vector<int>& dist, int L) {
    std::vector<int> result = {};
    if (L < 0) {
        std::cerr << "Предупреждение: Запрошено отрицательное количество пересадок (" << L << ")." << std::endl;
        return result;
    }
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == L) {
            result.push_back(i + 1);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}