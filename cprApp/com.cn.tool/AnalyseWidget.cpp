#include "AnalyseWidget.h"

AnalyseWidget::AnalyseWidget(FourViewWidget *myFourv,int wid,int heig) : QWidget(myFourv)
{
    this->fws = myFourv;
    this->theWid = wid; this->theHeigh = heig;
    this->initVariable();
    this->constructIHM(wid,heig);
    this->setconnections();
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::setconnections
//!
void AnalyseWidget::setconnections(){
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updatecenterCuttingQVTKWidget()));
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setLineEditValue(int)));
    connect(movingButton,SIGNAL(clicked(bool)),this,SLOT(movingExecute()));
}

//!--------------------------------------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::setLineEditValue
//!
void AnalyseWidget::setLineEditValue(int){
    int pos = slider->value();
    QString str = QString("%1").arg(pos);
    currentValuelineEdit->setText(str);
    //! keep synchronize ,dynamicly get the cutting slice
    if(!fws->getCenterlinefile().isEmpty()){
        this->centerCutting(pos);
    }
}

//!--------------------------------------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::dynamiclyShowSlice
//!
void AnalyseWidget::dynamiclyShowSlice(){
    cptTim ++;
    int pos = cptTim *50;
    if( pos < fws->getCenterLineVisualization_Object()->get_centerLineProcess()->getReferencecount()){
        QString str = QString("%1").arg(pos);
        currentValuelineEdit->setText(str);
        this->centerCutting(pos);

    }
}

//!--------------------------------------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::initVariable
//!
void AnalyseWidget::initVariable(){

    naviPointActor = new NavigationPointActor;
    myIntersedFrameActor = new InterestedFrameActor;
    txActor = new TextActor;

    mhdReader = vtkMetaImageReader::New();
    imageActor = vtkImageActor::New();
    shift = vtkImageShiftScale::New();
    fixedMapper = vtkFixedPointVolumeRayCastMapper::New();
    colorTran = vtkColorTransferFunction::New();
    piceFun = vtkPiecewiseFunction::New();
    volumeProperty = vtkVolumeProperty::New();
    pVolume = vtkVolume::New();
    planeWidget = vtkPlaneWidget::New();
    srenderer = vtkRenderer::New();
    srenderWindow = vtkRenderWindow::New();
    activeCamera = vtkCamera::New();

    pPlane = vtkPlane::New();
    pCut = vtkCutter::New();
    selectMapper = vtkPolyDataMapper::New();
    pActor = vtkActor::New();
    pCall = vtkWidgetCallsR::New();
    pCall->pPlane = pPlane;
    centerCuttingrenderer = vtkRenderer::New();
    centerCuttingrenderWindow = vtkRenderWindow::New();
    pInt = vtkRenderWindowInteractor::New();
    interstedSectionrenderer = vtkRenderer::New();
    interstedSectionrenderer->SetBackground(55.0/255,85.0/255,95.0/255);
    interstedSectionrenderWindow = vtkRenderWindow::New();
    append = vtkImageAppend::New();
    lastWidgetrenderer = vtkRenderer::New();  //!qVTKWidget[3]
    lastWidgetrenderer->SetBackground(55.0/255,85.0/255,95.0/255);
    lastWidgetrenderWindow = vtkRenderWindow::New();
    lastWidgetrenderWindow->AddRenderer(lastWidgetrenderer);

    //!
    plotActor = vtkXYPlotActor::New();
    plotActor->ExchangeAxesOff();
    plotActor->SetLabelFormat("%g");
    plotActor->PlotCurveLinesOff();

    labeledPointPolyMapper = vtkLabelPlacementMapper::New();
    labeledPointActor = vtkActor2D::New();
    actorX = vtkActor::New(); actorY = vtkActor::New(); actorZ = vtkActor::New();

    QString filename(fws->getVolumeVisualization_Object()->getmhdfilename());
    this->mymhdfilename = filename;
    this->setAcceptDrops(true);

    //!   define this QTimer to show the cutting slice timely
    updateTimer = new QTimer(this);
    updateTimer->setInterval(3);
    updateTimer->start(0.1);


    dynamiclyShowSliceTimer = new QTimer(this);
    dynamiclyShowSliceTimer->setInterval(5);   //  how often exe
    dynamiclyShowSliceTimer->start(0.1);

    //!   Qslider
    //!   QLabel *minValueLabel;
    minValueLabel= new QLabel(tr("  minValue:  ")); maxValueLabel= new QLabel(tr("  maxValue:  "));
    currentValueLabel = new QLabel(tr("  currentValue:"));
    minValuelineEdit = new QLineEdit("0"); maxValuelineEdit = new QLineEdit("99");
    currentValuelineEdit = new QLineEdit("Null");
    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0); // slider->setSliderPosition(5);
    hSpaceItem = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    //!   QSpinBox
    int spinHeight = 20;
    dyminValueLabel = new QLabel(tr("dminValue:"));dyminValueLabel->setFixedHeight(spinHeight);
    dymaxValueLabel = new QLabel(tr("dmaxValue:"));dymaxValueLabel->setFixedHeight(spinHeight);
    dycurrentValueLabel = new QLabel(tr("dcurrentValue:"));dycurrentValueLabel->setFixedHeight(spinHeight);
    stackedWidget = new QStackedWidget();

    QGroupBox *controlGroup;
    invertedAppearance = new QCheckBox(tr("Inverted appearance"));invertedAppearance->setFixedHeight(spinHeight);
    invertedKeyBindings = new QCheckBox(tr("Inverted key bindings"));invertedKeyBindings->setFixedHeight(spinHeight);
    minValueSpinBox = new QSpinBox();minValueSpinBox->setSingleStep(100);minValueSpinBox->setFixedHeight(spinHeight);
    maxValueSpinBox = new QSpinBox();maxValueSpinBox->setSingleStep(100);maxValueSpinBox->setFixedHeight(spinHeight);
    currentValueSpinBox = new QSpinBox();currentValueSpinBox->setFixedHeight(spinHeight);
    QComboBox *orientationCombo;

    dynamicChangeWidget = new QWidget();
    dynamicChangeWidget->setStyleSheet("background-color:RGB(55.0/255,85.0/255,95.0/255)");
    dynamicChangeLayout = new QGridLayout(dynamicChangeWidget);

    dynamicChangeLayout->addWidget(dyminValueLabel,0,0);
    dynamicChangeLayout->addWidget(minValueSpinBox,0,1);
    dynamicChangeLayout->addWidget(invertedAppearance,0,2);

    dynamicChangeLayout->addWidget(dymaxValueLabel,1,0);
    dynamicChangeLayout->addWidget(maxValueSpinBox,1,1);
    dynamicChangeLayout->addWidget(invertedKeyBindings,1,2);

    dynamicChangeLayout->addWidget(dycurrentValueLabel,2,0);
    dynamicChangeLayout->addWidget(currentValueSpinBox,2,1);
    dynamicChangeLayout->setSpacing(0);
    dynamicChangeLayout->setMargin(0);

    MPRWidget = new QWidget();
    qGridLayout = new QGridLayout(MPRWidget);


    cptTim = 0;

    movingButton = new QPushButton();
    movingButton->setText("move");
    movingButton->setFont(QFont("Helvetica", 12, QFont::AnyStyle, false));
    movingButton->setStyleSheet("color: black;background-color:Aliceblue;border-radius:0px");
}

