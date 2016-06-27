#ifndef MAY_H
#define MAY_H

#include "VolumeDisplayMath.h"
#include <vtkRenderWindowInteractor.h>
#include "CenterLineDisplayMath.h"
#include "GoldReslicer.h"
#include <vtkPolyData.h>

#include <vtkAppendPolyData.h>

class May
{
public:
    May();

    void straightenedMath(QString mhdfile, QString txtfile);
    GoldReslicer* getGoldSlicer();

    vtkRenderer* getRender1();

    void updateWindow();

    void test(vtkRenderer *render, vtkMetaImageReader *imgReader, vtkPolyData *polydata);

private:
    VolumeDisplayMath* volumeDisM;
    CenterLineDisplayMath* centLineM;
    GoldReslicer* goldSlicer;

    vtkRenderer *render;
    vtkRenderWindow *renderWindow;
    vtkRenderWindowInteractor *interactor;

    vtkRenderer *render1;
    vtkRenderWindow *renderWindow1;
    vtkRenderWindowInteractor *interactor1;

     vtkProbeFilter* probeFilter;
     vtkWindowLevelLookupTable* wlLut;
     vtkDataSetMapper* mapper;
     vtkActor* actor;
};

#endif // MAY_H
