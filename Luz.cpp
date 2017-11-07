#include <iostream>

using namespace std;


struct vertices{
    int id;
    int peso;

    vertices(int id = -1, int peso = -1){
        this->id = id;
        this->peso = peso;
    }
};

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

struct fila{
    int* vertice;
    int front;
    int rear;
    int size;

    fila(int n = 1){
        vertice = new int[n];
        front = 0;
        rear = 0;
        size = n;
    }

    void list_double(){
        size *=2;
        int* aux = new int[size];
        for(int i = 0; i < size/2; i++){
            aux[i] = vertice[(front+i)%(size/2)];
        }
        front = 0;
        rear = size/2;
        
        delete[] vertice;
        vertice = aux;
    }

    void enqueue(int v){        
        vertice[rear] = v;
        rear = (rear+1)%size;
        
        if (rear == front){
            list_double();
        }
    }
    
    int dequeue(){
        if(rear == front){
            return -1;
        }
        
        int aux = front;
        front = (front+1)%size;
        
        return vertice[aux];
    }
};

struct edges{
    int a;
    int b;
    int peso;
    
    edges(int a = -1, int b = -1, int peso = -1){
        this->a = a;
        this->b = b;
        this->peso = peso;
    }
};

struct grafo{
    int qntVert;
    lista* adjList;
    edges* arestas;
    int index;
    int qntEdg;
    
    grafo(int n, int m){
        adjList = new lista[n]   ;
        qntVert = n;
        arestas = new edges[m];
        index = 0;
        qntEdg = m;
    }

    void grafo_insert(int a, int b, int peso){
        vertices va, vb;
        va = vertices(a, peso);
        vb = vertices(b, peso);
        adjList[a].list_insert(b);
        adjList[b].list_insert(a);

        arestas[index] = edges(a, b, peso);
        index++;
    }
};

struct disjointset{
    int *par;
    int n;
    int *rank;
    
    disjointset(int n){
        this->n = n;
        this->par = new int[n];
        this->rank = new int[n];
        
        for(int i = 0; i < n; i++){
            rank[i] = 0;
            par[i] = i;
        }
    }
    
    int find(int u){
        if(u != par[u]){
            par[u] = find(par[u]);
        }
        return par[u];
    }
    
    void merge(int x, int y){
        x = find(x), y = find(y);
        
        if(rank[x] > rank[y]){
            par[y] = x;
        } else {
            par[x] = y;
        }
        
        if(rank[x] == rank[y]){
            rank[y]++;
        }
    }
};


int partition(edges *arestas,int l,int r){
    int pivot;
    pivot = arestas[r].peso;  
    int i;
    i = (l-1);

    for (int j = l; j <= r-1; j++){
        if (arestas[j].peso <= pivot){
            i++;
            swap(arestas[i],arestas[j]);
        }
    }
    swap(arestas[i+1], arestas[r]);
    return (i + 1);
}

void quickSort(edges *arestas,int l,int r){
    if (l < r){
        int pivot;
        pivot = partition(arestas, l, r);

        quickSort(arestas, l, pivot - 1);
        quickSort(arestas, pivot + 1, r);
    }
}



int kruskal(grafo g){
    grafo a = grafo(g.qntVert, g.qntEdg);
    disjointset ds = disjointset(g.qntVert);
    int soma = 0;

    //cerr << "quickSort:" << endl;
    quickSort(g.arestas, 0, g.qntEdg-1);
    /*
    cerr << "Arestas pos:" << endl;
    for (int i = 0; i < g.qntEdg; ++i){
        cerr << g.arestas[i].a << " " << g.arestas[i].b << " " << g.arestas[i].peso << endl;
    }
    */
    for(int i = 0; i < g.qntEdg; i++){
        int u, v;
        u = g.arestas[i].a;
        v = g.arestas[i].b;
        if(ds.find(u) != ds.find(v)){
            soma += g.arestas[i].peso;
            ds.merge(u,v);
        }
    }

    return soma;
}
/*
int bfs_visit(grafo g, int s, bool *p){
    p[s] = true;

    fila queue = fila(g.qntVert);

    while(fila.front != fila.rear){

    }
}

int bfs(grafo g){
    bool* p = new bool[g.qntVert];
    int sum = 0;

    for(int i = 0; i < g.qntVert; i++){
        p[i] = false;
    }

    for(int i = 0; i < g.qntVert; i++){
        if(!p[i]){
            sum += bfs_visit(g, i, p);
        }
    }

    return sum;
}
*/

int shortest_path(grafo g, int s){
    int n = g.qntVert;
    int* dist = new int[n];
    int sum = 0;

    for(int i = 0; i < n; i++){
        dist[i] = -1;
    }

    dist[s] = 0;

    fila queue = fila(n);

    queue.enqueue(s);

    while(queue.front != queue.rear){
        int u = queue.dequeue();
        lista e = g.adjList[u];
        for(int i = 0; i < e.index; i++){
            int v = e.vertice[i].id;
            if(dist[v] == -1){
                dist[v] = dist[u] + 1;
                sum += dist[v];
                queue.enqueue(v);
            }
        }
    }

    return sum;
}

int main(){
    int n, m;

    cin >> n >> m;

    grafo g = grafo(n,m);

    int c, r;

    cin >> c >> r;

    for (int i = 0; i < m; ++i){
        int u, v, l;
        cin >> u >> v >> l;

        g.grafo_insert(u, v, l*c);
    }

    /*
    cerr << "Grafo: " << endl << "Arestas" << endl;
    for (int i = 0; i < m; ++i){
        cerr << g.arestas[i].a << " " << g.arestas[i].b << " " << g.arestas[i].peso << endl;
    }
    */

    int t1, t2;


    t1 = kruskal(g);
    t2 = shortest_path(g, 0)*r;

    cout << t1 << " " << t2 << endl;

    /*
    disjointset ds = kruskal(g);

    for(int i =0; i < n; i++){

        cerr << ds.par[i] << endl;
    }
    */
}

