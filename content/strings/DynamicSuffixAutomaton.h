/**
 * Author: cp_trd
 * Description: Динамика из статики: мультимножество строк a..z. add(s) добавляет строку, count(p) — сумма вхождений непустого p с перекрытиями. Блок k хранит $2^k$ строк и статический автомат. Добавление как в двоичном счётчике: объединяем равные блоки, перестраиваем автомат. Ответы блоков суммируем. Разделитель \{ исключает совпадения через границы строк; порядок строк неважен. Допустимы пустые строки и дубликаты. Это набор строк, не дописывание к одной строке. Удаление: второй набор для удалённых копий, ответ — разность; удалять лишь существующую копию.
 * Time: N добавлений общей длины L: O((L+N)\log(N+1)) суммарно; запрос O(|p|\log(N+1)), память O(L+N) при фиксированном алфавите. Одна вставка может перестроить всё: это не O(|s|\log N) на каждую вставку.
 * Status: Random inserts/deletes and overlapping occurrences compared with direct search.
 */
#pragma once
#include "SuffixAutomaton.h"
struct dynamic_suffix_automaton {
    struct block {
        string text;
        suffix_automaton sa;
        explicit block(string s) : text(move(s)), sa(text) {}
    };
    vector<optional<block>> blocks;
    void add(string_view s) {
        for (char c : s) {
            assert('a' <= c && c <= 'z');
        }
        string text(s);
        text += '{'; // отдельный 27-й символ в SuffixAutomaton
        size_t k = 0;
        while (k < blocks.size() && blocks[k]) {
            text += blocks[k]->text;
            blocks[k].reset();
            ++k;
        }
        if (k == blocks.size()) {
            blocks.eb();
        }
        blocks[k].emplace(move(text));
    }
    ll count(string_view pattern) const {
        assert(!pattern.empty());
        for (char c : pattern) {
            assert('a' <= c && c <= 'z');
        }
        ll answer = 0;
        for (const auto &part : blocks) {
            if (!part) {
                continue;
            }
            int v = suffix_automaton::root;
            for (char c : pattern) {
                v = part->sa.st[v].get_next(c);
                if (v == 0) {
                    break;
                }
            }
            answer += part->sa.st[v].occ;
        }
        return answer;
    }
};
// Перекрытия: в "ababa" образец "aba" встречается дважды.
void dynamic_sam_example() {
    dynamic_suffix_automaton added, removed;
    added.add("ababa");
    added.add("aba");
    assert(added.count("aba") == 3);
    removed.add("aba"); // такой экземпляр действительно есть
    ll answer = added.count("aba") - removed.count("aba");
    assert(answer == 2);
    // added.add("ab"); added.add("cd") не создают вхождение "bc".
}
