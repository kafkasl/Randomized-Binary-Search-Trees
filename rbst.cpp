#include <string>
#include <exception>
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
	// constructora de la clase nodo_rbst
	nodo_rbst(const string& k, nodo_rbst* izq = NULL, nodo_rbst* der = NULL);
};
nodo_rbst* raiz;

static nodo_rbst* busca_en_bst(nodo_rbst* p, const string& k) throw();
static nodo_rbst* inserta_en_bst(nodo_rbst* p, const string& k);
static nodo_rbst* elimina_en_bst(nodo_rbst* p, const string& k) throw();
static nodo_rbst* juntar(nodo_rbst* t1, nodo_rbst* t2) throw();
static nodo_rbst* reubicar_max(nodo_rbst* p) throw();
};
