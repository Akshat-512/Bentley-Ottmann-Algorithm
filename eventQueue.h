#pragma once
#include "line.h"
#include<stdlib.h>
#include<iostream>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

class Node
{
    public:
    vector<double> point;
    vector<Line> lines;
    Node* left;
    Node* right;
    int height;
    int i;
 
    Node(){
        this->lines.resize(0) ; 
        this->left = NULL ;
        this->right = NULL ;
        this->height = 1 ;
        this->i =-1;


    }
    Node(vector<double> point , Line line, int i){
        this->point = point;
        if(line.upper_endpoint.size() != 0)this->lines.push_back(line) ;
        else this->lines.resize(0) ;
        this->left = NULL ;
        this->right = NULL ;
        this->height = 1 ;
        this->i=i;
    }
    
};

double compare(vector <double> p, vector <double> q)
{
    double px = p[0];
    double py = p[1];
    double qx = q[0];
    double qy = q[1];
    if(py!=qy)
        return qy-py;
    else
        return px-qx; //Points have same y coordinate 
}

class EventQueue
{   public:
    Node* root;
    
    
    EventQueue()
    {
        this->root = NULL;
    }
    
    Node* Insert(Node* root, vector<double> point, Line line, int i)//null shouldn't come here
    {
        if(root == NULL) 
            return root=new Node(point, line, i);
        
        else if (compare(point, root->point)<0)
        {
            root->left = this->Insert(root->left, point, line, i);
        }
        else if (compare(point, root->point)>0)
        {
            root->right= this->Insert(root->right, point, line, i);
        }
        else
        {
            if(line.upper_endpoint.size() != 0)
                root->lines.push_back(line);
            return root;
        }
            
        root->height = 1 + max(this->getHeight(root->left), this->getHeight(root->right));
        int balance = this->getBalance(root);    
            
        if(balance>1 && compare(point, root->point)<0)
        {
            return this->rightRotate(root);
        }
        if(balance<-1 && compare(point, root->point)>0)
        {
            return this->leftRotate(root);
        }
        if(balance>1 && compare(point, root->point)>0)
        {
            root->left =  this->rightRotate(root->left);
            return this->rightRotate(root);
        }
        if(balance<-1 && compare(point, root->point)<0 )
        {
            root -> right = this->rightRotate(root->right);
            return this->leftRotate(root);
        }
        return root;
    }
    
   
 /* useless  void insert_line(vector<Line> line)
    {
        upper_end = line->upper_endpoint ;
        lower_end = line->lower_endpoint ;
        this->root = this->Insert(this->root, upper_end, line) ;
        Line temp; 
        this->root = this->Insert(this->root, lower_end, temp) ;
    }
    
 */   
    //  void insert(vector<double> point)
    // {
    //     Line temp; 
    //     this->root = this->Insert(this->root, point, temp);
    // }
    
   
    //Left rotation of BST at a node
    Node* leftRotate(Node* z)
    {
            Node* y = z->right;
            Node* temp = y->left;
            y->left = z;
            z->right = temp;
            z->height = 1+max(this->getHeight(z->left), this->getHeight(z->right));
            y->height = 1+max(this->getHeight(y->left), this->getHeight(y->right));
            return y;
    }
    //Right rotation of BST at a node
    Node* rightRotate(Node* z)
    {
            Node* y = z->left;
            Node* temp = y->right;
            y->right = z;
            z->left = temp;
            z->height = 1+max(this->getHeight(z->left), this->getHeight(z->right));
            y->height = 1+max(this->getHeight(y->left), this->getHeight(y->right));
            return y;
    }
    
    int getHeight(Node* root)
    {
        if(root==NULL)
            return 0;
        return root->height;
    }
    
    int getBalance(Node* root) 
    {
        if(root==NULL)
            return 0;
        return this->getHeight(root->left)-this->getHeight(root->right);
    }
    
    void _inOrder(Node* root, vector<Node*>& result) 
    {
        if(root==NULL)
            return;
        this->_inOrder(root->left, result);
        result.push_back(root);
        this->_inOrder(root->right, result);
    }
    
    vector<Node*> inOrder()
    {
        vector<Node*> result;
        this->_inOrder(this->root, result);
        return result;
    }
        
    void delete_(vector<double> point)
    {
        this->root = this->_delete(this->root, point);
    }
    
    
    Node* get_max()
    {
        Node* current = this->root;
        while(current->right != NULL)
            current = current->right;
        return current;  
    }
    
    Node* pop_next_event()
    {
        Node* current = this->get_max();
        this->delete_(current->point);
        return current;
    }
    
    
    Node* _delete(Node* root, vector<double> key)
    {
        if(root == NULL)
            return root;
        else if (compare(key, root->point)<0)
            root->left = this->_delete(root->left, key);
        else if (compare(key, root->point)>0)
            root->right = this->_delete(root->right, key);
        else
        {
            if(root->left == NULL)
            {
                Node* temp = root->right; 
                root = NULL;
                return temp;
            }
            else if(root->right == NULL)
            {
                Node* temp = root->left;
                root = NULL;
                return temp;
            }
            
            Node* temp = this->getMinValueNode(root->right);
            root->point = temp->point;
            root->lines = temp->lines;
            root->right = this->_delete(root->right, temp->point);
        }
        
        if(root == NULL)
            return root;
            
        root->height = 1+max(this->getHeight(root->left), this->getHeight(root->right));
        int balance = this->getBalance(root);
        
        if(balance>1 && this->getBalance(root->left)>=0)
            return this->rightRotate(root);
        if(balance<-1 && this->getBalance(root->right)<=0)
            return this->leftRotate(root);
        if(balance>1 && this->getBalance(root->left)<0)
        {
            root->left = this->leftRotate(root->left);
            return this->rightRotate(root);
        }
        if(balance<-1 && this->getBalance(root->right)>0)
        {
            root->right = this->rightRotate(root->right);
            return this->leftRotate(root);
        }
        return root;
    }
    
    
    Node* getMinValueNode(Node* root)
    {
        if(root==NULL || root->left==NULL)
            return root;
        return this->getMinValueNode(root->left);
    }
    
    int is_empty()
    {
        if(this->root == NULL)
            return 1;
        else 
            return 0;
    }
    
    
};





