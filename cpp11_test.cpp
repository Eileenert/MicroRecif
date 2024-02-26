#include <iostream>
#include <vector>

using namespace std;

int main()
{
		vector<vector<double>> matrice { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
		
		cout << "Bonjour, voici une matrice:" << endl;
		for (auto element : matrice){
			for (auto val : element) {
				cout << val << " ";
		}
		cout << endl;
	}
		
		return 0;
}
