#include "line.h"
#include <bits/stdc++.h>
#include "statusStructure.h"
#include "eventQueue.h"

int main(){
       TreeNode * root = new TreeNode();

       vector<double> point1 = {2,2};
       vector<double> point2 = {-2,-2};
       vector<double>  point3 = {-1,5};
       vector<double>  point4 = {2,-4};

       Line l1 =  Line(point1,point2);
       Line l2 = Line(point3,point4);
      
      EventQueue * e = new EventQueue();
       
       e->root=e->Insert(e->root, point1,l1);
       e->root=e->Insert(e->root, point2,l1);
       e->root=e->Insert(e->root, point3,l2);
       e->root=e->Insert(e->root, point4,l2);

       vector<Node *> vec = e->inOrder();

       for(int i=0; i<vec.size(); i++){
         Line l = vec[i].lines;
       }

       



       












       return 0;

    }