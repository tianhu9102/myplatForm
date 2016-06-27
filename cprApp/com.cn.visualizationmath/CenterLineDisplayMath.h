#ifndef CENTERLINEDISPLAYMATH_H
#define CENTERLINEDISPLAYMATH_H

#include <vtkRenderer.h>
#include <QString>
#include <CenterLineProcess.h>
#include <vtkTubeFilter.h>

class CenterLineDisplayMath
{
public:
    CenterLineDisplayMath();

    void displayCenterLineData(vtkRenderer *render, QString filepath, QString pointColor);
    void displayVesselThreeDimReconstruction(vtkRenderer *render,
                                             QString filepath,
                                             QString pointColor);


    void typeConvert();
    void colorChoice(vtkActor *actor,QString str);
    CenterLineProcess *getCenterLinePr();
    vtkPolyData *ribbonFilter();

    vtkPoints *getAllpoints();

private:
    CenterLineProcess *centerLinePr;
    vtkPoints *points;
    vtkPolyVertex *poly;
    vtkUnstructuredGrid *grid;

    vtkSCurveSpline *xSpline;
    vtkSCurveSpline *ySpline;
    vtkSCurveSpline *zSpline;
    vtkParametricSpline *spline;
    vtkParametricFunctionSource *functionSource;

    vtkDataSetMapper *mapper;
    vtkActor *actor;

    //! 3-D Reconstruction
    vtkPoints* reconstructionPoints;
    vtkCellArray* reconstructionLines ;
    vtkPolyData* reconstructionPolyData;
    vtkDoubleArray* tubeRadius;
    vtkUnsignedCharArray *reconstructionColors;
    vtkTubeFilter* reconstructionTube ;
    vtkPolyDataMapper *reconstructionMapper ;
    vtkActor* reconstructionActor ;
};

#endif // CENTERLINEDISPLAYMATH_H
