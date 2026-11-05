# Источники и состав командного справочника

Зафиксированы версии:

- AlgoTemplates: 09b74d6f488ff7fa1b37280d478eaf8a1eb699d5.
- Andrew-A-13/Templates: ced8a147a0007d985ef80748e46e939a51ce64b6.
- База: KACTL, сохранены авторские заголовки исходных файлов.

Ссылки ниже указывают на просмотренные исходники. Это не массовое копирование всего репозитория: решения задач выделены в структуры, интерфейсы приведены к командному стилю. Лицензии исходников не переобозначены как CC0.

## Выбор реализаций

| Запрос | В PDF | Решение |
|---|---|---|
| Модульное FFT | ModularFFT.h | Andrew: NTT по модулю 998244353; убраны inverse series и таблица альтернативных модулей. Пустые/нулевые полиномы и signed int поддерживаются. |
| Отжиг | SimulatedAnnealing.h | Andrew: общий отжиг перестановки вместо отдельной задачи про ферзей; сохраняется лучший результат. |
| ДО / lazy / persistent | SegmentTree.h, LazySegmentTree.h, PersistentSegmentTree.h | Два обычных KACTL и новый персистентный point-add/range-sum. |
| ДД | Treap.h, TreapSet.h | Неявный KACTL и отдельный ordered multiset с дубликатами, kth и rank. |
| Centroid/HLD/Mo | CentroidDecomposition.h, HLD.h, MoQueries.h | Компактный centroid, HLD и Mo из KACTL. |
| Link-Cut | LinkCutTree.h | KACTL: link/cut/connectivity. Агрегаты путей нужно дописывать; Andrew-версия не перенесена как готовая сумма по пути. |
| Topsort / Floyd | TopoSort.h, FloydWarshall.h | KACTL: обнаружение циклов и настоящие веса; присланный Floyd ставил вес 1. |
| Kuhn/Dinic/MCMF | Kuhn.h, TeamDinic.h, TeamMinCostFlow.h | Адаптация Andrew; явные ll и обратные рёбра. MCMF без отрицательных циклов, с проверкой достижимости. |
| Суффиксный массив | TeamSuffixArray.h | Andrew: удвоение + counting sort, LCP; пустые строки и произвольные байты. |
| Суффиксный автомат | SuffixAutomaton.h | heesooyaam: root=1, traverser, число вхождений, LCS. Повторный подсчёт и add после подсчёта исправлены. Обобщённый SAM не включён. |
| Хешер | TeamHash.h | heesooyaam: C++20 array NTTP, обе ориентации; сохранены 1-based inclusive запросы. Добавлено сравнение длин. |
| Дерево окружностей | CircleTree.h | heesooyaam: отдельная структура без DP задачи; parent/children/roots и объяснение. |
| Математика | FastMint.h, FastCombinatorics.h, FastGcdLcm.h, FactorizationSieve.h, DivisorsSieve.h | Все различные алгоритмы из Math; только быстрый Montgomery mint. |
| ordered_set/map/multiset | OrderStatisticTree.h | GNU PBDS, примеры методов, member swap, пары с уникальным id. |
| std::hash для vector | VectorHash.h | Отдельный hasher для unordered_map вместо специализации std::hash стандартного типа. |
| binpow | ModPow.h | Та же схема бинарного возведения; имя modpow сохранено для зависимостей KACTL. |
| Прагмы | various/pragmas.tex | Codeforces + документация GCC, подробнее doc/pragmas.md. |

## Сокращения печатной версии

По выбору команды из PDF исключены двумерные префиксные суммы,
Берлекэмп — Мэсси и вычисление члена линейной рекурренты, hill climbing,
дискретный поиск экстремума, LIS, KD-tree и триангуляция Делоне.
Золотое сечение оставлено в разделе тернарного поиска (Various);
его заголовок перенесён в content/various/GoldenSectionSearch.h.
Из печати также исключены Push-relabel и глобальный разрез Стоера — Вагнера.
Гомори — Ху переведён на TeamDinic.h; входные неориентированные рёбра
добавляются в обоих направлениях, сторона разреза берётся из последнего BFS.
Остальные исключённые исходники сохранены в репозитории.

## Исправления при извлечении

- FastGcdLcm: не вызывается ctz(0), используется 64-битный ctz; lcm(0,0)=0 и деление до умножения.
- DivisorsSieve: корректные границы по числам, без неработающего копирующего конструктора view и бесконечной печати UNLUCK; память выделяется по действительному числу делителей.
- FactorizationSieve: список простых динамический, без оценочного фиксированного лимита; произведение проверяется делением до умножения.
- FastMint: по умолчанию 998244353 вместо 998224353, inverse проверяет обратимость. Факториалы вычисляют обратные факториалы одной инверсией.
- FFT и потоки: удалена скрытая зависимость от define int long long.
- Суффиксный массив: отдельный нулевой sentinel посредством перенумерации байтов; вход не мутируется; LCP пустой строки не пытается создать vector(-1).
- Хеширование массива работает по остаткам: значения, отличающиеся на общий модуль, могут давать одинаковые хеши. Вероятностную природу хеша не скрываем.

## Просмотренные версии

