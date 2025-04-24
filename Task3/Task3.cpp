#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

/**
 * @brief Загружает матрицу смежности из файла.
 *
 * @param filename Имя файла, содержащего матрицу.
 * @param n Ссылка на переменную, в которую будет записано количество городов.
 * @return std::vector<std::vector<int>> Матрица смежности.
 */
std::vector<std::vector<int>> loadAdjacencyMatrix(const std::string& filename, int& n) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл.");
    }

    file >> n;
    if (n <= 0 || n > 25) {
        throw std::invalid_argument("Некорректное количество городов.");
    }

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            file >> matrix[i][j];

    file.close();
    return matrix;
}

/**
 * @brief Выполняет BFS и возвращает вектор кратчайших расстояний от начального города.
 *
 * @param graph Матрица смежности.
 * @param start Индекс начального города (0-индексация).
 * @return std::vector<int> Вектор расстояний до каждого города.
 */
std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<int> dist(n, -1);
    std::queue<int> q;

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

/**
 * @brief Находит города, до которых можно добраться ровно с L пересадками.
 *
 * @param dist Вектор расстояний, полученный из BFS.
 * @param L Количество пересадок.
 * @return std::vector<int> Список номеров городов (1-индексация).
 */
std::vector<int> findCitiesWithTransfers(const std::vector<int>& dist, int L) {
    std::vector<int> result;
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == L) {
            result.push_back(i + 1);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

/**
 * @brief Точка входа в программу.
 *
 * Считывает данные, запускает BFS, выводит города, достижимые за L пересадок.
 *
 * @return int Код завершения программы.
 */
int main() {
    try {
        int n;
        std::vector<std::vector<int>> graph = loadAdjacencyMatrix("FileName.txt", n);

        int K, L;
        std::cout << "Введите номер начального города (1-" << n << "): ";
        std::cin >> K;
        std::cout << "Введите количество пересадок: ";
        std::cin >> L;

        if (K < 1 || K > n || L < 0) {
            std::cerr << "Некорректный ввод." << std::endl;
            return 1;
        }

        int start = K - 1;
        std::vector<int> distances = bfs(graph, start);
        std::vector<int> cities = findCitiesWithTransfers(distances, L);

        if (cities.empty()) {
            std::cout << -1 << std::endl;
        } else {
            for (size_t i = 0; i < cities.size(); ++i) {
                std::cout << cities[i] << (i + 1 == cities.size() ? '\n' : ' ');
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}