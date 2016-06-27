#ifndef VOLUMEDISPLAYMATH_H
#define VOLUMEDISPLAYMATH_H

#include <QString>
#include <vtkMetaImageReader.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

class VolumeDisplayMath
{
public:
    VolumeDisplayMath();

    void displayVolumeData(vtkRenderer *render,QString str);

    vtkMetaImageReader *getReader();

private:

    vtkMetaImageReader *reader;
    vtkFixedPointVolumeRayCastMapper *mapper;
    vtkVolumeRayCastMapper *volumeRaycastmapper;
    vtkColorTransferFunction *colorTranFun;
    vtkPiecewiseFunction *pieceFun;
    vtkPiecewiseFunction *gradientFun;
    vtkVolumeProperty *volumeProperty;
    vtkVolume *volume;
};

#endif // VOLUMEDISPLAYMATH_H
