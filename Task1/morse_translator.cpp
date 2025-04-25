#include "morse_translator.h"
#include <iostream>

void translate_to_morse(const std::wstring& message, const std::map<wchar_t, std::wstring>& morse_map) {
    for (wchar_t ch : message) {
        if (ch == L' ') {
            std::wcout << L"/ ";
        } else {
            wchar_t upperCh = std::towupper(ch);
            std::map<wchar_t, std::wstring>::const_iterator it = morse_map.find(upperCh);
            if (it != morse_map.end()) {
                std::wcout << it->second << L" ";
            }
        }
    }
}