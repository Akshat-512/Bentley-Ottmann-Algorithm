#pragma once
#include <bits/stdc++.h>
#include "line.h"
using namespace std;
class TreeNode{
    public:
    Line line;
    TreeNode* left;
    TreeNode* right;
    int height;
    
    TreeNode(){
        this->line =  Line() ; //check
        this->left = NULL ;
        this->right = NULL ;
        this->height = 1 ;

    }
    TreeNode(Line line){
        this->line = line ; //check
        this->left = NULL ;
        this->right = NULL ;
        this->height = 1 ;
    }
   
    void copy(TreeNode* node){
        this->line=Line(node->line.upper_endpoint , node->line.lower_endpoint)   ; // check
        this->left = node->left;
        this->right = node->right;
        this->height = node->height ;
    }
};
class StatusStructure{
    TreeNode* root ;
    public:
    StatusStructure(){
        this->root = NULL ;
    }
    TreeNode* Insert(TreeNode* root, vector<double> point , Line line){
        if(root == NULL) return new TreeNode(line) ;
        else if (root->line.compare_lower(point, line) > 0){
            root -> left = this->Insert(root->left, point, line) ;
        } 
        else{
            root-> right = this->Insert(root->right, point, line) ;
        }
        root->height = 1 + max(this->getHeight(root->left), this->getHeight(root->right)) ;
        int balance = this->getBalance(root) ;
        if(balance > 1 && root->line.compare_lower(point, line) > 0){
            return this->rightRotate(root) ;
        }
        if(balance < -1 && root->line.compare_lower(point, line) < 0){
            return this->leftRotate(root) ;
        }
        if(balance > 1 && root->line.compare_lower(point, line) < 0){
            root->left =  this->rightRotate(root->left) ;
            return this->rightRotate(root) ;
        }
        if(balance <-1 && root->line.compare_lower(point,line) >0 ){
            root -> right = this->rightRotate(root->right) ;
            return this->leftRotate(root) ;
        }
        return root ;
    }
    void insert(vector<double> point, vector<Line> lines){
        for(int i = 0 ; i < lines.size() ; i++){
            this -> root = this->Insert(this-> root , point , lines[i]) ;
        }
       
    }
    
