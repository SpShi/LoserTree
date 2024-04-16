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
	int id;//顺串号
	int key;//值
	bool operator<=(const ele& ss) const {//顺串号小的获胜，顺串号相同时元素小的获胜
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
		
		for (int i = 0; i < buffersize; i++) {//构建初始的输者树
			infile >> player[i].key;
			player[i].id = 1;//初始编号为1
		}
		visit_time++;
		LoserTree<ele> tree(buffersize, player);
		int num = 0;
		for (int i = 0; i < datasize; i++) {
			if (!(infile >> num)) {//文件全部读入后
				num = INT_MIN;
			}
			ele win = tree.getwinner();//找到当前胜者，即最小值
			//cout << win.id << " " << win.key << endl;
			ele temp;
			temp.key = num;
			if (num >= win.key) {//当前读入的大于胜者，加入胜者所在顺串
				temp.id = win.id;
			}
			else {
				if (num == INT_MIN) {//判断是否有效
					num = INT_MAX;
				}
				else {//有效，加入下一个顺串
					num = win.id + 1;
				}
				temp.id = num;
			}
			tree.popwinner(temp);//弹出胜者，使用新输入的值重构输者树
			seg_id_2 = win.id;
			string fname = path+choice+"//my//seg" + to_string(win.id) + ".txt";
			ofstream tempout(fname, ios::app);
			//ofstream file_writer(fname, ios_base::out);
			tempout << win.key << " ";//输出胜者
			tempout.close();
			visit_time+=2;
		}
		//cout << seg_id_2 << endl;
	}
	void mergeK(int start,int end,string outname) {//合并k个顺串
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
			queue<seg_member<T>> memory;//将顺串内容读入队列
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
		LoserTree<seg_member<T>> tree(mergecnt, segs);//在k个队列的头部建立输者树
		int cur_size = 0;
		buffuse = 0;
		queue<int> outbuff;//输出缓冲区
		while (cur_size < total_size) {
			seg_member<T> temp = tree.getwinner();//赢者输出到输出缓冲区
			outbuff.push(temp.value);
			buffuse++;
			if (buffuse == buffersize / (K + 1)) {
				buffuse = 0;
				visit_time++;
			}
			memorys[temp.seg_id].pop();//找到赢者所在顺串的下一个元素,用它来重构输者树
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
		if (seg_id_2 == 1) {//如果只生成了一个顺串，直接将顺串输出到输出文件中
			mergeone(1,"output");
			return;
		}
		//一个以上的顺串
		queue<to_be_merge> q;
		int start = 1;
		int num = seg_id_2;
		while (1) {//计算归并串号,即当前需要从哪个顺串归并到哪个顺串
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
		while (!q.empty()) {//进行归并
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
