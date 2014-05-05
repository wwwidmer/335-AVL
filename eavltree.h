//=============================================================
// Name:  AVLTREE / EAVLTREE.h
// Author(s): Mark Allen Weiss, Stewart Weiss (no relation)
//            Enhanced by (where noted): William Widmer
// Created: March 2014
// Build: g++ eavltree.h eavltree.cpp
//        or simply with attached makefile; make and ./eavl.out args
// Version: 1.0
// Description: Header file for an enhanced AVL Tree. Private Class AVLNode prevents implementation file from compiling with AVLNode return type so those functions are included. Copy, assignment, and default constructor are also fleshed out in this file. All other functions implemeneted in eavltree.cpp
//
//============================================================

#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED

#include <algorithm>
#include <iostream> 

using namespace std;

// (E)AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
//


template <typename Comparable>
class AvlTree
{
  
 public:
  // Enhanced default constructor, total finds/size/nodes_visited = 0
 AvlTree( ):root(NULL),size_t(0),finds(0.0),nodes_visited(0.0){}
  
 AvlTree( const AvlTree & rhs ):root(NULL)
    {
      *this = rhs;
    }
  
  /**
   * Deep copy.
   */
  AvlTree & operator=( const AvlTree & rhs )
    {
      if(this != &rhs){
	make_empty();
	root = clone(rhs.root);
      }
     return *this;
    }
  /*
   * Find the smallest item in the tree
   */
  const Comparable & find_min() const;
  
/**
 * Find the largest item in the tree. 
 */
  const Comparable & find_max( ) const;
  /**
   * Returns true if x is found in the tree.
   */
  bool contains( const Comparable & x ) const;
  
  /**
  * Test if the tree is logically empty.
  * Return true if empty, false otherwise.
  */
  bool is_empty( ) const;
  /**
   *  EAVL
   *  Enhanced Avl Tree public functions
   * ======================================
   *
   */
  
  /**
   * Report the size, height, internal path length, and average numbers of nodes visited. 
   * Format is "(attribute) = (number)"
   */
  void report();
  
  /**
   * Returns the height of the tree. 
   * Height is found by traversing the tree in both directions, selecting the larger height, and adding one (the root)
   */
  int height();
  
  /**
   * Returns the internal path length of the tree. 
   */
  int int_path_length();
  /**
   * Returns the size (number of nodes) in the tree. 
   * This is a class variable and is accounted for during insertion and deletion.
   */
  int size();
  
  /**
   * Returns the average number of nodes visited per find operation
   * finds and nodes_visited are accounted for in the find function.
   */
  float avge_node_visits();
  
  /**
   * Displays the tree in order from lowests to highests. (0,1,2...)(A,B,a,b...)
   */
  void display(ostream& os);
  
 /**
  * Find function for the tree. 
  * Returns the number of nodes visited and a variable is updated to view the current frequency of the item.
  */
  int find(const Comparable &x, int &freq);
  
  /**
   * END ENCHANCED PUBLIC METHODS
   * ======================================
   */
  
  
  /**
   * Print the tree contents in sorted order.
   */
  void print_tree(ostream& os);
  
  /**
   * Make the tree logically empty.
   */
  void make_empty();
  
  
  /**
  * Insert x into the tree; duplicates increase frequency.
  */
  int insert(const Comparable &x);
  
  /**
   * Remove x from the tree. Returns -1 if x is not found.
   */
  int remove(const Comparable &x);
  
 private:
  struct AvlNode
  {
    Comparable element;
    AvlNode *left;
    AvlNode * right;
    int height;
    int freq;
    // Enhanced node has a frequency, default is 1 because if the node exists there must be a frequency.
    
  AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0, int q = 1) : element(ele),left(lt),right(rt),height(h), freq(q){}
    
  };
  
  AvlNode* root;
  int size_t;
  int finds;
  int nodes_visited;
  
  
  /**
   * Internal method to insert into a subtree.
   * x is the item to insert.
   * t is the node that roots the subtree.
   * Set the new root of the subtree.
   *
   *
   * == Enhanced ==
   * Updates frequency, if need be, of x in the tree.
   * Returns the frequency of x in the tree.
   * 
   */
  int insert(const Comparable &x, AvlNode *&t);
  
  /**
   * Internal method to remove from a subtree.
   * x is the item to remove.
   * t is the node that roots the subtree.
   * Set the new root of the subtree.
   *
   * == Enhanced ==
   * 
   * If we remove x and x still has a frequency above 0, do nothing.  * If less, some pointer manipulation and remove recursively
   * Set 0 as a  placeholder, if we haven't found x it remains 0 andis returned
   * Using that information we can say we did not find x at all.
   * Returns the frequency of x in the tree, even if now 0.
   * 
   */
  int remove(const Comparable &x, AvlNode *&t);
  
  /**
   *
   * EAVL 
   * Enhanced Avl Tree private methods
   *
   */
  
  /**
   * Returns the internal path length of the tree.
   * Add 1 for every node inbetween the highest nodes and the root.
   */
  int int_path_length(AvlNode*& t, int val);

  /**
   * Returns the number of nodes visited during a find operation.
   * Finds the comparable x by traversing the tree iteratively. 
   * We update freq, which is a reference to another variable, to show the frequency of the found item in the tree.
   * If the item is not found, freq will not change.
   *
   */
  int find(const Comparable &x, int& freq, AvlNode *r);
  /**
   * ==========================
   * END ENHANCHED PRIVATE METHODS
   */
  
  static const int ALLOWED_IMBALANCE = 1;
  
  // Assume t is balanced or within one of being balanced
  void balance(AvlNode*& t);
  
  /**
   * Internal method to find the smallest item in a subtree t.
   * Return node containing the smallest item.
   */
  
  AvlNode * find_min( AvlNode *t ) const{
    
    if( t == NULL )
      return NULL;
    if( t->left == NULL )
      return t;
    return find_min( t->left );
  }
  /**
   * Internal method to find the largest item in a subtree t.
   * Return node containing the largest item.
   */ 
  AvlNode * find_max( AvlNode *t ) const{
    if( t != NULL )
      while( t->right != NULL )
	t = t->right;
    return t;
    
  }
  
  /**
   * Internal method to test if an item is in a subtree.
   * x is item to search for.
   * t is the node that roots the tree.
   */
  bool contains( const Comparable & x, AvlNode *t ) const;
  
  /**
   * Internal method to make subtree empty.
   */
  void make_empty( AvlNode * & t );
  
  
  /**
   * Internal method to print a subtree rooted at t in sorted order.
   * Enhanced to take an ostream as an argument.
   */
  void print_tree( AvlNode *t, ostream& os) const;
  
  /**
   * Internal method to clone subtree.
   */
  AvlNode * clone( AvlNode *t ) const{
    if( t == NULL )
      return NULL;
    else
      return new AvlNode(t->element, clone( t->left ), clone( t->right ), t->height);
  }
  
  // Avl manipulations
  
  /**
   * Return the height of node t or -1 if NULL.
   */
  int height( AvlNode *t ) const;
  
  int max( int lhs, int rhs ) const;
  
  /**
  * Rotate binary tree node with left child.
  * For AVL trees, this is a single rotation for case 1.
  * Update heights, then set new root.
  */
  void rotate_with_left_child( AvlNode * & k2 );
  
  /**
   * Rotate binary tree node with right child.
   * For AVL trees, this is a single rotation for case 4.
   * Update heights, then set new root.
   */
  void rotate_with_right_child( AvlNode * & k1 );
  
  /**
   * Double rotate binary tree node: first left child.
   * with its right child; then node k3 with new left child.
   * For AVL trees, this is a double rotation for case 2.
   * Update heights, then set new root.
   */
  void double_with_left_child( AvlNode * & k3 );
  
  /**
   * Double rotate binary tree node: first right child.
   * with its left child; then node k1 with new right child.
   * For AVL trees, this is a double rotation for case 3. 
   * Update heights, then set new root.
   */
  void double_with_right_child( AvlNode * & k1 );

};
#endif






