#include"LoseTree.h"
#include<iostream>
#include<limits.h>
using namespace std;
template<class T>
LoserTree<T>::LoserTree(int size, T* element) {
	Tree_size = size;
//	cout << size << endl;
	players = new T[Tree_size+1];
	tree = new int[Tree_size+1];
	id_of_winners = new int[Tree_size+1];
	initial(size,element);
}

template<class T>
void LoserTree<T>::compete(int position,int left, int right) {
	tree[position] = (players[left] <= players[right] ? right : left);//输者
	id_of_winners[position] = (players[left] <= players[right] ? left : right);//赢者
	while((position%2==1)&&(position>1)){//如果当前节点是右子树,继续比赛
		tree[position / 2] = (players[id_of_winners[position - 1]] <= players[id_of_winners[position]] ? id_of_winners[position] : id_of_winners[position - 1]);
		id_of_winners[position / 2] = (players[id_of_winners[position - 1]] <= players[id_of_winners[position]] ? id_of_winners[position-1] : id_of_winners[position]);
		position /= 2;//定位到父节点
	}
}

template<class T>
void LoserTree<T>::initial(int size,T*ele) {
	int n = size;
	for (int i = 1; i <= size; i++)
		players[i] = ele[i - 1];
	int tmp = 0;
	int s = 1;
	while (s * 2 <= n - 1)//最底层最左端的内部节点
		s *=  2;
	lowExt = 2 * (n - s);//最底层外部节点数量
	offset = 2 * s - 1;
	for (int i = 2; i <= lowExt; i += 2) {//底层节点
		int x = (i + offset) / 2;//父节点
		compete(x, i - 1, i);
	}
	if (n % 2 == 1) {
		compete(n / 2, id_of_winners[n - 1], lowExt + 1);//有一个还没有参与的外部节点
		tmp = lowExt + 3;//找到第一个倒数第二层外部节点的右孩子
	}
	else {//n为偶数
		tmp = lowExt + 2;
	}
	for (int i = tmp; i <= n; i += 2) {
		compete((i - lowExt + n - 1) / 2, i - 1, i);
	}
	tree[0] = id_of_winners[1];
	//for (int i = 0; i <= size; i++)
	//	cout << tree[i] << " ";
	//cout << endl;
}

template<class T>
int LoserTree<T>::Win(int a, int b) {
	return players[a] <= players[b] ? a : b;
}

template<class T>
int LoserTree<T>::Lose(int a, int b) {
	return players[a] <= players[b] ? b : a;
}

template<class T>
void LoserTree<T>::reform(int position, T the_element) {
	int n = this->Tree_size;
	players[position] = the_element;
	int matchNode;//matchNode为position的父节点
	if (position <= lowExt) {
		matchNode = (position + offset) / 2;
	}
	else {
		matchNode = (position - lowExt + Tree_size - 1) / 2;
	}

	while (matchNode >= 1) {
		int theloser = tree[matchNode];//上一场比赛的失败者
		tree[matchNode] = Lose(theloser, position);//更新输者下标
		id_of_winners[matchNode] = Win(theloser, position);//更新赢者下标
		position = id_of_winners[matchNode];
		matchNode /= 2;
	}

	tree[0] = id_of_winners[1];
}

template<class T>
T LoserTree<T>::getwinner() {/*
	for (int i = 1; i <= Tree_size; i++)
		cout << players[i] << " ";
	cout << endl;
	for (int i = 0; i < Tree_size; i++)
		cout << tree[i] << " ";
	cout << endl;
	for (int i = 0; i < Tree_size; i++)
		cout << id_of_winners[i] << " ";
	cout << endl;*/
	//cout << tree[0] << " " << players[tree[0]] << endl;
	return players[tree[0]];
}

template<class T>
int LoserTree<T>::gettree0() {
	return tree[0];
}

template<class T>
void LoserTree<T>::popwinner() {
	//cout << tree[0] << endl;
	reform(tree[0],INT_MAX);
}

template<class T>
void LoserTree<T>::popwinner(T ele) {
	//cout << tree[0] << endl;
	reform(tree[0],ele);
}

//template<class T>
//T LoserTree<T>::output(int i) {
//	return output_p[i];
//}
template<class T>
LoserTree<T>::~LoserTree() {
	delete[] players;
	delete[] tree;
	delete[] id_of_winners;
}