        // done till line 54 of the github code of status Structure
    TreeNode* leftRotate(TreeNode* z){
        TreeNode* y = z->right ;
        TreeNode* temp = y->left ;
        y -> left = z ;
        z -> right = temp ;
        z -> height = 1 + max(this->getHeight(z->left) , this->getHeight(z->right)) ;
        y -> height = 1 + max(this->getHeight(y->left) , this->getHeight(y->right)) ;
        return y ;

    }
        // 64 done
    TreeNode* rightRotate(TreeNode* z){
        TreeNode* y = z->left ;
        TreeNode* temp = y->right ;
        y -> right = z ;
        z -> left = temp ;
        z -> height = 1 + max(this->getHeight(z->left) , this->getHeight(z->right)) ;
        y -> height = 1 + max(this->getHeight(y->left) , this->getHeight(y->right)) ;
        return y ;

    }
    //76 done
    int getHeight(TreeNode* root){
        if(root == NULL)return 0 ;
        return root -> height ;
    }
    int getBalance(TreeNode* root ){
        if(root == NULL)return 0 ;
        return this->getHeight(root->left) - this->getHeight(root-> right) ;
    }
    //86 done
    void InOrderTree(TreeNode* root, vector<TreeNode*> *result){
        if(root == NULL)return ;
        this->InOrderTree(root -> left , result) ;
        (*result).push_back(root) ;
        this->InOrderTree(root -> right, result) ;
    }
    vector<TreeNode*> inOrder(){
        vector<TreeNode*> result ;
        this->InOrderTree(this->root, &result) ;
        return result ;
    }
    void deleteLine(vector<double> point, Line line){
        this->root = this->deletePoint(this->root,point, line) ;
    }
    void deleteLines(vector<double> point , vector<Line> lines) {
        for(int i = 0 ; i < lines.size() ; i++){
            this->deleteLine(point, lines[i]) ;
        }
    }
    TreeNode* deletePoint(TreeNode* root, vector<double> point, Line line){
        if(root == NULL){
            return root ;
        }
        else if((root -> line).compare_upper(point, line) > 0){               //compare _lower added instead of compare upper?
            root -> left = this->deletePoint(root->left,point, line) ;
        }
        else if((root-> line).compare_upper(point,line) < 0){
            root -> right = this->deletePoint(root -> right, point, line) ;
        }
        else{
            TreeNode* temp ;
            if(root -> left == NULL){
                temp = root -> right ;
                root = NULL ;
                return temp ;
            }
            else if(root -> right == NULL){
                temp = root -> left ;
                root = NULL ;
                return temp ;
            }
            temp = this->getMinimumValueOfNode(root->right) ;
            root -> line  = temp -> line ;
            root-> right = this->deletePoint(root -> right, point, temp -> line);
        }

        if(root == NULL)return root ;
        root->height = 1 + max(this->getHeight(root->left) , this->getHeight(root -> right)) ;
        int balance = this->getBalance(root) ;
        if(balance > 1 && this->getBalance(root -> left) >= 0){
            return this->rightRotate(root) ;
        }
        if(balance < -1 && this->getBalance(root -> right) <= 0){
            return this->leftRotate(root) ;
        }
        if(balance > 1 && this->getBalance(root -> left) < 0){
            root->left =  this->rightRotate(root->left) ;
            return this->rightRotate(root) ;
        }
        if(balance <-1 && this->getBalance(root -> right) >0 ){
            root -> right = this->rightRotate(root->right) ;
            return this->leftRotate(root) ;
        }
        return root ;
    }
    TreeNode* getMinimumValueOfNode(TreeNode* root ){
        if(root == NULL || root-> left == NULL)return root ;
        return this->getMinimumValueOfNode(root -> left) ;
    }
    //149 done
    void findSegmentsContain(vector<double> point){
        vector<Line> L ,C, LC ; 
        this->findSegments(this->root, point, &L, &C, &LC) ;
    }
    void findSegments(TreeNode* root , vector<double> point ,  vector<Line> *L , vector<Line> *C , vector<Line> *LC ){
        if(root == NULL) return ;
        else if(root -> line.point_location(point) > 0 ){
            this->findSegments(root->right , point , L , C, LC) ;
        }
        else if(root -> line.point_location(point) < 0 ){
            this->findSegments(root->left , point , L , C, LC) ;
        }
        else{
            if(root -> left != NULL){
                this->findSegments(root -> left , point, L,C ,LC) ; 
            }
            if(root -> line.lower_endpoint[0] == point[0] && root-> line.lower_endpoint[1] == point[1] ){
                (*L).push_back(root -> line) ;
            }
            else{
                (*C).push_back(root-> line) ;
            }
            (*LC).push_back(root -> line) ;
            if(root -> right != NULL){
                this->findSegments(root->right, point, L, C, LC) ;
            }
        }
    }
    Line findLeftNeighbour(vector<double> point){
        TreeNode* leftneighbour = NULL ;
        this->findLeft(this->root , point , &leftneighbour) ;
        return leftneighbour -> line ;

    }
    Line findRightNeighbour(vector<double> point){
        TreeNode* rightneighbour = NULL ;
        this->findRight(this->root, point, &rightneighbour) ;
        return rightneighbour -> line ;
    }
    void findLeft(TreeNode* root, vector<double> point, TreeNode **leftneighbour){
        if(root == NULL)return ;
        if(root -> line.point_location(point) > 0 ){
            *leftneighbour = new TreeNode() ;
            (**leftneighbour).copy(root) ;
            this->findLeft(root->right, point , leftneighbour) ;
        }
        else if (root -> line.point_location(point) <= 0){
            this->findLeft(root -> left, point, leftneighbour) ;
        }
    }
    void findRight(TreeNode* root, vector<double> point, TreeNode **rightneighbour){
        if(root == NULL)return ;
        if(root -> line.point_location(point) >= 0 ){
            
            this->findRight(root->right, point , rightneighbour) ;
        }
        else if (root -> line.point_location(point) < 0){
            *rightneighbour = new TreeNode() ;
            (**rightneighbour).copy(root) ;
            this->findRight(root -> left, point, rightneighbour) ;
        }
    }
    void findLeftMostNode(TreeNode* root , vector<double> point, TreeNode **leftmost){
        if(root == NULL) return ;
        if(root -> line.point_location(point) > 0){
            this->findLeftMostNode(root -> right , point, leftmost) ;
        }
        else if(root -> line.point_location(point) < 0){
            this->findLeftMostNode(root -> left , point, leftmost) ;
        }
        else {
             this->findLeftMostNode(root -> right , point, leftmost) ;
             *leftmost = new TreeNode() ;
             (**leftmost).copy(root) ;
             this->findLeftMostNode(root -> left , point, leftmost) ;

        }
    }
    void findRightMostNode(TreeNode* root , vector<double> point, TreeNode **rightmost){
        if(root == NULL) return ;
        if(root -> line.point_location(point) > 0){
            this->findRightMostNode(root -> right , point, rightmost) ;
        }
        else if(root -> line.point_location(point) < 0){
            this->findRightMostNode(root -> left , point, rightmost) ;
        }
        else {
             this->findRightMostNode(root -> left , point, rightmost) ;
             *rightmost = new TreeNode() ;
             (**rightmost).copy(root) ;
             this->findRightMostNode(root -> right , point, rightmost) ;

        }
    }
    Line findLeftMost(vector<double> point){
        TreeNode* leftmost = NULL ;
        this->findLeftMostNode(this->root , point, &leftmost ) ;
        return leftmost -> line ;
    }
    Line findRightMost(vector<double> point){
        TreeNode* rightmost = NULL ;
        this->findRightMostNode(this->root , point, &rightmost ) ;
        return rightmost -> line ;
    }
    
    
};

