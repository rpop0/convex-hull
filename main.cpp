#include <iostream>
#include "vector"
#include "algorithm"
#include "stack"
#include "Point.h"

#include "fstream";

std::ifstream f("points.txt");

Point p0;

std::ostream& operator<<(std::ostream& os, const Point& obj){ //Overloading output operator.
    os<<"("<<obj.getX()<<", "<<obj.getY()<<")";
    return os;
}

int distSq(Point p1, Point p2)
{
    return (p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) + (p1.getY() - p2.getY())*(p1.getY() - p2.getY());
}


int orientation(Point p, Point q, Point r)
{
    int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) - (q.getX() - p.getX()) * (r.getY() - q.getY());
    if (val == 0){
        return 0;
    } else if(val > 0){
        return 1;
    } else {
        return 2;
    }
}


Point nextToTop(std::stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}


int compare(const void *vp1, const void *vp2) //Function to compare two points for qsort.
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0){
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
    } else if (o == 2) {
        return -1;
    } else {
        return 1;
    }

}



void convexHull(std::vector<Point>& points){
    int ymin = points[0].getY();
    int min = 0;
    for(std::size_t i=1; i<points.size();i++){ //Finding the smallest y.
        int y = points[i].getY();
        if((y < ymin) or (ymin == y and points[i].getX() < points[min].getX())){
            ymin = points[i].getY();
            min = i;
        }
    }
    std::swap(points[0], points[min]); //Making it the first element.
    p0 = points[0];
    std::qsort(&points[1], points.size()-1, sizeof(Point), compare); //Had to use std::qsort, no matter what I did, I could not get std::sort to work.
    int m = 1;
    for(std::size_t i=1; i<points.size();i++){
        while (i < points.size() - 1 and orientation(p0, points[i], points[i+1]) == 0){
            i++;
        }
        points[m] = points[i];
        m++;
    }

    if (m<3){
        return;
    }
    std::stack<Point> pointStack;
    pointStack.push(points[0]);
    pointStack.push(points[1]);
    pointStack.push(points[2]);


    for(std::size_t i=3;i<m;i++){
        while( orientation(nextToTop(pointStack), pointStack.top(), points[i]) != 2 ){
            pointStack.pop();
        }
        pointStack.push(points[i]);
    }

    while (!pointStack.empty()){
        Point p = pointStack.top();
        std::cout<<p<<" ";
        pointStack.pop();
    }

}


int main() {
    std::vector<Point> points;
    while(!f.eof()){
        int x,y;
        f>>x>>y;
        points.push_back(Point(x,y)); //Placing all of the points from the file in the vector.s
    }
    f.close();
    convexHull(points);
    return 0;
}
