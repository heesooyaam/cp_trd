/**
 * Author: heesooyaam
 * Source: https://github.com/heesooyaam/AlgoTemplates/blob/main/Structures/Trees/Segment/Default/Template.cpp
 * Description: Универсальное ДО с отложенными обновлениями на [l,r). combine объединяет соседние узлы (ассоциативно); neutral\_node — нейтральный узел пустого отрезка. composition(old,new) применяет сначала старое, затем новое обновление; neutral\_push ничего не меняет. sync(node,upd) применяет обновление к агрегату; длину отрезка при необходимости хранить в node. sync должен согласовываться с combine и composition. Конструктор от размера заполняет листья node\_t{}, от контейнера — переданными узлами. Пустое дерево допустимо.
 * Time: O(n) построение и память; O(\log n) запрос/обновление, если операции O(1).
 * Status: Differential tests: range/point operations, noncommutative tag composition, empty ranges.
 */
#pragma once
template <typename node_t, auto combine, auto neutral_node,
          typename push_t,
          auto composition, /* сначала old, затем new */
          auto sync, auto neutral_push>
class seg_tree_t {
    static_assert(std::is_convertible<
                  decltype(combine),
                  std::function<node_t(node_t, node_t)>>());
    static_assert(std::is_convertible<
                  decltype(composition),
                  std::function<push_t(push_t, push_t)>>());
    static_assert(std::is_convertible<
                  decltype(sync),
                  std::function<node_t(node_t, push_t)>>());

    static_assert(
        std::is_convertible<decltype(neutral_node),
                            std::function<node_t()>>());
    static_assert(
        std::is_convertible<decltype(neutral_push),
                            std::function<push_t()>>());

    const int n;
    std::vector<node_t> tree;
    std::vector<push_t> lazy;

  public:
    // node_t{} — значение одного элемента, neutral_node() — пустого отрезка.
    explicit seg_tree_t(int sz)
        : seg_tree_t(vector<node_t>(sz)) {}

    template <typename container_t>
    seg_tree_t(const container_t &data)
        : n(data.size()), tree(n << 2),
          lazy(n << 2, neutral_push()) {
        if (n > 0) {
            build(0, 0, n, data);
        }
    }

    void update(const int l, const int r, const push_t &upd) {
        assert(0 <= l && l <= r && r <= n);
        if (l < r) {
            update(0, 0, n, l, r, upd);
        }
    }

    void update(const int pos, const push_t &upd) {
        assert(0 <= pos && pos < n);
        update(pos, pos + 1, upd);
    }

    node_t get(const int l, const int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) {
            return neutral_node();
        }
        return get(0, 0, n, l, r);
    }

    node_t get(const int pos) {
        assert(0 <= pos && pos < n);
        return get(pos, pos + 1);
    }

  private:
    template <typename container_t>
    void build(int idx, int cl, int cr,
               const container_t &data) {
        if (cl + 1 == cr) {
            tree[idx] = data[cl];
            return;
        }

        int mid = (cl + cr) >> 1;
        build((idx << 1) + 1, cl, mid, data);
        build((idx << 1) + 2, mid, cr, data);
        tree[idx] =
            combine(tree[(idx << 1) + 1], tree[(idx << 1) + 2]);
    }

    void update_node(int idx, const push_t &upd) {
        lazy[idx] = composition(lazy[idx], upd);
        tree[idx] = sync(tree[idx], upd);
    }

    void push(int idx) {
        update_node((idx << 1) + 1, lazy[idx]);
        update_node((idx << 1) + 2, lazy[idx]);

        lazy[idx] = neutral_push();
    }

    void update(int idx, int cl, int cr, int l, int r,
                const push_t &upd) {
        if (l >= cr || r <= cl) {
            return;
        }

        if (l <= cl && cr <= r) {
            update_node(idx, upd);
            return;
        }

        push(idx);

        int mid = (cl + cr) >> 1;
        update((idx << 1) + 1, cl, mid, l, r, upd);
        update((idx << 1) + 2, mid, cr, l, r, upd);
        tree[idx] =
            combine(tree[(idx << 1) + 1], tree[(idx << 1) + 2]);
    }

    node_t get(int idx, int cl, int cr, int l, int r) {
        if (l >= cr || r <= cl) {
            return neutral_node();
        }

        if (l <= cl && cr <= r) {
            return tree[idx];
        }

        push(idx);

        int mid = (cl + cr) >> 1;
        return combine(get((idx << 1) + 1, cl, mid, l, r),
                       get((idx << 1) + 2, mid, cr, l, r));
    }
};
