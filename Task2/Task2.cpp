#include "expression_tree.h"
#include <fstream>

/**
 * @brief Точка входа в программу. Читает выражение из файла,
 * строит дерево, выводит его, упрощает, выводит упрощенное дерево.
 * Ошибки выводятся в stderr.
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return 0 при успехе, 1 при ошибке.
 */
int main(int argc, char* argv[]) {
    std::string filename = "filename.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл: " << filename << std::endl;
        return 1;
    }

    std::string expression = "";
    if (!getline(file, expression)) {
        std::cerr << "Ошибка: Не удалось прочитать строку из файла: " << filename << std::endl;
        file.close();
        return 1;
    }
    file.close();

    if (expression.empty()) {
        std::cerr << "Ошибка: Файл пуст или содержит пустую строку." << std::endl;
        return 1;
    }

    std::cout << "Прочитано выражение: " << expression << std::endl;

    Node* root = nullptr;
    Node* simplifiedRoot = nullptr;

    std::vector<std::string> tokens = tokenize(expression);
    if (tokens.empty()) {
        std::cerr << "Ошибка: Выражение не содержит токенов после разделения." << std::endl;
        return 1;
    }

    int index = 0;
    root = buildTree(tokens, index);

    if (!root) {
        std::cerr << "Ошибка: Не удалось построить дерево выражений." << std::endl;
        return 1;
    }

    if (index < tokens.size()) {
        std::cerr << "Ошибка: Лишние токены в конце выражения, начиная с: " << tokens[index] << std::endl;
        delete root;
        return 1;
    }
    std::cout << "\nИсходное дерево выражения:" << std::endl;
    printTree(root);
    simplifiedRoot = simplify(root);
    std::cout << "\nУпрощенное дерево выражения:" << std::endl;
    printTree(simplifiedRoot);
    std::cout << "\nАдрес корня упрощенного дерева: " << simplifiedRoot << std::endl;
    delete simplifiedRoot;;
    return 0;
}