#include <string>
#include <iostream>
using namespace std;

const string INVALID_STRING="INVALID STRING";

class rbtree{
   private:
      // we maintain a pointer to the root of the tree
      struct node {
            node *right, *left, *parent;
            string      data;
            int key; 
	         bool red;
         } ;
      node *root;
      node *NO_NODE;
      

      // private, recursive routines
      // (used by the public methods)
      void deallocate(node* &n);
      bool insert(int k, string d, node* &n);
      bool deleteElement(int k, node* &n);
      string find(int k, node* n);
      void leftRotate(node* n);
      void testLeftRotate(int k, node* n);
      void print(node *n);
      void debugprint(node *n); 
      void swapElements(node* n, node* m);
	  void InsertNew(node* n);
	  void testrightRotate(int k, node* n);
	  void rightRotate(node* x);

   public:
      rbtree();
      ~rbtree();
      void display() { print(root); }
      void debug() { debugprint(root); }
      bool insert(int k, string d) {
           if (insert(k, d, root)) 
		         return true;
           else return false; }
      bool deleteElement(int k) {
           if (deleteElement(k, root)) return true;
           else return false; }
      string find( int k) { return(find(k, root)); }
      void testLeftRotate(int k) { testLeftRotate(k, root); } 
};

