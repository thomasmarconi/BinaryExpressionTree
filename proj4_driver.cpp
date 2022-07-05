#include <iostream>
#include <string>
#include "bet.h"

using namespace std;

int main() {
    string postfix;

    // get a postfix expression
    cout << "Enter the first postfix expression: ";
    getline(cin, postfix);

    // create a binary expression tree
    BET bet1(postfix);
    if (!bet1.empty()) {
    	cout << "Infix expression: ";
    	bet1.printInfixExpression();

	cout << "\nPostfix expression: ";
	bet1.printPostfixExpression();

	cout << "\nNumber of nodes: ";
	cout << bet1.size() << endl;

	cout << "Number of leaf nodes: ";
	cout << bet1.leaf_nodes() << endl;

  cout << "Height of tree: ";
  cout << bet1.height() << endl;
    	// test copy constructor
    	BET bet2(bet1);
    	cout << "Testing copy constructor: ";
    	bet2.printInfixExpression();

    	// test assignment operator
    	BET bet3;
    	bet3 = bet1;
    	cout << "\nTesting assignment operator: ";
    	bet3.printInfixExpression();

    }

    cout << "\nEnter a postfix expression (or \"quit\" to quit): ";
    while (getline(cin, postfix)) {
	if (postfix == "quit") {
	    break;
        }
	if (bet1.buildFromPostfix(postfix)) {
	    cout << "Infix expression: ";
	    bet1.printInfixExpression();

	    cout << "\nPostfix expression: ";
	    bet1.printPostfixExpression();

	    cout << "\nNumber of nodes: ";
	    cout << bet1.size() << endl;

	    cout << "Number of leaf nodes: ";
	    cout << bet1.leaf_nodes() << endl;

      cout << "Height of tree: ";
      cout << bet1.height() << endl;
	}
	cout << "Enter a postfix expression (or \"quit\" to quit): ";
    }
    return 0;
}
