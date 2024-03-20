#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;


template<typename T>
void print_node(int t[], int v, int spaces, function<string(T)> format_function) {
    for (int i=0; i<spaces; ++i) cout << ' ';
    cout << format_function(t[v]) << endl;
}


// TODO: make template
// TODO: make documentation
template<typename T>
void print_segtree(int t[], int v, int tl, int tr, int spaces, function<string(T)> format_function) {
    if (tl == tr) {
        print_node<T>(t, v, spaces, format_function);
    }
    else {
        int tm = (tl + tr) / 2;
        print_segtree<T>(t, v*2+1, tm+1, tr, spaces+2, format_function);
        print_node<T>(t, v, spaces, format_function);
        print_segtree<T>(t, v*2, tl, tm, spaces+2, format_function);
    }
}
