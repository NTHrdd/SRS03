#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Узел дерева выражения.
 */
struct Node {
    int value;
    Node* left;
    Node* right;

    /**
     * @brief Конструктор узла.
     * @param val Значение (операнд или код операции)
     */
    Node(int val) : value(val), left(nullptr), right(nullptr) {}

    /**
     * @brief Деструктор, рекурсивно удаляет поддеревья.
     */
    ~Node() {
        delete left;
        delete right;
    }

    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
};

/**
 * @brief Проверяет, является ли токен оператором.
 * @param token Строка токена
 * @return true если токен является оператором
 */
bool isOperator(const std::string& token);

/**
 * @brief Преобразует строку оператора в числовой код.
 * @param token Строка токена
 * @return Целочисленный код операции. В случае ошибки выводит сообщение в stderr и возвращает 0.
 */
int operatorToCode(const std::string& token);

/**
 * @brief Проверяет, является ли токен однозначным операндом.
 * @param token Строка токена
 * @return true если токен является цифрой
 */
bool isOperand(const std::string& token);

/**
 * @brief Преобразует строку-цифру в число.
 * @param token Строка токена
 * @return Целое число. Ошибки формата обрабатываются std::stoi, может выбросить исключение, если не цифра.
 */
int operandToValue(const std::string& token);

/**
 * @brief Рекурсивно строит дерево выражения из токенов.
 * @param tokens Вектор токенов
 * @param index Текущий индекс вектора (передается по ссылке и изменяется)
 * @return Указатель на корень поддерева. При ошибках парсинга (недостаточно токенов, неверный токен) выводит сообщение в stderr и возвращает nullptr.
 */
Node* buildTree(const std::vector<std::string>& tokens, int& index);

/**
 * @brief Рекурсивно вычисляет значение поддерева.
 * @param node Указатель на корень поддерева.
 * @param result Ссылка для возврата результата вычисления.
 * @return true если вычисление успешно, false в случае ошибки (деление на ноль, неизвестная операция, null узел). При ошибке выводит сообщение в stderr.
 */
bool evaluate(Node* node, int& result);

/**
 * @brief Упрощает дерево, заменяя + и - на вычисленные значения.
 * @param node Указатель на корень поддерева
 * @return Указатель на упрощённое поддерево (может быть новым узлом). Если вычисление узла невозможно, узел не упрощается.
 */
Node* simplify(Node* node);

/**
 * @brief Выводит дерево в консоль (разворот вправо).
 * @param root Указатель на корень дерева
 * @param depth Глубина текущего уровня
 */
void printTree(Node* root, int depth = 0);

/**
 * @brief Делит строку на токены по пробелам.
 * @param str Исходная строка
 * @return Вектор токенов
 */
std::vector<std::string> tokenize(const std::string& str);

#endif // EXPRESSION_TREE_H