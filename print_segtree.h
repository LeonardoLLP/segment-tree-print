#include <bits/stdc++.h>

namespace detail {

    enum direction { UP, DOWN };

    template<typename T>
    void print_node(T t[], int v, int spaces, int indent, std::string(*func)(T), std::vector<bool>* lines, direction d) {
        for (int i=0; i<spaces-indent; ++i) {
            if ((*lines)[i]) std::cout << "\u2503";
            else std::cout << " ";
        }

        if (d == UP) std::cout << "\u250F";
        else /* d == DOWN */ std::cout << "\u2517";

        for (int i=spaces-indent+1; i<spaces; ++i) std::cout << "\u2501";

        std::cout << func(t[v]) << std::endl;
    
    }

    template<typename T>
    void print_segtree_aux(T t[], int v, int tl, int tr, int spaces, int indent, std::string(*func)(T), std::vector<bool>* lines) {
        if (tl == tr) {
            print_node<T>(t, v, spaces, indent, func, lines);
        }
        else {
            int tm = (tl + tr) / 2;
            print_segtree_aux<T>(t, v*2+1, tm+1, tr, spaces+indent, indent, func);
            print_node<T>(t, v, spaces, indent, func, lines);
            print_segtree_aux<T>(t, v*2, tl, tm, spaces+indent, indent, func);
        }
    }
}

namespace format {
    std::string pii(std::pair<int,int> x) {
        return std::to_string(x.first) + " | " + std::to_string(x.second);
    }

    std::string vector_int(std::vector<int> v) {
        std::string res = "";
        if (!v.empty()) res += std::to_string(v[0]);
        for (int i=1; i<v.size(); ++i) res += "|" + std::to_string(v[i]);
        return res;
    }
}

template<typename T>
void print_segtree(T t[], int n, int indent) {
    detail::print_segtree_aux(t, 1, 1, n, 0, indent, format::pii, new std::vector<bool>());
}