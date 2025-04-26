/*
* @Author: chenggh
* @start-Date: 2025-04-26
*/

#include "lexical.hpp"
// ===================================1. 表 ====================================
// KT表
const vector<string> KT = {
	"int", "char", "string"
};
// CT表
vector<int> CT;
// IT表
vector<string> IT;
// PT表
const vector<string> Monocular_Operator{
	"=", "+", "-"
};

const vector<string> Delimiter{
	",", "(", ")", "[", "]", "{", "}", "#"// 结束符
};

const vector<string> PT{
	"=", "+", "-"
};
// =============================================================================


bool is_letter(char ch) {return (ch >= 'a' && ch <= 'z');}
bool is_number(char ch) {return (ch >= '0' && ch <= '9');}
bool is_PT(char ch){return (!is_letter(ch) && !is_number(ch) && ch != '#');}


vector<TOKEN> scan(string &src){
	int p = 0;
	char ch; // 当前处理哪个字符
	ch = src[p++]; // 读取当前处理的字符
	bool is_finish = false; // 当前扫描是否完成

	vector<TOKEN> ans; // 返回结果
	while(!is_finish){
		// 读到结束符
		if(ch == '#') is_finish = true;
		else if(is_letter(ch)){ // 字母开头
			int flag = 0;
			string cur;
			while(is_letter(ch)){
				cur.push_back(ch);
				ch = src[p++];
			}
			// 开始翻译
			for(int i = 0, I = KT.size(); i < I; i++){
				if(cur != KT[i]) continue;
				// 查到了
				ans.push_back(TOKEN('k', i));
				flag = 1;
				break;
			}
			if(flag == 1) continue;
			// 没查到，查找用户定义标识符
			for(int i = 0, I = IT.size(); i < I; i++){
				if(cur != IT[i]) continue;
				flag = 1;
				ans.push_back(TOKEN('i', i));
				break;
			}
			if(flag == 1) continue;
			// 仍然没查到，新定义标识符
			ans.push_back(TOKEN('i', IT.size()));
			IT.push_back(cur);
		}
		else if(is_number(ch)){ // 数字开头
			int cur = 0;
			int flag = 0;
			while(is_number(ch)){
				cur = cur * 10 + (ch - '0');
				ch = src[p++];
			}
			for(int i = 0, I = CT.size(); i < I; i++){
				if(cur != CT[i]) continue;
				ans.push_back(TOKEN('c', i));
				flag = 1;
				break;
			}
			if(flag == 1) continue;
			// 没找到
			ans.push_back(TOKEN('c', CT.size()));
			CT.push_back(cur);
		}
		else if(ch == '\n' || ch == ' ') {
			cout << "brank" << endl;
			ch = src[p++];
		}
		else{// 界符
			string cur;
			int flag = 0;
			while(is_PT(ch) && ch != ' '){
				cur.push_back(ch);
				ch = src[p++];
			}
			for(int i = 0, I = PT.size(); i < I; i++){
				if(cur != PT[i]) continue;
				ans.push_back(TOKEN('p', i));
				flag = 1;
				break;
			}
			if(flag == 1) continue;
			// 输入不合法
			cout << "error" << endl;
			ans.push_back(TOKEN('i', IT.size()));
			IT.push_back("error");
			return ans;
		}
	}
	return ans;
}

ostream &operator<<(ostream &out, TOKEN t){
	char key = t.key;
	int p = t.p;
	string val;
	printf("key: [%c], p = [%d] val: ", key, p);
	switch (key){
		case 'k':{
			val = KT[p];
			cout << '[' << val << ']';
		}break;
		case 'i':{
			val = IT[p];
			cout << '[' << val << ']';
		}break;
		case 'c':{
			cout << '[' << CT[p] << ']';
		}break;
		case 'p':{
			val = PT[p];
			cout << '[' << val << ']';
		}break;
	}
	
	return out;
}
void output(vector<TOKEN> v){
	for(int i = 0, I = v.size(); i < I; i++){
		cout << i << "." << " " << v[i] << endl;
	}
	return;
}
