#include <iostream>

using namespace std;
// Norte = Descer e Sul = Subir; Leste-Direira; Oeste-Esquerda

struct posHeightPath{
	int x;
	int y;
	int height;
	string path;

	posHeightPath(int x, int y, int height, string path){
		this->x = x;
		this->y = y;
		this->height = height;
		this->path = path;
	}

};

posHeightPath greedy(int x, int y, int** labyrinth, int size){
	string path = "";
	while(true){
		int height = 0, heightN = 0, heightS = 0, heightL = 0, heightO = 0;
		int xbig = x, ybig = y;
		height = labyrinth[2*x][2*y];
		//Norte
		if((x != size - 1) && (labyrinth[2*x+1][2*y] != -1)){
			heightN = labyrinth[2*x+2][2*y];
		}
		//Leste
		if((y != size - 1) && (labyrinth[2*x][2*y+1] != -1)){
			heightL = labyrinth[2*x][2*y+2];
		}
		//Sul
		if((x != 0) && (labyrinth[2*x-1][2*y] != -1)){
			heightS = labyrinth[2*x-2][2*y];
		}
		//Oeste
		if((y != 0) && (labyrinth[2*x][2*y-1] != -1)){
			heightO = labyrinth[2*x][2*y-2];
		}

		if ((heightN > height) && (heightN >= heightL) && (heightN >= heightO) && (heightN >= heightS)){
			x = x+1;
			y = y;
			path = path + "N";
		} else if((heightL > height) && (heightL >= heightO) && (heightL >= heightS)){
			x = x;
			y = y+1;
			path = path + "L";
		} else if ((heightS > height) && (heightS >= heightO)){
			x = x-1;
			y = y;
			path = path + "S"
		} else if(heightO > height){
			x = x;
			y = y-1;
			path = path + "O";
		} else {
			return posHeightPath(x, y, height, path);
		}

	}
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