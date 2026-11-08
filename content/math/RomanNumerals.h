/**
 * Author: cp_trd team
 * License: CC0
 * Description: Римские числа в канонической записи, диапазон 1..3999.
 * to возвращает пустую строку вне диапазона; from возвращает -1
 * для неверной записи (включая пустую строку, строчные буквы и пробелы).
 * I,V,X,L,C,D,M = 1,5,10,50,100,500,1000.
 * Вычитание только в IV,IX,XL,XC,CD,CM; 49 = XLIX, не IL.
 * I,X,C,M подряд не более трёх; V,L,D не повторяются.
 * Ноль, отрицательные и числа >=4000 требуют отдельного соглашения.
 * Для сравнения и арифметики сначала перевести в int:
 * лексикографический порядок строк не совпадает с числовым.
 * Usage: to_roman(1994); // "MCMXCIV"
 *  from_roman("XLIX"); // 49; "IC", "IIII", "VX" -> -1
 * Time: O(|s|) на обработку строки; при данном диапазоне O(1).
 */
#pragma once

string to_roman(int x) {
    if (x < 1 || x > 3999) {
        return "";
    }
    const pair<int, string_view> parts[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"},  {90, "XC"},  {50, "L"},  {40, "XL"},
        {10, "X"},   {9, "IX"},   {5, "V"},   {4, "IV"},
        {1, "I"}};
    string result;
    for (auto [value, text] : parts) {
        while (x >= value) {
            result += text;
            x -= value;
        }
    }
    return result;
}

int from_roman(string_view s) {
    if (s.empty() || s.size() > 15) {
        return -1;
    }
    const string_view symbols = "IVXLCDM";
    const int values[] = {1, 5, 10, 50, 100, 500, 1000};
    int result = 0, right = 0;
    for (int i = int(s.size()) - 1; i >= 0; --i) {
        auto pos = symbols.find(s[i]);
        if (pos == string_view::npos) {
            return -1;
        }
        int value = values[pos];
        result += value < right ? -value : value;
        right = value;
    }
    // Одного вычитания недостаточно: проверяем каноничность.
    return to_roman(result) == s ? result : -1;
}
