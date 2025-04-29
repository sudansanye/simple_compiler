/*
* @Author: chenggh
* @Date: 2025-04-26
*/
#include "lexical.hpp"
// 注释内容为文件输入
// 目前是终端输入 ctrl + c 终止

int main(){
	// ifstream file("test.txt");
	// if(!file.is_open()){
	// 	cout << "can`t open the test file!" << endl;
	// }
	string line;
	while(getline(cin, line)){
		// 终端输出的缓冲
		// int temp;
		// cin >> temp;
		vector<TOKEN> t = scan(line);
		// 输出格式1
		if(t.front().key == "ERROR") cout << "ERROR" << endl;
		else show_all_tokens(t);
	}
	// file.close();
	return 0;
}