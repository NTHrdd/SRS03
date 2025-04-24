#include <iostream>
#include <string>
#include <map>
#include <locale>
#include <cwctype> // для towupper

int main() {
    // Устанавливаем локаль для поддержки русского языка в консоли
    std::setlocale(LC_ALL, "");

    // Карта Морзе: буква (в любом регистре) -> код Морзе
    std::map<wchar_t, std::wstring> morse = {
            {L'А', L".-"},    {L'Б', L"-..."},  {L'В', L".--"},   {L'Г', L"--."},
            {L'Д', L"-.."},   {L'Е', L"."},     {L'Ж', L"...-"},  {L'З', L"--.."},
            {L'И', L".."},    {L'Й', L".---"},  {L'К', L"-.-"},   {L'Л', L".-.."},
            {L'М', L"--"},    {L'Н', L"-."},    {L'О', L"---"},   {L'П', L".--."},
            {L'Р', L".-."},   {L'С', L"..."},   {L'Т', L"-"},     {L'У', L"..-"},
            {L'Ф', L"..-."},  {L'Х', L"...."},  {L'Ц', L"-.-."},  {L'Ч', L"---."},
            {L'Ш', L"----"},  {L'Щ', L"--.-"},  {L'Ъ', L".--.-."},{L'Ы', L"-.--"},
            {L'Ь', L"-..-"},  {L'Э', L"..-.."}, {L'Ю', L"..--"},  {L'Я', L".-."}
    };

    std::wcout << L"Введите сообщение на русском языке: ";
    std::wstring message;
    std::getline(std::wcin, message);

    std::wcout << L"Сообщение в азбуке Морзе:\n";

    for (wchar_t ch : message) {
        if (ch == L' ') {
            // Разделение слов — символ "/"
            std::wcout << L"/ ";
        } else {
            // Преобразуем к верхнему регистру
            wchar_t upperCh = std::towupper(ch);

            if (morse.count(upperCh)) {
                std::wcout << morse[upperCh] << L" ";
            }
            // Прочие символы (цифры, знаки препинания) — игнорируем
        }
    }

    std::wcout << std::endl;
    return 0;
}