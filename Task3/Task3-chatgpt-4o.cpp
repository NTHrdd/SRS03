#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ifstream in("FileName.txt");

    if (!in.is_open()) {
        cerr << "Ошибка при открытии файла!" << endl;
        return 1;
    }

    int n;
    in >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    // Чтение матрицы смежности
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            in >> graph[i][j];

    in.close();

    int K, L;
    cout << "Введите номер начального города (K): ";
    cin >> K;
    cout << "Введите количество пересадок (L): ";
    cin >> L;

    K--; // Переводим в 0-индексацию

    vector<int> dist(n, -1); // -1 означает, что город недостижим
    queue<int> q;

    dist[K] = 0;
    q.push(K);

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

    vector<int> result;
    for (int i = 0; i < n; ++i) {
        if (dist[i] == L + 1) { // L пересадок => L+1 шагов
            result.push_back(i + 1); // обратно к 1-индексации
        }
    }

    if (result.empty()) {
        cout << -1 << endl;
    } else {
        sort(result.begin(), result.end());
        for (int city : result) {
            cout << city << " ";
        }
        cout << endl;
    }

    return 0;
}