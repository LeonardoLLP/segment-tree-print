#include <bits/stdc++.h>

namespace detail {
    template<typename T>
    void print_node(T t[], int v, int spaces, std::string(*func)(T)) {
        std::cout << " ";
        for (int i=1; i<spaces; ++i) std::cout << " ";
        std::cout << func(t[v]) << std::endl;
    
    }

    template<typename T>
    void print_segtree_aux(T t[], int v, int tl, int tr, int spaces, int indent, std::string(*func)(T)) {
        if (tl == tr) {
            print_node<T>(t, v, spaces, func);
        }
        else {
            int tm = (tl + tr) / 2;
            print_segtree_aux<T>(t, v*2+1, tm+1, tr, spaces+indent, indent, func);
            print_node<T>(t, v, spaces, func);
            print_segtree_aux<T>(t, v*2, tl, tm, spaces+indent, indent, func);
        }
    }
}

namespace format {
    std::string pii(std::pair<int,int> x) {
        return std::to_string(x.first) + " | " + std::to_string(x.second);
    }
}

template<typename T>
void print_segtree(T t[], int n, int indent) {
    detail::print_segtree_aux(t, 1, 1, n, 0, indent, format::pii);
}