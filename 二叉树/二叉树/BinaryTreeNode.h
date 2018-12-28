#pragma once
#include"Pre.h"
#include"LinkedQueue.h"

//链表二叉树的节点类定义
template<class T>
class BinaryTreeNode
{

private:
	T data;
	BinaryTreeNode<T> * LeftChild;  //左子树
	BinaryTreeNode<T> * RightChild; //右子树
public:
	BinaryTreeNode() { LeftChild = RightChild = 0; }
	BinaryTreeNode(const T  e) { data = e;  LeftChild = RightChild = 0; }
	BinaryTreeNode(const T e, BinaryTreeNode* l, BinaryTreeNode* r) { data = e; LeftChild = l; RightChild = r; }
	BinaryTreeNode<T> * find_L()const{ return LeftChild; }
	BinaryTreeNode<T> * find_R() const{ return RightChild; }
	T & find_data() { return data; }


};

