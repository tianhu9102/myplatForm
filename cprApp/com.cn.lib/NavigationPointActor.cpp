#include "NavigationPointActor.h"

//!---------------------------------------------------------------------------
//!
//! \brief NavigationPointActor::NavigationPointActor
//!
//!  this class is used to navigate a 3D/2D point in Volume
//!  to get a better outcoming, it is better to connect with a timer
//!
//!  the point color can be changed to red,green,blue or ...
//!
//!  ! test successfully !
//!  date: 2016-05-10    add: ShenZhen
//!---------------------------------------------------------------------------

NavigationPointActor::NavigationPointActor()
{
    points = vtkPoints::New();
    vertices = vtkCellArray::New();
    polyData = vtkPolyData::New();
    polyMapper = vtkPolyDataMapper::New();
    actor = vtkActor::New();
}

//!---------------------------------------------------------------------------
//!
//! \brief NavigationPointActor::displayNavigationPoint
//! \param render \param x \param y \param z \param pointColor
//!
void NavigationPointActor::displayNavigationPoint(vtkRenderer *render,
                                                  double x, double y , double z,
                                                  QString pointColor){
    p[0] ={x};
    p[1] ={y};
    p[2] ={z};
    vtkIdType pid[1];
    pid[0] = points->InsertNextPoint(p);
    vertices->InsertNextCell(1,pid);
    polyData->SetPoints(points);
    polyData->SetVerts(vertices);
    polyMapper->SetInputData(polyData);
    actor->SetMapper(polyMapper);
    actor->GetProperty()->SetPointSize(5);

    if(pointColor.contains("r")){
        actor->GetProperty()->SetColor(255,0,0);
    }else if(pointColor.contains("g")){
        actor->GetProperty()->SetColor(0,255,0);
    }else if(pointColor.contains("b")){
        actor->GetProperty()->SetColor(0,0,255);
    }else {
        actor->GetProperty()->SetColor(0,255,255);
    }
    render->AddActor(actor);
}