//!--------------------------------------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::constructIHM
//! \param w
//! \param h
//!
void AnalyseWidget::constructIHM(int w,int h){
    for(int i=0;i<4;i++){
        qVTKWidget[i] = new QVTKWidget();
        qVTKWidget[i]->setFixedSize(w/2,h*0.49);
        irenderer[i] = vtkRenderer::New();
        irenderer[i]->SetBackground(55.0/255,85.0/255,95.0/255);
        irenderWindow[i] = vtkRenderWindow::New();
        irenderWindow[i]->AddRenderer(irenderer[i]);
        qVTKWidget[i]->SetRenderWindow(irenderWindow[i]);
        qVTKWidget[i]->update();
    }
    //! use QSlider
    funtionBarWidget = new QWidget();
    funtionBarWidget->setFixedSize(w,w*0.02);
    movingButton->setFixedSize(funtionBarWidget->width()*0.05,funtionBarWidget->height());
    funtionBarLayout = new QHBoxLayout(funtionBarWidget);
    funtionBarLayout->addWidget(minValueLabel);
    funtionBarLayout->addWidget( minValuelineEdit);
    funtionBarLayout->addWidget(maxValueLabel);
    funtionBarLayout->addWidget( maxValuelineEdit);
    funtionBarLayout->addWidget(currentValueLabel);
    funtionBarLayout->addWidget(currentValuelineEdit);
    funtionBarLayout->addWidget(slider);
    funtionBarLayout->addSpacerItem(hSpaceItem);
    funtionBarLayout->addWidget(movingButton);
    funtionBarLayout->addSpacerItem(hSpaceItem);
    funtionBarLayout->setMargin(0);
    funtionBarLayout->setSpacing(0);
    //! use QSpinBox
    qGridLayout->addWidget(qVTKWidget[0],0,0);
    qGridLayout->addWidget(qVTKWidget[1],0,1);
    qGridLayout->addWidget(funtionBarWidget,1,0);
    qGridLayout->addWidget(qVTKWidget[2],2,0);
    qGridLayout->addWidget(qVTKWidget[3],2,1);
    //qGridLayout->addWidget(dynamicChangeWidget,2,1);  //TODO........
    qGridLayout->setSpacing(1);
    qGridLayout->setMargin(0);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(MPRWidget);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::source3DVolumeDisplay
//! \return
//!  planeWidget can be hidden here
//!
bool AnalyseWidget::source3DVolumeDisplay(){
    if(!mymhdfilename.isEmpty()){
        mhdReader->SetFileName(mymhdfilename.toLocal8Bit());
        mhdReader->SetDataScalarTypeToUnsignedChar();
        mhdReader->Update();

        double range[2];
        mhdReader->GetOutput()->GetScalarRange(range);
        shift->SetShift(-1.0*range[0]);
        shift->SetScale(255.0/(range[1]-range[0]));
        shift->SetOutputScalarTypeToUnsignedChar();
        shift->SetInputConnection(mhdReader->GetOutputPort());
        shift->ReleaseDataFlagOff();
        shift->Update();

        fixedMapper->SetInputConnection(mhdReader->GetOutputPort()); //project
        colorTran->AddRGBSegment(0, 1, 1, 1, 255, 1, 1, 1);//color
        colorTran->AddRGBPoint(3000.0, 0.91, 0.65, 0.66);
        colorTran->AddRGBPoint(1208.0, 0.91, 0.65, 0.66);
        colorTran->AddRGBPoint(1200.0, 0.43, 0.43, 0.43);
        colorTran->AddRGBPoint(1800, 0.43, 0.43, 0.43);
        colorTran->AddRGBPoint(2095, 0.9, 0.0, 0.0);
        colorTran->AddRGBPoint(3050, 0.9, 0.0, 0.0);
        colorTran->ClampingOff();

        piceFun->AddSegment(0, 0, 3000, 1);//vtkPiecwise
        piceFun->AddPoint(0,0.0);
        piceFun->AddPoint(800,0);
        piceFun->AddPoint(1000,0.2);
        piceFun->AddPoint(1200,1);
        piceFun->AddPoint(2000,1);

        fixedMapper->SetBlendModeToMaximumIntensity();

        volumeProperty->SetColor(colorTran);//set paras
        volumeProperty->SetScalarOpacity(piceFun);
        volumeProperty->SetInterpolationTypeToLinear();
        volumeProperty->ShadeOff();
        pVolume->SetProperty(volumeProperty);
        pVolume->SetMapper(fixedMapper); //create volume object
        srenderer->AddVolume(pVolume);
        srenderer->SetBackground(55.0/255,85.0/255,95.0/255);
        srenderWindow->AddRenderer(srenderer);
        qVTKWidget[0]->SetRenderWindow(srenderWindow);
        qVTKWidget[0]->update();

        //!---------------------------------------------------------------
        //! only in this position ,no error occurs!
        planeWidget->SetInteractor(srenderWindow->GetInteractor());
        planeWidget->SetInputData(shift->GetOutput());
        planeWidget->SetResolution(10);
        planeWidget->SetPlaceFactor(.5);//........
        planeWidget->SetHandleSize(0.01);//........
        planeWidget->GetPlaneProperty()->SetColor(.9, .4, .4);
        planeWidget->GetHandleProperty()->SetColor(0, .4, .7);
        planeWidget->GetHandleProperty()->SetLineWidth(1.5);

        planeWidget->NormalToXAxisOn();
        planeWidget->SetRepresentationToSurface();
        planeWidget->SetCenter(shift->GetOutput()->GetCenter());
        planeWidget->PlaceWidget();
        planeWidget->Off(); // now is hidden. It can be set On,then displayed
    }
    return 1;
}



//!-----------------------------------------------------------------------------------------------
//!
//! \brief  AnalyseWidget::centerCutting
//! \param  pos keeps synchronize ,dynamicly get the cutting slice.
//!
//! \brief AnalyseWidget::centerCutting
//! \param pos
//!
void AnalyseWidget::centerCutting(int pos){
    // this->maxValue = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->getReferencecount();


     double xi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_abscissa();
     double yi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_ordinate();
     double zi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_isometric();

     double x10 = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos+10)->get_abscissa();
     double y10 = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos+10)->get_ordinate();
     double z10 = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos+10)->get_isometric();

     //! **********************************************************************************************************
     //!   wanna to get dx,dy,dz ???             hav been replaced                   **
     //!   please ensure CenterLineVisualization::coremath() implemented             **
     //!   @ 2016/3/30                                                               **
     //! **********************************************************************************************************
     double origin[3]={xi,yi,zi};
     this->navigationPX = xi; this->navigationPY = yi; this->navigationPZ = zi;
     std::cout<<"*******************************************************************************"<<std::endl;
     std::cout<<"AnalyseWidget::centerCutting()--"<<pos<<"<xi,yi,zi>: "<<xi<<yi<<zi<<std::endl;

     pPlane->SetOrigin(origin);
     pPlane->SetNormal(fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_xdiff(),
                       fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_ydiff(),
                       fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_zdiff());   //! two Vectors:(xi-x0,yi-yo,zi-zo) and (x1-xi,y1-yi,z1-zi),choose the KMean.

     pCut->SetCutFunction(pPlane);//pPlane
     pCut->SetInputData(shift->GetOutput());
     //pCut->SetValue(0,0.5);
     pCut->Update();
     pCut->SetGenerateTriangles(3);
     pCut->SetGenerateCutScalars(3);
     pCut->GenerateTrianglesOff();

     selectMapper->SetInputConnection(pCut->GetOutputPort());
     selectMapper->Update();
     pActor->SetMapper(selectMapper);

     //! *******************************************************
     //! in qVTKWidget[1]
     centerCuttingrenderer->AddActor(pActor);

     //naviPointActor->displayNavigationPoint(centerCuttingrenderer,xi,yi,zi,"m");
     this->myIntersedFrameActor->displayInterestedFrame(centerCuttingrenderer,xi,yi,zi,
         fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos-1)->get_xdiff(),
         fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos-1)->get_ydiff(),
         fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos-1)->get_zdiff(),
         fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_xdiff(),
         fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_ydiff(),
         fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(pos)->get_zdiff());

     //!...
    // this->flyThrough(x10,y10,z10,xi,yi,zi,0.2,0.2,0.2);

     txActor->displayTextActors(centerCuttingrenderer,14);


     //     centerCuttingrenderer->AddActor(this->fws->getCenterLineVisualization_Object()->get_ribbonActor(
