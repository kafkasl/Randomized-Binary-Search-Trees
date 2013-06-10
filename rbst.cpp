#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Rbst {
public:
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
	nodo_rbst(const string& k, nodo_rbst* izq = NULL, nodo_rbst* der = NULL);
};
nodo_rbst* raiz;

static nodo_rbst* busca_en_bst(nodo_rbst* p, const string& k) throw();
static nodo_rbst* elimina_en_bst(nodo_rbst* p, const string& k) throw();
static nodo_rbst* juntar(nodo_rbst* t1, nodo_rbst* t2) throw();
static nodo_rbst* reubicar_max(nodo_rbst* p) throw();

void min(string& min, bool& error){
	if(raiz == NULL) error = true;
	else {
		nodo_rbst* act = raiz;
		while (act->_izq != NULL){
			act = act->_izq;
		}
		min = act->_k;
		error = false;
	}
}

void max(string& max, bool& error){
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
		vector<string> res;
		listAll(raiz, res);	
		error = false;
	}
	error = true;
	
}

};


int main(){}
