/*
* @Author: chenggh
* @Date: 2025-04-26
*/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ===================================
#define KEY_NUM 2
#define MON_NUM 1
#define BO_NUM 2
// ===================================

class TOKEN{
public:
	TOKEN(string key, int i): key(key), p(i) {}
	string key;// 类型
	int p;// 指向表的第p项
};

extern const vector<string> KT;
// CT表
extern vector<string> C1T; // 常整数型
extern vector<string> C2T; // 常实数型
// 字符表
extern vector<string> ST; // 字符串常量
extern vector<char> CT;
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
bool is_blank(char ch);
bool is_letter_and_num(char ch);
bool is_number_all(char ch);
string number_deal_with(string num);
// 函数声明
vector<TOKEN> scan(string &src);
void output(vector<TOKEN> t);
void show_all_tokens(vector<TOKEN> t);