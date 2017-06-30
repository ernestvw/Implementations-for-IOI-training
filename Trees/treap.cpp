#include <iostream>
#include <random>

using namespace std;
//took 37m to code, including test routine
//Does not support duplicate keys
//this program runs deterministically, because the same seed is used each run
//This program does not handle misuse by the user, for example overflows or out of bound indexes
class node {
public:
	node *l, *r, *p;
	int sz;
	int v, k;
	node(int m_v, node *m_p){
		v = m_v;
		p = m_p;
		sz = 1;
		k = rand();
	}
};

class treap {
public:
	node *rt;
	treap(){
		rt = NULL;
	}
	void insert(int v){
		node *r = m_insert(rt, NULL, v);
		if(r)
			rt = r;
	}
	void prtTree(){
		m_prtTree(rt);
	}
	int qr(int ndx){
		return m_qr(rt, ndx);
	}
private:
	int m_qr(node *n, int ndx){
		int lv = 0;
		if(n->l!=NULL)
			lv = (n->l)->sz;
		if(ndx<=lv)
			return m_qr(n->l, ndx);
		else if(ndx==1+lv)
			return n->v;
		else
			return m_qr(n->r, ndx-lv-1);
	}
	node *m_insert(node *n, node *p, int v){
		if(n==NULL){
			n = new node(v, p);
			while(n->p!=NULL){
				if((n->v)<(p->v))
					p->l = n;
				else
					p->r = n;
				if((p->k)>=(n->k))
					break;
				if((n->v)<(p->v)){
					//left child
					node *tmpr = (n->r);
					node *pp = p->p;
					n->r = p;
					p->p = n;
					n->p = pp;
					p->l = tmpr;
					int psz = p->sz;
					p->sz = (p->sz)-(n->sz)+((tmpr?tmpr->sz:0));
					n->sz = psz;
				} else {
					//right child
					node *pp = p->p;
					node *tmpl = (n->l);
					n->l = p;
					p->p = n;
					n->p = pp;
					p->r = tmpl;
					int psz = p->sz;
					p->sz = (p->sz)-(n->sz)+(tmpl?(tmpl->sz):0);
					n->sz = psz;
				}
				p = n->p;
			}
			if(n->p==NULL)
				return n;
			else
				return NULL;
		} else {
			(n->sz)++;
			if(v<(n->v))
				return m_insert(n->l, n, v);
			else
				return m_insert(n->r, n, v);
		}
	}
	void m_prtTree(node *n){
		if(n==NULL)
			return;
		cout << n->v << " " << n->k << " " << n->sz << endl;
		m_prtTree(n->l);
		cout << n->v << endl;
		m_prtTree(n->r);
		cout << n->v << endl;
	}
};

int main(){
	treap *trp = new treap();
	srand(228);
	int N; cin>>N;
	int a;
	for(int n=0; n<N; n++){
		cin>>a;
		trp->insert(a);
		//cout << (trp->rt?trp->rt->v:0) << endl;
	}
	int M; cin>>M;
	int ndx;
	for(int m=0; m<M; m++){
		cin>>ndx;
		printf("Test case %d: %d\n", m+1, trp->qr(ndx));
	}
//	trp->prtTree();
	return 0;
}
