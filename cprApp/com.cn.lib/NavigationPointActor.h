#ifndef NAVIGATIONPOINTACTOR_H
#define NAVIGATIONPOINTACTOR_H

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkIdTypeArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <QString>

class NavigationPointActor
{
public:
    NavigationPointActor();

    void displayNavigationPoint(vtkRenderer *render,double x, double y , double z, QString pointColor);

private:
    double p[3];
    vtkPoints* points;
    vtkCellArray *vertices;
    vtkPolyData *polyData;

    vtkPolyDataMapper *polyMapper;
    vtkActor *actor;
};

#endif // NAVIGATIONPOINTACTOR_H
