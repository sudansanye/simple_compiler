/*
* @Author: chenggh
* @Date: 2025-04-26
*/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// ===================================
#define KEY_NUM 2
#define MON_NUM 1
#define BO_NUM 2
// ===================================

class TOKEN{
public:
	TOKEN(char key, int i): key(key), p(i) {}
	char key;// 类型
	int p;// 指向表的第p项
};

extern const vector<string> KT;
// CT表
extern vector<int> CT;
// IT表
extern vector<string> IT;
// PT表
extern const vector<string> Monocular_Operator;
extern const vector<string> Delimiter;
extern const vector<string> PT;

// 工具函数

bool is_letter(char ch);
bool is_number(char ch);
bool is_PT(char ch);
// 函数声明
vector<TOKEN> scan(string &src);
void output(vector<TOKEN> t);
void show_all_token();