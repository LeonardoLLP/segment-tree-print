#include <bits/stdc++.h>

template<typename T>
class TreePrint {
public:
    void print(T t[], int n, int indent) {
        detail::print_segtree_aux(t, 1, 1, n, 0, indent, format::pii, new std::vector<bool>(), detail::NONE);
    }
};

namespace detail {

    enum direction { UP, DOWN, NONE };

    template<typename T>
    void print_node(T t[], int v, int spaces, int indent, std::string(*func)(T), std::vector<bool>* lines, direction d) {
        for (int i=0; i<spaces-indent; ++i) {
            if ((*lines)[i]) std::cout << "\u2503";
            else std::cout << " ";
        }

        if (d != NONE) {
            if (d == UP) std::cout << "\u250F";
            else /* d == DOWN */ std::cout << "\u2517";

            for (int i=spaces-indent+1; i<spaces; ++i) std::cout << "\u2501";
        }

        std::cout << func(t[v]) << std::endl;
    
    }

    template<typename T>
    void print_segtree_aux(T t[], int v, int tl, int tr, int spaces, int indent, std::string(*func)(T), std::vector<bool>* lines, direction d) {
        if (tl == tr) {
            print_node<T>(t, v, spaces, indent, func, lines, d);
        }
        else {
            int tm = (tl + tr) / 2;
            lines->push_back(true);
            for (int i=1; i<indent; ++i) lines->push_back(false);
            std::vector<bool> *l_up = new std::vector<bool>(), *l_down = new std::vector<bool>();
            l_up->assign(lines->begin(), lines->end());
            l_down->assign(lines->begin(), lines->end());

            if (d == UP) (*l_up)[spaces-indent] = false;
            else if (d == DOWN) (*l_down)[spaces-indent] = false;

            print_segtree_aux<T>(t, v*2+1, tm+1, tr, spaces+indent, indent, func, l_up, UP);
            print_node<T>(t, v, spaces, indent, func, lines, d);
            print_segtree_aux<T>(t, v*2, tl, tm, spaces+indent, indent, func, l_down, DOWN);
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