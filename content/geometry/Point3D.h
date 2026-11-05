/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Точка/вектор в пространстве, T — double или long long.

 * Usage:
 * Status: tested, except for phi and theta
 */
#pragma once

template <class T> struct Point3D {
    typedef Point3D P;
    T x, y, z;
    explicit Point3D(T x = 0, T y = 0, T z = 0)
        : x(x), y(y), z(z) {}
    bool operator<(P p) const {
        return tie(x, y, z) < tie(p.x, p.y, p.z);
    }
    bool operator==(P p) const {
        return tie(x, y, z) == tie(p.x, p.y, p.z);
    }
    P operator+(P p) const {
        return P(x + p.x, y + p.y, z + p.z);
    }
    P operator-(P p) const {
        return P(x - p.x, y - p.y, z - p.z);
    }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    T dot(P p) const { return x * p.x + y * p.y + z * p.z; }
    P cross(P p) const {
        return P(y * p.z - z * p.y, z * p.x - x * p.z,
                 x * p.y - y * p.x);
    }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double)dist2()); }
    //Азимут (долгота) от оси x в [-pi,pi]
    double phi() const { return atan2(y, x); }
    //Полярный угол от оси z в [0,pi]
    double theta() const {
        return atan2(sqrt(x * x + y * y), z);
    }
    P unit() const {
        return *this / (T)dist();
    } //нормирует длину к 1
    //единичная нормаль к *this и p
    P normal(P p) const { return cross(p).unit(); }
    //поворот на angle радиан против часовой вокруг axis
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle);
        P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this) * c -
               cross(u) * s;
    }
};
