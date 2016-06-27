#ifndef PROJECTIONIMPL_H
#define PROJECTIONIMPL_H

#pragma once
#include <iostream>
#include <vtkActor.h>
#include <vtkCylinderSource.h>
#include <vtkSphereSource.h>
#include <vtkDiskSource.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNew.h>
#include <vtkPolyDataSilhouette.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkCubeAxesActor.h>
#include <vtkCellArray.h>

class ProjectionImpl
{
public:
    int implate();
};

#endif // PROJECTIONIMPL_H
