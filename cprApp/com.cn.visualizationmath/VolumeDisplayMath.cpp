#include "VolumeDisplayMath.h"

//!------------------------------------------------------------------------------
//!
//! \brief VolumeDisplayMath::VolumeDisplayMath
//!  this class is used to display a 3D raw file
//!
//!  ! test successfully !
//!  date: 2016-05-11    add: ShenZhen
//!------------------------------------------------------------------------------

VolumeDisplayMath::VolumeDisplayMath()
{
    reader = vtkMetaImageReader::New();
    mapper = vtkFixedPointVolumeRayCastMapper::New();
    colorTranFun = vtkColorTransferFunction::New();
    pieceFun = vtkPiecewiseFunction::New();
    gradientFun = vtkPiecewiseFunction ::New();
    volumeProperty = vtkVolumeProperty::New();
    volume = vtkVolume::New();
    volumeRaycastmapper = vtkVolumeRayCastMapper::New();
}

//!------------------------------------------------------------------------------
//!
//! \brief VolumeDisplayMath::displayVolumeData
//! \param render
//! \param str
//!
void VolumeDisplayMath::displayVolumeData(vtkRenderer *render, QString str){

    reader->SetFileName(str.toLocal8Bit());
    reader->SetDataScalarTypeToUnsignedShort(); //!pixel spacing:0-65536
    //!volumeReader->SetNumberOfScalarComponents(1);
    reader->Update();

    mapper->SetInputData(reader->GetOutput());
    colorTranFun->AddRGBSegment(0, 1, 1, 1, 255, 1, 1, 1);
    pieceFun->AddSegment(0,0,3000,1);

    pieceFun->ClampingOff();
    gradientFun->AddPoint(0, 1);
    gradientFun->AddPoint(255, 1);

    mapper->SetBlendModeToMaximumIntensity();
    volumeProperty->SetColor(colorTranFun);
    volumeProperty->SetScalarOpacity(pieceFun);
    //!volumeProperty->SetGradientOpacity(gradientFun);
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();

    volume->SetMapper(mapper);
    volume->SetProperty(volumeProperty);
    render->AddVolume(volume);
}

vtkMetaImageReader *VolumeDisplayMath::getReader(){
    return this->reader;
}
