#include <iostream>

using namespace std;

struct labyrinth{
	int size;
	string** grid;

	labyrinth(int size){
		this->size = 2*size + 1;
		grid = new string*[size];
		for (int i = 0; i < size; ++i){
			grid[i] = new string[size];
		}

		for (int i = 0; i < size; ++i){
			for (int j = 0; j < size; ++j){
				if((i==0 && j == 0) || (i==size-1 && j==0) || (i==0 && j==size-1) || (i==size-1 && j==size-1)){
					grid[i][j] = "+";			
				} else if(i==0 || i == size-1){
					grid[i][j] = "-";
				} else if(j==0 || j ==size-1){
					grid[i][j] = "|";
				} else{
					grid[i][j] = " ";
				}
			}
		}
	}
};

int main(){
	labyrinth lab = labyrinth(2);
	// cout<< lab.grid[0][0] << " ";
	// for (int i = 0; i < lab.size; ++i){
	// 	for (int j = 0; j < lab.size; ++j){
	// 		cout<< lab.grid[i][j] << " ";
	// 		if(j == lab.size - 1){
	// 			cout << endl;
	// 		}
	// 	}
	// }
}