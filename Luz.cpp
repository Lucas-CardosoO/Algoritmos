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
    vertices* vertice;
    int front;
    int rear;
    int size;

    fila(int n = 1){
        vertice = new vertices[n];
        front = 0;
        rear = 0;
        size = n;
    }

    void list_double(){
        size *=2;
        vertices* aux = new vertices[size];
        for(int i = 0; i < size/2; i++){
            aux[i] = vertice[(front+i)%(size/2)];
        }
        front = 0;
        rear = size/2;
        
        delete[] vertice;
        vertice = aux;
    }

    void queue_push(vertices v){        
        vertice[rear] = v;
        rear = (rear+1)%size;
        
        if (rear == front){
            list_double();
        }
    }
    
    vertices queue_pop(){
        if(rear == front){
            return vertices();
        }
        
        int aux = front;
        front = (front+1)%size;
        
        return vertice[aux];
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

struct node{
    int *par;
    int n;
    int *rank;
    
    node(int n){
        this->n = n;
        this->par = new int[n+1];
        this->rank = new int[n+1];
        
        for(int i = 0; i < n+1; i++){
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

edges* kruskal(){


}

int main(){
    fila queue = fila();
    
    for(int i = 0; i < 10; i++){
        vertices v = vertices(i);
        queue.queue_push(v);
    }
    for(int i = 0; i < 3; i++){
        queue.queue_pop();
    }
    for(int i = 10; i < 19; i++){
        vertices v = vertices(i);
        queue.queue_push(v);
    }
    int front = queue.front;
    int rear = queue.rear;
    while(front != rear){
        cout << queue.vertice[front].id << endl;
        front = (front+1)%queue.size;
    }
}

