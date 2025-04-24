#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <string>

int main() {

    std::ifstream file("FileName.txt");

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << std::endl;
        return 1;
    }

    int n; // Количество городов
    file >> n;

    if (n <= 0 || n > 25) {
        std::cerr << "Некорректное количество городов: " << n << std::endl;
        return 1;
    }

    // Матрица смежности
    std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> adj_matrix[i][j];
        }
    }

    file.close();

    int K; // Начальный город (1-индексированный)
    int L; // Требуемое количество пересадок

    // Читаем K и L из стандартного ввода
    std::cout << "Введите номер начального города (1-" << n << "): ";
    std::cin >> K;
    std::cout << "Введите требуемое количество пересадок: ";
    std::cin >> L;

    // Проверка корректности K
    if (K < 1 || K > n) {
        std::cerr << "Некорректный номер начального города K: " << K << std::endl;
        return 1;
    }

    // Преобразуем K в 0-индексированный формат
    int start_node = K - 1;

    // Используем BFS для поиска кратчайших путей (в терминах количества пересадок)
    std::vector<int> dist(n, -1); // dist[i] хранит кратчайшее количество пересадок до города i
    std::queue<int> q;

    // Начинаем с города K
    dist[start_node] = 0;
    q.push(start_node);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Если мы уже достигли или превысили требуемое количество пересадок L
        // на кратчайшем пути до текущего города, дальнейшие пути через него
        // будут иметь больше пересадок, чем L, или не будут кратчайшими
        // до новых городов, если те уже посещены с меньшим расстоянием.
        // Однако, нам нужно исследовать все достижимые города, чтобы найти
        // те, до которых кратчайший путь РАВЕН L.
        // Поэтому BFS должен пройти до конца.

        for (int v = 0; v < n; ++v) {
            // Если есть перелет из u в v и город v еще не посещен (dist[v] == -1)
            if (adj_matrix[u][v] == 1 && dist[v] == -1) {
                dist[v] = dist[u] + 1; // Кратчайшее расстояние до v на 1 больше, чем до u
                q.push(v);
            }
        }
    }

    // Собираем города, до которых кратчайшее расстояние равно L
    std::vector<int> result_cities;
    for (int i = 0; i < n; ++i) {
        // Если кратчайшее расстояние до города i равно L
        if (dist[i] == L) {
            // Добавляем город i+1 (1-индексированный) в результат
            result_cities.push_back(i + 1);
        }
    }

    // Сортируем города в порядке возрастания
    std::sort(result_cities.begin(), result_cities.end());

    // Выводим результат
    if (result_cities.empty()) {
        std::cout << -1 << std::endl;
    } else {
        for (size_t i = 0; i < result_cities.size(); ++i) {
            std::cout << result_cities[i] << (i == result_cities.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

    return 0;
}