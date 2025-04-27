/*
* @Author: chenggh
* @Date: 2025-04-27
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
using namespace std;
vector<char> w1 = {'+', '-'};
vector<char> w2 = {'*', '/'};
// 变量或者常数(词法分析做的，这里姑且1-4)
vector<char> word_i = {'1', '2', '3', '4'};
// 返回这个词在句子中的位置,已经读了第i位置并传过来

int F(string src, int i);
int E(string src, int i);
int T(string src, int i);


int F(string src, int i){
	for(auto &x: word_i){
		if(x == src[i]) return i + 1;
	}
	if(src[i] == '('){
		int pos = E(src, i + 1);
		if(src[pos] == ')') return pos + 1;
	}
	cout << "error_F" << endl;
	assert(false);
	return 0;
}
int T(string src, int i){
	int pos = F(src, i);
	while(1){
		int flag = 0;
		for(auto &x: w2){
			if(x != src[pos]) continue;
			flag = 1;
			break;
		}
		if(flag == 0) return pos;
		pos = F(src, pos + 1);
	}
	return 0;
}
int E(string src, int i){
	int pos = T(src, i);
	while(1){
		int flag = 0;
		for(auto &x: w1){
			if(x != src[pos]) continue;
			flag = 1;
			break;
		}
		if(flag == 0) return pos;
		pos = T(src, pos + 1);
	}
	return 0;
}

int main(){
	ifstream file("test.txt");
	if(!file.is_open()){
		cout << "can`t open the test file!" << endl;
	}
	string line;
	while(getline(file, line)){
		// 缓冲一下
		int temp; cin >> temp;
		// line是本行句子，0说明我已经读了第零位
		int pos = E(line, 0);
		if(line[pos] == '#') cout << "the sentence is legal" << endl;
		else cout << "error 0" << endl;
	}
	file.close();
	return 0;
}