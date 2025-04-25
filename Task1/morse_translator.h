#ifndef MORSE_TRANSLATOR_H
#define MORSE_TRANSLATOR_H

#include <string>
#include <map>

/**
 * @brief Выполняет перевод строки на азбуку Морзе и выводит результат.
 *
 * Поддерживаются буквы русского алфавита (верхний и нижний регистр), пробелы между словами.
 * Прочие символы игнорируются. Буквы разделяются пробелом, слова - символом '/'.
 *
 * @param message Входное сообщение на русском языке.
 * @param morse_map Карта соответствия русских букв (верхний регистр) кодам Морзе.
 */
void translate_to_morse(const std::wstring& message, const std::map<wchar_t, std::wstring>& morse_map);

#endif