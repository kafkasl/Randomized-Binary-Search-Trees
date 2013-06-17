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

//pre: -
//post: si la classe contenia un arbol este se elimina y raiz = NULL, si no tenia arbol se queda como estaba
//coste: maximo N (borrar todo los nodos del arbol)
void init(){
	if(raiz != NULL) deleteRbst(raiz);
	raiz = NULL;
}


//pre: -
//post: a = numero de nodos del rbst
//coste: 1
void card(int& a){
	if(raiz == NULL) a = 0;
	else a = raiz->N;
    //cout << raiz->_k << endl;
}

//pre: 
void find(const string& elem, bool& found, nodo_rbst* x){
	if(x != NULL){
		if (x->_k < elem) find(elem, found, x->_der);
		else if(x->_k > elem) find(elem, found, x->_izq);
		else found = true;
	}
}

void cont(const string& x, bool& found){
	found = false;
	if(raiz != NULL){
		find(x, found, raiz);
	}
}

void deleteRbst(nodo_rbst* x){
	if(x->_izq != NULL)deleteRbst(x->_izq);
	if(x->_der != NULL)deleteRbst(x->_der);
	delete x;
}

void gt(int & total, const string& min, bool& error){
	if(raiz != NULL){
		total = 0;
		error = false;
		greater(total, min, raiz);
	}
	else error = true;
}

void lesser(int& res, const string& min, nodo_rbst* x){
	if(x != NULL and x->_k <= min){
		lesser(res, min, x->_izq);
		++res;
		lesser(res, min, x->_der);
	}
}

void leq(int& res, const string& max, bool& error){
	if(raiz != NULL){
		res = 0;
		error = false;
		lesser(res, max, raiz);
	}
	else error = true;
}

void greater(int& res, const string& max, nodo_rbst* x){
	if(x != NULL and x->_k >= max){
		greater(res, max, x->_der);
		++res;
		greater(res, max, x->_izq);
	}
}


void between(vector<string>& res, const string& min, const string& max, bool& error){
	res.clear();
	error = false;
	if(raiz != NULL) interval(res, min, max, raiz); 
	else error = true;
}


void interval(vector<string>& res, const string& min, const string& max, nodo_rbst* x){
    if(x != NULL){
        if(x->_k >= min)interval(res, min, max, x->_izq);
        res.push_back(x->_k);
        if(x->_k <= max)interval(res, min, max, x->_der);
    }
}

void min(string& min, bool& error){
	//cerr << "min" << endl;
	if(raiz == NULL) error = true;
	else {
	//cerr << "root not null" << endl;
		nodo_rbst* act = raiz;
		while (act->_izq != NULL){
			//cerr << "evaluating: " << act->_izq->_k;
			act = act->_izq;
			//cerr << "...done" << endl;
		}
		//cerr << "min found" << endl;
		min = act->_k;
		error = false;
	}
}

