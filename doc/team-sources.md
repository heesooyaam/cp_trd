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


## Второй пересмотр состава

Из печати исключены Simplex, SimulatedAnnealing, FastInput, 3dHull, Point3D,
PolyhedronVolume и обычный SegmentTree. Исходники оставлены для upstream-тестов.
LazySegmentTree заменён GenericSegmentTree из пользовательского AlgoTemplates:
исправлен пересчёт предков при точечном обновлении, добавлены пустые интервалы
и пример суммы; HLD использует новый универсальный шаблон.
Персистентное ДО заменено на пользовательский SumTree с присваиванием и примером
версий для ограниченных частот; сумма возвращает T, дублирующее обновление убрано.
Добавлены мосты/точки сочленения, Дилуорс/Мирский, пояснения ориентированного
остова и настройки отладки через макросы. Сокращения vi/pii и контейнерные
алиасы vd/vl/vpi/vb/vv развёрнуты в полные типы в content.

Документация отладки: https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html
и https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode_using.html.

## Диофантовы уравнения и динамика из статики

Добавлен Diophantine.h: расширенный Евклид с положительным НОД, корректное
целочисленное деление для обоих знаков, произвольные включительные/неограниченные
границы, точный подсчёт решений и минимум линейной функции. Нулевые коэффициенты
обрабатываются отдельно, вычисления в __int128 при входах по модулю до 10^18.
Пояснения и проверяемые примеры входят в diophantine.tex.

DynamicSuffixAutomaton.h иллюстрирует метод двоичного счётчика для мультимножества
строк и суммы вхождений. В базовом автомате добавлен 27-й символ-разделитель;
подсчёт occ теперь использует линейную сортировку подсчётом. Поддержка прежних
строк a..z и интерфейс сохранены. Удаления показаны разностью двух историй.

В Kuhn уточнено, что меньшую долю нужно выбрать левой самостоятельно.
В CompressTree добавлены объяснение сжатых путей, пример, расшифровка индексов
и длины рёбер; пустое множество теперь безопасно возвращает пустой результат.
Подробности и источники: doc/diophantine-dynamic-virtual.md.

## Код Прюфера и римские числа

Prufer.h — собственная реализация стандартного удаления минимального листа
с минимальной кучей; сосед листа при кодировании получается через XOR
оставшихся соседей. Оба преобразования работают за O(n log n) и не используют
рекурсию. Вход encode — простое неориентированное дерево на вершинах 0..n-1,
n >= 2; decode возвращает пары концов рёбер. Пример: код {3,3,3} соответствует
рёбрам {0,3}, {1,3}, {2,3}, {3,4}. Пустой код соответствует дереву из двух
вершин; одну вершину нужно обрабатывать отдельно.

Каждая вершина встречается в коде degree[v]-1 раз. Для заданных степеней
нужны degree[v] >= 1 и сумма 2n-2: составить указанные количества копий меток
и перемешать. Равномерное перемешивание даёт равномерное дерево среди деревьев
с такими степенями. Для произвольного равномерного помеченного дерева выбрать
каждый из n-2 элементов кода независимо и равномерно из 0..n-1.

Справка по алгоритму и биекции:
[CP-Algorithms](https://cp-algorithms.com/graph/pruefer_code.html).
Код написан для этого справочника, не скопирован из статьи.

RomanNumerals.h — собственная реализация жадного кодирования и разбора
с проверкой каноничности через обратное преобразование. Выбрана обычная
контестная конвенция 1..3999 и ASCII-буквы IVXLCDM:
[Integer to Roman](https://leetcode.com/problems/integer-to-roman/description/),
[Roman to Integer](https://leetcode.com/problems/roman-to-integer/description/).
Это не универсальный парсер исторических вариантов: IIII и числа вне
диапазона намеренно отклоняются. Если задача допускает другую запись,
соглашения нужно адаптировать явно.

Тест PruferRoman.cpp перебирает все коды до n=7, проверяет биекцию, степени,
связность, независимое медленное кодирование, случайные деревья и большие
цепочки/звёзды. Римские числа проверяются для всех 3999 значений по независимой
таблице десятичных разрядов, а неверные записи — по словарю допустимых строк.

## Стартовый шаблон с 64-битным int

По запросу команды template.cpp использует `using ll = int64_t`,
`#define int ll` и `int32_t main()`. Заголовки GNU PBDS подключаются через
`bits/extc++.h` до макроса. В смешанных вызовах min/max явно задан тип:
это работает и с обычным int, и с int64_t (long либо long long на разных
платформах). В SIMD заголовок immintrin подключается при временно отключённом
макросе, а элементы epi32 явно имеют тип int32_t.

Int64Template.cpp подключает настоящий стартовый шаблон и проверяет
вместе с ним суффиксные структуры, хеширование, PBDS, персистентное дерево,
поток, Флойда, рюкзак, клику и новые преобразования; значения и ключи выше
2^31 не обрезаются. На x86 отдельно проверяется ширина элементов SIMD.

## Обычная DSU, потенциалы и XOR-базис

UnionFind.h — обычная KACTL DSU со сжатием путей и объединением по размеру;
теперь включена в PDF отдельно от версии с откатами. Интерфейс UF сохранён
для совместимости с остальными шаблонами; описание переведено на русский.

PotentialDSU.h написан для справочника. В режиме разностей delta[v]
хранит value[v]-value[parent[v]], после find — разность с корнем.
При добавлении value[b]-value[a]=w потенциал корня b относительно корня a
равен w+delta[a]-delta[b]; при обратном подвешивании знак меняется.
В XOR-режиме сложение и вычитание заменяются XOR, а обратный элемент
совпадает с самим элементом. Несовместимое ограничение отклоняется;
пользователь сам сохраняет факт противоречивости полного набора ограничений.
Потенциалы и все промежуточные вычисления должны помещаться в ll.
Идея хранения относительных значений и чётностей:
[CP-Algorithms](https://cp-algorithms.com/data_structures/disjoint_set_union.html).

XorBasis.h написан для справочника: по одному вектору на старший бит,
приведение к минимальному остатку, проверка представимости и жадный
максимум. Используется uint64_t, поэтому старший, 63-й бит также работает.
Нулевые и повторные добавления не увеличивают rank; при подсчёте числа
представлений n включает и эти добавления. merge объединяет пространства,
но не хранит число первоначальных элементов. Справка по базису:
[USACO Guide](https://usaco.guide/adv/xor-basis).

DSUXor.cpp использует настоящий int64-шаблон. Обычная DSU сравнивается
с перекраской компонент, потенциалы — с обходом графа принятых ограничений,
XOR-базис — с полным перебором подмножеств, включая случайные 64-битные
значения, полный ранг 64, слияния и зависимые добавления.

В doc/stress-demo находится отдельная запускаемая демонстрация
стресс-скрипта с намеренно неверным решением максимума массива. Сам скрипт
пока не включён в печатный TRD: сначала команда знакомится с примером.
