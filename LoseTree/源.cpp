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
	cout << "�Ƿ�ʹ�������? 1 -yes   2 -no" << endl;
	int rd;
	cin >> rd;
	if (rd == 1) {
		cout << "���������������" << endl;
		int num;
		cin >> num;
		filename = "data8";
		create_rand(num);
	}
	cout << "buffer��СΪ��" << endl;
	cin >> buffersize;
	cout << "��·�鲢��" << endl;
	cin >> K;
	if (rd == 2) {
		cout << "�ĸ��ļ���" << endl;
		cin >> filename;
	}
	externalsort<int> exs(buffersize,K);
	exs.sort(filename);
	exs.merge();
	cout << "��������Ϊ��" << exs.get_visit_time() << endl;
}