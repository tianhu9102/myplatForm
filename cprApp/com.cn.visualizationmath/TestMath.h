#ifndef TESTMATH_H
#define TESTMATH_H

#include "Importinclude.h"
#include "CenterLineProcess.h"
#include "AcquisitionPoint.h"

//!   time:2016-04-14
//!   softWare: osirix

class TestMath
{
public:
    TestMath();
    void initialize();
    void centerlineProcess(QString str);

    void createNewImg(QString sourcemhdfile);

    void test();

    vtkActor *get_actor();
    vtkActor *get_actorcenterline();


private:
    CenterLineProcess *vesselReader;
    QVector<AcquisitionPoint *> acquisitionPoints;

    vtkUnstructuredGrid *grid;
    vtkPoints *pointset;
    vtkPolyVertex *poly;
    vtkDataSetMapper *mapper;
    vtkActor *actor;

    vtkUnstructuredGrid *gridcenterline;
    vtkPoints *pointsetcenterline;
    vtkPolyVertex *polycenterline;
    vtkDataSetMapper *mappercenterline;
    vtkActor *actorcenterline;

    vtkRenderer *renderer;
    vtkRenderWindow *renderwindow;
    vtkRenderWindowInteractor *interactor;

    vtkImageData *volumeData;
};

#endif // TESTMATH_H
