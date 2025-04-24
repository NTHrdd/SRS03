#include <iostream>
#include <map>
#include <string>
#include <locale>
#include <codecvt>

int main() {
    // Устанавливаем русскую локаль

    // Используем wstring для поддержки Юникода
    std::wstring message;

    // Словарь азбуки Морзе для русского алфавита
    std::map<wchar_t, std::wstring> morse = {
            {L'А', L"·−"},   {L'Б', L"−···"}, {L'В', L"·−−"},  {L'Г', L"−−·"},
            {L'Д', L"−··"},  {L'Е', L"·"},    {L'Ж', L"···−"}, {L'З', L"−−··"},
            {L'И', L"··"},   {L'Й', L"·−−−"}, {L'К', L"−·−"},  {L'Л', L"·−··"},
            {L'М', L"−−"},   {L'Н', L"−·"},   {L'О', L"−−−"},  {L'П', L"·−−·"},
            {L'Р', L"·−·"},  {L'С', L"···"},  {L'Т', L"−"},    {L'У', L"··−"},
            {L'Ф', L"··−·"}, {L'Х', L"····"}, {L'Ц', L"−·−·"}, {L'Ч', L"−−−·"},
            {L'Ш', L"−−−−"}, {L'Щ', L"−−·−"}, {L'Ъ', L"·−−·−·"},{L'Ы', L"−·−−"},
            {L'Ь', L"−··−"}, {L'Э', L"··−··"},{L'Ю', L"··−−"}, {L'Я', L"·−·"}
    };

    std::cout << L"Введите сообщение на русском: ";
    std::getline(std::wcin, message);

    std::wcout << L"Сообщение в азбуке Морзе:\n";

    for (wchar_t ch : message) {
        // Преобразуем к верхнему регистру
        ch = std::towupper(ch);

        if (ch == L' ') {
            std::wcout << L" / "; // Разделитель слов
        } else if (morse.count(ch)) {
            std::wcout << morse[ch] << L" ";
        } else {
            // Пропускаем символы, которых нет в словаре
        }
    }

    std::wcout << std::endl;
    return 0;
}