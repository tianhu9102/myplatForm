#include "VolumeVisualization.h"

VolumeVisualization::VolumeVisualization(QWidget *parent) : QWidget(parent)
{
    this->initVariable();
   // this->constructIHM();
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::initVariable
//!
void VolumeVisualization::initVariable(){
    volumeReader = vtkMetaImageReader::New();
    mapper = vtkFixedPointVolumeRayCastMapper::New();
    colorTranFun = vtkColorTransferFunction::New();
    pieceFun = vtkPiecewiseFunction::New();
    gradientFun = vtkPiecewiseFunction ::New();
    volumeProperty = vtkVolumeProperty::New();

    volume = vtkVolume::New();
    renderer = vtkRenderer::New();
    renderwindow =  vtkRenderWindow::New();
    renderer0 = vtkRenderer::New();
    renderwindow0 =  vtkRenderWindow::New();
    volumeRaycastmapper = vtkVolumeRayCastMapper::New();
 }

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::constructIHM
//!
void VolumeVisualization::constructIHM(){
    qHboxLayout = new QHBoxLayout(this);
    qVTKWidget = new QVTKWidget();
    qHboxLayout->addWidget(qVTKWidget);
    qHboxLayout->setSpacing(0);
    qHboxLayout->setMargin(0);
    renderer0->SetBackground(55.0/255,85.0/255,95.0/255);
    renderwindow0->AddRenderer(renderer0);
    qVTKWidget->SetRenderWindow(renderwindow0);
    qVTKWidget->update();
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::mathdisplay
//!
void VolumeVisualization::mathdisplay(QString filename){
    mathdisplayofmath(filename);
    mathdisplayofQVTKWidget();
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::mathdisplayofmath
//! \param mhdFile
//! \TODO... read different type of dataset
//!
void VolumeVisualization::mathdisplayofmath(QString filename){
    if(filename.toLocal8Bit().contains(".mhd")){
        this->mhdpipeline(filename);
    } else if(filename.toLocal8Bit().contains(".dcm")){
        this->dcmpipeline(filename);
    } else if(filename.toLocal8Bit().contains(".vtp")){
        this->vtppipeline(filename);
    } else if(filename.toLocal8Bit().contains(".vtk")){
        this->vtkpipeline(filename);
    } else if(filename.toLocal8Bit().contains(".mha")){
        this->mhdpipeline(filename);
    } else if(filename.toLocal8Bit().contains(".mat")){
        this->matpipeline(filename);
    }else  {
        qDebug()<<"this is not conventional medical data";
    }
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::mhdpipeline
//!
void VolumeVisualization::mhdpipeline(QString mhdFile){

    //!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    volumeReader->SetFileName(mhdFile.toLocal8Bit());
    volumeReader->SetDataScalarTypeToUnsignedShort(); //pixel spacing:0-65536
    //volumeReader->SetNumberOfScalarComponents(1);
    volumeReader->Update();

    mapper->SetInputData(volumeReader->GetOutput());
    colorTranFun->AddRGBSegment(0, 1, 1, 1, 255, 1, 1, 1);
    pieceFun->AddSegment(0,0,3000,1);

    pieceFun->ClampingOff();
    gradientFun->AddPoint(0, 1);
    gradientFun->AddPoint(255, 1);

    mapper->SetBlendModeToMaximumIntensity();
    volumeProperty->SetColor(colorTranFun);
    volumeProperty->SetScalarOpacity(pieceFun);
    //volumeProperty->SetGradientOpacity(gradientFun);
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();


    volume->SetMapper(mapper);
    volume->SetProperty(volumeProperty);
    renderer->AddVolume(volume);

    //! below are some basic parameters  ----used in Class BasicParameters----
    int dims[3];
    vtkImageData *iamgeData = volumeReader->GetOutput();
    iamgeData->GetDimensions(dims);
    this->xdim = dims[0];
    this->ydim = dims[1];
    this->zdim = dims[2];
    std::cout<<"**************VolumeVisualization::mhdpipeline(QString mhdFile)****************\n"<<std::endl;

    //! obtain the coordinates of a point in a vtkImageData object------->>> useful
    std::cout<<"dims:" <<"x:"<<dims[0]<<" y:"<<dims[1]<<" z:"<<dims[2]<<std::endl;
    std::cout<<"Number of points:" <<iamgeData->GetNumberOfPoints()<<std::endl;
    std::cout<<"Number of cells:" <<iamgeData->GetNumberOfCells()<<std::endl;

    double origin[3];
    iamgeData->GetOrigin(origin);
    this->xorigin = origin[0];
    this->yorigin = origin[1];
    this->zorigin = origin[2];
    std::cout<<"Origin:" <<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;

    double spaceing[3];
    iamgeData->GetSpacing(spaceing);
    this->xspacing = spaceing[0];
    this->yspacing = spaceing[1];
    this->zspacing = spaceing[2];
    std::cout<<"spacing:" <<spaceing[0]<<" "<<spaceing[1]<<" "<<spaceing[2]<<std::endl;
    std::cout<<"\n****************************************************************************************************\n";
}

void VolumeVisualization::dcmpipeline(QString dcmFile){

}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::vtkpipeline
//! \param vtkFile
//!
void VolumeVisualization::vtkpipeline(QString vtkFile){
    vtkPolyDataReader *vtkReader = vtkPolyDataReader::New();
    vtkReader->SetFileName(vtkFile.toLocal8Bit());
    vtkReader->Update();
    vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
    skinMapper->SetInputConnection(vtkReader->GetOutputPort());
    skinMapper->ScalarVisibilityOff();
    vtkActor* skin = vtkActor ::New();
    skin->SetMapper (skinMapper);

    vtkCamera* thevtkCamera = vtkCamera::New();
    thevtkCamera->SetViewUp (0, 0, -1);
    thevtkCamera->SetPosition (0, 1, 0);
    thevtkCamera->SetFocalPoint (0, 0, 0);
    thevtkCamera->ComputeViewPlaneNormal ();
    thevtkCamera->Azimuth (30.0);
    thevtkCamera->Elevation (30.0);
    thevtkCamera->Dolly (1.5);

    renderer->AddActor(skin);
    renderer->SetActiveCamera (thevtkCamera);
    renderer->ResetCamera ();
    renderer->ResetCameraClippingRange ();
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::vtppipeline
//! \param vtpFile
//!
void VolumeVisualization::vtppipeline(QString vtpFile){
    vtkXMLPolyDataReader *vtpReader = vtkXMLPolyDataReader::New();
    vtkPolyDataMapper *vtpPolyMapper = vtkPolyDataMapper::New();
    vtkActor *vtpactor = vtkActor::New();
    vtpReader->SetFileName(vtpFile.toLocal8Bit());
    vtpReader->Update();
    vtpPolyMapper->SetInputConnection(vtpReader->GetOutputPort());
    vtpactor->SetMapper(vtpPolyMapper);
    renderer->AddActor(vtpactor);
}

void VolumeVisualization::mhapipeline(QString mhaFile){

}

void VolumeVisualization::matpipeline(QString matFile){

}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::mathdisplayofQVTKWidget
//!
void VolumeVisualization::mathdisplayofQVTKWidget(){
    renderer->SetBackground(55.0/255,85.0/255,95.0/255);
    renderwindow->AddRenderer(renderer);
    qVTKWidget->SetRenderWindow(renderwindow);
    qVTKWidget->update();
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::mhdfileChoose
//!
void VolumeVisualization::mhdfileChoose(){
    QString filename = QFileDialog::getOpenFileName(this,tr("Load File"),"D:\\school\\dataset\\CoronaryData_CTA\\",
                                                    tr("mhdfile(*.mhd*);;dcm(*.dcm*);;"
                                                       "vtk(*.vtk*);;vtp(*.vtp*);;"
                                                       "allfile(*.*)"));
    this->filepathname = filename;
    if(filename==NULL){
        return ;
    } else
        this->mathdisplay(filename);
        qDebug()<<"VolumeVisualization-mhdfileChoose()"<<filename;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::getmhdfilename
//!
QString VolumeVisualization::getmhdfilename(){
    return this->filepathname;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::get_renderer
//!
vtkRenderer* VolumeVisualization::get_renderer(){
    return this->renderer;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::get_rendererWindow
//!
vtkRenderWindow* VolumeVisualization::get_rendererWindow(){
    return this->renderwindow;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::get_volumeReader
//!
vtkMetaImageReader* VolumeVisualization::get_volumeReader(){
    return this->volumeReader;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::get_colorTranFun
//!
vtkColorTransferFunction *VolumeVisualization::get_colorTranFun(){
    return this->colorTranFun;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::get_qvtkWidget
//!
QVTKWidget* VolumeVisualization::get_qvtkWidget(){
    return this->qVTKWidget;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::get_volume
//!
vtkVolume *VolumeVisualization::get_volume(){
    return this->volume;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::getxDimsion
//!
int VolumeVisualization::getxDimsion(){
    return this->xdim;
}
int VolumeVisualization::getyDimsion(){
    return this->ydim;
}
 int VolumeVisualization::getzDimsion(){
    return this->zdim;
}

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::getxOrigin
//!
 double VolumeVisualization::getxOrigin(){
     return this->xorigin;
 }
 double VolumeVisualization::getyOrigin(){
     return this->yorigin;
 }
 double VolumeVisualization::getzOrigin(){
     return this->zorigin;
 }

//!---------------------------------------------------------------------------------
//!
//! \brief VolumeVisualization::getxSpacing
//!
 double VolumeVisualization::getxSpacing(){
     return this->xspacing;
 }
 double VolumeVisualization::getySpacing(){
     return this->yspacing;
 }
 double VolumeVisualization::getzSpacing(){
     return this->zspacing;
 }

 //!---------------------------------------------------------------------------------
 //!
 //! \brief VolumeVisualization::getVolume
 //! \return
 //!
 vtkVolume *VolumeVisualization::getVolume(){
    return this->volume;
}
