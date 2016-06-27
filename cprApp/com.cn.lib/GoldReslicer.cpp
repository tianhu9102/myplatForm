#include "GoldReslicer.h"


//!---------------------------------------------------------------------------
//!
//! \brief GoldReslicer::GoldReslicer
//!
//!  this class is used to reslcier a special slice
//!
//!  ! test successfully !
//!  date: 2016-05-13    add: ShenZhen
//!---------------------------------------------------------------------------

GoldReslicer::GoldReslicer()
{
   resliceAxes = vtkMatrix4x4::New();
   reslice = vtkImageReslice::New();
   colorTable = vtkLookupTable::New();
   colorMap = vtkImageMapToColors::New();
   imgActor = vtkImageActor::New();

   naviPoint = new NavigationPointActor;

   appendPolydata = vtkAppendPolyData::New();
}

//!---------------------------------------------------------------------------
//!
//! \brief GoldReslicer::displaySlicer
//! \param render \param img
//! \param x \param y \param z
//!
void GoldReslicer::displaySlicer(vtkRenderer* render,
                   vtkImageData* img,
                   double x,double y,double z){

    int extent[6];
    double spacing[3];
    double origin[3];

    img->GetExtent(extent);
    img->GetSpacing(spacing);
    img->GetOrigin(origin);

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

    static double axialElements[16] = {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };

    resliceAxes->DeepCopy(axialElements);
    resliceAxes->SetElement(0, 3, x);
    resliceAxes->SetElement(1, 3, y);
    resliceAxes->SetElement(2, 3, z);

    reslice->SetInputData(img);
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();
    reslice->Update();

    colorTable->SetRange(0, 1000);
    colorTable->SetValueRange(0.0, 1.0);
    colorTable->SetSaturationRange(0.0, 0.0);
    colorTable->SetRampToLinear();
    colorTable->Build();

    colorMap->SetLookupTable(colorTable);
    colorMap->SetInputConnection(reslice->GetOutputPort());
    colorMap->Update();

    imgActor->SetInputData(reslice->GetOutput());
    imgActor->Update();

    render->AddActor(imgActor);
    naviPoint->displayNavigationPoint(render,x,y,z,"mm");  //! display the navigationPoint
    std::cout<<"..GoldReslicer::displaySlicer()"<<std::endl;
}

//!---------------------------------------------------------------------------
//!
//! \brief GoldReslicer::displayCutterImg
//! \param render \param img \param cP
//!
void GoldReslicer::displayCutterImg(vtkRenderer* render,
                   vtkImageData* img,
                   CenterLineProcess *cP){

    m_pShift = vtkImageShiftScale::New();

    double range[2];
    img->GetScalarRange(range);
    m_pShift->SetShift(-1.0*range[0]);
    m_pShift->SetScale(255.0/(range[1]-range[0]));
    m_pShift->SetOutputScalarTypeToUnsignedChar();
    m_pShift->SetInputData(img);
    m_pShift->ReleaseDataFlagOff();
    m_pShift->Update();

    std::vector<vtkSmartPointer<vtkActor> > actors;
    for(int cpt =0; cpt<5;cpt++){
        plane = vtkPlane::New();
        cutter = vtkCutter::New();
        polyMapper = vtkPolyDataMapper::New();
        cutActor = vtkActor::New();
        transformFilter = vtkTransformPolyDataFilter::New() ;
        translation = vtkTransform::New();

        plane->SetOrigin(cP->get_vesselsPoints().at(cpt*50)->get_abscissa(),
                         cP->get_vesselsPoints().at(cpt*50)->get_ordinate(),
                         cP->get_vesselsPoints().at(cpt*50)->get_isometric());
        plane->SetNormal(cP->get_vesselsPoints().at(cpt*50)->get_xdiff(),
                         cP->get_vesselsPoints().at(cpt*50)->get_ydiff(),
                         cP->get_vesselsPoints().at(cpt*50)->get_zdiff());
        naviPoint->displayNavigationPoint(render,
                                          cP->get_vesselsPoints().at(cpt*50)->get_abscissa(),
                                          cP->get_vesselsPoints().at(cpt*50)->get_ordinate(),
                                          0,
                                          "mm");  //! display the navigationPoint
        cutter->SetCutFunction(plane);
        cutter->SetInputData(m_pShift->GetOutput());
        cutter->Update();

        translation->Translate(0,0,
                               cP->get_vesselsPoints().at(cpt*50)->get_isometric());

        transformFilter->SetInputData(cutter->GetOutput());
        transformFilter->SetTransform(translation);
        transformFilter->Update();

        appendPolydata->SetInputData(transformFilter->GetOutput());
        appendPolydata->Update();


        polyMapper->SetInputData(appendPolydata->GetOutput());
        polyMapper->Update();
        cutActor->SetMapper(polyMapper);
        actors.push_back(cutActor);

        plane->Delete();
        cutter->Delete();
        translation->Delete();
        transformFilter->Delete();
        polyMapper->Delete();
        cutActor->Delete();
        std::cout<<"GoldReslicer::displayCutterImg   "<<cpt<<std::endl;
    }
    for(int cpt=0;cpt<actors.size();cpt++){
        render->AddActor(actors[cpt]);
    }
}
