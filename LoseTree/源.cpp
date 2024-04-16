#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<algorithm>
#include"externalsort.h"
using namespace std;

void create_rand(int num) {
	srand((unsigned)time(NULL) * 10);
	ofstream out1;
	out1.open("D:\data_structure_data2\\data8\\data8.txt", ios::app | ios::out);
	ofstream file_writer("D:\data_structure_data2\\data8\\data8.txt", ios_base::out);
	int cnt = num;
	out1 << cnt << endl;
	for (int i = 0; i < cnt; i++) {
		int num = rand() % INT_MAX;
		out1 << num << " ";
	}
	out1.close();
	ifstream infile;
	infile.open("D:\data_structure_data2\\data8\\data8.txt", ios::in);
	out1.open("D:\data_structure_data2\\data8\\output.txt", ios::app | ios::out);
	ofstream file_writer1("D:\data_structure_data2\\data8\\output.txt", ios_base::out);
	infile >> num;
	int* temp = new int[num];
	for (int i = 0; i < num; i++)
		infile >> temp[i];
	sort(temp, temp + num);
	for (int i = 0; i < num; i++)
		out1<< temp[i]<<" ";
	delete[] temp;
}

int main() {
	int buffersize, K;
	string filename;
	cout << "是否使用随机数? 1 -yes   2 -no" << endl;
	int rd;
	cin >> rd;
	if (rd == 1) {
		cout << "生成随机数个数：" << endl;
		int num;
		cin >> num;
		filename = "data8";
		create_rand(num);
	}
	cout << "buffer大小为：" << endl;
	cin >> buffersize;
	cout << "几路归并：" << endl;
	cin >> K;
	if (rd == 2) {
		cout << "哪个文件：" << endl;
		cin >> filename;
	}
	externalsort<int> exs(buffersize,K);
	exs.sort(filename);
	exs.merge();
	cout << "访外存次数为：" << exs.get_visit_time() << endl;
}