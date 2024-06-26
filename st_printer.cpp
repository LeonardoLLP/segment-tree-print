// #include "print_segtree.h"
// #include <bits/stdc++.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/**
 * Collects all predefined format functions.
 * @namespace
*/
namespace format {
    /**
     * Converts a pair of same type to a string.
     * @param x A pair of type T.
    */
    template <typename T>
    static string _pair(const pair<T,T>& x) {
        return to_string(x.first) + "|" + to_string(x.second);
    }

    /**
     * Converts a vector to a string separated by the "|" character.
     * @param x A vector of type T.
    */
    template <typename T>
    static string _vector(const vector<T>& v) {
        string res;
        if (!v.empty()) res += to_string(v[0]);
        for (int i=1; i<v.size(); ++i) res += "|" + to_string(v[i]);
        return res;
    }

    /**
     * Converts a single argument to a string
     * @param x A single type T argument.
    */
    template <typename T>
    static string _single(const T& x) {
        return to_string(x);
    }
}

template<typename T>
class TreePrinter {
private:
    enum direction { UP, DOWN, NONE };

    void print_node(T t[], int v, int spaces, int indent, string(*func)(const T&), vector<bool>* lines, direction d) {
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
    
    }

    void print_line(vector<bool>* lines) {
        for (auto b: *lines) {
            if (b) cout << "\u2503";
            else cout << " ";
        }
        cout << endl;
    }

    void print_segtree_aux(T t[], int v, int tl, int tr, int spaces, int indent, string(*func)(const T&), vector<bool>* lines, direction d, bool compressed) {
        if (tl == tr) {
            print_node(t, v, spaces, indent, func, lines, d);
        }
        else {
            int tm = (tl + tr) / 2;
            vector<bool> *l_up = new vector<bool>(), *l_down = new vector<bool>();
            l_up->assign(lines->begin(), lines->end());
            l_up->push_back(true);
            for (int i=1; i<indent; ++i) l_up->push_back(false);
            l_down->assign(l_up->begin(), l_up->end());

            if (d == UP) (*l_up)[spaces-indent] = false;
            else if (d == DOWN) (*l_down)[spaces-indent] = false;

            print_segtree_aux(t, v*2+1, tm+1, tr, spaces+indent, indent, func, l_up, UP, compressed);
            if (!compressed) print_line(l_up);
            print_node(t, v, spaces, indent, func, lines, d);
            if (!compressed) print_line(l_down);
            print_segtree_aux(t, v*2, tl, tm, spaces+indent, indent, func, l_down, DOWN, compressed);

            delete l_up, l_down;
        }
    }

public:
    /**
     * Prints the specified tree.
     * @param t A pointer to the array of the tree.
     * @param n Range of the segment tree (number of elements of the original array).
     * @param indent Number of spaces to indent each level. If uncertain, use 4.
     * @param format_f Function that formats from a node type to a string. If using your own, make it static.
     */
    void print(T t[], int n, int indent, string(*format_f)(const T&)) {
        if (indent < 1) indent = 1;
        print_segtree_aux(t, 1, 1, n, 0, indent, format_f, new vector<bool>(), NONE, false);
    }

    void print_compressed(T t[], int n, int indent, string(*format_f)(const T&)) {
        if (indent < 1) indent = 1;
        print_segtree_aux(t, 1, 1, n, 0, indent, format_f, new vector<bool>(), NONE, true);
    }

    TreePrinter() {}
};