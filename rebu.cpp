#include <iostream>
#include <cstring>

using namespace std;

struct vertices{
    int id;
    int peso;
    int cidade;
    int cost;

    vertices(int id = -1, int peso = -1, int cidade = -1, int cost = -1){
        this->id = id;
        this->peso = peso;
        this->cidade = cidade;
        this->cost = cost;
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

    void bubble_up(int i);
    void heap_insert(vertices p, int peso, int cost);
    void heapify(int i);
    vertices heap_extract();
    void permuta(int a, int b);
    void heap_update(vertices p, int peso, int cost);
};



void vertices_heap :: permuta(int a, int b){
    swap(pos[heap[a].id], pos[heap[b].id]);
    swap(heap[a], heap[b]);
}

void vertices_heap :: bubble_up(int i = - 1){
    if(i == -1){
    	i = index - 1;
    }

    while(i > 0 && heap[i].peso <= heap[(i-1)/2].peso){
        if(heap[i].peso == heap[(i-1)/2].peso){
            if(heap[i].cost < heap[(i-1)/2].cost){
                permuta(i,(i-1)/2);
                i = (i -1)/2;
            } else{
                break;
            }
        } else {
            permuta(i,(i-1)/2);
            i = (i -1)/2;
        }

    }
}

void vertices_heap :: heap_insert(vertices p, int peso, int cost){

    heap[index] = p;
    pos[p.id] = index;
    heap[pos[p.id]].peso = peso;
    heap[pos[p.id]].cost = cost;
    index++;
    bubble_up();
}

void vertices_heap :: heapify(int i){
    int l = 2*i + 1;
    int r = 2*i + 2;
    int m = i;

    if(l < index && heap[l].peso <= heap[m].peso){
        if(heap[l].peso == heap[m].peso){
            if(heap[l].cost < heap[m].cost){
                m = l;
            }
        } else {
            m = l;
        }
    }

    if(r < index && heap[r].peso <= heap[m].peso){
        if(heap[r].peso == heap[m].peso){
            if(heap[r].cost < heap[m].cost){
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
void vertices_heap :: heap_update(vertices p, int peso, int cost){
	if(pos[p.id] == -1){
		heap_insert(p, peso, cost);
	} else {
        heap[pos[p.id]].cost = cost;
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
        for(int i = 0; i < index; i++){
        	aux[i] = vertice[i];
        }
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

struct vertices_heap_cost{
    vertices* heap;
    int* pos;
    int index;
    int tamanho;

    vertices_heap_cost(int tamanho){
        index = 0;
        this->tamanho = tamanho;
        pos = new int[tamanho];
        memset(pos, -1, 4*tamanho); //tamanho*4
        heap = new vertices[tamanho];
    }

    void bubble_up(int i);
    void heap_insert(vertices p, int peso, int cost);
    void heapify(int i);
    vertices heap_extract();
    void permuta(int a, int b);
    void heap_update(vertices p, int peso, int cost);
};


void vertices_heap_cost :: permuta(int a, int b){
    swap(pos[heap[a].id], pos[heap[b].id]);
    swap(heap[a], heap[b]);
}

void vertices_heap_cost :: bubble_up(int i = - 1){
    if(i == -1){
    	i = index - 1;
    }
    while(i > 0 && heap[i].cost <= heap[(i-1)/2].cost){
        if(heap[i].cost == heap[(i-1)/2].cost){
            if(heap[i].peso < heap[(i-1)/2].peso){
                permuta(i,(i-1)/2);
                i = (i -1)/2;
            } else{
                break;
            }
        } else {
            permuta(i,(i-1)/2);
            i = (i -1)/2;
        }
    }
}

void vertices_heap_cost :: heap_insert(vertices p, int peso, int cost){
    heap[index] = p;
    pos[p.id] = index;
    heap[pos[p.id]].peso = peso;
    heap[pos[p.id]].cost = cost;
    index++;
    bubble_up();
}

void vertices_heap_cost :: heapify(int i){
    int l = 2*i + 1;
    int r = 2*i + 2;
    int m = i;

    if(l < index && heap[l].cost <= heap[m].cost){
        if(heap[l].cost == heap[m].cost){
            if(heap[l].peso < heap[m].peso){
                m = l;
            }
        } else {
            m = l;
        }
    }

    if(r < index && heap[r].cost <= heap[m].cost){
        if(heap[r].cost == heap[m].cost){
            if(heap[r].peso < heap[m].peso){
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

vertices vertices_heap_cost :: heap_extract(){
    index--;
    vertices r = heap[0];
    permuta(0, index);
    pos[r.id] = -1;
    heapify(0);
    return r;
}
void vertices_heap_cost :: heap_update(vertices p, int peso, int cost){
	//heap_insert(p);
    if(pos[p.id] == -1){
        heap_insert(p, peso, cost);
	} else {
        heap[pos[p.id]].peso = peso;
		heap[pos[p.id]].cost = cost;
		bubble_up(pos[p.id]);
	}
}


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


pair<int*, int*> dijkstra_short(grafo g, vertices v, int* citycost){
    int tamanho = g.qntVert;
    int* d = new int[tamanho];
    int* cost = new int[tamanho];
    memset(d, -1, 4*tamanho);
    memset(cost, -1, 4*tamanho);
    d[v.id] = 0;
    cost[v.id] = 0;
    vertices* f = new vertices[tamanho];
    vertices_heap heap = vertices_heap(tamanho);
   
    v.peso = 0;
    heap.heap_insert(v, 0, 0);


    for (int i = 0; i < tamanho; ++i){
        vertices u = heap.heap_extract();
        lista e = g.adjList[u.id];

        for(int j = 0; j < e.index; j++){
        	if(d[e.vertice[j].id] == -1 || d[u.id]+e.vertice[j].peso < d[e.vertice[j].id]){
        		cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
        		d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
        		f[e.vertice[j].id] = u;
        		heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);
        	} else if(d[u.id]+e.vertice[j].peso == d[e.vertice[j].id]){
                if(cost[u.id] + e.vertice[j].peso*citycost[u.cidade] < cost[e.vertice[j].id]){
                    cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
                    d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
                    f[e.vertice[j].id] = u;
                    heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);    
                }   
	        }
        }
    }

    for (int i = 0; i < heap.index; ++i){
        cerr << i << ": " << heap.heap[i].id << endl;
    }
 	

    return make_pair(d,cost);
}

pair<int*, int*> dijkstra_cheap(grafo g, vertices v, int* citycost){
    int tamanho = g.qntVert;
    int* d = new int[tamanho];
    int* cost = new int[tamanho];
    memset(d, -1, 4*tamanho);
    memset(cost, -1, 4*tamanho);
    d[v.id] = 0;
    cost[v.id] = 0;
    vertices* f = new vertices[tamanho];
    vertices_heap_cost heap = vertices_heap_cost(tamanho);
   
    v.peso = 0;
    heap.heap_insert(v, 0, 0);


    for (int i = 0; i < tamanho; ++i){
        vertices u = heap.heap_extract();
        lista e = g.adjList[u.id];

        for(int j = 0; j < e.index; j++){
        	if(cost[e.vertice[j].id] == -1 || cost[u.id] + e.vertice[j].peso*citycost[u.cidade] < cost[e.vertice[j].id]){
        		cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
        		d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
        		f[e.vertice[j].id] = u;
        		heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);
        	} else if(cost[u.id] + e.vertice[j].peso*citycost[u.cidade] == cost[e.vertice[j].id]){
                if(d[u.id]+e.vertice[j].peso < d[e.vertice[j].id]){
                    cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
                    d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
                    f[e.vertice[j].id] = u;
                    heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);    
                }  
	        }
        }
    }

    for (int i = 0; i < heap.index; ++i){
        cerr << i << ": " << heap.heap[i].id << endl;
    }
 	

    return make_pair(d,cost);
}


int main(){
	int m;

	cin >> m;

	int* tarifas = new int[m];

	for (int i = 0; i < m; ++i){
		cin >> tarifas[i];
	}

	int n;

	cin >> n;

	vertices* vertice = new vertices[n];
	grafo g = grafo(n);
	
	for(int i = 0; i < n; i++){
		int q;
		cin >> q;
		vertices v = vertices(i);
		v.cidade = q;
		vertice[i] = v;
	}

	int w;

	cin >> w;

	for (int i = 0; i < w; ++i){
		int x, y, z;

		cin >> x >> y >> z;

		g.grafo_insert(vertice[x], vertice[y], z);
	}

    /*cerr << "grafo: " << endl;
    for (int i = 0; i < g.qntVert; ++i){
        cerr << "vertice [" << i << "]:" << endl;
        for (int j = 0; j < g.adjList[i].index; ++j){
            cerr << g.adjList[i].vertice[j].id << " ";
        } 
        cerr << endl;
    }*/

	string comando;

	while(cin >> comando){
		if(comando == "RIDE"){
			int c, d;
			char o;
			cin >> c >> d >> o;

			int* dist;
			int* cost;
			if(o == 'S'){
							
				pair<int*,int*> result = dijkstra_short(g,vertice[c], tarifas);
				dist = result.first;
				cost = result.second;
						

			} else if(o == 'E'){
				pair<int*,int*> result = dijkstra_cheap(g,vertice[c], tarifas);
				dist = result.first;
				cost = result.second;
			}

			cout << dist[d] << " " << cost[d] << endl;

            /*cerr << "dist:" << endl;
            for(int i = 0; i < n; i++){
                cerr << "v[" << i << "]" << dist[i] << endl;
            }

            cerr << "cost:" << endl;
            for(int i = 0; i < n; i++){
                cerr << "v[" << i << "]" << cost[i] << endl;
            }*/
		} else if(comando == "UPDA"){
			int j, r;
			cin >> j >> r;
			tarifas[j] = r;

            /*cerr << "tarifas" << endl;
            for (int i = 0; i < n; ++i){
                cerr << i << tarifas[i] << endl;
            }*/
		}
	}


}