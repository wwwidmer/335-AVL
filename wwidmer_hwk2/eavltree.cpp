//=============================================================
// Name:  AVLTREE / EAVLTREE.cpp
// Author(s): Mark Allen Weiss, Stewart Weiss (no relation)
//            Enhanced by (where noted): William Widmer
// Created: March 2014
// Build: g++ eavltree.h eavltree.cpp
//        or simply with attached makefile; make and the ./eavl.out args
// Version: 1.0
// Description: Implementation file for an enhanced AVL Tree class. 
//
//============================================================

#include "eavltree.h"
/**
 *
 * Public Methods
 *
 */
template <typename Comparable>
const Comparable & AvlTree<Comparable>::find_min( ) const
{
  return find_min( root )->element;
}


template <typename Comparable>
const Comparable & AvlTree<Comparable>::find_max( ) const
{
  return find_max( root )->element;
}

template <typename Comparable>
bool AvlTree<Comparable>::contains( const Comparable & x ) const
{
  return contains( x, root );
}


template <typename Comparable>
bool  AvlTree<Comparable>::is_empty( ) const{	
  return root == NULL;
}


/**
 *  EAVL
 *  Enhanced Avl Tree public functions
 * ======================================
 *
 */

template <typename Comparable>
void AvlTree<Comparable>::report(){
  cout << "size = " << size() << endl;
  cout << "height = " << height() << endl;
  cout << "internal path length = " << int_path_length() << endl;
  cout << "average number of nodes visited = "<< avge_node_visits() << endl;
}


template <typename Comparable>
int AvlTree<Comparable>::height(){
  if( root != NULL){
    return max(height(root->left), height(root->right))+1;   
  }
  return 0;
}

template <typename Comparable>
int AvlTree<Comparable>::int_path_length(){
  return int_path_length(root,0);
}

template <typename Comparable>
int AvlTree<Comparable>::size(){
  return size_t;
}

template <typename Comparable>
float AvlTree<Comparable>::avge_node_visits(){
  if(finds > 0 && nodes_visited > 0)
    return (float)nodes_visited / finds;
  else
    return 0;
}

template <typename Comparable>
void AvlTree<Comparable>::display(ostream& os){
  print_tree(os);
}

template <typename Comparable>
int AvlTree<Comparable>::find(const Comparable &x, int &freq){
  return find(x,freq,root);   
}

/**
 * END ENCHANCED PUBLIC METHODS
 * ======================================
 */


template <typename Comparable>
void AvlTree<Comparable>::print_tree(ostream& os)
{
  if( is_empty( ) )
    os << "Empty tree" << endl;
  else
    print_tree(root, os);
}


template <typename Comparable>
void AvlTree<Comparable>::make_empty( )
{
  make_empty( root );
}

template <typename Comparable>
int AvlTree<Comparable>::insert( const Comparable & x )
{
  return insert( x, root );
}

template <typename Comparable>
int AvlTree<Comparable>::remove( const Comparable & x )
{
  return remove(x,root);
}

/**
 * Private methods
 *
 */
template <typename Comparable>	
int AvlTree<Comparable>::insert( const Comparable & x, AvlNode * & t)
{
  int freq = 1;
  if( t == NULL ){
    t = new AvlNode(x,NULL,NULL);
    size_t++;
  } else if( x == t->element){
    t->freq = t->freq++;
    freq = t->freq;
  }
  else if( x < t->element ){
    freq = insert( x, t->left );
  }
  else if( t->element < x ){
    freq = insert( x, t->right );
  }
  balance(t);
  t->height = max(height(t->left),height(t->right))+1;
  return freq;
}

