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

    void double_array();
    void bubble_up(int i);
    void heap_insert(vertices p);
    void heapify(int i);
    vertices heap_extract();
    void permuta(int a, int b);
    void heap_update(vertices p, int peso, int cost);
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
    }/*
    cerr << "i = " << i << endl;
    cerr << "id = " << heap[i].id << endl;
    cerr << "peso = " << heap[i].peso << endl;
    cerr << "id2 = " << heap[(i-1)/2].id << endl;
    cerr << "peso2 = " << heap[(i-1)/2].peso << endl;*/
    while(i > 0 && heap[i].peso <= heap[(i-1)/2].peso){
        if(heap[i].peso == heap[(i-1)/2].peso){
            if(heap[i].cost < heap[(i-1)/2].cost){
                permuta(i,(i-1)/2);
            }
            i = (i -1)/2;
        } else {
            permuta(i,(i-1)/2);
            i = (i -1)/2;
        }
        permuta(i,(i-1)/2);
        
        i = (i -1)/2;/*
        cerr << "i = " << i << endl;
        cerr << "id = " << heap[i].id << endl;
        cerr << "peso = " << heap[i].peso << endl;
        cerr << "id2 = " << heap[(i-1)/2].id << endl;
        cerr << "peso2 = " << heap[(i-1)/2].peso << endl;*/
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
		heap_insert(p);
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

    void double_array();
    void bubble_up(int i);
    void heap_insert(vertices p);
    void heapify(int i);
    vertices heap_extract();
    void permuta(int a, int b);
    void heap_update(vertices p, int peso, int cost);
};

void vertices_heap_cost :: double_array(){
    tamanho = 2*tamanho;
    vertices* aux = new vertices[tamanho];
    for (int i = 0; i < index; ++i){
        aux[i] = heap[i];
    }

    //delete[] heap;
    heap = aux;
}

void vertices_heap_cost :: permuta(int a, int b){
    swap(heap[a], heap[b]);
    //vertices aux = heap[a];
    //heap[a] = heap[b];
    swap(pos[heap[a].id], pos[heap[b].id]);
    //heap[b] = aux;
}

void vertices_heap_cost :: bubble_up(int i = - 1){
    if(i == -1){
    	i = index - 1;
    }/*
    cerr << "i = " << i << endl;
    cerr << "id = " << heap[i].id << endl;
    cerr << "peso = " << heap[i].peso << endl;
    cerr << "id2 = " << heap[(i-1)/2].id << endl;
    cerr << "peso2 = " << heap[(i-1)/2].peso << endl;*/
    while(i > 0 && heap[i].cost <= heap[(i-1)/2].cost){
        if(heap[i].cost == heap[(i-1)/2].cost){
            if(heap[i].peso < heap[(i-1)/2].peso){
                permuta(i,(i-1)/2);
            }
            i = (i -1)/2;
        } else {
            permuta(i,(i-1)/2);
            i = (i -1)/2;
        }
        permuta(i,(i-1)/2);
        
        i = (i -1)/2;/*
        cerr << "i = " << i << endl;
        cerr << "id = " << heap[i].id << endl;
        cerr << "peso = " << heap[i].peso << endl;
        cerr << "id2 = " << heap[(i-1)/2].id << endl;
        cerr << "peso2 = " << heap[(i-1)/2].peso << endl;*/
    }
}

