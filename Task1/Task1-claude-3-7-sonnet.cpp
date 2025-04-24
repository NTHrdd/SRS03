#include <iostream>
#include <string>
#include <map>
#include <locale>
#include <codecvt>

int main() {
    // Установка русской локали
    setlocale(LC_ALL, "Russian");

    // Создаем словарь для азбуки Морзе
    std::map<wchar_t, std::string> morseCode = {
            {L'а', ".-"}, {L'б', "-..."}, {L'в', ".--"}, {L'г', "--."},
            {L'д', "-.."}, {L'е', "."}, {L'ж', "...-"}, {L'з', "--.."},
            {L'и', ".."}, {L'й', ".---"}, {L'к', "-.-"}, {L'л', ".-.."},
            {L'м', "--"}, {L'н', "-."}, {L'о', "---"}, {L'п', ".--."},
            {L'р', ".-."}, {L'с', "..."}, {L'т', "-"}, {L'у', "..-"},
            {L'ф', "..-."}, {L'х', "...."}, {L'ц', "-.-."}, {L'ч', "---."},
            {L'ш', "----"}, {L'щ', "--.-"}, {L'ъ', ".--.-."}, {L'ы', "-.--"},
            {L'ь', "-..-"}, {L'э', "..-.."}, {L'ю', "..--"}, {L'я', ".-."},
            {L' ', " "}  // Пробел между словами
    };

    std::wstring message;
    std::wcout << L"Введите сообщение для перевода в азбуку Морзе: ";
    std::getline(std::wcin, message);

    std::wstring result;
    for (size_t i = 0; i < message.length(); ++i) {
        wchar_t c = std::towlower(message[i]);

        // Проверяем, есть ли символ в нашем словаре
        if (morseCode.find(c) != morseCode.end()) {
            result += std::wstring(morseCode[c].begin(), morseCode[c].end());

            // Добавляем пробел между символами
            if (i < message.length() - 1 && c != L' ') {
                result += L" ";
            }
        }
    }

    std::wcout << L"Сообщение в азбуке Морзе: " << result << std::endl;

    return 0;
}