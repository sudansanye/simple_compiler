/*
* @Author: chenggh
* @Date: 2025-04-26
*/
#include "lexical.hpp"

int main(){
	ifstream file("test.txt");
	if(!file.is_open()){
		cout << "can`t open the test file!" << endl;
	}
	string line;
	while(getline(file, line)){
		int temp;
		cin >> temp;
		vector<TOKEN> t = scan(line);
		output(t);
	}
	file.close();
	// show_all_tokens();

	return 0;
}