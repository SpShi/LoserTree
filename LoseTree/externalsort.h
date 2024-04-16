#pragma once
#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<queue>
#include<vector>
#include"LoseTree.h"
#include"LoseTree.cpp"
using namespace std;
template<class T>
struct seg_member {
	int seg_id;
	T value;
	seg_member() {}
	~seg_member() {}
	bool operator <(const seg_member& s) const {
		return value < s.value;
	}
	bool operator >(const seg_member& s) const {
		return value > s.value;
	}
	bool operator <=(const seg_member& s) const {
		return value <= s.value;
	}
};
struct ele {
	int id;//˳����
	int key;//ֵ
	bool operator<=(const ele& ss) const {//˳����С�Ļ�ʤ��˳������ͬʱԪ��С�Ļ�ʤ
		if (id != ss.id) {
			return id < ss.id;
		}
		else {
			return key < ss.key;
		}
	}
}player[200000];
struct to_be_merge {
	int start;
	int end;
	int seg_num;
	to_be_merge(){}
	~to_be_merge() {}
};
template<class T>
class externalsort {
public:
	externalsort(int buffer_size,int K){
		buffersize = buffer_size;
		this->K = K;
	}
	void sort(string filename) {
		fstream infile;
		string path = "D://data_structure_data2//";
		choice = filename;
		string txtfile = filename + ".txt";
		string fullname = path + choice + "//" + txtfile;
		infile.open(fullname, ios::in);
		if (!infile) {
			cerr << "fail to open " + fullname << endl;
			exit(0);
		}
		infile >> datasize;
		//fstream outfile;
		//string outfile_fullname = path + choice + "//my//" + "seg" + to_string(seg_id_2) + ".txt";
		//outfile.open(outfile_fullname, ios::app | ios::out);
		//visit_time++;
		//ofstream file_writer(outfile_fullname, ios_base::out);
		//cout << buffersize << endl;
		
		for (int i = 0; i < buffersize; i++) {//������ʼ��������
			infile >> player[i].key;
			player[i].id = 1;//��ʼ���Ϊ1
		}
		visit_time++;
		LoserTree<ele> tree(buffersize, player);
		int num = 0;
		for (int i = 0; i < datasize; i++) {
			if (!(infile >> num)) {//�ļ�ȫ�������
				num = INT_MIN;
			}
			ele win = tree.getwinner();//�ҵ���ǰʤ�ߣ�����Сֵ
			//cout << win.id << " " << win.key << endl;
			ele temp;
			temp.key = num;
			if (num >= win.key) {//��ǰ����Ĵ���ʤ�ߣ�����ʤ������˳��
				temp.id = win.id;
			}
			else {
				if (num == INT_MIN) {//�ж��Ƿ���Ч
					num = INT_MAX;
				}
				else {//��Ч��������һ��˳��
					num = win.id + 1;
				}
				temp.id = num;
			}
			tree.popwinner(temp);//����ʤ�ߣ�ʹ���������ֵ�ع�������
			seg_id_2 = win.id;
			string fname = path+choice+"//my//seg" + to_string(win.id) + ".txt";
			ofstream tempout(fname, ios::app);
			//ofstream file_writer(fname, ios_base::out);
			tempout << win.key << " ";//���ʤ��
			tempout.close();
			visit_time+=2;
		}
		//cout << seg_id_2 << endl;
	}
	void mergeK(int start,int end,string outname) {//�ϲ�k��˳��
		fstream outfile;
		string output_name = "D://data_structure_data2//" + choice + "//my//" + outname;
		outfile.open(output_name, ios::out);
		//visit_time++;
		int mergecnt = end - start;
		seg_member<T>* segs = new seg_member<T>[mergecnt];
		queue<seg_member<T>>* memorys = new queue<seg_member<T>>[mergecnt];
		int total_size = 0;
		int buffuse=0;
		for (int i = 0; i < mergecnt; i++) {
			string file = "D://data_structure_data2//" + choice + "//my//" + "seg" + to_string(start+i) + ".txt";
			ifstream infile;
			infile.open(file, ios::in);
			visit_time++;
			queue<seg_member<T>> memory;//��˳�����ݶ������
			seg_member<T> seg;
			int j = 0;
			while (infile >> seg.value) {
				seg.seg_id = i;
				memory.push(seg);
				if (j == 0) {
					segs[i] = seg;
				}
				j++;
				buffuse++;
				if (buffuse == buffersize / (K + 1)) {
					visit_time++;
					buffuse = 0;
				}
			}
			total_size += memory.size();
			memorys[i] = memory;
			infile.close();
		}
		LoserTree<seg_member<T>> tree(mergecnt, segs);//��k�����е�ͷ������������
		int cur_size = 0;
		buffuse = 0;
		queue<int> outbuff;//���������
		while (cur_size < total_size) {
			seg_member<T> temp = tree.getwinner();//Ӯ����������������
			outbuff.push(temp.value);
			buffuse++;
			if (buffuse == buffersize / (K + 1)) {
				buffuse = 0;
				visit_time++;
			}
			memorys[temp.seg_id].pop();//�ҵ�Ӯ������˳������һ��Ԫ��,�������ع�������
			if (!memorys[temp.seg_id].empty()) {
				temp = memorys[temp.seg_id].front();
				tree.popwinner(temp);
			}
			else {
				temp.value = INT_MAX;
				tree.popwinner(temp);
			}
			cur_size++;
		}
		while (!outbuff.empty()) {
			outfile << outbuff.front() << " ";
			outbuff.pop();
		}
		delete[] segs;
		delete[]memorys;
		outfile.close();
}
	void mergeone(int segnum,string outname) {
		int x;
		int buffuse = 0;
		fstream outfile;
		string output_name = "D://data_structure_data2//" + choice + "//my//" + outname+".txt";
		outfile.open(output_name, ios::out);
		ofstream file_writer(output_name, ios_base::out);
		string file = "D://data_structure_data2//" + choice + "//my//" + "seg"+to_string(segnum)+".txt";
		ifstream infile;
		infile.open(file, ios::in);
		while (infile >> x) {
			outfile << x << " ";
			buffuse++;
			if (buffuse == buffersize / 2) {
				visit_time++;
				buffuse = 0;
			}
		}
		outfile.close();
		infile.close();
	}
	void merge() {
		if (seg_id_2 == 1) {//���ֻ������һ��˳����ֱ�ӽ�˳�����������ļ���
			mergeone(1,"output");
			return;
		}
		//һ�����ϵ�˳��
		queue<to_be_merge> q;
		int start = 1;
		int num = seg_id_2;
		while (1) {//����鲢����,����ǰ��Ҫ���ĸ�˳���鲢���ĸ�˳��
			to_be_merge tbm;
			tbm.start = start;
			tbm.end = start + K;
			start += K;
			tbm.seg_num = ++num;
			if (tbm.end >= num) {
				tbm.end = num;
				q.push(tbm);
				break;
			}
			q.push(tbm);
		}
		while (!q.empty()) {//���й鲢
			to_be_merge temp = q.front();
			q.pop();
			string outname = "seg" + to_string(temp.seg_num) + ".txt";
			if (temp.start == temp.end)
				mergeone(temp.seg_num,outname);
			else {
				mergeK(temp.start, temp.end, outname);
			}
		}
		//mergeK(1, 4, "output.txt");
	}
	  //double gettime() { return (double)(end - start); }
	  int get_visit_time() { return visit_time; }
protected:
	int seg_id_2=1;
	int datasize;
	int K;
	int buffersize;
	int visit_time=0;
	string choice="data3";
};
