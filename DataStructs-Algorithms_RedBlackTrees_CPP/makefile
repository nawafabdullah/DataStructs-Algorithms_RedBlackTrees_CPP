
testapp:	testapp.o rbtree.o
	g++ -o testapp testapp.o rbtree.o

testapp.o:	rbtree.h testapp.cpp
	g++ -c testapp.cpp

bst.o:	bst.h rbtree.cpp
	g++ -c rbtree.cpp

