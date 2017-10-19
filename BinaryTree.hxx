#include "BinaryTree.h"

template< class T >
BinaryTree< T >::BinaryTree()
{
	this->root = nullptr;
}

template< class T >
BinaryTree< T >::BinaryTree( T& val )
{
	this->root = new BinaryNode< T >( val );
}

template< class T >
BinaryTree< T >::~BinaryTree()
{

}

template< class T >
bool BinaryTree< T >::isEmpty()
{
	if( this->root == nullptr )
		return true;
	return false;
}

template< class T >
T& BinaryTree< T >::getDatoRaiz()
{
	return ( this->root )->getDato();
}

template< class T >
void BinaryTree< T >::preOrden()
{
	if( !this->isEmpty() )
		( this->root )->preOrden();
	std::cout << std::endl;
}

template< class T >
void BinaryTree< T >::inOrden()
{
	if( !this->isEmpty() )
		( this->root )->inOrden();
	std::cout << std::endl;
}

template< class T >
void BinaryTree< T >::posOrden()
{
	if( !this->isEmpty() )
		( this->root )->posOrden();
	std::cout << std::endl;
}

template< class T >
std::list< BinaryNode< T >* > BinaryTree< T >::nivelOrden()
{
	std::list< BinaryNode< T >* > lista;
	if( !this->isEmpty() )
	{
		lista.push_back( this->root );
		for( typename std::list< BinaryNode< T >* >::iterator it = lista.begin(); it != lista.end(); ++it)
			( *it )->nivelOrden( lista );
	}
	return lista;
}

template< class T >
int BinaryTree< T >::height()
{
	return ( this->root )->getHeight();
}

template< class T >
int BinaryTree< T >::size()
{
	return this->size;
}

template< class T >
bool BinaryTree< T >::buscar( T& val )
{
	if( !this->isEmpty() )
		return ( this->root )->buscar( val );
	return 0;
}

template< class T >
bool BinaryTree< T >::insert( T& val )
{
	if( !this->isEmpty() )
	{
		if( !this->buscar( val ) )
		{
			return ( this->root )->insert( val );
		}
		return false;
	}
	this->root = new BinaryNode< T >( val );
	return 1;
}

template< class T >
bool BinaryTree< T >::erase( T& val )
{
	if( this->buscar( val ) )
	{
		return ( this->root )->erase( val );
	}
	return false;
}

template< class T >
T BinaryTree< T >::min()
{
	return ( this->root )->min();
}

template< class T >
T BinaryTree< T >::max()
{
	return ( this->root )->max();
}
