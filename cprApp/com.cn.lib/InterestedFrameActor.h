#ifndef INTERESTEDFRAMEACTOR_H
#define INTERESTEDFRAMEACTOR_H

#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkUnsignedCharArray.h>
#include <vtkVersion.h>
#include <vtkPolyDataMapper.h>
#include <vtkCellData.h>
#include <vtkRenderer.h>

#include "CrossMath.h"

class InterestedFrameActor
{
public:
    InterestedFrameActor();
    void displayInterestedFrame(vtkRenderer *renderer,
                                double origin_x,double origin_y,double origin_z,
                                double vector1_x,double vector1_y,double vector1_z,
                                double vector2_x,double vector2_y,double vector2_z);

private:
    CrossMath* cross;
    vtkPolyDataMapper* mapper;
    vtkActor* actor;
};

#endif // INTERESTEDFRAMEACTOR_H
