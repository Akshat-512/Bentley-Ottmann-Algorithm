#pragma once
#include<bits/stdc++.h>
#include<math.h>
#include<stdlib.h>
#include <cmath>
#include<tgmath.h>
#include<typeinfo>
#define _USE_MATH_DEFINES
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
using namespace std;
class Line{
    public:
    vector<double> upper_endpoint ;
    vector<double> lower_endpoint ; 
    
    Line(){
        upper_endpoint.resize(0) ;
        lower_endpoint.resize(0) ;
    
    }
    Line(vector<double> endpoint_1, vector<double> endpoint_2){
        if(endpoint_1[1] > endpoint_2[1]){
            this->upper_endpoint.push_back(endpoint_1[0]) ;
            this->upper_endpoint.push_back(endpoint_1[1]) ;
            this->lower_endpoint.push_back(endpoint_2[0]) ;
            this->lower_endpoint.push_back(endpoint_2[1]) ;

        }
        else if (endpoint_1[1] < endpoint_2[1]){
            this->upper_endpoint.push_back(endpoint_2[0]) ;
            this->upper_endpoint.push_back(endpoint_2[1]) ;
            this->lower_endpoint.push_back(endpoint_1[0]) ;
            this->lower_endpoint.push_back(endpoint_1[1]) ;
        }
        else if (endpoint_1[0] < endpoint_2[0]){
            this->upper_endpoint.push_back(endpoint_1[0]) ;
            this->upper_endpoint.push_back(endpoint_1[1]) ;
            this->lower_endpoint.push_back(endpoint_2[0]) ;
            this->lower_endpoint.push_back(endpoint_2[1]) ;

        }
        else {
            this->upper_endpoint.push_back(endpoint_2[0]) ;
            this->upper_endpoint.push_back(endpoint_2[1]) ;
            this->lower_endpoint.push_back(endpoint_1[0]) ;
            this->lower_endpoint.push_back(endpoint_1[1]) ;
        }
        
    }
    vector<double> intersect(Line line){
        vector<double> temp;
        double x1 = this->upper_endpoint[0] ;
        double y1 = this->upper_endpoint[1] ;
        double x2 = this->lower_endpoint[0] ;
        double y2 = this->lower_endpoint[1] ;
        double x3 = line.upper_endpoint[0] ;
        double y3 = line.upper_endpoint[1] ;
        double x4 = line.lower_endpoint[0] ;
        double y4 = line.lower_endpoint[1] ;
        if ((x4-x3)*(y2-y1) == (x1-x2)*(y3-y4)) return temp ;
        double xi = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4))/((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)) ;
        double yi = ((x1*y2-y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4))/((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)) ;
        if (xi < max(min(x1, x2), min(x3, x4)) or xi > min(max(x1, x2), max(x3, x4))) return temp ;
        temp.push_back(xi) ;
        temp.push_back(yi) ;
        return temp ;
    }
    int point_location(vector<double> point){
        double x1 = this->upper_endpoint[0] ;
        double y1 = this->upper_endpoint[1] ;
        double x2 = this->lower_endpoint[0] ;
        double y2 = this->lower_endpoint[1] ;
        double x = point[0] ; int y = point[1] ;
        if ((x2 - x1)*(y - y1) - (y2 - y1)*(x - x1) < 0) return -1 ;
        else if ((x2 - x1)*(y - y1) - (y2 - y1)*(x - x1) == 0) return 0 ;
        else return 1 ;        
    }
    double get_lower_angle() {
        double x1 = this->upper_endpoint[0] ;
        double y1 = this->upper_endpoint[1] ;
        double x2 = this->lower_endpoint[0] ;
        double y2 = this->lower_endpoint[1] ;
        double angle = atan2(y2 - y1 , x2 - x1)*180/M_PI ;
        if(angle <= 0 ) angle += 360 ;
        return angle ;
    }
    double get_upper_angle() {
        double x1 = this->lower_endpoint[0] ;
        double y1 = this->lower_endpoint[1] ;
        double x2 = this->upper_endpoint[0] ;
        double y2 = this->upper_endpoint[1] ;
        
        double angle = atan2(y2 - y1 , x2 - x1)*180/M_PI ;
        if(angle < 0 ) angle += 360 ;
        return angle ;
    }
    double get_x(int y){
        double x1 = this->lower_endpoint[0] ;
        double y1 = this->lower_endpoint[1] ;
        double x2 = this->upper_endpoint[0] ;
        double y2 = this->upper_endpoint[1] ;
        if (y1 == y2) return x1 ;
        double x = (y - y1)/(y2 - y1)*(x2 - x1) + x1 ;
        return x ;
    }
    int is_vertical(){
        double y1 = this->lower_endpoint[1] ;
        double y2 = this->upper_endpoint[1] ;
        return y1 == y2 ;
    }
    double compare_lower(vector<double> point, Line line){
        int point_loc = this->point_location(point) ;
        if (point_loc != 0)return -1 * point_loc ;
        double a1 = this->get_lower_angle() ;
        double a2 = line.get_lower_angle() ;
        return a1 - a2 ; 
    }
    double compare_upper(vector<double> point, Line line){
        double y1 = this->upper_endpoint[1];
        double y = point[1] ;
        double y2 = line.upper_endpoint[1] ;
        double point_y = point[1] ;
        vector<double> intersect_point ;
        if(line.is_vertical()){
            intersect_point.push_back(point[0]) ;
            intersect_point.push_back(point[1]) ;
            
        }
        else{
            intersect_point.push_back(line.get_x(point_y)) ;
            intersect_point.push_back(point_y) ;
        }
        int point_loc = this->point_location(intersect_point);
        if(point_loc != 0)return -1*point_loc ;
        double a1 = this->get_upper_angle() ;
        double a2 = line.get_upper_angle() ;
        return a2 -a1 ; 


    }
    

};