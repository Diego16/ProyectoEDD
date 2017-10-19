 #include "BinaryNode.h"

template< class T >
BinaryNode< T >::BinaryNode( T& val )
{
	this->dato = val;
	this->left = nullptr;
	this->right = nullptr;
	this->height = 0;
}

template< class T >
BinaryNode< T >::BinaryNode( T& val, BinaryNode< T > *left,BinaryNode< T > *right )
{
	this->dato = val;
	this->left = left;
	this->right = right;
	this->updateHeight();
}

template< class T >
T& BinaryNode< T >::getDato()
{
	return this->dato;
}

template< class T >
void BinaryNode< T >::setDato( T& val )
{
	this->dato = val;
}

template< class T >
BinaryNode< T >* BinaryNode< T >::getLeft()
{
	return this->left;
}

template< class T >
BinaryNode< T >* BinaryNode< T >::getRight()
{
	return this->right;
}

template< class T >
void BinaryNode< T >::setLeft( BinaryNode< T > *left )
{
	this->left = left;
}

template< class T >
void BinaryNode< T >::setRight( BinaryNode< T > *right)
{
	this->right = right;
}

template < class T >
int BinaryNode< T >::getHeight()
{
	return this->height;
}

template< class T >
void BinaryNode< T >::preOrden()
{
	std::cout << this->getDato() << " ";
	if( this->left != nullptr)
		( this->left )->preOrden();
	if( this->right != nullptr )
		( this->right )->preOrden();
}

template< class T >
void BinaryNode< T >::inOrden()
{
	if( this->left != nullptr)
		( this->left )->inOrden();
	std::cout << this->getDato() << " ";
	if( this->right != nullptr )
		( this->right )->inOrden();
}

template< class T >
void BinaryNode< T >::posOrden()
{
	if( this->left != nullptr)
		( this->left )->posOrden();
	if( this->right != nullptr )
		( this->right )->posOrden();
	std::cout << this->getDato() << " ";
}

template< class T >
void BinaryNode< T >::nivelOrden( std::list< BinaryNode< T >* > &lista )
{
	if( this->left != nullptr )
		lista.push_back( left );
	if( this->right != nullptr )
		lista.push_back( right );
}

template< class T >
bool BinaryNode< T >::buscar( T& val )
{
	if( val == this->dato )
		return true;
	else
		if( val < this->dato && this->left != nullptr)
			return ( this->left )->buscar( val );
		else
			if( val > this->dato && this->right != nullptr )
				return ( this->right )->buscar( val );
	return false;
}

template< class T >
bool BinaryNode< T >::insert( T& val )
{
	if( val < this->dato)
	{
		if( this->left == nullptr )
		{
			this->left = new BinaryNode( val );
			this->updateHeight();
			return 1;
		}
		else
		{
			bool insert = ( this->left )->insert( val );
			this->updateHeight();
			return insert;
		}
	}
	else
	{
		if( val > this->dato )
		{
			if( this->right == nullptr )
			{
				this->right = new BinaryNode( val );
				this->updateHeight();
				return 1;
			}
			else
			{
				bool insert = ( this->right )->insert( val );
				this->updateHeight();
				return insert;
			}
		}
	}	
	return 0;
}

template< class T >
bool BinaryNode< T >::erase( T& val )
{
	if( val < this->dato )
	{
		if( val == ( this->left )->dato )
		{
			auto *temp = this->left ;
			if( temp->getLeft() == nullptr )
			{
				if( temp->getRight() == nullptr )
				{
					delete temp;
					this->left = nullptr;
				}
				else
				{
					BinaryNode< T > *aux = temp->getRight();
					temp->dato = aux->getDato();
					delete aux;
					temp->right = nullptr;
				}
			}
			else
				if( this->right == nullptr )
				{
					BinaryNode< T > *aux = temp->getLeft();
					temp->dato = aux->getDato();
					delete aux;
					temp->left = nullptr;
				}
				else
				{
					auto aux = ( temp->left )->max();
					( this->left )->erase( aux );
					this->dato = aux;
				}
		this->updateHeight();
		return true;
		}
		else
			if( val < this->dato)
			{
				bool eras = ( this->left )->erase( val );
				this->updateHeight();
				return eras;
			}
			else
				if( val > this->dato )
				{
					bool eras = ( this->right )->erase( val );
					this->updateHeight();
					return eras;
			}
	}
	else
	{
		if( val > this->dato )
		{
			if( val == ( this->right )->dato )
			{
				auto *temp = ( this->right );
				if( temp->getLeft() == nullptr )
					if( temp->getRight() == nullptr )
					{
						delete temp;
						this->right = nullptr;
					}
					else
					{
						BinaryNode< T > *aux = temp->getRight();
						temp->dato = aux->getDato();
						delete aux;
						temp->right = nullptr;
					}
				else
					if( this->right == nullptr )
					{
						BinaryNode< T > *aux = temp->getLeft();
						temp->dato = aux->getDato();
						delete aux;
						temp->left = nullptr;
					}
					else
					{
						auto aux = ( temp->left )->max();
						( this->left )->erase( aux );
						this->dato = aux;
					}
				this->updateHeight();
				return true;
			}
			else
				if( val < this->dato)
				{
					bool eras = ( this->left )->erase( val );
					this->updateHeight();
					return eras;
				}
				else
					if( val > this->dato )
					{
						bool eras = ( this->right )->erase( val );
						this->updateHeight();
						return eras;
					}
		}
		else
		{
			auto aux = ( this->left )->max();
			( this->left )->erase( aux );
			this->dato = aux;
			this->updateHeight();
			return true;
		}
	}
	return false;
}

template< class T >
T BinaryNode< T >::min()
{
	if( this->left != nullptr )
		return ( this->left )->min();
	return this->dato;
}

template< class T >
T BinaryNode< T >::max()
{
	if( this->right != nullptr )
		return ( this->right )->max();
	return this->dato;
}

template< class T >
void BinaryNode< T >::updateHeight()
{
	if( this->left == nullptr)
		if( this->right != nullptr )
			this->height = ( this->right )->getHeight() + 1;
		else
			this->height = 0;
	else
		if( this->right == nullptr )
			this->height = ( this->left )->getHeight() + 1;
		else
			if( ( this->left )->getHeight() > ( this->right )->getHeight() )
				this->height = ( this->left )->getHeight() + 1;
			else
				this->height = ( this->right )->getHeight() + 1;
}

/*template< class T >
BinaryNode< T >* BinaryNode< T >::searchFather();
*/