- [heesooyaam/AlgoTemplates: Math/DivisorsSieve.cpp](https://github.com/heesooyaam/AlgoTemplates/blob/09b74d6f488ff7fa1b37280d478eaf8a1eb699d5/Math/DivisorsSieve.cpp)
- [heesooyaam/AlgoTemplates: Math/FactorizationSieve.cpp](https://github.com/heesooyaam/AlgoTemplates/blob/09b74d6f488ff7fa1b37280d478eaf8a1eb699d5/Math/FactorizationSieve.cpp)
- [heesooyaam/AlgoTemplates: Math/FastGcdLcm.cpp](https://github.com/heesooyaam/AlgoTemplates/blob/09b74d6f488ff7fa1b37280d478eaf8a1eb699d5/Math/FastGcdLcm.cpp)
- [heesooyaam/AlgoTemplates: Math/fast_mint.cpp](https://github.com/heesooyaam/AlgoTemplates/blob/09b74d6f488ff7fa1b37280d478eaf8a1eb699d5/Math/fast_mint.cpp)
- [heesooyaam/AlgoTemplates: Other/circles_to_tree_scanline.cpp](https://github.com/heesooyaam/AlgoTemplates/blob/09b74d6f488ff7fa1b37280d478eaf8a1eb699d5/Other/circles_to_tree_scanline.cpp)
- [heesooyaam/AlgoTemplates: Strings/hash.cpp](https://github.com/heesooyaam/AlgoTemplates/blob/09b74d6f488ff7fa1b37280d478eaf8a1eb699d5/Strings/hash.cpp)
- [heesooyaam/AlgoTemplates: Strings/suffix_structures/generalized_suffix_automaton.cpp](https://github.com/heesooyaam/AlgoTemplates/blob/09b74d6f488ff7fa1b37280d478eaf8a1eb699d5/Strings/suffix_structures/generalized_suffix_automaton.cpp)
- [heesooyaam/AlgoTemplates: Strings/suffix_structures/suffix_automaton.cpp](https://github.com/heesooyaam/AlgoTemplates/blob/09b74d6f488ff7fa1b37280d478eaf8a1eb699d5/Strings/suffix_structures/suffix_automaton.cpp)
- [Andrew-A-13/Templates: FFT/modular](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/FFT/modular)
- [Andrew-A-13/Templates: Garbage/Centroid1](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/Garbage/Centroid1)
- [Andrew-A-13/Templates: Garbage/HLD1](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/Garbage/HLD1)
- [Andrew-A-13/Templates: Garbage/MO1](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/Garbage/MO1)
- [Andrew-A-13/Templates: Garbage/Отжиг](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/Garbage/%D0%9E%D1%82%D0%B6%D0%B8%D0%B3)
- [Andrew-A-13/Templates: Ordered_set](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/Ordered_set)
- [Andrew-A-13/Templates: std::hash](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/std::hash)
- [Andrew-A-13/Templates: Графы/Link cut/Basic Link cut](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%93%D1%80%D0%B0%D1%84%D1%8B/Link%20cut/Basic%20Link%20cut)
- [Andrew-A-13/Templates: Графы/topsort](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%93%D1%80%D0%B0%D1%84%D1%8B/topsort)
- [Andrew-A-13/Templates: Графы/Флойд-Уоршелл](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%93%D1%80%D0%B0%D1%84%D1%8B/%D0%A4%D0%BB%D0%BE%D0%B9%D0%B4-%D0%A3%D0%BE%D1%80%D1%88%D0%B5%D0%BB%D0%BB)
- [Andrew-A-13/Templates: Деревья и прочее/Treap/Better Treap](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%94%D0%B5%D1%80%D0%B5%D0%B2%D1%8C%D1%8F%20%D0%B8%20%D0%BF%D1%80%D0%BE%D1%87%D0%B5%D0%B5/Treap/Better%20Treap)
- [Andrew-A-13/Templates: Потоки/Kuhn](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%9F%D0%BE%D1%82%D0%BE%D0%BA%D0%B8/Kuhn)
- [Andrew-A-13/Templates: Потоки/MinCostMaxFlow](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%9F%D0%BE%D1%82%D0%BE%D0%BA%D0%B8/MinCostMaxFlow)
- [Andrew-A-13/Templates: Потоки/dinic](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%9F%D0%BE%D1%82%D0%BE%D0%BA%D0%B8/dinic)
- [Andrew-A-13/Templates: Строковые алгоритмы/Суффиксный массив](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%A1%D1%82%D1%80%D0%BE%D0%BA%D0%BE%D0%B2%D1%8B%D0%B5%20%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D1%8B/%D0%A1%D1%83%D1%84%D1%84%D0%B8%D0%BA%D1%81%D0%BD%D1%8B%D0%B9%20%D0%BC%D0%B0%D1%81%D1%81%D0%B8%D0%B2)
- [Andrew-A-13/Templates: Теория чисел/бинарное возведение в степень](https://github.com/Andrew-A-13/Templates/blob/ced8a147a0007d985ef80748e46e939a51ce64b6/%D0%A2%D0%B5%D0%BE%D1%80%D0%B8%D1%8F%20%D1%87%D0%B8%D1%81%D0%B5%D0%BB/%D0%B1%D0%B8%D0%BD%D0%B0%D1%80%D0%BD%D0%BE%D0%B5%20%D0%B2%D0%BE%D0%B7%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%B2%20%D1%81%D1%82%D0%B5%D0%BF%D0%B5%D0%BD%D1%8C)

