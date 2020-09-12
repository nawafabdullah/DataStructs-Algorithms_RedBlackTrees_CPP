//Noah Alharbi
// November 2017
#include "rbtree.h"

// struct node {
//     node *right, *left, *parent;
//     string      key, data;
//     bool red;
// } *root;


rbtree::rbtree()
{  
   NO_NODE = new node;
   NO_NODE->red= 0;
   NO_NODE->data=INVALID_STRING;
   root = NO_NODE;
}

rbtree::~rbtree()
{
   deallocate(root);
}

void rbtree::deallocate(node* &n)
// delete all nodes in the subtree rooted at n,
//    and set n to null
{
   if (n == NO_NODE) return;
   deallocate(n->left);
   deallocate(n->right);
   delete n;
   n = NO_NODE; 
}

bool rbtree::insert(int k, string d, node* &n)
// insert a new node in the rbtree rooted at n,
// returning true if successful, false otherwise
// If k is a duplicate of n->key, it will insert the duplicat
// into the left subtree of n
{
   // if we've found the end of a chain,
   //    insert the node here
   if (n == NO_NODE) {
   	n = new node;
	n->left = NO_NODE;
	n->right = NO_NODE;
	n->parent= NO_NODE;
	root = n;
	n->key = k;
	n->data = d;
   	return 1;
   }

   if (k <= n->key) 
	{
   	if (n->left == NO_NODE) {
   		n->left = new node;
         n->left->left = NO_NODE;
         n->left->right = NO_NODE;
		   n->left->parent= n;
		   n->left->key = k;
		   n->left->data = d;
		   //n->left->red=0;
		   //return 1;
		   InsertNew(n->left);
   		}
	   else return insert(k,d,n->left);
	}
   else {
   	if (n->right == NO_NODE) {
   		n->right= new node;
		   n->right->left = NO_NODE;
		   n->right->right = NO_NODE;
		   n->right->parent= n;
		   n->right->key = k;
		   n->right->data = d;
		   //n->right->red=0;
		   //return 1;
			InsertNew(n->right);
   		}
	   else return insert(k,d,n->right);
	}

}

string rbtree::find(int k, node* n)
// Find a node with key k
// return the data associated with the first occurence of key k
// encountered.
{
     if (n == NO_NODE) return INVALID_STRING;
     if (k > n->key) return find(k,n->right);
     if (k==n->key) return n-> data;       
    else return find(k,n->left);
}

bool rbtree::deleteElement(int k, node* &n)
// if the subtree rooted at n contains a node whose key
//    matches k then remove it from the subtree, and return true,
//    otherwise return 
{
	if (n==NO_NODE) return 0;
	if (n->key == k) {
		if (n->left==NO_NODE) {
			node* temp = n->right;
         temp->parent = n->parent;
			delete n;
			n = temp;
			return 1;
			}
		if (n->right == NO_NODE) {
			node* temp = n->left;
         temp->parent = n->parent;
			delete n;
			n= temp;
			return 1;
			}
		node* victim = n->right;
		while (victim->left!=NO_NODE) {
			victim = victim->left;
			}
		swapElements(victim, n);
	 	if (victim == victim->parent->right) 
			victim->parent->right = victim->right;
		else victim->parent->left = victim->right;
		delete victim;
		return 1;
		}
	else if (k< n->key) return deleteElement(k,n->left);
	else return deleteElement(k,n->right);
}

void rbtree::print(node *n)
// display the key/data contents of the subtree rooted at n,
// sorted (ascending) by key value
{
   if (n == NO_NODE) return;
   print(n->left);
   cout << n->key << ":" << n->data << endl;
   print(n->right);
}

