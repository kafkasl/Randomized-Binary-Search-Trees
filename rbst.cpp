#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <string>
#include <vector>
#include <iostream>
#include <map>

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

void init(){
	if(raiz != NULL) deleteRbst(raiz);
	raiz = NULL;
}

void deleteRbst(nodo_rbst* x){
	if(x->_izq != NULL)deleteRbst(x->_izq);
	if(x->_der != NULL)deleteRbst(x->_der);
	delete x;
}

void gt(vector<string>& res, const string& min, bool& error){
	if(raiz != NULL){
		error = false;
		lesser(res, min, raiz);
	}
	else error = true;
}

void lesser(vector<string>& res, const string& min, nodo_rbst* x){
	if(x->_k > min){
		lesser(res, min, x->_izq);
		res.push_back(x->_k);
		lesser(res, min, x->_der);
	}
}

void leq(vector<string>& res, const string& max, bool& error){
	if(raiz != NULL){
		error = false;
		greater(res, max, raiz);
	}
	else error = true;
}

void greater(vector<string>& res, const string& max, nodo_rbst* x){
	if(x->_k < max){
		greater(res, max, x->_der);
		res.push_back(x->_k);
		greater(res, max, x->_izq);
	}
}


void between(vector<string>& res, const string& min, const string& max, bool& error){
	error = false;
	if(raiz != NULL) interval(res, min, max, raiz); 
	else error = true;
}


void interval(vector<string>& res, const string& min, const string& max, nodo_rbst* x){
	if(x->_k >= min)interval(res, min, max, x->_izq);
	res.push_back(x->_k);
	if(x->_k <= max)interval(res, min, max, x->_der);
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
	nodo_rbst* nou = new nodo_rbst();
	nou->_izq = raiz_izq;
	nou->_der = raiz_der;
	nou->_k = x;
	cerr << "...done" << endl;
	return nou;
	

}

};

int main(){
	std::map<string, Rbst> sets;
	std::map<string, Rbst>::iterator it;
	string op, id_set1, id_set2, elem, elem2;
	int i;
	vector<string> res;
	bool error;
	while(1){
		cin >> op;
		if(op == "init"){
			cin >> id_set1;
			cout << "> " << op << " " << id_set1 << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
				Rbst a;
				sets.insert(make_pair(id_set1, a));
				/*it = sets.find(id_set1);
				if(it != sets.end())cerr << "inserted" << endl;*/
			}
			sets[id_set1].init();
			cout << "OK" << endl;	
		}
		else if (op == "ins"){
			cin >> id_set1 >> elem;
			cout << "> " << op << " " << id_set1 << " " << elem << endl;
			it = sets.find(id_set1);
			if(it == sets.end()){
				cout << "ERROR" << endl;
			} else {
				sets[id_set1].put(elem);
				cout << "OK" << endl;	
			}
		}
		else if (op == "del"){
			cin >> id_set1 >> elem;
		}
		else if (op == "cont"){
			cin >> id_set1 >> elem;
			
		}
		else if (op == "merge"){
			cin >> id_set1 >> id_set2;
		}
		else if (op == "card"){
			cin >> id_set1;
		}
		else if (op == "nth"){
			cin >> id_set1 >> i;
		}
		else if (op == "leq"){
			cin >> id_set1 >> elem;
		}
		else if (op == "gt"){
			cin >> id_set1 >> elem;
		}
		else if (op == "between"){
			cin >> id_set1 >> elem >> elem2;
		}
		else if (op == "min"){
			cin >> id_set1;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].min(elem, error);
				if (error == false) cout << elem << endl;
				else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
		else if (op == "max"){
			cin >> id_set1;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].max(elem, error);
				if (error == false) cout << elem << endl;
				else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
		else if (op == "all"){
			cin >> id_set1;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].all(res, error);
				if (error == false) {
					cout << "[" << res[0];
					for(int i = 1; i < res.size(); ++i)cout << "," << res[i];
					cout << "]" << endl;
				} else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
	}
}
