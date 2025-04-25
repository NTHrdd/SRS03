#ifndef GRAPH_BFS_H
#define GRAPH_BFS_H

#include <vector>
#include <string>
#include <iostream>

/**
 * @brief Загружает матрицу смежности из файла.
 *
 * В случае ошибки (не удалось открыть файл, некорректные данные)
 * выводит сообщение в stderr и возвращает пустой вектор.
 *
 * @param filename Имя файла, содержащего матрицу.
 * @param n Ссылка на переменную, в которую будет записано количество городов (устанавливается в 0 при ошибке).
 * @return std::vector<std::vector<int>> Матрица смежности или пустой вектор при ошибке.
 */
std::vector<std::vector<int>> loadAdjacencyMatrix(const std::string& filename, int& n);

/**
 * @brief Выполняет BFS и возвращает вектор кратчайших расстояний от начального города.
 *
 * @param graph Матрица смежности.
 * @param start Индекс начального города (0-индексация).
 * @return std::vector<int> Вектор расстояний до каждого города (-1 если недостижим). Возвращает вектор с -1, если граф пуст или start некорректен.
 */
std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start);

/**
 * @brief Находит города, до которых можно добраться ровно с L пересадками.
 *
 * @param dist Вектор расстояний, полученный из BFS.
 * @param L Количество пересадок (равное расстоянию в невзвешенном графе).
 * @return std::vector<int> Отсортированный список номеров городов (1-индексация).
 */
std::vector<int> findCitiesWithTransfers(const std::vector<int>& dist, int L);

#endif // GRAPH_BFS_H