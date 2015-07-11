#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <climits>
#include <chrono>
#include <random>


using namespace std;

string longestPrefix(string s1, string s2) {
	int n = min(s1.length(), s2.length());
	string pfx = "";
	for (int i = n; i >= 0; i--) {
		string tmp1 = s1.substr(0, i);
		string tmp2 = s2.substr(0, i);
		if (tmp1 == tmp2) {
			pfx = tmp1;
			break;
		}
	}
	
	return pfx;
}

/*vector<tuple<int,int>>*/void addUpTo100(vector<int> v) {
	vector<tuple<int,int>> ret;
	
	map<int,int> hash;
	for (auto i : v) {
		if (hash.count(i)) hash[i]++;
		else hash[i] = 1; 
	}
	
	for (auto i : v) {
		if (i == 50) {
			if (hash[i] > 1) {
				ret.push_back(tuple<int,int>(i,i));
				hash[i] -= 2;
			}
		} else if (hash[100 - i] /*&& hash.count(i)*/) {
			ret.push_back(tuple<int,int>(i, 100 - i));
			hash[i]--;
			hash[100 - i]--;
		}
	}
	/*
	for (auto kvp : hash) {
		cout << kvp.first << " : " << kvp.second << endl;
	}
	*/
	
	for (auto kvp : ret) {
		cout << get<0>(kvp) << " : " << get<1>(kvp) << endl;
	}
	//return ret;
}

void getRandomMaxElement(vector<int> v) {
	map<int,vector<int>> hash;
	
	int max = v[0];
	for (unsigned int i = 1; i < v.size(); i++) {
		if (v[i] >= max) {
			max = v[i];
			if (hash.count(max) == 0) hash[max] = vector<int>(); 
			hash[max].push_back(i);
		}
	}
	
	vector<int> tmp = hash[max];
	cout << max << endl;
	for (auto i : tmp) {
		cout << i << endl;
	}
}

//INCOMPLETE
void binaryAdd(string s1, string s2) {
	string ret = "";
	int carry = 0;
	
	for (int i1 = s1.length()-1, i2 = s2.length()-1; i1 >= 0 && i2 >= 0; i1--, i2--) {
		int digit1 = s1.c_str()[i1] - '0';
		int digit2 = s2.c_str()[i2] - '0';
		int res = carry + digit1 + digit2;
		if (res == 0 || res == 1) {
			//ret += itoa(res);
			carry = 0;
		} else if (res == 2) {
			ret += "0";
			carry = 1;
		} else {
			ret += "1";
			carry = 1;
		}	
	}
}

int recSum(vector<int> v) {
	if (v.size() == 0) return 0;
	int tmp = v.back();
	v.pop_back();
	return tmp + recSum(v);
}

int accSum(vector<int> v, int acc) {
	if (v.size() == 0) return acc;
	int tmp = v.back(); 
	v.pop_back();
	return accSum(v, acc + tmp);
}

int doAccSum(vector<int> v) {
	return accSum(v, 0);
}

template<typename T>
vector<T> myReverse(vector<T> v1, vector<T> v2) {
	if (v1.size() == 0) return v2;
	v2.push_back(v1.back());
	v1.pop_back();
	return myReverse(v1, v2);
}

void mostFrequentSubstring(vector<string> v, int k) {
	map<string,int> hash;
	
	for (auto s : v) {
		for (unsigned i = 1; i < s.length() - k; ++i) {
			string sub = s.substr(i, k);
			if (hash.count(sub) == 0) hash[sub] = 0;
			++hash[sub];
		}
	}
	
	//make sure substrings are present in all strings
	vector<tuple<string, int>> freq;
	for (auto it = hash.begin(); it != hash.end(); it++) {
		bool present = true;
		for (auto s: v) {
			//cout << it->first << ": " << s.find_first_of(it->first) << endl;
			if (s.find(it->first) == string::npos) {
				present = false;
				break;
			}
		}
		
		if (present) freq.push_back(tuple<string, int>(it->first, it->second));
	}
	
	sort(freq.begin(), freq.end(), [=](tuple<string, int> a, tuple<string, int> b) {
		return get<1>(a) > get<1>(b);
	}
	);
	
	for (auto val : freq) {
		cout << get<0>(val) << " : " << get<1>(val) << endl; 
	}
	
}

