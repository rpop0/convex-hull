//
// Created by rozi on 23.05.2020.
//

#ifndef HW4_POINT_H
#define HW4_POINT_H
#include "iostream"

class Point {
private:
    int x;
    int y;
public:
    Point();
    Point(int, int);
    Point(const Point&);
    int getX() const;
    void setX(int);
    int getY() const;
    void setY(int);

};


#endif //HW4_POINT_H
