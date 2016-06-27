#ifndef CROSSMATH_H
#define CROSSMATH_H

#include <QtMath>
#include <QDebug>
#include <iostream>

class CrossMath
{
public:
    CrossMath();

    void crossCore(double x1, double y1, double z1, double x2, double y2, double z2);
    void frenetSerretFrame(double x1, double y1, double z1, double x2, double y2, double z2);
    void crossNormalize(double m, double n, double p);

    double get_i();
    double get_j();
    double get_k();
    double get_tangent_i();
    double get_tangent_j();
    double get_tangent_k();
    double get_normal_i();
    double get_normal_j();
    double get_normal_k();
    double get_binormal_i();
    double get_binormal_j();
    double get_binormal_k();
    void printOut();

private:
    double arry[3];
    double tangent[3];
    double binormal[3];
    double normal[3];
};

#endif // CROSSMATH_H
