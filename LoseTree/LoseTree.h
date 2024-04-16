#pragma once
#include<iostream>
using namespace std;
template<class T>
class LoserTree {
public:
	LoserTree(int size, T* element);
	void initial(int size,T*element);
	void compete(int p,int left,int right);
	T getwinner();
	int gettree0();
	void popwinner();
	void popwinner(T ele);
	void reform(int position,T the_element);
	void sort();
	int Win(int a, int b);
	int Lose(int a, int b);
	//T output(int position);
	~LoserTree();
protected:
	int Tree_size;
	int lowExt;
	int offset;
	int* tree;
	int* id_of_winners;
	T* players;
};