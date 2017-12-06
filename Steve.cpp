#include <iostream>

using namespace std;
// Norte = Descer e Sul = Subir

struct posHeightPath{
	int x;
	int y;
	int height;
	string path;
};

posHeightPath greedy(int x, int y, int** labyrinth){

}

int main(){
	int** labyrinth;
	int m;
	int height;

	cin >> m;

	labyrinth = new int*[2*m];
	for (int i = 0; i < 2*m; ++i){
		labyrinth[i] = new int[2*m];
	}

	for (int i = 0; i < 2*m; i++){
		for(int j = 0; j < 2*m; j++){
			labyrinth[i][j] = 0;
		}
	}

	for (int i = 0; i < 2*m; i+=2){
		for(int j = 0; j < 2*m; j+=2){
			cin >> height;
			labyrinth[i][j] = height;
		}
	}

	int w;

	for (int i = 0; i < w; ++i){
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if(x1 == x2){
			labyrinth[2*x1][2*y1 + 1] = -1;
		} else if (y1 == y2){
			labyrinth[2*x1 +1][2*y1] = -1;
		}
	}

	int r;
	cin >> r;

	int k;
	cin >> k;

	for (int i = 0; i < k; ++i){
		
	}
}