void max(string& max, bool& error){
	//cerr << "max" << endl;
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

void all(vector<string>& all){
	all.clear();
	if(raiz != NULL){
		listAll(raiz, all);	
	}
}


//pre: -
//post: el elemento x se inserta en el rbst
//cost: FALTAAAAA 
void put(const string& x){
	raiz = insert(x, raiz);
}



nodo_rbst* insert(const string& x, nodo_rbst* T) {
	if(T == NULL) return insert_at_root(x,T);
	int n, r;
	n = T->N;
	//cerr << "Insert" << endl;
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
    int auxizq,auxder;
    auxizq = auxder = 0;
    if(T->_izq != NULL) auxizq = T->_izq->N;
    if(T->_der != NULL) auxder = T->_der->N;
    T->N = 1 + auxizq + auxder;
	return T;
}


nodo_rbst* insert_at_root(const string& x, nodo_rbst* arbre ){
	//cerr << "insert at root";
	nodo_rbst* raiz_izq, *raiz_der, *ins_izq, *ins_der;
	raiz_izq = raiz_der = ins_izq = ins_der = NULL;
    bool contar = false;
	while ( arbre != NULL){
        contar = true;
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
	if(contar) {
        nou->N = counter(nou->_izq)+ counter(nou->_der)+1;
        //nou->N = contarizk(nou->_izq)+ contardre(nou->_der)+1;
    }
    else nou->N = 1;
    //cerr << "...done" << endl;
	return nou;
}
    
    
    int contarizk(nodo_rbst* abc){
        int res = 0;
        if(abc != NULL) {
            ++res;
            res+= contarizk(abc->_der);
            if(abc->_izq != NULL) res=+(abc->_izq)->N;
            abc->N = res;
        }
        return res;
    }
    
    int contardre(nodo_rbst* abc){
        int res = 0;
        if(abc != NULL) {
            ++res;
            res+= contardre(abc->_izq);
            if(abc->_der != NULL) res=+(abc->_der)->N;
            abc->N = res;
        }
        return res;
    }
    
    int counter(nodo_rbst* abc) {
        if(abc == NULL) return 0;
        else {
            abc->N = 1 + counter(abc->_izq) + counter(abc->_der);
            return abc->N;
        }
    }
    
    
    void delete_element(string x){
        raiz = findAndDelete(x,raiz);
    }
    
    nodo_rbst* findAndDelete(string elem, nodo_rbst* x){
        if(x == NULL) return NULL;
        else {
            if (x->_k < elem) {x->_der = findAndDelete(elem, x->_der);--(x->N);}
            else if(x->_k > elem){ x->_izq = findAndDelete(elem, x->_izq);--(x->N);}
            else {
                nodo_rbst* aux;
                aux = joinToDelete(x->_izq, x->_der);
                x = aux;
                counter(x);
            }
            return x;
        }
        
    }
    
    nodo_rbst* joinToDelete(nodo_rbst* L, nodo_rbst* R){
       // cout << "LLEGO HASTA AQUI" << endl;
        int m,n,r,total;
        m = n = 0;
        if (L != NULL) m = L->N;
        if(R != NULL) n = R->N;
        
        total = n + m;
        if (total == 0)return NULL;
        r = rand() % (total - 1);
        if(r < m) {
            L->_der = joinToDelete(L->_der, R);
            return L;
        }
        else {
            R->_izq = joinToDelete(L,R->_izq);
            return R;
        }
    }
    
    string iessim(int i) {
        if(i < 1 or i > raiz->N) return "ERROR";
        else {
            return nthFunction(i,raiz,0);
        }
    }
    
    string nthFunction(int i, nodo_rbst *arbre,int count){
        int aux = count+1;
        if(arbre->_izq != NULL) aux+=arbre->_izq->N;
        if(i == aux) return arbre->_k;
        else if(arbre->_der == NULL) return nthFunction(i,arbre->_izq,count);
        else if(arbre->_izq == NULL) return nthFunction(i,arbre->_der,count+1);
        else {
            if(i < aux) return  nthFunction(i,arbre->_izq,count);
            else return nthFunction(i,arbre->_der,aux);
        }
    }
    
    void escriuArbre(nodo_rbst* nodo) {
        if(nodo->_izq!= NULL) escriuArbre(nodo->_izq);
        
       // cout << nodo->N << ',' << ' ';
        
        if(nodo->_der != NULL) escriuArbre(nodo->_der);
    }
    
    void escriuArbre(){
        escriuArbre(raiz);
    }
    
};

int main(){
	std::map<string, Rbst> sets;
	std::map<string, Rbst>::iterator it;
	string op, id_set1, id_set2, elem, elem2;
	int i;
	vector<string> res;
	bool error;
	while(cin >> op){
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
				sets[id_set1].cont(elem, error);
				if(error == false)sets[id_set1].put(elem);
				cout << "OK" << endl;
                		sets[id_set1].escriuArbre();
            		}
		}
		else if (op == "cont"){
			cin >> id_set1 >> elem;
			cout << "> " << op << " " << id_set1 << " " << elem << endl;
			it = sets.find(id_set1);
			if(it == sets.end()) cout << "ERROR" << endl;
			else {
				bool found;
				sets[id_set1].cont(elem, found);
				if(found) cout << "true" << endl;
				else cout << "false" << endl;
			}
			
		}
		else if (op == "merge"){
			cin >> id_set1 >> id_set2;
			cout << "> " << op << " " << id_set1 << " " << id_set2 << endl;
			it = sets.find(id_set1);
			if(it == sets.end()) cout << "ERROR" << endl;
			else {
				it = sets.find(id_set2);
				if (it == sets.end())cout << "ERROR" << endl;
				else {
					sets[id_set2].all(res);
					if(error == false)for(int i = 0; i < res.size(); ++i){
						sets[id_set1].cont(res[i], error);
						if( error == false)sets[id_set1].put(res[i]);
					}
					sets[id_set2].init();
					cout << "OK" << endl;
				}
			}
		}
		else if (op == "card"){
			cin >> id_set1;
			cout << "> " << op << " " << id_set1 << endl;
			it = sets.find(id_set1);
			if(it == sets.end()) cout << "ERROR" << endl;
			else {
				sets[id_set1].card(i);
				cout << i << endl;
			}
		}
		else if (op == "nth"){
			cin >> id_set1 >> i;
			cout << "> " << op << " " << id_set1 << " " << i << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
				int n;
				sets[id_set1].card(n);
				if( i < 1 or i > n) cout << "ERROR" << endl;
            			else cout << sets[id_set1].iessim(i) << endl;
			} else cout << "ERROR" << endl;
        	}
		else if (op == "leq"){
			cin >> id_set1 >> elem;
			cout << "> " << op << " " << id_set1 << " " << elem << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].leq(i, elem, error);
				if(error == false) cout << i << endl;
				else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
		else if (op == "gt"){
			cin >> id_set1 >> elem;
			cout << "> " << op << " " << id_set1 << " " << elem << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].gt(i, elem, error);
				if(error == false) cout << i << endl;
				else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
		else if (op == "between"){
			cin >> id_set1 >> elem >> elem2;
			cout << "> " << op << " " << id_set1 << " " << elem << " " << elem2 << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].between(res, elem, elem2, error);
				if (error == false) {
					cout << "[" << res[0];
					for(int i = 1; i < res.size(); ++i)cout << "," << res[i];
					cout << "]" << endl;
				} else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
		else if (op == "min"){
			cin >> id_set1;
			cout << "> " << op << " " << id_set1 << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].min(elem, error);
				if (error == false) cout << elem << endl;
				else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
		else if (op == "max"){
			cin >> id_set1;
			cout << "> " << op << " " << id_set1 << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].max(elem, error);
				if (error == false) cout << elem << endl;
				else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
		else if (op == "all"){
			cin >> id_set1;
			cout << "> " << op << " " << id_set1 << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
				sets[id_set1].all(res);
				if (error == false) {
					cout << "[";
					if(res.size() > 0) {
						cout << res[0];
						for(int i = 1; i < res.size(); ++i)cout << "," << res[i];
					}
					cout << "]" << endl;
				} else cout << "ERROR" << endl;
			} else cout << "ERROR" << endl;
		}
        	else if(op == "del") {
            		cin >> id_set1 >> elem;
			cout << "> " << op << " " << id_set1 << " " << elem << endl;
			it = sets.find(id_set1);
			if(it != sets.end()){
            			sets[id_set1].delete_element(elem);
				cout << "OK" << endl;
			} else cout << "ERROR" << endl;
        	}
	}
}
