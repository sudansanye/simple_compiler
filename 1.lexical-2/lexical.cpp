/*
* @Author: chenggh
* @start-Date: 2025-04-26
*/

#include "lexical.hpp"
// ===================================1. 表 ====================================
// KT表
const vector<string> KT = {
	"int", "void", "break", "float", "while", "do", "struct", "const",
	"case", "for", "return", "if", "default", "else"
};
// PT表
const vector<string> PT{
	"-", "/", "(", ")", "==", "<=", "<", "+", "*", ">","=", ",", ";", "++", "{", "}"
};
// CT表
vector<string> C1T; // 常整数型
vector<string> C2T; // 常实数型
// 字符表
vector<string> ST; // 字符串常量
vector<char> CT;
// IT表
vector<string> IT;
// =============================================================================

bool is_letter(char ch) {return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');}
bool is_number(char ch) {return (ch >= '0' && ch <= '9');}
bool is_PT(char ch){return (!is_letter(ch) && !is_number(ch) && !is_blank(ch));}
bool is_blank(char ch) {return (ch == '\n' || ch == ' ');}
bool is_letter_and_num(char ch) {return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');}
bool is_number_all(char ch) {return is_number(ch) || ch == 'e' || ch == 'x' || ch == 'X' || ch == '-' || ch == '.'; }
bool is_number_16(char ch, int flag) {return (flag == 2) && (is_number(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F')); }
string number_deal_with(string num){
	if (num.size() >= 2 && num[0] == '0' && (num[1] == 'x' || num[1] == 'X')) {
        string hexStr = num.substr(2);
        if (hexStr.empty()) {
            return "0";
        }
        // 转换为十进制
        unsigned long hexValue = std::stoul(hexStr, nullptr, 16);
        return std::to_string(hexValue);
    }
	else return num;
}

vector<TOKEN> error_token(vector<TOKEN> ans){
	ans.clear();
	ans.push_back(TOKEN("ERROR", 0));
	return ans;
}


vector<TOKEN> scan(string &src){
	int p = 0;
	char ch; // 当前处理哪个字符
	ch = src[p++]; // 读取当前处理的字符
	// bool is_finish = false; // 当前扫描是否完成

	vector<TOKEN> ans; // 返回结果
	int P = src.size();
	while(p <= P){ // p是下一个该读的
		if(is_letter(ch)){ // 字母开头
			int flag = 0;
			string cur;
			while(is_letter_and_num(ch)){
				cur.push_back(ch);
				ch = src[p++];
			}
			// 开始翻译
			for(int i = 0, I = KT.size(); i < I; i++){
				if(cur != KT[i]) continue;
				// 查到了
				ans.push_back(TOKEN("K", i));
				flag = 1;
				break;
			}
			if(flag == 1) continue;
			// 没查到，查找用户定义标识符
			for(int i = 0, I = IT.size(); i < I; i++){
				if(cur != IT[i]) continue;
				flag = 1;
				ans.push_back(TOKEN("I", i));
				break;
			}
			if(flag == 1) continue;
			// 仍然没查到，新定义标识符
			ans.push_back(TOKEN("I", IT.size()));
			IT.push_back(cur);
		}
		else if(is_number(ch)){ // 数字开头
			string cur;
			int flag_kind = 0; // 整数
			while(is_number_all(ch) || is_number_16(ch, flag_kind)){
				if(!is_number(ch) && flag_kind != 2) flag_kind = 1;
				if(ch == 'x' || ch == 'X') flag_kind = 2;
				cur.push_back(ch);
				ch = src[p++];
			}
			if(is_letter(ch) && !is_number_all(ch)){
				ans = error_token(ans);
				return ans;
			}
			cur = number_deal_with(cur);
			if(flag_kind == 2) flag_kind = 0;
			if(flag_kind == 0){
				int flag_found = 0;
					for(int i = 0, I = C1T.size(); i < I; i++){
						if(cur != C1T[i]) continue;
						ans.push_back(TOKEN("C1", i));
						flag_found = 1;
						break;
					}
					if(flag_found == 1) continue;
					// 没找到
					ans.push_back(TOKEN("C1", C1T.size()));
					C1T.push_back(cur);
			}
			else if(flag_kind == 1){
				int flag_found = 0;
					for(int i = 0, I = C2T.size(); i < I; i++){
						if(cur != C2T[i]) continue;
						ans.push_back(TOKEN("C2", i));
						flag_found = 1;
						break;
					}
					if(flag_found == 1) continue;
					// 没找到
					ans.push_back(TOKEN("C2", C2T.size()));
					C2T.push_back(cur);
			}
		}
		// blank
		else if(is_blank(ch)) {
			// cout << "brank" << endl;
			ch = src[p++];
		}
		else if(ch == '\''){ // 期待是一个char
			ch = src[p++];
			char cur = ch;
			ch = src[p++];
			if(p > P || ch != '\''){
				ans = error_token(ans);
				return ans;
			}
			int flag = 0;
			for(int i = 0, I = CT.size(); i < I; i++){
				if(cur != CT[i]) continue;
				flag = 1;
				ans.push_back(TOKEN("C", i));
				break;
			}
			if(p < P) ch = src[p++];
			else p++;
			if(flag == 1) continue; // 找到了，往下走
			// 没找到
			ans.push_back(TOKEN("CT", CT.size()));
			CT.push_back(cur);
		}
		else if(ch == '\"'){ // 期待是一个string
			string cur;
			ch = src[p++];
			while(p <= P && ch != '\"'){
				// cout << p << ":" << src[p] << endl;
				cur.push_back(ch);
				ch = src[p++];
			}
			if(p > P){
				cout << p << endl;
				ans = error_token(ans);
				return ans;
			}
			int flag = 0;
			for(int i = 0, I = ST.size(); i < I; i++){
				if(cur != ST[i]) continue;
				flag = 1;
				ans.push_back(TOKEN("ST", i));
				break;
			}
			if(p < P) ch = src[p++];
			else p++;
			if(flag == 1) continue; // 找到了，往下走
			// 没找到
			ans.push_back(TOKEN("ST", ST.size()));
			ST.push_back(cur);
		}
		else{// 界符
			string cur;
			int flag = 0;
			cur.push_back(ch);
			if(p < P && is_PT(ch)){
				ch = src[p++];
			}
			int dou_flag = 0;
			if(p <= P && is_PT(ch)){
				if(is_PT(ch)){
					char pre = cur[0];
					switch (pre){
					case '=':{
						if(ch == '=') dou_flag = 1;
					}break;
					case '+':{
						if(ch == '+') dou_flag = 1;
					}break;
					default:
						break;
					}
					// cout << cur << dou_flag << ch << endl;
					if(dou_flag == 1) cur.push_back(ch);
				}
			}
			if(p < P) ch = src[p++];
			else p++;
			for(int i = 0, I = PT.size(); i < I; i++){
				if(cur != PT[i]) continue;
				ans.push_back(TOKEN("P", i));
				flag = 1;
				break;
			}
			if(flag == 1) continue;
			// 输入不合法 ===================================================================
			ans = error_token(ans);
			return ans;
		}
		if(ans.front().key == "ERROR"){
			return ans;
		}
	}
	return ans;
}


void show_all_tokens(vector<TOKEN> t){
	cout << "Token :";
	for(int i = 0, I = t.size(); i < I; i++){
		cout << "(" << t[i].key << " " << t[i].p + 1 << ")";
	}cout << endl;

	cout << "I :";
	for(int i = 0, I = IT.size(); i < I; i++){
		cout << IT[i];
		cout << " ";
	}cout << endl;

	cout << "C1 :";
	for(int i = 0, I = C1T.size(); i < I; i++){
		cout << C1T[i];
		cout << " ";
	}cout << endl;

	cout << "C2 :";
	for(int i = 0, I = C2T.size(); i < I; i++){
		cout << C2T[i];
		cout << " ";
	}cout << endl;

	cout << "CT :";
	for(int i = 0, I = CT.size(); i < I; i++){
		cout << CT[i];
		cout << " ";
	}cout << endl;

	cout << "ST :";
	for(int i = 0, I = ST.size(); i < I; i++){
		cout << ST[i];
		cout << " ";
	}cout << endl;

	return;
}