#include "graph_bfs.h"

/**
 * @brief Точка входа в программу.
 *
 * Считывает данные из файла "FileName.txt", запрашивает у пользователя
 * начальный город и количество пересадок, запускает BFS и выводит
 * города, достижимые ровно за L пересадок. Сообщения об ошибках
 * выводятся в stderr.
 *
 * @return int 0 при успехе, 1 при ошибке.
 */
int main() {
    std::string filename = "FileName.txt";
    int size_graph = 0;
    std::vector<std::vector<int>> graph = loadAdjacencyMatrix(filename, size_graph);

    if (graph.empty() || size_graph == 0) {
        std::cerr << "Не удалось загрузить граф из файла. Выполнение прекращено." << std::endl;
        return 1;
    }

    int start_city = 0;
    int num_transfer = -1;

    std::cout << "Введите номер начального города (1-" << size_graph << "): ";
    if (!(std::cin >> start_city)) {
        std::cerr << "Ошибка ввода номера начального города." << std::endl;
        return 1;
    }

    std::cout << "Введите количество пересадок (>= 0): ";
    if (!(std::cin >> num_transfer)) {
        std::cerr << "Ошибка ввода количества пересадок." << std::endl;
        return 1;
    }

    if (start_city < 1 || start_city > size_graph || num_transfer < 0) {
        std::cerr << "Некорректный ввод: Город K=" << start_city << " (должен быть 1.." << size_graph << "), Пересадки L=" << num_transfer << " (должны быть >= 0)." << std::endl;
        return 1;
    }

    int start_node = start_city - 1;
    std::vector<int> distances = bfs(graph, start_node);

    if (distances.empty() || distances.size() != size_graph) {
    std::cerr << "Ошибка выполнения BFS." << std::endl;
    return 1;
    }

    std::vector<int> cities = findCitiesWithTransfers(distances, num_transfer);

    if (cities.empty()) {
        std::cout << -1 << std::endl;
    } else {
        for (size_t i = 0; i < cities.size(); ++i) {
            std::cout << cities[i] << (i + 1 == cities.size() ? '\n' : ' ');
        }
    }

    return 0;
}