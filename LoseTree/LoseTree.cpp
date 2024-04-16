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
	tree[position] = (players[left] <= players[right] ? right : left);//����
	id_of_winners[position] = (players[left] <= players[right] ? left : right);//Ӯ��
	while((position%2==1)&&(position>1)){//�����ǰ�ڵ���������,��������
		tree[position / 2] = (players[id_of_winners[position - 1]] <= players[id_of_winners[position]] ? id_of_winners[position] : id_of_winners[position - 1]);
		id_of_winners[position / 2] = (players[id_of_winners[position - 1]] <= players[id_of_winners[position]] ? id_of_winners[position-1] : id_of_winners[position]);
		position /= 2;//��λ�����ڵ�
	}
}

template<class T>
void LoserTree<T>::initial(int size,T*ele) {
	int n = size;
	for (int i = 1; i <= size; i++)
		players[i] = ele[i - 1];
	int tmp = 0;
	int s = 1;
	while (s * 2 <= n - 1)//��ײ�����˵��ڲ��ڵ�
		s *=  2;
	lowExt = 2 * (n - s);//��ײ��ⲿ�ڵ�����
	offset = 2 * s - 1;
	for (int i = 2; i <= lowExt; i += 2) {//�ײ�ڵ�
		int x = (i + offset) / 2;//���ڵ�
		compete(x, i - 1, i);
	}
	if (n % 2 == 1) {
		compete(n / 2, id_of_winners[n - 1], lowExt + 1);//��һ����û�в�����ⲿ�ڵ�
		tmp = lowExt + 3;//�ҵ���һ�������ڶ����ⲿ�ڵ���Һ���
	}
	else {//nΪż��
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
	int matchNode;//matchNodeΪposition�ĸ��ڵ�
	if (position <= lowExt) {
		matchNode = (position + offset) / 2;
	}
	else {
		matchNode = (position - lowExt + Tree_size - 1) / 2;
	}

	while (matchNode >= 1) {
		int theloser = tree[matchNode];//��һ��������ʧ����
		tree[matchNode] = Lose(theloser, position);//���������±�
		id_of_winners[matchNode] = Win(theloser, position);//����Ӯ���±�
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
