#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__

#include "BinaryNode.h"

template< class T >
class BinaryTree
{
protected:
	BinaryNode< T > *root;

public:
	BinaryTree();
	BinaryTree( T& val );
	~BinaryTree();
	bool isEmpty();
	T& getDatoRaiz();
	void preOrden();
	void inOrden();
	void posOrden();
	std::list< BinaryNode< T >* > nivelOrden();
	int height();
	int size();
	bool buscar( T& val );
	bool insert( T& val );
	bool erase( T& val );
	T min();
	T max();
};

#include "BinaryTree.hxx"

#endif
