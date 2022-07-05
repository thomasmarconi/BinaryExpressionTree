#include <iostream>
BET::BET() //default zero-parameter constructor. Builds an empty tree.
{
  root = nullptr;
  h = 0;
}
BET::BET(const string& postfix) //one-parameter constructor, where parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by spaces.
{
  h = 0;
  int counter = 0;
  stringstream stream(postfix);
  string current;

  while (stream >> current)
  {
    if(counter<0)
      std::cout<<"error: bad string"<<std::endl;
    if(current != "+" && current != "-" && current != "*" && current != "/")
    {
      //create a new node
      //push it into the stack
      BinaryNode* bNode = new BinaryNode{current,nullptr,nullptr};
      stack.push_back(bNode);
      counter++;
    }
    else
    {
      BinaryNode* right = stack.back();
      stack.pop_back();
      BinaryNode* left = stack.back();
      stack.pop_back();
      BinaryNode* b = new BinaryNode{current,left,right};
      stack.push_back(b);
      counter--;
      counter--;
      if(counter<0)
        std::cout<<"error: bad string"<<std::endl;
      counter++;
    }
  }
  root = stack.back();
  if(counter != 1)
    std::cout<<"error: bad string"<<std::endl;
}
BET::BET(const BET& rhs) : root{nullptr} //copy constructor -- makes appropriate deep copy of the tree
{
  root = clone(rhs.root);
}
BET::~BET() //destructor -- cleans us all dynamic space in the tree
{
  makeEmpty(root);
}
bool BET::buildFromPostfix(const string& postfix) //parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by spaces. If the tree contains nodes before the function is called, you need to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is encountered.
{
  if(!empty())
    makeEmpty(root);

  stringstream stream(postfix);
  string current;
  int counter = 0;
  while (stream >> current)
  {
    if(counter<0)
    {
      std::cout<<"error: bad string"<<std::endl;
      return false;
    }
    if(current != "+" && current != "-" && current != "*" && current != "/")
    {
      //create a new node
      //push it into the stack
      BinaryNode* bNode = new BinaryNode{current,nullptr,nullptr};
      stack.push_back(bNode);
      counter++;
    }
    else
    {
      BinaryNode* right = stack.back();
      stack.pop_back();
      BinaryNode* left = stack.back();
      stack.pop_back();
      BinaryNode* b = new BinaryNode{current,left,right};
      stack.push_back(b);
      counter--;
      counter--;
      if(counter<0)
      {
        std::cout<<"error: bad string"<<std::endl;
        return false;
      }
      counter++;
    }
  }
  root = stack.back();
  if(counter != 1)
  {
    std::cout<<"error: bad string"<<std::endl;
    return false;
  }
  else
    return true;
}
const BET& BET::operator=(const BET& rhs) //assignment operator -- makes appropriate deep copy
{
  root = clone(rhs.root);
  return *this;
}
void BET::printInfixExpression() const //print out the infix expression Should do this by making use of the private (recursive) version
{
  printInfixExpression(root);
}
void BET::printPostfixExpression() const //Print the postfix form of the expression. Use the private recursive function to help
{
  printPostfixExpression(root);
}
size_t BET::size() const //Return the number of nodes in the tree (using the private recursive function)
{
  return size(root);
}
size_t BET::leaf_nodes() const // Return the number of leaf nodes in the tree. (Use the private recursive function to help)
{
  return leaf_nodes(root);
}
bool BET::empty() const //return true if the tree is empty. Return false otherwise.
{
  if(root == nullptr)
    return true;
  else
    return false;
}

//all following must be recursive
void BET::printInfixExpression(BinaryNode* n) const //print to the standard output the corresponding infix expression. Note that you may need to add parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
{
  bool openParen = false;
  if(n != nullptr)
  {
    if(n->leftChild != nullptr && isOperator(n->element) && isOperator(n->leftChild->element) &&(isOperator(n->element) > isOperator(n->leftChild->element)))
    {
      std::cout<<"( ";
      openParen = true;
    }
    printInfixExpression(n->leftChild);
    if(openParen)
    {
      std::cout<<") ";
      openParen = false;
    }
    std::cout<<n->element<<" ";
    if(n->leftChild != nullptr && isOperator(n->element) && isOperator(n->rightChild->element) && (isOperator(n->element) >= isOperator(n->rightChild->element)))
    {
      std::cout<<"( ";
      openParen = true;
    }
    printInfixExpression(n->rightChild);
    if(openParen)
    {
      std::cout<<") ";
      openParen = false;
    }
  }
}
void BET::makeEmpty(BinaryNode* &t) //delete all nodes in the subtree pointed to by t.
{
  if( t != nullptr )
  {
      makeEmpty( t->leftChild );
      makeEmpty( t->rightChild );
      delete t;
  }
  t = nullptr;
}
BET::BinaryNode* BET::clone(BinaryNode *t) const // clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator=
{
  if (t == nullptr)
    return nullptr;
  else
    return new BinaryNode{t->element, clone(t->leftChild), clone(t->rightChild)};
}
void BET::printPostfixExpression(BinaryNode *n) const //print to the standard output the corresponding postfix expression.
{
  if(n != nullptr)
  {
    printPostfixExpression(n->leftChild);
    printPostfixExpression(n->rightChild);
    std::cout<<n->element<<" ";
  }
}
size_t BET::size(BinaryNode *t) const // return the number of nodes in the subtree pointed to by t.
{
  if(t==nullptr)
    return 0;
  else
    return (1 + size(t->leftChild) + size(t -> rightChild));
}
size_t BET::leaf_nodes(BinaryNode *t) const // return the number of leaf nodes in the subtree pointed to by t.
{
  if(t == nullptr)
    return 0;
  else if (t->leftChild == nullptr && t->rightChild == nullptr)
    return 1;
  else
    return (leaf_nodes(t->leftChild) + leaf_nodes(t->rightChild));

}
int BET::isOperator(string s) const
{
  if(s == "*" || s =="/" )
    return 2;
  else if(s=="+" || s=="-")
    return 1;
  else
    return 0;
}
