#ifndef GOLDRESLICER_H
#define GOLDRESLICER_H

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkImageCast.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>
#include "NavigationPointActor.h"

#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkImageShiftScale.h>

#include "CenterLineProcess.h"
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vector>
#include <vtkProbeFilter.h>
#include <vtkAppendPolyData.h>


class GoldReslicer
{
public:
    GoldReslicer();


    void displaySlicer(vtkRenderer* render,
                       vtkImageData* img,
                       double x,double y,double z);

    void displayCutterImg(vtkRenderer* render,
                       vtkImageData* img,
                       CenterLineProcess *cP);


private:
   vtkMatrix4x4* resliceAxes;
   vtkImageReslice* reslice;
   vtkLookupTable* colorTable;
   vtkImageMapToColors* colorMap;
   vtkImageActor* imgActor;

   NavigationPointActor* naviPoint;

   vtkPlane* plane;
   vtkCutter* cutter;
   vtkPolyDataMapper* polyMapper;
   vtkActor* cutActor;
   vtkImageShiftScale *m_pShift;
   vtkTransformPolyDataFilter* transformFilter;
   vtkTransform* translation;

   vtkAppendPolyData* appendPolydata;


};

#endif // GOLDRESLICER_H
