#include <iostream>
#include <cstring>

using namespace std;

struct vertices{
    int id;
    int peso;
    int cidade;

    vertices(int id = -1, int peso = -1, int cidade = -1){
        this->id = id;
        this->peso = peso;
        this->cidade = cidade;
    }
};

struct vertices_heap{
    vertices* heap;
    int* pos;
    int index;
    int tamanho;

    vertices_heap(int tamanho){
        index = 0;
        this->tamanho = tamanho;
        pos = new int[tamanho];
        memset(pos, -1, 4*tamanho); //tamanho*4
        heap = new vertices[tamanho];
    }

    void double_array();
    void bubble_up(int i);
    void heap_insert(vertices p);
    void heapify(int i);
    vertices heap_extract();
    void permuta(int a, int b);
    void heap_update(vertices p, int peso);
};

void vertices_heap :: double_array(){
    tamanho = 2*tamanho;
    vertices* aux = new vertices[tamanho];
    for (int i = 0; i < index; ++i){
        aux[i] = heap[i];
    }

    //delete[] heap;
    heap = aux;
}

void vertices_heap :: permuta(int a, int b){
    swap(heap[a], heap[b]);
    //vertices aux = heap[a];
    //heap[a] = heap[b];
    swap(pos[heap[a].id], pos[heap[b].id]);
    //heap[b] = aux;
}

void vertices_heap :: bubble_up(int i = - 1){
    if(i == -1){
    	i = index - 1;
    }
    cerr << "i = " << i << endl;
    cerr << "id = " << heap[i].id << endl;
    cerr << "peso = " << heap[i].peso << endl;
    cerr << "id2 = " << heap[(i-1)/2].id << endl;
    cerr << "peso2 = " << heap[(i-1)/2].peso << endl;
    while(i > 0 && heap[i].peso <= heap[(i-1)/2].peso){
        /*if(heap[i].peso == heap[(i-1)/2].peso){
            if(heap[i].id < heap[(i-1)/2].id){
                permuta(i,(i-1)/2);
            }
            i = (i -1)/2;
        } else {
            permuta(i,(i-1)/2);
            i = (i -1)/2;
        }*/
        permuta(i,(i-1)/2);
        i = (i -1)/2;
        cerr << "i = " << i << endl;
        cerr << "id = " << heap[i].id << endl;
        cerr << "peso = " << heap[i].peso << endl;
        cerr << "id2 = " << heap[(i-1)/2].id << endl;
        cerr << "peso2 = " << heap[(i-1)/2].peso << endl;
    }
}

void vertices_heap :: heap_insert(vertices p){
    if(index == tamanho){
        //double_array();
        return;
    }
    heap[index] = p;
    pos[p.id] = index;
    index++;
    bubble_up();
}

void vertices_heap :: heapify(int i){
    int l = 2*i + 1;
    int r = 2*i + 2;
    int m = i;

    if(l < index && heap[l].peso <= heap[m].peso){
        if(heap[l].peso == heap[m].peso){
            if(heap[l].id < heap[m].id){
                m = l;
            }
        } else {
            m = l;
        }
    }

    if(r < index && heap[r].peso <= heap[m].peso){
        if(heap[r].peso == heap[m].peso){
            if(heap[r].id < heap[m].id){
                m = r;
            }
        } else {
            m = r;
        }
    }

    if(m != i){
        permuta(m, i);
        heapify(m);
    }
}

vertices vertices_heap :: heap_extract(){
    index--;
    vertices r = heap[0];
    permuta(0, index);
    pos[r.id] = -1;
    heapify(0);
    return r;
}
void vertices_heap :: heap_update(vertices p, int peso){
	if(pos[p.id] == -1){
		heap_insert(p);
	} else {
		heap[pos[p.id]].peso = peso;
		bubble_up(pos[p.id]);
	}
}

struct lista{
    vertices* vertice;
    int index;
    int tamanho;

    lista(int n = 1){
        vertice = new vertices[n];
        index = 0;
        tamanho = n;
    }

    void list_double(){
        tamanho *=2;
        vertices* aux = new vertices[tamanho];
        delete[] vertice;
        vertice = aux;
    }

    void list_insert(vertices v){
        if (index == tamanho){
            list_double();
        }
        vertice[index] = v;
        index++;
    }
};

struct grafo{
    int qntVert;
    lista* adjList;

    grafo(int n){
        adjList = new lista[n]   ;
        qntVert = n;
    }

    void grafo_insert(vertices a, vertices b, int peso){
        a.peso = peso;
        b.peso = peso;
        adjList[a.id].list_insert(b);
        adjList[b.id].list_insert(a);
    }
};

pair<int*, vertices*> dijkstra(grafo g, vertices v){
    int tamanho = g.qntVert;
    int* d = new int[tamanho]; 
    memset(d, -1, 4*tamanho);
    d[v.id] = 0; 
    vertices* f = new vertices[tamanho];
    vertices_heap heap = vertices_heap(tamanho);
    
    v.peso = 0;
    heap.heap_insert(v);


    //REVISE ISSOOOOOO!!!!!!!!!!!!!
    for (int i = 0; i < tamanho; ++i){
        vertices u = heap.heap_extract();
        lista e = grafo.adjList[u.id];

        for(int i = 0; i < e.index; i++){
            if(d[u.id]+e[i].peso < d[e[i].id]){
                d[e[i].id] = d[u.id] + e[i].peso;
                f[e[i].id] = u;
                heap_update(e[i], d[e[i].id]);
            }
        }
    }


    return make_pair(d, p);
}




/*int main(){
	int n;
	cin >> n;
	vertices_heap heap = vertices_heap(n);

	for(int i = 0; i < n; i++){
		cout << heap.heap[i].id << endl;
	}

    for(int i = 0; i < n; i++){        
        cerr << i << ": " << heap.pos[i] << endl;
    }

	vertices vertice1 = vertices(0, 1, 1);
	vertices vertice2 = vertices(1, 2, 1);
	vertices vertice3 = vertices(2, 3, 1);
	vertices vertice4 = vertices(3, 4, 1);

	heap.heap_insert(vertice1);
    cerr << "pos1: " << endl;
    for(int i = 0; i < n; i++){        
        cerr << i << ": " << heap.pos[i] << endl;
    }  

	heap.heap_insert(vertice2);
    cerr << "pos2: " << endl;
    for(int i = 0; i < n; i++){        
        cerr << i << ": " << heap.pos[i] << endl;
    }   
	heap.heap_insert(vertice3);
    cerr << "pos3: " << endl;
    for(int i = 0; i < n; i++){        
        cerr << i << ": " << heap.pos[i] << endl;
    }   
	heap.heap_insert(vertice4);
    cerr << "pos4: " << endl;
    for(int i = 0; i < n; i++){        
        cerr << i << ": " << heap.pos[i] << endl;
    }   

    cerr << "heap inicial: " << endl;
	for(int i = 0; i < n; i++){
		cout << heap.heap[i].id << endl;
	}

    cerr << "heap final: " << endl;
	heap.heap_extract();
	for(int i = 0; i < n; i++){
		cerr << heap.heap[i].id << endl;
	}

    cerr << "pos: " << endl;
	for(int i = 0; i < n; i++){        
		cerr << i << ": " << heap.pos[i] << endl;
	}

    heap.heap_update(vertice3, 0);	

    cerr << "heap update: " << endl;
    for(int i = 0; i < n; i++){
        cerr << heap.heap[i].id << endl;
    }

    cerr << "pos: " << endl;
    for(int i = 0; i < n; i++){        
        cerr << i << ": " << heap.pos[i] << endl;
    }
}*/

