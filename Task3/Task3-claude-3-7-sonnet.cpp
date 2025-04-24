#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main() {
    int K, L;

    // Ввод имени файла и параметров K и L
    cin >> K >> L;

    ifstream fin("FileName.txt");
    if (!fin) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }

    int n;
    fin >> n;

    // Считываем матрицу смежности
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> matrix[i][j];
        }
    }

    fin.close();

    // Корректируем K, так как нумерация в задаче начинается с 1
    K--;

    // Массив для хранения расстояний до каждого города
    vector<int> distances(n, -1);
    queue<int> q;

    // Начинаем с города K
    q.push(K);
    distances[K] = 0;

    // BFS
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int next = 0; next < n; next++) {
            if (matrix[current][next] == 1 && distances[next] == -1) {
                distances[next] = distances[current] + 1;
                q.push(next);
            }
        }
    }

    // Находим города, до которых расстояние равно L
    set<int> result;
    for (int i = 0; i < n; i++) {
        if (distances[i] == L) {
            // Возвращаем к нумерации с 1
            result.insert(i + 1);
        }
    }

    // Выводим результат
    if (result.empty()) {
        cout << -1 << endl;
    } else {
        for (int city : result) {
            cout << city << " ";
        }
        cout << endl;
    }

    return 0;
}