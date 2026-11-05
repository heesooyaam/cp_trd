/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Точка/вектор на плоскости. T — double или long long; int легко переполняется на произведениях.

 * Status: Works fine, used a lot
 */
#pragma once

template <class T> int sgn(T x) {
    return (x > 0) - (x < 0);
}
template <class T> struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
    bool operator==(P p) const {
        return tie(x, y) == tie(p.x, p.y);
    }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const {
        return (a - *this).cross(b - *this);
    }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // угол к оси x в [-pi,pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // нормирует длину к 1
    P perp() const { return P(-y, x); } // поворот на +90 градусов
    P normal() const { return perp().unit(); }
    // поворот на a радиан против часовой вокруг начала
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a),
                 x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
