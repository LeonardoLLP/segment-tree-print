#include "print_segtree.h"
#include <bits/stdc++.h>
using namespace std;


template<typename T>
class TreePrinter {
private:
    enum direction { UP, DOWN, NONE };

    void print_node(T t[], int v, int spaces, int indent, string(*func)(T), vector<bool>* lines, direction d) {
        for (int i=0; i<spaces-indent; ++i) {
            if ((*lines)[i]) cout << "\u2503";
            else cout << " ";
        }

        if (d != NONE) {
            if (d == UP) cout << "\u250F";
            else /* d == DOWN */ cout << "\u2517";

            for (int i=spaces-indent+1; i<spaces; ++i) cout << "\u2501";
        }

        cout << func(t[v]) << endl;

        delete lines;
    
    }

    void print_segtree_aux(T t[], int v, int tl, int tr, int spaces, int indent, string(*func)(T), vector<bool>* lines, direction d) {
        if (tl == tr) {
            print_node<T>(t, v, spaces, indent, func, lines, d);
        }
        else {
            int tm = (tl + tr) / 2;
            lines->push_back(true);
            for (int i=1; i<indent; ++i) lines->push_back(false);
            vector<bool> *l_up = new vector<bool>(), *l_down = new vector<bool>();
            l_up->assign(lines->begin(), lines->end());
            l_down->assign(lines->begin(), lines->end());

            if (d == UP) (*l_up)[spaces-indent] = false;
            else if (d == DOWN) (*l_down)[spaces-indent] = false;

            print_segtree_aux<T>(t, v*2+1, tm+1, tr, spaces+indent, indent, func, l_up, UP);
            print_node<T>(t, v, spaces, indent, func, lines, d);
            print_segtree_aux<T>(t, v*2, tl, tm, spaces+indent, indent, func, l_down, DOWN);
        }
    }
    
    string pii(const pair<int,int>& x) {
        return to_string(x.first) + " | " + to_string(x.second);
    }

    string vector_int(const vector<int>& v) {
        string res;
        if (!v.empty()) res += to_string(v[0]);
        for (int i=1; i<v.size(); ++i) res += "|" + to_string(v[i]);
        return res;
    }

public:
    void print(T t[], int n, int indent) {
        print_segtree_aux(t, 1, 1, n, 0, indent, format::pii, new vector<bool>(), detail::NONE);
    }

    TreePrinter() {}
};

