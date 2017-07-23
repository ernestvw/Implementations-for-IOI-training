#include <bits/stdc++.h>
using namespace std;

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
  int height;
};

int height(Node *node) {
  if(node==NULL)
    return 0;
  return node->height;
}

Node *newNode(int data) {
  Node *node=new Node;
  node->data=data;
  node->left=NULL;
  node->right=NULL;
  node->height=1;
  return node;
}

Node *rightRotate(Node *y) {
  Node *x=y->left;
  Node *T2=x->right;
  x->right=y;
  y->left=T2;
  y->height=max(height(y->left),height(y->right))+1;
  x->height=max(height(x->left),height(x->right))+1;
  return x;
}

Node *leftRotate(Node *x) {
  Node *y=x->right;
  Node *T2=y->left;
  y->left=x;
  x->right=T2;
  x->height=max(height(x->left),height(x->right))+1;
  y->height=max(height(y->left),height(y->right))+1;
  return y;
}

int getBalance(Node *node) {
  if(node==NULL)
    return 0;
  return height(node->left)-height(node->right);
}

Node *insert(Node *node,int data) {
  if(node==NULL)
    return newNode(data);
  if(data<node->data)
    node->left=insert(node->left,data);
  else if(data>node->data)
    node->right=insert(node->right,data);
  else
    return node;
  node->height=1+max(height(node->left),height(node->right));
  int balance=getBalance(node);
  if(balance>1 && data<node->left->data)
    return rightRotate(node);
  if(balance<-1 && data>node->right->data)
    return leftRotate(node);
  if(balance>1 && data<node->left->data) {
    node->left=leftRotate(node->left);
    return rightRotate(node);
  }
  if(balance<-1 && data<node->right->data) {
    node->right=rightRotate(node->right);
    return leftRotate(node);
  }
  return node;
}

Node *minValue(Node *node) {
  Node *cur=node;
  while(cur->left!=NULL)
    cur=cur->left;
  return cur;
}

Node *remove(Node *root,int data) {
  if(root==NULL)
    return root;
  if(data<root->data)
    root->left=remove(root->left,data);
  else if(data>root->data)
    root->right=remove(root->right,data);
  else {
    if(root->left==NULL || root->right==NULL) {
      Node *temp=root->left ? root->left : root->right;
      if(temp==NULL) {
        temp=root;
        root=NULL;
      }
      else
        *root=*temp;
      free(temp);
    }
    else {
      Node *temp=minValue(root->right);
      root->data=temp->data;
      root->right=remove(root->right,temp->data);
    }
  }
  if(root==NULL)
    return root;
  root->height=1+max(height(root->left),height(root->right));
  int balance=getBalance(root);
  if(balance>1 && getBalance(root->left)>=0)
    return rightRotate(root);
  if(balance>1 && getBalance(root->left)<0) {
    root->left=leftRotate(root->left);
    return rightRotate(root);
  }
  if(balance<-1 && getBalance(root->right)<=0)
    return leftRotate(root);
  if(balance<-1 && getBalance(root->right)>0) {
    root->right=rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

void preOrder(Node *root) {
  if(root!=NULL) {
    printf("(");
    preOrder(root->left);
    printf(")");
    printf("%d",root->data);
    printf("(");
    preOrder(root->right);
    printf(")");
  }
}

int main()
{
  Node *root=NULL;
  int n;
  scanf("%d",&n);
  for(int i=0;i<n;i++) {
    int data;
    scanf("%d",&data);
    root=insert(root,data);
  }
  preOrder(root);
  printf("\n");
  root=remove(root,10);
  preOrder(root);
  printf("\n");

  return 0;
}