void rbtree::debugprint(node *n)
// display the contents and structure of the subtree rooted at n,
// performed via preorder traversal
{
   string colstring[2] = {"B","R"};
   if (n == NO_NODE) return;
   cout << n->key << ":" << n->data << ":" << colstring[n->red]<<" (";
   if (n->left != NO_NODE) cout << n->left->key;
   else cout << "N";
   if (n->parent!=NO_NODE) cout << "<-left " << n->parent->key << " right->";
   else cout << "<-left N right->";
   if (n->right!= NO_NODE) cout << n->right->key;
   else cout << "N";
   cout << ") ";

   debugprint(n->left);
   debugprint(n->right);
}


void rbtree::swapElements(node* n, node* m)
{
   node temp;
   temp.data = n->data;
   n->data = m->data;
   m->data = temp.data;

   temp.key = n->key;
   n->key= m->key;
   m->key= temp.key;
}

void rbtree::leftRotate(node* x)
{
   
   if (x == NO_NODE) return; 
   if (x->right== NO_NODE) return; 
   //if (x->parent == NO_NODE) return; 
   // write your leftRotate code here
   node* c_child = x->right;
   x->right = c_child->left;
	
   if(c_child->left != NO_NODE){
   	 c_child -> parent = x->parent;
   } 

   c_child->parent = x->parent;
   if(x->parent == NO_NODE){
	  root = c_child;
   }else if(x == x->parent->left){
	  x->parent->left = c_child;
   }else{
	 x->parent->right = c_child;
   }
   
   c_child->left = x;
   x->parent = c_child;
	  	
}
void rbtree::rightRotate(node* x)
{
   if (x == NO_NODE) return; 
   if (x->left == NO_NODE) return; 
   //if (x->parent == NO_NODE) return; 
   // write your leftRotate code here
   node* c_child = x->left;
   x->left = c_child->right;
	
   if(c_child->right != NO_NODE)
   {
   	 c_child->parent = x->parent;
   } 

   c_child->parent = x->parent;
   if(x->parent==NO_NODE)
   {
	  root = c_child;
   }else if(x==x->parent->right)
   {
	  x->parent->right = c_child;
   }else
   {
	 x->parent->left = c_child;
   }
   
   c_child->right = x;
   x->parent = c_child;
}

void rbtree::InsertNew(node* n)
{
     n->red =1;
	while(n != root&&n->parent->red ==1)
	{
		if(n->parent == n->parent->parent->left)
		{
			node *uncle = n->parent->parent->right;
			if(uncle->red == 1)
			{
				n->parent->red = 0;
				uncle->red = 0;
				n->parent->parent->red = 1;
				n = n->parent->parent;	
			}
		
		else if(n == n->parent->right)
		{
			n = n->parent;
			leftRotate(n);
			n->parent->parent->red = 1;
			rightRotate(n->parent->parent);
		}
		else
		{
			n->parent->red = 0;
			n->parent->parent->red = 1;
			rightRotate(n->parent->parent);
		
		}
	
	 }else
	 {
		
		node *uncle = n->parent->parent->left;
			if(uncle->red == 1)
			{
				n->parent->red = 0;
				uncle->red = 0;
				n->parent->parent->red = 1;
				n = n->parent->parent;	
			}
		
		else if(n == n->parent->right)
		{
			n = n->parent;
			leftRotate(n);
			n->parent->parent->red = 1;
			rightRotate(n->parent->parent);
		}
		else
		{
			n->parent->red = 0;
			n->parent->parent->red = 1;
			rightRotate(n->parent->parent);
		
		}
	}
 
}	 
	root->red = 0;
}
void rbtree::testrightRotate(int k, node* n)
{
     if (n == NO_NODE) return;
     if (k < n->key) testrightRotate(k,n->left);
     else if (k > n->key) testrightRotate(k,n->right);
     else 
	      rightRotate(n);

}
void rbtree::testLeftRotate(int k, node* n)
{
     if (n == NO_NODE) return;
     if (k < n->key) testLeftRotate(k,n->left);
     else if (k > n->key) testLeftRotate(k,n->right);
     else 
	      leftRotate(n);

}