//                                        this->fws->getCenterLineVisualization_Object()->getPointSource()));//!add ribbonActor in qVTKWidget[1]

     centerCuttingrenderer->SetBackground(55.0/255,85.0/255,95.0/255);
     planeWidget->AddObserver(vtkCommand::EndInteractionEvent, pCall);
     centerCuttingrenderer->ResetCamera();
     centerCuttingrenderWindow->AddRenderer(centerCuttingrenderer);
     qVTKWidget[1]->SetRenderWindow(centerCuttingrenderWindow);
     qVTKWidget[1]->update();      //!pInt->Initialize(); pInt->Start();

     //! *******************************************************
     //!   in the qVTKWidget[0]
     this->srenderer->AddActor(this->getPActor()); //! add the plane in qVTKWidget[0]
     naviPointActor->displayNavigationPoint(srenderer,xi,yi,zi,"b");
     // interstedSectionrenderer->AddActor(this->interstedFrameFuntion(x0,y0,z0,xi,yi,zi,x1,y1,z1));//!add Frame in qVTKWidget[2]

     //! *******************************************************
     //! in the qVTKWidget[3]

     this->lastWidgetFunction();
     //lastWidgetrenderer->AddActor(this->interstedFrameFuntion(x0,y0,z0,xi,yi,zi,x1,y1,z1));

     this->update();
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::flyThrough
//! \param foc_x  //! \param foc_y  //! \param foc_z
//! \param pos_x  //! \param pos_y  //! \param pos_z
//! \param vie_x  //! \param vie_y  //! \param vie_z
//!
void AnalyseWidget::flyThrough(double foc_x,double foc_y,double foc_z,
                               double pos_x,double pos_y,double pos_z,
                               double vie_x,double vie_y,double vie_z){

    activeCamera->SetClippingRange(0.1,5);
    activeCamera->SetFocalPoint(foc_x ,foc_y ,foc_z);
    activeCamera->SetPosition(pos_x,pos_y, pos_z);
    activeCamera->ComputeViewPlaneNormal();

   // activeCamera->SetViewUp(vie_x,vie_y, vie_z);
    //! qvtkWidget[0]
    srenderer->SetActiveCamera(activeCamera);
    centerCuttingrenderWindow->Render();


    fws->getCenterLineVisualization_Object()->get_renderer()->SetActiveCamera(activeCamera);
    fws->getCenterLineVisualization_Object()->get_renderWindow()->Render();
    fws->getCenterLineVisualization_Object()->get_QVTKWidget()->update();

    //!VolumeVisualization.cpp
//    fws->getVolumeVisualization_Object()->get_renderer()->SetActiveCamera(activeCamera);
//    fws->getVolumeVisualization_Object()->get_rendererWindow()->Render();
//    fws->getVolumeVisualization_Object()->get_qvtkWidget()->update();
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::lastWidgetFunction
//!
void AnalyseWidget::lastWidgetFunction(){
    lastWidgetrenderer->AddActor(this->getPActor());
    //lastWidgetrenderer->AddActor(this->getNavigationPointActor(this->getnavigationPX(),this->getnavigationPY(),this->getnavigationPZ()));



    lastWidgetrenderWindow->AddRenderer(lastWidgetrenderer);
    qVTKWidget[3]->SetRenderWindow(lastWidgetrenderWindow);
    qVTKWidget[3]->update();
}

void AnalyseWidget::newextractInterstedSection(){
    int extent[6]; double spacing[3]; double origin[3];
    mhdReader->Update();
    mhdReader->GetOutput()->GetExtent(extent);
    mhdReader->GetOutput()->GetSpacing(spacing);
    mhdReader->GetOutput()->GetOrigin(origin);

    std::cout<<"the extent0::"<<extent[1]<<" "<<extent[3]<<" "<<extent[5]<<std::endl;
    std::cout<<"the spacing0::"<<spacing[0]<<" "<<spacing[1]<<" "<<spacing[2]<<std::endl;
    std::cout<<"the origin0::"<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5*(extent[0]+ extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5*(extent[2]+ extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5*(extent[4]+ extent[5]);

    double xi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(5)->get_abscissa();
    double yi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(5)->get_ordinate();
    double zi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(5)->get_isometric();


    static double axisElement[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };

    vtkMatrix4x4 * resliceAxis = vtkMatrix4x4::New();
    resliceAxis->DeepCopy(axisElement);
    resliceAxis->SetElement(0,3,center[0]);
    resliceAxis->SetElement(1,3,center[1]);
    resliceAxis->SetElement(2,3,center[2]);


    vtkImageReslice *reslice = vtkImageReslice::New();
    reslice->SetInputData(mhdReader->GetOutput());
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxis);
    reslice->SetInterpolationModeToLinear();
    reslice->Update();

    std::cout<<"the center1::"<<reslice->GetOutput()->GetCenter()[0]<<" "<<
               reslice->GetOutput()->GetCenter()[1]<<" "<<reslice->GetOutput()->GetCenter()[2]<<std::endl;
    vtkLookupTable* colorTable = vtkLookupTable::New();
    colorTable->SetRange(0, 1000);
    colorTable->SetValueRange(0.0, 1.0);
    colorTable->SetSaturationRange(0.0, 0.0);
    colorTable->SetRampToLinear();
    colorTable->Build();

    vtkImageMapToColors* colorMap = vtkImageMapToColors::New();
    colorMap->SetLookupTable(colorTable);
    colorMap->SetInputConnection(reslice->GetOutputPort());
    colorMap->Update();
    std::cout<<"the origin1::"<<reslice->GetOutput()->GetOrigin()[0]<<" "<<
               reslice->GetOutput()->GetOrigin()[1]<<" "<<reslice->GetOutput()->GetOrigin()[2]<<std::endl;

    vtkImageActor* imgActor = vtkImageActor::New();
    imgActor->SetInputData(reslice->GetOutput());
    imgActor->Update();

    interstedSectionrenderer->AddActor(imgActor);
    interstedSectionrenderWindow->AddRenderer(interstedSectionrenderer);

    qVTKWidget[2]->SetRenderWindow(interstedSectionrenderWindow);
    qVTKWidget[2]->update();

    vtkRenderWindowInteractor* renderWindowInteractor = vtkRenderWindowInteractor::New();
    vtkInteractorStyleImage* imagestyle = vtkInteractorStyleImage::New();

    renderWindowInteractor->SetInteractorStyle(imagestyle);
    renderWindowInteractor->SetRenderWindow(qVTKWidget[2]->GetRenderWindow());
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::extractInterstedSection
//!
 void AnalyseWidget::extractInterstedSection(){
     int dimsSource[3];
     vtkImageData *iamgeData = mhdReader->GetOutput();
     iamgeData->GetDimensions(dimsSource);

     double voiW = 45.0;double voiL = 45.0;
     for(int i =0;i<fws->getCenterLineVisualization_Object()->get_centerLineProcess()->getReferencecount()-1;i++){
         double xi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(i)->get_abscissa();
         double yi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(i)->get_ordinate();
         double zi = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(i)->get_isometric();
         double x1 = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(i+1)->get_abscissa();
         double y1 = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(i+1)->get_ordinate();
         double z1 = fws->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().at(i+1)->get_isometric();
         double dx = x1 -xi;double dy = y1 -yi;double dz = z1 -zi;

         vtkExtractVOI *extractVOI = vtkExtractVOI::New();
         extractVOI->SetInputData(iamgeData);
         extractVOI->SetVOI(xi-2,xi+2,yi-voiW/7,yi+voiW/7,zi,zi);

         extractVOI->Update();
         vtkImageData *extractedData = extractVOI->GetOutput();

         vtkImageCast *extractedDataFilter = vtkImageCast::New();
         extractedDataFilter->SetInputData(extractedData);
         extractedDataFilter->SetOutputScalarTypeToUnsignedChar();
         extractedDataFilter->Update();

         vtkImageMagnify *magnifyFilter = vtkImageMagnify::New();
         magnifyFilter->SetInputData(extractedDataFilter->GetOutput());
         magnifyFilter->SetMagnificationFactors(10,10,1);
         magnifyFilter->Update();

         append->SetInputData(magnifyFilter->GetOutput());

         vtkImageActor *extractedDataActor = vtkImageActor::New();
         extractedDataActor->GetMapper()->SetInputData(magnifyFilter->GetOutput());
         extractedDataActor->SetOrigin(xi,yi,-10);
         extractedDataActor->SetOrientation(dx,dy,dz);
         interstedSectionrenderer->AddActor(extractedDataActor);  // single slice
     }
     std::cout<<" AnalyseWidget::extractInterstedSection()-----all vtkExtractVOI finnished"<<std::endl;
     append->PreserveExtentsOff();
     append->SetAppendAxis(0);
     append->Update( );
     vtkFixedPointVolumeRayCastMapper *mapper = vtkFixedPointVolumeRayCastMapper::New();
     vtkColorTransferFunction *colorTranFun;
     vtkPiecewiseFunction *pieceFun;
     vtkVolumeProperty *volumeProperty;
     vtkVolume *volume;
     colorTranFun = vtkColorTransferFunction::New();
     pieceFun = vtkPiecewiseFunction::New();
     volumeProperty = vtkVolumeProperty::New();
     volume = vtkVolume::New();

     mapper->SetInputConnection(append->GetOutputPort());
     colorTranFun->AddRGBSegment(0, 1, 1, 1, 255, 1, 1, 1);

     colorTranFun->ClampingOff();
     pieceFun->AddPoint(0,0.1);
     pieceFun->AddPoint(200,0.7);
     pieceFun->AddPoint(1000,0.8);
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
   // interstedSectionrenderer->AddVolume(volume);

    vtkImageShiftScale *m_pShift = vtkImageShiftScale::New();
    vtkCutter* pCut = vtkCutter::New();
    vtkPlane* pPlane = vtkPlane::New();

    double range[2];
    iamgeData->GetScalarRange(range);
    m_pShift->SetShift(-1.0*range[0]);
    m_pShift->SetScale(255.0/(range[1]-range[0]));
    m_pShift->SetOutputScalarTypeToUnsignedChar();
    m_pShift->SetInputConnection(append->GetOutputPort());
    m_pShift->ReleaseDataFlagOff();
    m_pShift->Update();

    pPlane->SetOrigin(volume->GetCenter());
    pPlane->SetNormal(1,0,0);
    pCut->SetCutFunction(pPlane);
    pCut->SetInputConnection(m_pShift->GetOutputPort());
    pCut->GetOutput()->GetBounds();

    vtkPolyDataMapper* selectMapper = vtkPolyDataMapper::New();
    selectMapper->SetInputConnection(pCut->GetOutputPort());
    vtkActor *actor = vtkActor::New();
    actor->SetMapper(selectMapper);
  //  interstedSectionrenderer->AddActor(actor);

    //!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//    interstedSectionrenderer->AddActor(pActor);
//    interstedSectionrenderer->AddActor(navigationPointActor);
    interstedSectionrenderWindow->AddRenderer(interstedSectionrenderer);
    qVTKWidget[2]->SetRenderWindow(interstedSectionrenderWindow);
    qVTKWidget[2]->update();
}



//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::getLabeledPointActor
//!        add point of labeles  . no need to do this
//!
vtkActor2D *AnalyseWidget::getLabeledPointActor(){
//  labeledPointPolyMapper->SetInputConnection(fws->getc);
//  labeledPointActor->SetMapper(labeledPointPolyMapper);
    return this->labeledPointActor;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::multiView
//!  used in MainWidget::mhdfileChoose() ,a SLOT
//!
void AnalyseWidget::multiView(){
    this->source3DVolumeDisplay();

    //int position[3] = {0,0,0};                 //give a position,get it's pix
    //this->getPixel(mymhdfilename, position);
}

//!-------------------------------------------------------------------------------------------------------------
//!
//!  function: once give a position ,get it's pixsel
//!
double *AnalyseWidget::getPixel(QString filePath, int pos[3]){
    if(!filePath.isEmpty()){
        mhdReader->SetFileName(filePath.toLocal8Bit());
        mhdReader->Update();
        std::cout<<"AnalyseWidget::getPixel(QString filePath, int pos[3]):  "<<mhdReader->GetFileName()<<std::endl;
        vtkImageData *imageData = mhdReader->GetOutput();
        int *dims = imageData->GetDimensions();

        double* pixel = static_cast<double*>(imageData->GetScalarPointer(pos[0],pos[1],pos[2]));
        std::cout<<"AnalyseWidget::getPixel(QString filePath, int pos[3]):  "<<pixel[0]<<std::endl;
        return pixel;
    }
}


//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::get_Srenderer
//!
vtkRenderer* AnalyseWidget::get_Srenderer(){
     return this->srenderer;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::get_CenterCuttingrenderer
//!
vtkRenderer* AnalyseWidget::get_CenterCuttingrenderer(){
     return this->centerCuttingrenderer;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::updatecenterCuttingQVTKWidget
//!
void AnalyseWidget::updatecenterCuttingQVTKWidget(){
  this->qVTKWidget[1]->update();
  this->qVTKWidget[0]->update();
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::getSlider
//!
QSlider *AnalyseWidget::getSlider(){
    return this->slider;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::getMaxValuelineEdit
//!
QLineEdit *AnalyseWidget::getMaxValuelineEdit(){
  return this->maxValuelineEdit;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::getMinValueSpinBox
//! \return
//!
QSpinBox *AnalyseWidget::getMinValueSpinBox(){
    return this->minValueSpinBox;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::getMaxValueSpinBox
//! \return
//!
QSpinBox *AnalyseWidget::getMaxValueSpinBox(){
    return this->maxValueSpinBox;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::getCurrentValueSpinBox
//! \return
//!
QSpinBox *AnalyseWidget::getCurrentValueSpinBox(){
    return this->currentValueSpinBox;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::getPActor
//! \return
//!
vtkActor *AnalyseWidget::getPActor(){
    return this->pActor;
}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief AnalyseWidget::getColorTran
//! \return
//!
 vtkColorTransferFunction* AnalyseWidget::getColorTran(){
     return this->colorTran;
 }

 double AnalyseWidget::getnavigationPX(){
     return this->navigationPX;
 }
 double AnalyseWidget::getnavigationPY(){
     return this->navigationPY;
 }
 double AnalyseWidget::getnavigationPZ(){
     return this->navigationPZ;

 }

 //!-----------------------------------------------------------------------------------------------
 //!
 //! \brief AnalyseWidget::movingExecute
 //!
 void AnalyseWidget::movingExecute(){
     cptTim = 0;
     if(!fws->getCenterlinefile().isEmpty()){
         connect(dynamiclyShowSliceTimer,SIGNAL(timeout()),this,SLOT(dynamiclyShowSlice()));
     }else
         std::cout<<"please choose a centerline!"<<std::endl;
}

 //!-----------------------------------------------------------------------------------------------
 //!
 //! \brief AnalyseWidget::ThreeDimensionReconstruction
 //!
void AnalyseWidget::ThreeDimensionReconstruction(){

    /*
    #include <vtkRenderer.h>
    #include <vtkRenderWindow.h>
    #include <vtkRenderWindowInteractor.h>
    #include <vtkDICOMImageReader.h>
    #include <vtkPolyDataMapper.h>
    #include <vtkActor.h>
    #include <vtkOutlineFilter.h>
    #include <vtkCamera.h>
    #include <vtkProperty.h>
    #include <vtkPolyDataNormals.h>
    #include <vtkContourFilter.h>
    #include <vtkInteractorStyleTrackballCamera.h>

     int main(int argc, char *argv[])
    {
       if (argc!=2) {
       std::cout << "usage: ./your_executable_fle   /path/to/slices"<<std::endl; }
    // Create the renderer, the render window, and the interactor. The renderer
      // draws into the render window, the interactor enables mouse- and
      // keyboard-based interaction with the data within the render window.
      vtkRenderer *Render = vtkRenderer::New();
      vtkRenderWindow *renWin = vtkRenderWindow::New();
        renWin->AddRenderer(Render);
      vtkInteractorStyleTrackballCamera *style=vtkInteractorStyleTrackballCamera::New();
      vtkRenderWindowInteractor *ireninter = vtkRenderWindowInteractor::New();
        ireninter->SetInteractorStyle(style);
        ireninter->SetRenderWindow(renWin);


      // The following reader is used to read a series of 2D slices (images) that compose the volume.
        vtkDICOMImageReader *imageseries = vtkDICOMImageReader::New();
        imageseries->SetDirectoryName("F:\\someonlindatasets\\sample\\");
        imageseries->SetDataSpacing (3.2, 3.2, 1.5);

      // An isosurface, or contour value of 500 is known to correspond to the
      // skin of the patient. Once generated, a vtkPolyDataNormals filter is
      // is used to create normals for smooth surface shading during rendering.
      vtkContourFilter *skinExtractor = vtkContourFilter::New();
        skinExtractor->SetInputConnection(imageseries->GetOutputPort());
        skinExtractor->SetValue(0, 300);
      vtkPolyDataNormals *skinNormals = vtkPolyDataNormals::New();
        skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
        skinNormals->SetFeatureAngle(60.0);
      vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
        skinMapper->SetInputConnection(skinNormals->GetOutputPort());
        skinMapper->ScalarVisibilityOff();
      vtkActor *skin = vtkActor::New();
        skin->SetMapper(skinMapper);

      // An outline provides context around the data.
      vtkOutlineFilter *outlineData = vtkOutlineFilter::New();
        outlineData->SetInputConnection(imageseries->GetOutputPort());
      vtkPolyDataMapper *mapOutline = vtkPolyDataMapper::New();
        mapOutline->SetInputConnection(outlineData->GetOutputPort());
      vtkActor *outline = vtkActor::New();
        outline->SetMapper(mapOutline);
        outline->GetProperty()->SetColor(1,0,0);

      // It is convenient to create an initial view of the data. The FocalPoint
      // and Position form a vector direction. Later on (ResetCamera() method)
      // this vector is used to position the camera to look at the data in
      // this direction.
        vtkCamera *aCamera = vtkCamera::New();
        aCamera->SetViewUp (0, 0, -1);
        aCamera->SetPosition (0, 1, 0);
        aCamera->SetFocalPoint (0, 0, 0);
        aCamera->ComputeViewPlaneNormal();

      // Actors are added to the renderer. An initial camera view is created.
      // The Dolly() method moves the camera towards the FocalPoint,
      // thereby enlarging the image.
      Render->AddActor(outline);
      Render->AddActor(skin);
      Render->SetActiveCamera(aCamera);
      Render->ResetCamera ();
      aCamera->Dolly(2);

      // Set a background color for the renderer and set the size of the
      // render window (expressed in pixels).
      Render->SetBackground(0.0,0.0,0.0);
      renWin->SetSize(640, 480);

      // Note that when camera movement occurs (as it does in the Dolly()
      // method), the clipping planes often need adjusting. Clipping planes
      // consist of two planes: near and far along the view direction. The
      // near plane clips out objects in front of the plane; the far plane
      // clips out objects behind the plane. This way only what is drawn
      // between the planes is actually rendered.
      Render->ResetCameraClippingRange ();
      // Initialize the event loop and then start it.
      ireninter->Initialize();
      ireninter->Start();

      // It is important to delete all objects created previously to prevent
      // memory leaks. In this case, since the program is on its way to
      // exiting, it is not so important. But in applications it is
      // essential.
      imageseries->Delete();
      skinExtractor->Delete();
      skinNormals->Delete();
      skinMapper->Delete();
      skin->Delete();
      outlineData->Delete();
      mapOutline->Delete();
      outline->Delete();
      aCamera->Delete();
      ireninter->Delete();
      renWin->Delete();
      Render->Delete();
      return 0;
    }
*/
}