template<typename T>
void recPrintContents(vector<T> v) {
	if (v.size() == 0) return;
	auto tmp = v.back();
	v.pop_back();
	recPrintContents(v);
	cout << tmp << endl;
}

bool findBestFit(int required, vector<int> &capacities) {
	int min = INT_MAX;
	int min_index = -1;
	
	for (unsigned i = 0; i < capacities.size(); ++i) {
		if (capacities[i] >= required) {
			min = capacities[i] - required;
			min_index = i;
		}
	}
	
	if (min_index > -1) {
		capacities[min_index] = min;
		return true;
	}
	
	return false;
}

bool canSchedule(vector<int> required, vector<int> &capacities) {
	for (auto r : required) {
		bool tmp = findBestFit(r, capacities);
		
		#ifndef NDEBUG
		cout << r << " : " << tmp << endl;
		for (auto i : capacities) {
			cout << i << endl;
		}
		cout << "------------------" << endl;
		#endif
		
		if (!tmp) return false;
	}
	return true;
}

void getRandomMaxIndex(vector<int> v) {
	map<int, vector<int>> hash;
	
	int max = INT_MIN;
	for (unsigned i = 0; i < v.size(); ++i) {
		if (hash.count(v[i]) == 0) hash[v[i]] = vector<int>();
		hash[v[i]].push_back(i);
		if (v[i] > max) max = v[i];
	}
	
	for (auto i : hash[max]) {
		cout << i << endl;
	}
	
	unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine eng(seed);
	uniform_real_distribution<float> dist(0.0, (hash[max].size() - 1)/1.);
		
	int rand = round(dist(eng));
	cout << "Random Index: " << hash[max][rand] << endl;
	
}

typedef struct node {
    int freq;
    char data;
    node * left;
    node * right;
    
} node;

node *process(node *n, string s, int depth) {
    if (s[depth] == '0') {
        if (n->left) 
            return process(n->left, s, depth + 1);
    } else {
        if (n->right)
            return process(n->right, s, depth + 1);
    }

    node *ret = new node;
    ret->freq = depth;
    ret->data = n->data;
    return ret; 
}

void decode_huff(node *root, string s) {  
    if (!root) return;
    string ret = "";
    while (s.length()) {
        node *t = process(root, s, 0);
        char c = t->data;
        int i = t->freq;
        s = s.substr(i);
        ret += c;
    }

    cout << ret;
}

int main() {
	
	vector<int> capacities = {8, 16, 8, 32, 8};
	vector <int> required = {18, 4, 8, 4, 18, 6, 8, 18};
	
	getRandomMaxIndex(required);
	
	/*
	bool ret = canSchedule(required, capacities);
	
	cout << "success: " << ret << endl;
	
	for (auto i : capacities) {
		cout << i << endl;
	}
	*/
	
	/*
	void (*fp)(vector<int>) = recPrintContents;
	fp(vector<int>{1,2,3,4,5});
	
	vector<string> vec{"xyzabcdef","zabcd", "yzabcd", "abcd"};
	
	recPrintContents(vec);
	*/
	//mostFrequentSubstring(vec, 3);
	
	/*
	auto res = myReverse(vec, vector<string>());
	for (auto i : res) {
		cout << i << endl;
	}
	*/
	
	//cout << doAccSum(vector<int> {25,1,75,99,5,5}) << endl;
	
	//addUpTo100(vector<int> {25,1,75,99,5,5});
	
	//getRandomMaxElement(vector<int> {25,1,75,99,99,5,5});
	
	//binaryAdd("100111", "1111");
	
	//cout << longestPrefix("standby", "stand") << endl;
	
	return 0;
}