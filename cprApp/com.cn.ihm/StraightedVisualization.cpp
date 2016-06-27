#include "StraightedVisualization.h"

StraightedVisualization::StraightedVisualization(QWidget *parent) : QWidget(parent)
{
    this->initVariable();
    this->constructIHM();
}

//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::initVariable
//!
void StraightedVisualization::initVariable(){
    mapper = vtkFixedPointVolumeRayCastMapper::New();
    colorTranFun = vtkColorTransferFunction::New();
    pieceFun = vtkPiecewiseFunction::New();
    volumeProperty = vtkVolumeProperty::New();
    volume = vtkVolume::New();

    renderer = vtkRenderer::New();
    renderwindow =  vtkRenderWindow::New();

    qVTKWidget = new QVTKWidget();
    renderer->SetBackground(55.0/255,85.0/255,95.0/255);
    renderwindow->AddRenderer(renderer);
    qVTKWidget->SetRenderWindow(renderwindow);
    qVTKWidget->update();
}


//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::constructIHM
//!
void StraightedVisualization::constructIHM(){
    qHboxLayout = new QHBoxLayout(this);
    qHboxLayout->addWidget(qVTKWidget);
    qHboxLayout->setSpacing(0);
    qHboxLayout->setMargin(0);
}

//!---------------------------------------------------------------------------------------------------
void StraightedVisualization::mathdisplay(){
    // TODO...
}

//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::reconstructedmathdisplay
//! \param outputport
//!
void StraightedVisualization::reconstructedmathdisplay(vtkAlgorithmOutput *outputport){
    mapper->SetInputConnection(outputport);
    colorTranFun->AddRGBSegment(0, 1, 1, 1, 255, 1, 1, 1);
    colorTranFun->AddRGBPoint(3000.0, 0.91, 0.65, 0.66);
    colorTranFun->AddRGBPoint(1208.0, 0.91, 0.65, 0.66);
    colorTranFun->AddRGBPoint(1200.0, 0.23, 0.23, 0.43);
    colorTranFun->AddRGBPoint(1800, 0.43, 0.43, 0.43);
    colorTranFun->AddRGBPoint(2095, 0.9, 0.0, 0.0);
    colorTranFun->AddRGBPoint(3050, 0.9, 0.0, 0.0);
    colorTranFun->ClampingOff();
    pieceFun->AddSegment(0,0,3000,1);
    pieceFun->AddPoint(100,0.0);
    pieceFun->AddPoint(2000,1);
    pieceFun->AddPoint(1000,0.2);
    pieceFun->AddPoint(1200,1);
    pieceFun->AddPoint(2000,1);
    pieceFun->ClampingOff();
    mapper->SetBlendModeToMaximumIntensity();
    volumeProperty->SetColor(colorTranFun);
    volumeProperty->SetScalarOpacity(pieceFun);
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOff();
    volume->SetProperty(volumeProperty);
    volume->SetMapper(mapper);
    camera = vtkCamera::New();
    camera->SetViewUp(0,0,-1);
    camera->SetFocalPoint(3.9,9.95,20);
    camera->SetPosition(78.9,84.95,20);
    renderer->SetActiveCamera(camera);
}

//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::selectedmathdisplay
//! \param outputport
//! \param str
//!
void StraightedVisualization::selectedmathdisplay(int txt,vtkAlgorithmOutput *outputport,double arr[],double *center){
    vtkPolyDataMapper * selectMapper = vtkPolyDataMapper::New();
    vtkActor* actor = vtkActor::New();
    vtkCamera *scamera = vtkCamera::New();
    vtkTextActor *textActor = vtkTextActor::New();
    vtkRenderer* srenderer = vtkRenderer::New();
    vtkRenderWindow* srenderwindow = vtkRenderWindow::New();
    selectMapper->SetInputConnection(outputport);
    actor ->SetMapper(selectMapper);
    QString str = QString::number(txt,'f',0);
    textActor->SetInput(str.toUtf8().constData());
    textActor->SetDisplayPosition( actor->GetPosition()[0]+60, 10 );
    textActor->SetPosition2 ( actor->GetPosition()[0], 40 );
    textActor->GetTextProperty()->SetFontSize ( 14);
    textActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
    srenderer->AddActor(actor);
    srenderer->AddActor2D ( textActor );
    srenderer->SetBackground(55.0/255,85.0/255,95.0/255);
    srenderwindow->AddRenderer(srenderer);
    scamera->SetViewUp(0,0,-1);
    scamera->SetFocalPoint(center[0],center[1],center[2]);
    scamera->SetPosition(center[0]+ arr[0],center[1]+ arr[1], center[2]);
    srenderer->SetActiveCamera(scamera);
    QVTKWidget *sqVTKWidget = new QVTKWidget();
    sqVTKWidget->setFixedSize(this->width()*0.125,this->height());
    sqVTKWidget->SetRenderWindow(srenderwindow);
    sqVTKWidget->update();
    qHboxLayout->addWidget(sqVTKWidget);
    qHboxLayout->setSpacing(0);
}

//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::extractVOI
//! \param outputport
//!
void StraightedVisualization::extractVOI(vtkImageData *outputport){
    vtkImageActor* imageActor = vtkImageActor::New();
    vtkRenderer* rendererVOI = vtkRenderer::New();
    vtkRenderWindow* renderwindowVOI = vtkRenderWindow::New();

    imageActor->SetInputData(outputport);
    rendererVOI->AddActor(imageActor);
    rendererVOI->SetBackground(55.0/255,85.0/255,95.0/255);
    renderwindowVOI->AddRenderer(rendererVOI);

    QVTKWidget *qVTKWidgetVOI = new QVTKWidget();
    qVTKWidgetVOI->setFixedSize(100,299);
    qVTKWidgetVOI->SetRenderWindow(renderwindowVOI);
    qVTKWidgetVOI->update();
    qHboxLayout->addWidget(qVTKWidgetVOI);
    qHboxLayout->setSpacing(0);
}

//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::getActivecamera
//! \return
//!
vtkCamera* StraightedVisualization::getActivecamera(){
    return this->camera;
}

//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::getQVTKWidget
//! \return
//!
QVTKWidget *StraightedVisualization::getQVTKWidget(){
    return this->qVTKWidget;
}

//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::get_volume
//! \return
//!
vtkVolume* StraightedVisualization::get_volume(){
    return this->volume;
}

//!---------------------------------------------------------------------------------------------------
//!
//! \brief StraightedVisualization::get_colorTranFun
//! \return
//!
vtkColorTransferFunction *StraightedVisualization::get_colorTranFun(){
    return this->colorTranFun;
}
