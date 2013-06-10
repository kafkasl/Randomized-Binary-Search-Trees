#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Rbst {
public:
	Rbst(){
		raiz = NULL;
		srand (time(NULL));
	}
	void busca(const string& k, bool& esta);
	void inserta(const string& k);
	void elimina(const string& k);
private:
struct nodo_rbst {
	string _k;
	nodo_rbst* _izq;
	nodo_rbst* _der;
	int N;
	// constructora de la clase nodo_rbst
};
nodo_rbst* raiz;


public:

void between(vector<string>& res, const string& min, const string& max){

}

void min(string& min, bool& error){
	cerr << "min" << endl;
	if(raiz == NULL) error = true;
	else {
	cerr << "root not null" << endl;
		nodo_rbst* act = raiz;
		while (act->_izq != NULL){
			cerr << "evaluating: " << act->_izq->_k;
			act = act->_izq;
			cerr << "...done" << endl;
		}
		cerr << "min found" << endl;
		min = act->_k;
		error = false;
	}
}

void max(string& max, bool& error){
	cerr << "max" << endl;
	if(raiz == NULL) error = true;
	else {
	nodo_rbst* act = raiz;
		while (act->_der != NULL){
			act = act->_der;
		}
		max = act->_k;
		error = false;
	}
}

void listAll(nodo_rbst* x, vector<string>& res){
	if(x->_izq != NULL)listAll(x->_izq, res);
	res.push_back(x->_k);
	if(x->_der != NULL)listAll(x->_der, res);
}

void all(vector<string>& all, bool& error){
	if(raiz != NULL){
		listAll(raiz, all);	
		error = false;
	}
	else error = true;
}

void put(const string& x){
	cerr << "Put";
	raiz = insert(x, raiz);
	cerr << "...done" << endl;
}



nodo_rbst* insert(const string& x, nodo_rbst* T) {
	if(T == NULL) return insert_at_root(x,T);
	int n, r;
	n = T->N;
	cerr << "Insert" << endl;
	r = rand() % (n + 1);
	cerr << r << endl;
	if (r == n)
		return insert_at_root(x,T);

	if (x < T->_k){
		T->_izq = insert(x, T->_izq);
	}
	else{
		T->_der = insert(x, T->_der);
	}
	return T;
}


nodo_rbst* insert_at_root(const string& x, nodo_rbst* arbre ){
	cerr << "insert at root";
	nodo_rbst* raiz_izq, *raiz_der, *ins_izq, *ins_der;
	raiz_izq = raiz_der = ins_izq = ins_der = NULL;
	while ( arbre != NULL){
		if(x > arbre->_k){
			if(raiz_izq == NULL){raiz_izq = arbre; ins_izq = arbre;}
			else { ins_izq->_der = arbre; ins_izq = ins_izq->_der;}
			arbre = arbre->_der;
			ins_izq->_der = NULL;
		} else if (x < arbre->_k){
			if(raiz_der == NULL){raiz_der = arbre; ins_der = arbre;}
			else { ins_der->_izq = arbre; ins_der = ins_der->_izq;}
			arbre = arbre->_izq;
			ins_der->_izq = NULL;
		}
	}
	cerr << "...done" << endl;
	nodo_rbst* nou = new nodo_rbst();
	nou->_izq = raiz_izq;
	nou->_der = raiz_der;
	nou->_k = x;
	cerr << "...done" << endl;
	return nou;
	

}

};

int main(){
	Rbst a;
	a.put("hola");
	a.put("ie");
	a.put("oei");
	a.put("aaaaaa");
	cout << "put" << endl;
	string res;
	bool error;
	a.min(res, error);
	if(!error)cout << res << endl;
	a.max(res, error);
	if(!error)cout << res << endl;
	vector<string> resV;
	a.all(resV,error);
	if(!error){
		for (int i = 0; i < resV.size(); ++i)
			cout << resV[i] << "  ";
	}
}
