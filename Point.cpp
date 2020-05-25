//
// Created by rozi on 23.05.2020.
//

#include "Point.h"


Point::Point(int x, int y)
    :x(x),y(y){

}

Point::Point(const Point &point2)
    :x(point2.x), y(point2.y){

}

int Point::getX() const{
    return this->x;
}

void Point::setX(int inputX) {
    this->x = inputX;
}

int Point::getY() const{
    return this->y;
}

void Point::setY(int inputY) {
    this->y = inputY;
}

Point::Point()
    :x(0),y(0) {

}

