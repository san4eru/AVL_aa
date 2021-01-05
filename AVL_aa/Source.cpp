#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>

#include <iostream>
#include <iomanip>

using namespace std;

struct node // ��������� ��� ������������� ����� ������
{
	int key; // ���� ����
	unsigned char height; // ������ ��������� � ������ � ������ ����
	node* left; // ����� ���������
	node* right; // ������ ���������

	node(int k) // ���������� - ����� ���� (������ 1) � �������� ������ k.
	{
		key = k;
		left = right = 0;
		height = 1;
	}
};

unsigned char height(node* p) // ������� ��� ���� height, ����� �������� � �������� ����������� (� ������� ���������)
{
	if (p)
		return p->height;
	else
		return 0;
}

// balance factor - ������� ����� ������� � ������ ����������� (����� ���� -1, 0 � 1)
int bfactor(node* p) // ��������� balance factor ��������� ���� (� �������� ������ � ���������� �����������)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p) // ��������������� ���������� �������� ���� height ��������� ���� (��� �������, ��� �������� ����� ���� � ������ � ����� �������� ����� �������� �����������)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	if (hl > hr)
		p->height = hl + 1;
	else
		p->height = hr + 1;
}

node* rotateright(node* p) // ������ ������� ������ p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // ����� ������� ������ q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // ������������ ���� p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // ������������ �� �����
}

node* insert(node* p, int k) // ������� ����� k � ������ � ������ p
{
	if (!p) return new node(k); // ���� ������ ������
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // ����� ���� � ����������� ������ � ������ p
{
	if (p->left)
		return findmin(p->left);
	else
		return p;
}

node* removemin(node* p) // �������� ���� � ����������� ������ �� ������ p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // �������� ����� k �� ������ p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void PrintTree(node* tree, int r, int ch)
{
	//������ ���������
	if (tree->right)
	{
		PrintTree(tree->right, r + 10, 2);
	}

	for (int i = 0; i < r - 1; i++)
		cout << " ";

	if (ch == 0)
		cout << "";
	else if (ch == 1)
		cout << "\\";
	else if (ch == 2)
		cout << "/";

	cout << "(" << tree->key << ")" << endl;

	//����� ���������
	if (tree->left)
	{
		PrintTree(tree->left, r + 10, 1);
	}
}

void postorder(node* p, int indent)
{
	if (p != NULL)
	{
		if (p->right)
		{
			postorder(p->right, indent + 4);
		}

		if (indent)
		{
			cout << setw(indent) << ' ';
		}

		if (p->right)
			cout << " /\n" << setw(indent) << ' ';

		cout << p->key << "\n ";

		if (p->left)
		{
			cout << setw(indent) << ' ' << " \\\n";
			postorder(p->left, indent + 4);
		}
	}
}

int main() {
	//10; 5; 3; 11; 12;
	/*node tr(10);
	node* ptr = &tr;
/*
			  5
			 / \
			3  11
			  /  \
			 10  12

	ptr = insert(ptr, 5);
	ptr = insert(ptr, 3);
	ptr = insert(ptr, 11);
	ptr = insert(ptr, 12);*/

	
	//4, 6, 2, 1, 5, 3, 7
	node tr(4);
	node* ptr = &tr;
	
/*
			  5
			 / \
			3  11
			  /  \
			 10  12
*/
	ptr = insert(ptr, 6);
	ptr = insert(ptr, 2);
	ptr = insert(ptr, 1);
	ptr = insert(ptr, 5);
	ptr = insert(ptr, 3);
	ptr = insert(ptr, 7);
	
	postorder(ptr, 0);
	return 0;
}