template <typename Comparable>
int AvlTree<Comparable>::remove( const Comparable & x, AvlNode * & t )
{
  int freq = 0;
  if( t == NULL)
    return -1;   // Item not found; do nothing
  
  if( x < t->element )
    freq = remove( x, t->left );
  else if( t->element < x )
    freq = remove( x, t->right );
  else
    {
      t->freq--;
      if( t->left != NULL & t->right != NULL) // Two children
	{	   
	  if(t->freq <= 0){
	    t->element = find_min( t->right )->element;
	    t->freq = find_min(t->right)->freq;
	    remove( t->element, t->right );
	  }
	}
      else
	{
	  freq = t->freq;
	  if(t->freq < 1){
	    AvlNode *old_node = t;
	    t = ( t->left != NULL ) ? t->left : t->right;
	    delete old_node;
	    size_t--;
	  }
	} 
    }
  
  balance( t );
  return freq;
}

template <typename Comparable>
int AvlTree<Comparable>::int_path_length(AvlNode*& t, int val){
  if(t == NULL){
    return 0;
  }
  return val + int_path_length(t->left,val+1)+int_path_length(t->right,val+1);
}   

template <typename Comparable>
int AvlTree<Comparable>::find(const Comparable &x, int& freq, AvlNode* r){
  finds++;
  int visited = 0;
  AvlNode* t = r;
  while(t != NULL){
    if(t->element == x){       
      freq = t->freq;
      nodes_visited += visited;
      return visited;
    }else if(t->element > x){
      t = t->left;
    }else if(t->element < x){
      t = t->right;
    }
    visited++;
  }
  nodes_visited+=visited;
  return visited;
}

// Assume t is balanced or within one of being balanced
template <typename Comparable>
void AvlTree<Comparable>::balance(AvlNode * & t )
{
  if( t == NULL )
    return;
  
  if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ){
    if( height( t->left->left ) >= height( t->left->right ) ){
      rotate_with_left_child( t );
    }
    else{
      double_with_left_child( t );}
  }
  else{
    if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ){
      if( height( t->right->right ) >= height( t->right->left ) ){
	rotate_with_right_child( t );
      }
      else{
	double_with_right_child( t );
      }
    }
  }   
  t -> height = max( height( t->left ), height( t->right ) ) + 1;
}

template <typename Comparable>
bool AvlTree<Comparable>::contains( const Comparable & x, AvlNode *t ) const
{
  if( t == NULL )
    return false;
  else if( x < t->element )
    return contains( x, t->left );
  else if( t->element < x )
    return contains( x, t->right );
  else
    return true;    // Match
}

template <typename Comparable>
void AvlTree<Comparable>::make_empty( AvlNode * & t )
{
  if( t != NULL )
    {
      make_empty( t->left );
      make_empty( t->right );
      delete t;
    }
  t = NULL;
}
template <typename Comparable>
void AvlTree<Comparable>::print_tree( AvlNode *t, ostream& os ) const
{
  if( t != NULL )
    {
      print_tree( t->left, os );
      os << t->element << endl;
      print_tree( t->right, os );
    }
}

// Avl manipulations

template <typename Comparable>
int AvlTree<Comparable>::height( AvlNode *t ) const
{
  return t == NULL ? -1 : t->height;
}
template <typename Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs ) const
{
  return lhs > rhs ? lhs : rhs;
}
template <typename Comparable>
void AvlTree<Comparable>::rotate_with_left_child( AvlNode * & k2 )
{
  AvlNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
  k1->height = max( height( k1->left ), k2->height ) + 1;
  k2 = k1;
}

template <typename Comparable>
void AvlTree<Comparable>::rotate_with_right_child( AvlNode * & k1 )
{
  AvlNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
  k2->height = max( height( k2->right ), k1->height ) + 1;
  k1 = k2;
}

template <typename Comparable>
void AvlTree<Comparable>::double_with_left_child( AvlNode * & k3 )
{
  rotate_with_right_child( k3->left );
  rotate_with_left_child( k3 );
}

template <typename Comparable>
void AvlTree<Comparable>::double_with_right_child( AvlNode * & k1 )
{
  rotate_with_left_child( k1->right );
  rotate_with_right_child( k1 );
}
