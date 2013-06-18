/*************************************


AUTORES:

Pol Alvarez Vecino

Jordi Montes Sanabria



***************************************/





/*************************************
 
 
 AUTORES:
 
 Pol Alvarez Vecino
 
 Jordi Montes Sanabria
 
 
 
 ***************************************/





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
    
    //pre: x es un nodo valido del rbst
    //post: si se ha encontrado el elemento -> found = true else found = false
    //cost: log (N) la altura mayor del arbol, que siendo un rbst consideramos log N
    void find(const string& elem, bool& found, nodo_rbst* x){
        if(x != NULL){
            if (x->_k < elem) find(elem, found, x->_der);
            else if(x->_k > elem) find(elem, found, x->_izq);
            else found = true;
        }
    }
    
    //pre: -
    //post: si string pertenece al rbst -> found = true else found = false
    //cost: es el coste de find + la llamada que es negligible.
    void cont(const string& x, bool& found){
        found = false;
        if(raiz != NULL){
            find(x, found, raiz);
        }
    }
    
    
    //pre: x es un nodo valido
    //post: x y todo el subarbol contenido por el y sus hijos es eliminado
    //cost: N (hay que borrar todo el arbol)
    void deleteRbst(nodo_rbst* x){
        if(x->_izq != NULL)deleteRbst(x->_izq);
        if(x->_der != NULL)deleteRbst(x->_der);
        delete x;
    }
    
    
    //pre: -
    //post: si el arbol es valido -> error = false, total = numero de elementos mayores que min, else -> error = true
    //cost: es el coste de la funcion greater + la llamada (negligible)
    void gt(int & total, const string& min, bool& error){
        if(raiz != NULL){
            total = 0;
            error = false;
            greater(total, min, raiz);
        }
        else error = true;
    }
    
    
    //pre: -
    //post: si el arbol es valido -> error = false, total = numero de elementos inferiors que max, else -> error = true
    //cost: cota superior de log N para encontrar el primer menor que max + el coste de recorrer los b menores que el.
    void lesser(int& res, const string& min, nodo_rbst* x){
        if(x != NULL) {
            lesser(res, min, x->_izq);
            if(x->_k <= min){
                ++res;
                lesser(res, min, x->_der);
            }
        }
    }
    
    //pre: -
    //post: si el arbol es valido -> error = false, total = numero de elementos inferiors que max, else -> error = true
    //cost: es el coste de la funcion lesser + la llamada (negligible)
    void leq(int& res, const string& max, bool& error){
        if(raiz != NULL){
            res = 0;
            error = false;
            lesser(res, max, raiz);
        }
        else error = true;
    }
    
    //pre: -
    //post: si el arbol es valido -> error = false, total = numero de elementos mayores que min, else -> error = true
    //cost: cota superior de log N para encontrar el primer mayor + el coste de recorrer los b mayores que el.
    void greater(int& res, const string& max, nodo_rbst* x){
        if(x != NULL) {
            greater(res, max, x->_der);
            if (x->_k >= max){
                ++res;
                greater(res, max, x->_izq);
            }
        }
        
    }
    
    
    //pre: -
    //post: si el arbol contiene elementos -> error = false & res contiene un vector ordenado con los elementos comprendidos entre min y max, else error = true
    //cost: coste de la funcion interval + llamada (negligible)
    void between(vector<string>& res, const string& min, const string& max, bool& error){
        res.clear();
        error = false;
        if(raiz != NULL) interval(res, min, max, raiz);
        else error = true;
    }
    
    
    
    //pre: -
    //post: res contiene todos los elementos del rbst (total) mayores que min e inferiores que max
    //cost: log N para encontrar el primero mayo que min + recorrer los b nodos inferiores que max = (log N) + b
    void interval(vector<string>& res, const string& min, const string& max, nodo_rbst* x){
        if(x != NULL){
            if(x->_k >= min) interval(res, min, max, x->_izq);
            if(x->_k >= min and x->_k <= max)res.push_back(x->_k);
            if(x->_k <= max)interval(res, min, max, x->_der);
        }
    }
    
    
    //pre: -
    //post: si el arbol tiene elementos -> error = false & min es el elemento minimo del arbol, else error = true
    //cost: cota superior = altura del arbol (cota superior log N) si altura rbst = N
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
    
    
    //pre: -
    //post: si el arbol tiene elementos -> error = false & max es el elemento maximo del arbol, else error = true
    //cost: cota superior = altura del arbol (cota superior log N) si altura rbst = N
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
    
    
    //pre: -
    //post: res contiene todos los elementos del arbol rbst
    //cost: esta funcion es un recorrido en inorden del arbol asi que su coste es cota de N, siendo N el total de elementos
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
    
    //pre: el rbst no contiene x
    //post: el rbst contiene x
    //cost: coste de la funcion insert + llamada (negligible)
    void put(const string& x){
        bool insertat = false;
        raiz = insert(x, raiz,insertat);
    }
    
    
    
    
    //pre: -
    //post: el elemento x se inserta en el rbst
    //cost: coste de encontrar sitio para insertar + coste de insertarlo -> cota superior = altura arbol + coste insert_at_root
    nodo_rbst* insert(const string& x, nodo_rbst*& T, bool& insertat) {
        
        if(T == NULL) return insert_at_root(x,T,insertat);
        int  r;
        r = rand() % (T->N + 1);
        if(T->_k != x){
            if (r == T->N) return insert_at_root(x,T,insertat);
            if (x < T->_k) T->_izq = insert(x, T->_izq,insertat);
            else T->_der = insert(x, T->_der,insertat);
            if(insertat) ++T->N;
        }
        return T;
    }
    
    
    
    //pre: arbre no contiene x
    //post: devuelve un arbol t' cuya raiz es el elemento x a insertar y su hijo izquierdo son los elementos de arbre menos que x y el derecho los mayores
    //cost: coste de la llamada a faux + comprobacions y llamada (negligible)
    nodo_rbst* insert_at_root(const string& x, nodo_rbst* &arbre, bool& insertat ){
        nodo_rbst* ins_izq, *ins_der;
        ins_izq = ins_der = NULL;
        insertat = true;
        if(arbre != NULL) {
            final(x,arbre,ins_izq, ins_der);
        }
        nodo_rbst* nou = new nodo_rbst();
        nou->_izq = ins_izq;
        nou->_der = ins_der;
        nou->_k = x;
        nou->N = 1;
        if(nou->_izq != NULL) nou->N += nou->_izq->N;
        if(nou->_der != NULL) nou->N += nou->_der->N;
        return nou;
    }
    
    <<<<<<< HEAD
    void final(const string& x, nodo_rbst* &arbre, nodo_rbst*& ins_izq, nodo_rbst*& ins_der) {
        if(arbre != NULL) {
            nodo_rbst* ci = ins_izq;
            nodo_rbst* cd = ins_der;
            if(x > arbre->_k){
                if(ins_izq == NULL){ins_izq = arbre;}
                else {ins_izq->_der = arbre; ins_izq = ins_izq->_der;}
                nodo_rbst* aux =  arbre->_der;
                ins_izq->_der = NULL;
                final(x,aux,ins_izq,ins_der);
            }
            else {
                if(ins_der == NULL){ins_der = arbre;}
                else { ins_der->_izq = arbre; ins_der = ins_der->_izq;}
                nodo_rbst* aux = arbre->_izq;
                ins_der->_izq = NULL;
                final(x,aux,ins_izq,ins_der);
                
            }
            arbre->N = 1;
            if(arbre->_izq != NULL) arbre->N += arbre->_izq->N;
            if(arbre->_der != NULL) arbre->N += arbre->_der->N;
            if(ci != NULL) ins_izq = ci;
            if(cd != NULL) ins_der = cd;
        }
    }
    
    
    
    int counter(nodo_rbst* abc) {
        if(abc == NULL) return 0;
        else {
            abc->N = 1 + counter(abc->_izq) + counter(abc->_der);
            return abc->N;
        }
    }
    
    
    void delete_element(string x){
        bool seguir = false;
        find(x, seguir, raiz);
        if( seguir) raiz = findAndDelete(x,raiz);
        
    }
    
    
    //pre: elem es un elemento del rbst y x es valido
    //post: devuelve el arbol resultante de eliminar elem de x y reestructurarlo
    //cost coste de encontrar el elemento + coste de borrarlo y reestructurar el arbol = cota superior log N (altura rbst == log N) + coste de llamar a joinToDelete
    nodo_rbst* findAndDelete(string elem, nodo_rbst* x){
        if(x == NULL) return NULL;
        else {
            if (x->_k < elem) {x->_der = findAndDelete(elem, x->_der);--(x->N);}
            else if(x->_k > elem){ x->_izq = findAndDelete(elem, x->_izq);--(x->N);}
            else {
                nodo_rbst* aux;
                aux = joinToDelete(x->_izq, x->_der);
                delete x;
                x = aux;
                if(x!= NULL) counter(x);
            }
            return x;
        }
        
    }
    
    
    //pre: L i R son dos nodos validos del rbst
    //post: devuelve un nuevo nodo n' que es el resultado de unir L y R en un nuevo arbol
    //cost:
    nodo_rbst* joinToDelete(nodo_rbst* L, nodo_rbst* R){
        int m,n,r,total;
        m = n = 0;
        if (L != NULL) m = L->N;
        if(R != NULL) n = R->N;
        total = n + m;
        if (total == 0) return NULL;
        if(total == 1) r = 0;
        else { r = rand() % (total - 1);}
        if(r < m) {
            L->_der = joinToDelete(L->_der, R);
            return L;
        }
        else {
            R->_izq = joinToDelete(L,R->_izq);
            return R;
        }
    }
    
    //pre: -
    //post: string es el elemtno i-essimo si este es un indice valido, sino string es = "ERROR"
    //cost: es el coste de nthFunction mas su llamada que es negligible.
    string iessim(int i) {
        if(i < 1 or i > raiz->N) return "ERROR";
        else {
            return nthFunction(i,raiz,0);
        }
    }
    
    //pre: 	0 <= i < N, arbre es la raiz del arbol
    //post: string es la palabra i-essima del arbol
    //cost: cota superior (log N) suponiendo que en general el arbol tiene de altura log N
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
    
    //funcion de prueba auxiliar no usada en la entrega
    void escriuArbre(nodo_rbst* nodo) {
        if(nodo->_izq!= NULL) escriuArbre(nodo->_izq);
        
        // cout << nodo->N << ',' << ' ';
        
        if(nodo->_der != NULL) escriuArbre(nodo->_der);
    }
    
    //funcion de prueba auxiliar no usada en la entrega
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
