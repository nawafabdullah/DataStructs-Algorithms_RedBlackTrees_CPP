/* 
* Nawaf Alharbi
* Data structures and Algorithms
* Red Black Trees 
*/

#include "rbtree.h"
#include <iostream>

char getcommand();
void printmenu();
bool processcommand(char cmd, rbtree &tree);

int main()
{
   rbtree B;
   
   printmenu();
   char cmd = getcommand();
   while (processcommand(cmd, B)) { 
      cout << endl;
      cmd = getcommand();
   }

   return 0;
}

char getcommand()
{
   cout << "Enter your command choice (D, P, H, I, Q, R, or F)" << endl;
   char cmd;
   cin >> cmd;
   cmd = toupper(cmd);
   switch (cmd) {
      case 'H':
      case 'I':
      case 'R':
      case 'F':
      case 'P':
      case 'Q':
      case 'L':
      case 'D': return cmd;
      default:  cout << "You have entered an invalid command" << endl;
                return getcommand();
   }
}

void printmenu()
{
   cout << "Enter I to insert a new element," << endl;
   cout << "   or R to remove an element with given key," << endl;
   cout << "   or F to find an element with given key and print its data," 
      << endl;
   cout << "   or P to print all elements," << endl;
   cout << "   or D to for debug data display," << endl;
   cout << "   or H for help," << endl;
   cout << "   or Q to quit." << endl;
   cout << "   or L to left-rotate at a node." << endl;
}

bool processcommand(char cmd, rbtree &tree)
{
   int k; string d;
   switch (cmd) {
      case 'H': printmenu(); 
                break;
      case 'I': cout << "Enter the key integer" << endl;
               cin >> k;
               cout << "Enter the data word" << endl;
               cin >> d;
               cout << "(" << k << "," << d << ") ";
               if (tree.insert(k, d)) 
                  cout << "was inserted successfully" << endl;
               else cout << "was not inserted correctly" << endl;
               break;
      case 'R': cout << "Enter the key integer" << endl;
      	      cin >> k;
		         if (tree.deleteElement(k))
		            cout << k << " was successfully deleted." << endl;
		         else cout << k << " was not deleted -- not in tree." << endl;
                break;   
   case 'F': cout << "Enter the key integer" << endl;
      	      cin >> k;
		         d = (tree.find(k));
		         if (d==INVALID_STRING)   
                  cout << k << " was not found." << endl;
		         else cout <<"Key associated with "<< k << " is " << d <<endl;
               break;
      case 'P': cout << "The tree contents are: ";
               tree.display();
                break;
      case 'L': cout << "Enter the key to rotate left: ";
      	      cin >> k;
		         tree.testLeftRotate(k);
               break; 
      case 'D': cout << "The tree debug data is:" << endl;
               tree.debug();
               break; 
      default: return false;
   }
   return true;
}

