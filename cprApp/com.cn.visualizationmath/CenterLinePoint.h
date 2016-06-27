#ifndef CENTERLINEPOINT_H
#define CENTERLINEPOINT_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>

#include "vtkMath.h"
#include "AcquisitionPoint.h"

class CenterLinePoint
{


public:
    CenterLinePoint();

private:
    double pos_x;
    double pos_y;
    double pos_z;
    double xdiff;
    double ydiff;
    double zdiff;
    double radius;

    double cos_sigma;
    double cos_theta;
    double constant_k;

    double acquisition_radius;
    int acquisition_frequence;

    double vector[3];

    double acquisition_vector[3];

    QVector<AcquisitionPoint *> acquisitionPoints;

public:
    void normalize();
    void update();
    void print();

    void printAcquisitionPoints();
    void normalize_uvw();

    void appendAcquisitionPoints(AcquisitionPoint *acqPoint);
    AcquisitionPoint * getAcquisitionPointAt(int index);

    void set_acquisition_k(double constant_k);
    void set_cos_sigma(double cos_sigma);
    void set_cos_theta(double cos_theta);
    void set_abscissa(double pos_x);
    void set_ordinate(double pos_y);
    void set_isometric(double pos_z);
    void set_xdiff(double xdiff);
    void set_ydiff(double ydiff);
    void set_zdiff(double zdiff);
    void set_radius(double radius);

    void set_acquisition_vector_u(double u);
    void set_acquisition_vector_v(double v);
    void set_acquisition_vector_w(double w);
    void set_acquisition_radius(double r);
    void set_acquisition_frequence(int frequence);

    double get_abscissa();
    double get_ordinate();
    double get_isometric();
    double get_xdiff();
    double get_ydiff();
    double get_zdiff();
    double get_radius();

    double get_acquisition_vector_u();
    double get_acquisition_vector_v();
    double get_acquisition_vector_w();
    double get_acquisition_radius();
    int get_acquisition_frequence();
    double get_cos_sigma();
    double get_cos_theta();
    double get_acquisition_k();

};

#endif // CENTERLINEPOINT_H