void vertices_heap_cost :: heap_insert(vertices p){
    if(index == tamanho){
        //double_array();
        return;
    }
    heap[index] = p;
    pos[p.id] = index;
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
	if(pos[p.id] == -1){
		heap_insert(p);
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
/*
struct distepre{
	int* d;
	vertices* f;	
};
/*
pair<int*, vertices*> dijkstra(grafo g, vertices v){
    int tamanho = g.qntVert;
    int* d = new int[tamanho]; 
    memset(d, -1, 4*tamanho);
    d[v.id] = 0; 
    vertices* f = new vertices[tamanho];
    vertices_heap heap = vertices_heap(tamanho);
   
    v.peso = 0;
    heap.heap_insert(v);
    cerr << v.id << endl;

    cerr << "criou tudo" << endl;

    //REVISE ISSOOOOOO!!!!!!!!!!!!!
    for (int i = 0; i < tamanho; ++i){
    	cerr << i << endl;
        vertices u = heap.heap_extract();
        cerr << u.id << endl;
        lista e = g.adjList[u.id];
        /*for(int j; j < e.index; j++){
        	cerr << j << ": " << e.vertice[j].id << endl;
        }

        for(int j = 0; j < e.index; j++){
        	if(d[e.vertice[j].id] == -1){
        		cerr << "entrou no -1" << endl;
        		d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
        		f[e.vertice[j].id] = u;
        		heap.heap_update(e.vertice[j], d[e.vertice[j].id]);
        	} else {
        		cerr << "entrou no else" << endl;
	            if(d[u.id]+e.vertice[j].peso < d[e.vertice[j].id]){
	            	cerr << "entrou no if do else" << endl;
	                d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
	                f[e.vertice[j].id] = u;
	                cerr << "heap update" << endl;
	                heap.heap_update(e.vertice[j], d[e.vertice[j].id]);
	                cerr << "saiu do heap update" << endl;
	            }
	        }
        }
    }
 	/*
    distepre result;
    result.d = d;
    result.f = f;
    

    return make_pair(d,f);
}*/

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
    heap.heap_insert(v);


    for (int i = 0; i < tamanho; ++i){
        vertices u = heap.heap_extract();
        lista e = g.adjList[u.id];

        for(int j = 0; j < e.index; j++){
        	if(d[e.vertice[j].id] == -1){
        		cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
        		d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
        		f[e.vertice[j].id] = u;
        		heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);
        	} else {
                if(d[u.id]+e.vertice[j].peso == d[e.vertice[j].id]){
                    if(cost[u.id] + e.vertice[j].peso*citycost[u.cidade] < cost[e.vertice[j].id]){
                        cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
                        d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
                        f[e.vertice[j].id] = u;
                        heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);    
                    }
                } else if(d[u.id]+e.vertice[j].peso < d[e.vertice[j].id]){
	            	cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
	                d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
	                f[e.vertice[j].id] = u;
	                
	                heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);
	                
	            }
	        }
        }
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
    heap.heap_insert(v);


    for (int i = 0; i < tamanho; ++i){
        vertices u = heap.heap_extract();
        lista e = g.adjList[u.id];

        for(int j = 0; j < e.index; j++){
        	if(cost[e.vertice[j].id] == -1){
        		cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
        		d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
        		f[e.vertice[j].id] = u;
        		heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);
        	} else {
        		if(cost[u.id] + e.vertice[j].peso*citycost[u.cidade] == cost[e.vertice[j].id]){
                    if(d[u.id]+e.vertice[j].peso < d[e.vertice[j].id]){
                        cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
                        d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
                        f[e.vertice[j].id] = u;
                        heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);    
                    }
                } else if(cost[u.id] + e.vertice[j].peso*citycost[u.cidade] < cost[e.vertice[j].id]){
	            	cost[e.vertice[j].id] = cost[u.id] + e.vertice[j].peso*citycost[u.cidade];
	                d[e.vertice[j].id] = d[u.id] + e.vertice[j].peso;
	                f[e.vertice[j].id] = u;
	                
	                heap.heap_update(e.vertice[j], d[e.vertice[j].id], cost[e.vertice[j].id]);
	                
	            }
	        }
        }
    }
 	

    return make_pair(d,cost);
}


/*
int main(){
	int n;
	cin >> n;

	grafo g = grafo(n);

	vertices v0 = vertices(0);
	vertices v1 = vertices(1);
	vertices v2 = vertices(2);
	vertices v3 = vertices(3);
	vertices v4 = vertices(4);
	vertices v5 = vertices(5);
	vertices v6 = vertices(6);

	g.grafo_insert(v1,v0,1);
	g.grafo_insert(v1,v2,1);
	g.grafo_insert(v1,v4,1);
	g.grafo_insert(v3,v4,0);
	g.grafo_insert(v5,v6,1);
	g.grafo_insert(v6,v3,1);
	g.grafo_insert(v6,v4,2);
	
	for(int i = 0; i < n; i++){
		cerr << "i: " << i << endl;
		for(int j = 0; j < g.adjList[i].index; j++){
			cerr << "id: " << g.adjList[i].vertice[j].id << endl;
			cerr << "peso: " << g.adjList[i].vertice[j].peso << endl;
		}
	}
	

	int* p;
	vertices* f;
	//distepre result;
	pair<int*,vertices*> result = dijkstra(g,v1);
	p = result.first;
	f = result.second;

	for (int i = 0; i < n; ++i){
		cerr << "vertice: " << i << endl;
		cerr << "distancia: " << p[i] << endl;
		cerr << "precursor: " << f[i].id << endl;
	}

}*/




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

    cerr << "grafo: " << endl;
    for (int i = 0; i < g.qntVert; ++i){
        cerr << "vertice [" << i << "]:" << endl;
        for (int j = 0; j < g.adjList[i].index; ++j){
            cerr << g.adjList[i].vertice[j].id << " ";
        } 
        cerr << endl;
    }

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

            cerr << "dist:" << endl;
            for(int i = 0; i < n; i++){
                cerr << "v[" << i << "]" << dist[i] << endl;
            }

            cerr << "cost:" << endl;
            for(int i = 0; i < n; i++){
                cerr << "v[" << i << "]" << cost[i] << endl;
            }
		} else if(comando == "UPDA"){
			int j, r;
			cin >> j >> r;
			tarifas[j] = r;

            cerr << "tarifas" << endl;
            for (int i = 0; i < n; ++i){
                cerr << i << tarifas[i] << endl;
            }
		}
	}


}