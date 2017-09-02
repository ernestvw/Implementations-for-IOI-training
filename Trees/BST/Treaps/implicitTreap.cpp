#include <bits/stdc++.h>
using namespace std;

typedef struct item * pitem;
struct item {
    int prior, i, cnt;
    bool rev;
    pitem l, r;
};

const int MAXI = 100 * 1000;
char nom[MAXI][100];
int nbCanards, nbRequetes;

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push (t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}

void reverse (pitem t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void insert(pitem *t, int cnt, int i) {
    push(*t);
    int y = rand();
    pitem u = new item {y, i, cnt, 0, NULL, NULL};
    pitem t1, t2;
    split(*t, t1, t2, cnt);
    merge(u, u, t2);
    merge(*t, t1, u);
}

int find(pitem t, int q) {
    push(t);
    if(cnt(t->l) == q) return t->i;
    else if(q < cnt(t->l)) return find(t->l, q);
    else return find(t->r, q-cnt(t->l)-1);
}

void output (pitem t) {
    if (!t)  return;
    push (t);
    output (t->l);
    printf ("%d ", t->i);
    output (t->r);
}

int main()
{
    cin >> nbCanards >> nbRequetes;
    pitem root = NULL;
    for(int i = 0; i < nbCanards; i++) {
        cin >> nom[i];
        insert(&root, i+1, i);
    }
    // output(root);
    cout << endl;
    
    for(int i = 0; i < nbRequetes; i++) {
        char tp[2];
        cin >> tp;
        if(tp[0] == 'R') {
            int l, r;
            cin >> l >> r;
            l--, r--, r--;
            reverse(root, l, r);
            // output(root);
        }
        else {
            int q; cin >> q;
            q--;
            cout << nom[find(root, q)] << '\n';
        }
    }
    return 0;
}

















































