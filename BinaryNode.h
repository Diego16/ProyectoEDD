#ifndef __BINARYNODE_H__
#define __BINARYNODE_H__

#include <iostream>
#include <list>
#include <iterator>

template< class T >
class BinaryNode
{
protected:
	T dato;
	BinaryNode< T > *left;
	BinaryNode< T > *right;
	int height;
	void updateHeight();

public:
	BinaryNode();
	BinaryNode( T& val );
	BinaryNode( T& val, BinaryNode< T > *left, BinaryNode< T > *right );
	~BinaryNode() = default;
	T& getDato();
	void setDato( T& val );
	BinaryNode< T >* getLeft();
	BinaryNode< T >* getRight();
	void setLeft( BinaryNode< T > *left );
	void setRight( BinaryNode< T > *right);
	int getHeight();
	void preOrden();
	void inOrden();
	void posOrden();
	void nivelOrden( std::list< BinaryNode< T >* > &cola );
	bool buscar( T& val );
	bool insert( T& val );
	bool erase( T& val );
	T min();
	T max();
};

#include "BinaryNode.hxx"

#endif
