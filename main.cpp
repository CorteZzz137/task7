#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

void trim_right(string& s){
	if(s.size()>=1)
	while (*(s.end()-1) == ' ')
		s.erase(s.size() - 1, 1);
}

void trim_left(string& s) {
	if (s.size() >= 1)
		while (*(s.begin()) == ' ')
			s.erase(s.begin());
}

struct diag {
	int len = 0;
	long long sum = 0;
	long long max = -1;
	int n;
};

bool comp(diag& a, diag& b) {
	if (a.len < b.len)
		return true;
	else if (a.len == b.len) {
		if (a.sum < b.sum)
			return true;
		else if (a.sum == b.sum) {
			return a.max < b.max;
		}
		else
			return false;

	}
	else
		return false;



}

void task7_1() {
	setlocale(LC_ALL, "Rus.1251");
	ifstream fin("in1.txt");
	int n;
	fin >> n;
	string s, tmp;
	getline(fin, s);
	map<string, vector<string>> a;
	vector<string> words;

	for (int i = 0; i < n; i++) {
		getline(fin, s);
		regex reg("[a-zA-Zà-ÿÀ-ß]+");
		for (sregex_token_iterator it(begin(s), end(s), reg), last; it != last; ++it) {
			words.push_back(it->str());
		}
		for (int j = words.size() - 1; j >= 1; j--) {
			a[words[j]].push_back(words[0]);
		}
		words.clear();
	}
	cout << a.size() << endl;
	for (auto& i : a) {
		cout << i.first << " - ";
		for (auto j = i.second.begin(); j != i.second.end(); j++) {
			if (j == i.second.end() - 1)
				cout << *j << endl;
			else {
				cout << *j << ", ";
			}
		}
	}
	fin.close();
}

void task7_2() {
	setlocale(LC_ALL, "Rus.1251");
	ifstream fin("in2.txt");
	ofstream fout("out2.txt");
	string s;
	getline(fin, s);
	trim_right(s);
	vector<string> roles;
	if (s == "roles:") {
		getline(fin, s);
		trim_right(s);
		while (s != "textLines:") {
			
			roles.push_back(s);
			getline(fin, s);
			trim_right(s);
		}
	}
	int i = 1;
	map<string, vector<pair<int, string>>> a;
	while (!fin.eof()) {
		getline(fin, s);
		trim_right(s);
		if (s.find(":") != string::npos) {
			string tmp = s;
			tmp.erase(s.find(":"), s.size()-s.find(":"));
			s.erase(0, s.find(":")+1);
			trim_left(s);
			a[tmp].push_back(make_pair(i, s));
			i++;
		}
	}
	for (auto& i : roles) {
		
		fout << i << ":" << endl;
		for (auto& j : a[i]) {
			fout << j.first << ") " << j.second << endl;
		}
		fout << endl;
	}

	fin.close();
	fout.close();



}

void task7_3() {
	setlocale(LC_ALL, "Rus.1251");
	ifstream fin("in3.txt");
	int n, m;
	long long tmp;
	fin >> n >> m;
	vector<diag> a(n+m-1);
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			fin >> tmp;
			cout << tmp << " ";
			a[i + j].len++;
			a[i + j].sum += tmp;
			a[i + j].max = max(a[i + j].max, tmp);
			a[i + j].n = i + j + 1;


		}
		cout << endl;
	}
	
	sort(a.begin(), a.end(), comp);
	for (auto& i : a) {
		cout << "Äèàãîíàëü " << i.n << ": äëèíà - " << i.len << ", ñóììà - " << i.sum << ", ìàêñèìóì - " << i.max << endl;
	}

	fin.close();



}

int main() {
	task7_1();
	return 0;
}

//4 3
//18 16 13 5
//3 2 4 8
//6 23 11 15


//ÐÀÇÎÁÐÀÒÜÑß Ñ ÏÐÎÁÅËÀÌÈ Â ÊÎÍÖÅ!!!


//apple - malum, pomum, popula