#include "MainWidget.h"
#include "CenterLineProcess.h"

MainWidget::MainWidget(QWidget *parent): QWidget(parent)
{
    this->initVariable();
    this->constructIHM();
    this->setconnections();
}
MainWidget::~MainWidget()
{

}

//!---------------------------------------------------------------------------------
//! \brief MainWidget::initVariable
//!
void MainWidget::initVariable(){
    desktop = QApplication::desktop();
    this->width = desktop->width();
    this->height = desktop->height()*0.9;
    this->resize(this->width,this->height);
    this->setWindowTitle("cpr Analyse Platform");
    this->setWindowIcon(QIcon(":/images/splash.png"));

    fs = new FourViewWidget();


    timeLCD = new QLCDNumber();
    timeLCD->setStyleSheet("color:rgb(85, 85, 255);background-color:rgb(0, 0, 0);");
    timeLCD->setFont(QFont("Segoe UI", 8, QFont::AnyStyle, true));
    timeLCD->setDigitCount(10);
    timeLCD->setMode(QLCDNumber::Dec);
    timeLCD->setSegmentStyle(QLCDNumber::Flat);
    updatetimer = new QTimer();
    updatetimer->setInterval(10);
    updatetimer->start(1000);

    datasetSpaceItem= new  QSpacerItem(50, 30, QSizePolicy::Expanding, QSizePolicy::Expanding);
    pushBtnSpaceItem = new  QSpacerItem(5, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);
    vSpaceItem1 = new  QSpacerItem(20, 30, QSizePolicy::Expanding, QSizePolicy::Expanding);

    fs->getVolumeVisualization_Object()->setFixedSize(this->width*0.4,this->height*0.92*0.45);
    fs->getCenterLineVisualization_Object()->setFixedSize(this->width*0.4,this->height*0.92*0.45);
    fs->getStraightedVisualization_Object()->setFixedSize(this->width*0.8,this->height*0.92*0.5);
}

//!---------------------------------------------------------------------------------
//! \brief MainWidget::constructIHM
//!
void MainWidget::constructIHM(){
    toolBarWidget = new QWidget();
    toolBarWidget->setStyleSheet("color: rgb(255, 255, 255);background-color:gray;border-radius:5px");
    toolBarWidget->setFixedSize(this->width,this->height*0.04);
    toolBarLayout = new QHBoxLayout(toolBarWidget);

    firstBtn = new QPushButton(); secondBtn = new QPushButton();
    mhdfileloadBtn = new QPushButton();
    centerfileloadBtn = new QPushButton();
    cprBtn = new QPushButton();
    projected_CenterlineBtn = new QPushButton();
    anaylseBtn = new QPushButton();
    volumeRenderingBtn = new QPushButton();

    firstBtn->setFixedSize(toolBarWidget->width()*0.05,toolBarWidget->height());
    secondBtn->setFixedSize(toolBarWidget->width()*0.05,toolBarWidget->height());
    mhdfileloadBtn->setFixedSize(toolBarWidget->width()*0.05,toolBarWidget->height());
    centerfileloadBtn->setFixedSize(toolBarWidget->width()*0.1,toolBarWidget->height());
    cprBtn->setFixedSize(toolBarWidget->width()*0.05,toolBarWidget->height());
    projected_CenterlineBtn->setFixedSize(toolBarWidget->width()*0.05,toolBarWidget->height());
    anaylseBtn->setFixedSize(toolBarWidget->width()*0.05,toolBarWidget->height());
    volumeRenderingBtn->setFixedSize(toolBarWidget->width()*0.1,toolBarWidget->height());

    //    firstBtn->setStyleSheet("QPushButton{border-image: url(:/images/image_zoomin.png);}"
    //                            //                       "QPushButton:hover{border-image: url(:/images/addfile-hover.png);}"
    //                            "QPushButton:pressed{border-image: url(:/images/addButton.png);}");

    QFont btnFont("Helvetica", 12, QFont::AnyStyle, false);

    firstBtn->setText("add");
    firstBtn->setFont(btnFont);
    firstBtn->setStyleSheet("color: beige;background-color:transparent;border-radius:0px");
    secondBtn->setText("delete");
    secondBtn->setFont(btnFont);
    secondBtn->setStyleSheet("color: beige;background-color:transparent;border-radius:0px");

    mhdfileloadBtn->setText("volume");
    mhdfileloadBtn->setFont(btnFont);
    mhdfileloadBtn->setStyleSheet("color: beige;background-color:transparent;border-radius:0px");
    centerfileloadBtn->setText("centerline");
    centerfileloadBtn->setFont(btnFont);
    centerfileloadBtn->setStyleSheet("color: beige;background-color:transparent;border-radius:0px");
    cprBtn->setText("cpr");
    cprBtn->setFont(btnFont);
    cprBtn->setStyleSheet("color: beige;background-color:transparent;border-radius:0px");
    projected_CenterlineBtn->setText("projected");
    projected_CenterlineBtn->setFont(btnFont);
    projected_CenterlineBtn->setStyleSheet("color:beige;background-color:transparent;border-radius:0px");
    anaylseBtn->setText("anaylse");
    anaylseBtn->setFont(btnFont);
    anaylseBtn->setStyleSheet("color: beige;background-color:transparent;border-radius:0px");
    volumeRenderingBtn->setText("volumeRender");
    volumeRenderingBtn->setFont(btnFont);
    volumeRenderingBtn->setStyleSheet("color:beige;background-color:transparent;border-radius:0px");

    toolBarLayout->addSpacerItem(datasetSpaceItem);
    toolBarLayout->addWidget(firstBtn);
    toolBarLayout->addWidget(secondBtn);
    toolBarLayout->addSpacerItem(datasetSpaceItem);
    toolBarLayout->addSpacerItem(datasetSpaceItem);
    toolBarLayout->addSpacerItem(datasetSpaceItem);
    toolBarLayout->addWidget(mhdfileloadBtn);
    toolBarLayout->addSpacerItem(datasetSpaceItem);
    toolBarLayout->addWidget(centerfileloadBtn);
    toolBarLayout->addSpacerItem(datasetSpaceItem);
    toolBarLayout->addWidget(cprBtn);
    toolBarLayout->addSpacerItem(datasetSpaceItem);
    toolBarLayout->addWidget(anaylseBtn);
    toolBarLayout->addSpacerItem(datasetSpaceItem);
    toolBarLayout->addWidget(volumeRenderingBtn);
    toolBarLayout->addSpacerItem(datasetSpaceItem);

    toolBarLayout->setSpacing(0);
    toolBarLayout->setMargin(0);

    middleWidget = new QWidget();
    middleWidget->setFixedSize(this->width,this->height*0.92);
    middleWidget->setStyleSheet("border-radius:5px");
    middleLayout = new QHBoxLayout(middleWidget);
    //! --------------------------------------------
    subtoolWidget = new QWidget();
    subtoolWidgetLayout = new QVBoxLayout(subtoolWidget);

    //! ------------- 1.centerlineTreeWidget ------------
    centerlineTreeWidget = new QTreeWidget(); // middle left up
    centerlineTreeWidget->setStyleSheet("border:1px solid gray");
    centerlineTreeWidget->setFixedHeight(this->height*0.92*0.5);
    centerlineTreeWidget->setColumnCount(1);
    centerlineTreeWidget->setHeaderLabel("Datasets");
    centerlineTreeWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    centerlineTreeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QHeaderView *pHeader = centerlineTreeWidget->header();
    pHeader->resizeSections(QHeaderView::ResizeToContents);
    pHeader->setStretchLastSection(false);

    //! ------------- 2.waitingWidget ------------
    waitingWidget = new QWidget();  // middle left bottom
    waitingWidget->setFixedHeight(this->height*0.92*0.5);

    addcurvePlaneBtn = new QPushButton();
    deletecurvePlaneBtn = new QPushButton();
    bloodThreeDimensionReconstuctionBtn = new QPushButton();
    deletebloodThreeDimensionReconstuctionBtn = new QPushButton();
    addnavigationActorBtn = new QPushButton();
    deletenavigationActorBtn = new QPushButton();
    addgridActorBtn = new QPushButton();
    deletegridActorBtn = new QPushButton();
    addprojectedBtn = new QPushButton();
    deleteprojectedBtn = new QPushButton();

    addnavigationActorBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    addnavigationActorBtn->setText("addnavigation");
    addnavigationActorBtn->setFont(btnFont);
    addnavigationActorBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");
    deletenavigationActorBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    deletenavigationActorBtn->setText("deletenavigation");
    deletenavigationActorBtn->setFont(btnFont);
    deletenavigationActorBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");
    addgridActorBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    addgridActorBtn->setText("addgrid");
    addgridActorBtn->setFont(btnFont);
    addgridActorBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");
    deletegridActorBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    deletegridActorBtn->setText("deletegrid");
    deletegridActorBtn->setFont(btnFont);
    deletegridActorBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");
    bloodThreeDimensionReconstuctionBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    bloodThreeDimensionReconstuctionBtn->setText("3D_blood");
    bloodThreeDimensionReconstuctionBtn->setFont(btnFont);
    bloodThreeDimensionReconstuctionBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");
    deletebloodThreeDimensionReconstuctionBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    deletebloodThreeDimensionReconstuctionBtn->setText("delete");
    deletebloodThreeDimensionReconstuctionBtn->setFont(btnFont);
    deletebloodThreeDimensionReconstuctionBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");
    addcurvePlaneBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    addcurvePlaneBtn->setText("curveplane");
    addcurvePlaneBtn->setFont(btnFont);
    addcurvePlaneBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");
    deletecurvePlaneBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    deletecurvePlaneBtn->setText("deletecurve");
    deletecurvePlaneBtn->setFont(btnFont);
    deletecurvePlaneBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");

    addprojectedBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    addprojectedBtn->setText("addprojected");
    addprojectedBtn->setFont(btnFont);
    addprojectedBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");
    deleteprojectedBtn->setFixedSize(waitingWidget->width()*0.2,waitingWidget->height()*0.08);
    deleteprojectedBtn->setText("deleteprojected");
    deleteprojectedBtn->setFont(btnFont);
    deleteprojectedBtn->setStyleSheet("background-color:Aliceblue;border-radius:0px");

    timeLCD->setFixedSize(waitingWidget->width()*0.4,waitingWidget->height()*0.1);

    waitingWidgetLayout = new QGridLayout(waitingWidget);
    waitingWidgetLayout->addWidget(addgridActorBtn,0,0);
    waitingWidgetLayout->addWidget(deletegridActorBtn,0,1);
    waitingWidgetLayout->addWidget(addnavigationActorBtn,1,0);
    waitingWidgetLayout->addWidget(deletenavigationActorBtn,1,1);
    waitingWidgetLayout->addWidget(addprojectedBtn,2,0);
    waitingWidgetLayout->addWidget(deleteprojectedBtn,2,1);
    waitingWidgetLayout->addWidget(bloodThreeDimensionReconstuctionBtn,3,0);
    waitingWidgetLayout->addWidget(deletebloodThreeDimensionReconstuctionBtn,3,1);
    waitingWidgetLayout->addWidget(addcurvePlaneBtn,4,0);
    waitingWidgetLayout->addWidget(deletecurvePlaneBtn,4,1);
    waitingWidgetLayout->addWidget(timeLCD,5,0); // show system time

    subtoolWidgetLayout->addWidget(centerlineTreeWidget); //1.centerlineTreeWidget
    subtoolWidgetLayout->addWidget(waitingWidget);// 2.waitingWidget
    subtoolWidgetLayout->setSpacing(0);
    subtoolWidgetLayout->setMargin(0);
    subtoolWidget->setFixedSize(this->width*0.2,this->height*0.92);
    subtoolWidget->setStyleSheet("background-color:lightyellow; border-radius:0px");
    //! --------------------------------------------

    qTabWidget = new QTabWidget();
    QIcon iconwindow1(":/images/start.png");
    qTabWidget->addTab(fs,iconwindow1,"main wind");
    qTabWidget->setStyleSheet("background-color:gray");

    middleLayout->addWidget(subtoolWidget);
    middleLayout->addWidget(qTabWidget);
    middleLayout->setMargin(0);
    middleLayout->setSpacing(0);

    statusBarWidget = new QWidget();
    statusBarWidget->setFixedSize(this->width,this->height*0.04);
    statusBarWidget->setStyleSheet("background-color:gray");

    qGridLayout = new QVBoxLayout(this);
    qGridLayout->addWidget(toolBarWidget);
    qGridLayout->addWidget(middleWidget);
    qGridLayout->addWidget(statusBarWidget);
    qGridLayout->setMargin(0);
    qGridLayout->setSpacing(0);
}

FourViewWidget *MainWidget::getFourViewWidget(){
    return this->fs;
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::setconnections
//!
void MainWidget::setconnections(){
    connect(mhdfileloadBtn,SIGNAL(clicked(bool)),this,SLOT(mhdfileChoose()));
    connect(centerfileloadBtn,SIGNAL(clicked(bool)),this,SLOT(centerfileChoose()));
    connect(cprBtn,SIGNAL(clicked(bool)),this,SLOT(straightedCPR()));
    connect(projected_CenterlineBtn,SIGNAL(clicked(bool)),this,SLOT(projected_Centerline()));
    connect(anaylseBtn,SIGNAL(clicked(bool)),this,SLOT(anaylse()));
    connect(volumeRenderingBtn,SIGNAL(clicked(bool)),this,SLOT(volumeRenderingfunction()));
    connect(firstBtn,SIGNAL(clicked(bool)),this,SLOT(addreference()));
    connect(centerlineTreeWidget,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(SlotItemClicked(QTreeWidgetItem *, int)));
    connect(updatetimer,SIGNAL(timeout()),this,SLOT(getSystemTime()));

    //!...
    connect(addnavigationActorBtn,SIGNAL(clicked(bool)),this,SLOT(addnavigationActor()));
    connect(deletenavigationActorBtn,SIGNAL(clicked(bool)),this,SLOT(deletenavigationActor()));
    connect(addgridActorBtn,SIGNAL(clicked(bool)),this,SLOT(addgridActor()));
    connect(deletegridActorBtn,SIGNAL(clicked(bool)),this,SLOT(deletegridActor()));
    connect(addprojectedBtn,SIGNAL(clicked(bool)),this,SLOT(addprojectedCenterline()));
    connect(deleteprojectedBtn,SIGNAL(clicked(bool)),this,SLOT(deleteprojectedCenterline()));
    connect(bloodThreeDimensionReconstuctionBtn,SIGNAL(clicked(bool)),this,SLOT(bloodThreeDimensionReconstuction()));
    connect(deletebloodThreeDimensionReconstuctionBtn,SIGNAL(clicked(bool)),this,SLOT(deletebloodThreeDimensionReconstuction()));
    connect(addcurvePlaneBtn,SIGNAL(clicked(bool)),this,SLOT(on_addcurvePlaneBtn()));
    connect(deletecurvePlaneBtn,SIGNAL(clicked(bool)),this,SLOT(on_deletecurvePlaneBtn()));
}

//!---------------------------------------------------------------------------------
//! \brief MainWidget::mhdfileChoose
//!  1.FourViewWidget.cpp\ 2.BasicParameters.cpp\ 3.AnalyseWidget.cpp
//!---------------------------------------------------------------------------------
void MainWidget::mhdfileChoose(){
    fs->getVolumeVisualization();
    if(!fs->getMhdfile().isEmpty()){
        basicParameters = new BasicParameters(fs);
        this->anaylseofBasicParameters()->mhdfileparameterItem();
        analyseWidget = new AnalyseWidget(fs,this->width*0.8,this->height*0.9);
        this->anaylseofAnaylse()->multiView();
    }
    if(!fs->getCenterlinefile().isEmpty()){
        this->anaylseofBasicParameters()->centerlineparameterItem();
    }
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::centerfileChoose
//!
void MainWidget::centerfileChoose(){
    fs->getCenterLineVisualization();

    if(!fs->getCenterlinefile().isEmpty()&&!fs->getMhdfile().isEmpty()){
        fs->function();
        this->anaylseofBasicParameters()->centerlineparameterItem();
        //! show the reference in analyseWidget->qVTKWidget[0]
        //! this->analyseWidget->get_Srenderer()->AddActor(fs->getCenterLineVisualization_Object()->get_actor());
        //! show the reference in analyseWidget->qVTKWidget[1]
        this->analyseWidget->get_CenterCuttingrenderer()->AddActor(fs->getCenterLineVisualization_Object()->get_actor());
        int maxValue = fs->getCenterlinepointsize();
        this->analyseWidget->getSlider()->setMaximum(maxValue);//!set slider maxValue
        QString maxValueString = QString("%1").arg(maxValue);
        this->analyseWidget->getMaxValuelineEdit()->setText(maxValueString);
        this->analyseWidget->getMinValueSpinBox()->setRange(0,maxValue);this->analyseWidget->getMinValueSpinBox()->setValue(maxValue/3);
        this->analyseWidget->getMaxValueSpinBox()->setRange(10,maxValue);this->analyseWidget->getMaxValueSpinBox()->setValue(maxValue);
        int minSpinValue= analyseWidget->getMinValueSpinBox()->value();
        int maxSpinValue= analyseWidget->getMaxValueSpinBox()->value();
        qDebug()<<"MainWidget::centerfileChoose() ---"<<"minSpinValue:"<<minSpinValue<<"maxSpinValue:"<<maxSpinValue;
        this->analyseWidget->getCurrentValueSpinBox()->setRange(minSpinValue,maxSpinValue);this->analyseWidget->getCurrentValueSpinBox()->setValue(maxValue/2);
        //this->basicParameters->plotRadius(this->getFourViewWidget()->getCenterlinepointsize());
        //! in  analyseWidget->qVTKWidget[2]
       // analyseWidget->extractInterstedSection();   //!in analyseWidget->qVTKWidget[2]
        // this->analyseWidget->newextractInterstedSection();  //!in analyseWidget->qVTKWidget[2]
        //!basicParameters->plotRadius(fs->getCenterlinepointsize());
    }
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::straightedCPR
//!
void MainWidget::straightedCPR(){
    //fs->getStraightedVisualization1();
    this->straightedCPR_implementation();   // used to replace getStraightedVisualization1()
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::reconstructed
//!
void MainWidget::reconstructed(){
    fs->getStraightedVisualization();
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::getSystemTime
//!
void MainWidget::getSystemTime(){
    QTime cutrrentTime = QTime::currentTime();
    timeLCD->display(cutrrentTime.toString("hh:mm:ss"));
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::projected_Centerline
//!
void MainWidget::projected_Centerline(){
    qDebug()<<"this function is going to realize projected_Centerline";
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::anaylse
//!
void MainWidget::anaylse(){

}

void MainWidget::addnavigationActor(){
    if(!fs->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName().isEmpty()){
        fs->getCenterLineVisualization_Object()->get_renderer()->AddActor( fs->getCenterLineVisualization_Object()->getAcquisitioncenterlineActor());
        fs->getCenterLineVisualization_Object()->get_QVTKWidget()->update();
    }
}
void MainWidget::deletenavigationActor(){
    if(!fs->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName().isEmpty()){
        fs->getCenterLineVisualization_Object()->get_renderer()->RemoveActor(
                    fs->getCenterLineVisualization_Object()->getAcquisitioncenterlineActor());
        fs->getCenterLineVisualization_Object()->get_QVTKWidget()->update();
    }
}
void MainWidget::addgridActor(){
    if(!fs->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName().isEmpty()){
        fs->getCenterLineVisualization_Object()->get_renderer()->AddActor( fs->getCenterLineVisualization_Object()->getAcquisitionActor());
        fs->getCenterLineVisualization_Object()->get_QVTKWidget()->update();
    }
}
void MainWidget::deletegridActor(){

    if(!fs->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName().isEmpty()){
        fs->getCenterLineVisualization_Object()->get_renderer()->RemoveActor(
                    fs->getCenterLineVisualization_Object()->getAcquisitionActor());
        fs->getCenterLineVisualization_Object()->get_QVTKWidget()->update();
    }
}

void MainWidget::addprojectedCenterline(){
    if(!fs->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName().isEmpty()){
        fs->getCenterLineVisualization_Object()->get_renderer()->AddActor(
                    fs->getCenterLineVisualization_Object()->get_ProjectedpointActor(0.0,6.0,14.15,0.0,0.0,1.0));
        fs->getCenterLineVisualization_Object()->get_QVTKWidget()->update();
    }
}
void MainWidget::deleteprojectedCenterline(){
    if(!fs->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName().isEmpty()){
        fs->getCenterLineVisualization_Object()->get_renderer()->RemoveActor(
                    fs->getCenterLineVisualization_Object()->getProjectedCenterlineActor());
        fs->getCenterLineVisualization_Object()->get_QVTKWidget()->update();
    }
}

//!------------------------------------------------------------------------------------------------
//!
//! \brief MainWidget::bloodThreeDimensionReconstuction
//!
void MainWidget::bloodThreeDimensionReconstuction(){
    if(!fs->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName().isEmpty()){
        fs->getCenterLineVisualization_Object()->get_renderer()->AddActor(fs->getCenterLineVisualization_Object()->getReconstructionActor());
        fs->getCenterLineVisualization_Object()->get_QVTKWidget()->update();
    }
}


//!------------------------------------------------------------------------------------------------
//!
//! \brief MainWidget::deletebloodThreeDimensionReconstuction
//!
void MainWidget::deletebloodThreeDimensionReconstuction(){
    if(!fs->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName().isEmpty()){
        fs->getCenterLineVisualization_Object()->get_renderer()->RemoveActor(fs->getCenterLineVisualization_Object()->getReconstructionActor());
        fs->getCenterLineVisualization_Object()->get_QVTKWidget()->update();
    }
}

//! todo
void MainWidget::on_addcurvePlaneBtn(){

}
//!todo
void MainWidget::on_deletecurvePlaneBtn(){

}

//! TODO:     2016-3-18
AnalyseWidget *MainWidget::anaylseofAnaylse(){
    QIcon iconwindow1(":/images/start.png");
    qTabWidget->addTab(analyseWidget,iconwindow1,"i"); //new in this->mhdfileChoose()
    return  analyseWidget;
}

//! TODO:     2016-3-18
BasicParameters *MainWidget::anaylseofBasicParameters(){
    QIcon iconwindow1(":/images/start.png");
    qTabWidget->addTab(basicParameters,iconwindow1,"i");// new this->centerfileChoose()
    return basicParameters;
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::volumeRenderingfunction
//! TODO:  to realize ray casting function dynamicaly   2016-3-18
//!
void MainWidget::volumeRenderingfunction(){
    if(!fs->getVolumeVisualization_Object()->getmhdfilename().isEmpty()){
        //! rendering in VolumeVisualization.cpp
        colorTran=  fs->getVolumeVisualization_Object()->get_colorTranFun();
        colorTranofStraight = fs->getStraightedVisualization_Object()->get_colorTranFun();
        colorTran->AddHSVPoint(0.0,0.01,1.0,1.0);
        colorTran->AddHSVPoint(1000.0,0.49,3.0,1.0);
        colorTran->AddHSVPoint(2000.0,0.99,1.0,1.0);
        colorTran->SetColorSpaceToHSV();
        fs->getVolumeVisualization_Object()->get_qvtkWidget()->update();

        //! rendering in StraightedVisualization.cpp
        colorTranofStraight = fs->getStraightedVisualization_Object()->get_colorTranFun();
        colorTranofStraight->AddHSVPoint(0.0,0.01,1.0,1.0);
        colorTranofStraight->AddHSVPoint(1000.0,0.49,3.0,1.0);
        colorTranofStraight->AddHSVPoint(2000.0,0.99,1.0,1.0);
        colorTranofStraight->SetColorSpaceToHSV();
        fs->getStraightedVisualization_Object()->getQVTKWidget()->update();
        //!
        colorTranofAnaly = analyseWidget->getColorTran();
        colorTranofAnaly->AddHSVPoint(0.0,0.01,1.0,1.0);
        colorTranofAnaly->AddHSVPoint(1000.0,0.49,3.0,1.0);
        colorTranofAnaly->AddHSVPoint(2000.0,0.99,1.0,1.0);
        colorTranofAnaly->SetColorSpaceToHSV();
        analyseWidget->updatecenterCuttingQVTKWidget();
    }
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::addreference
//!  TODO:  return special files,"mhd" or "txt"   2016-3-18
//!
void MainWidget::addreference(){
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "E:/",
                                                    QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDir referencesDir(dir);
    referencesDir.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
    referencesDir.setSorting(QDir::Size|QDir::Reversed);

    //QStringList allFiles = referencesDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);//(QDir::Filter::Files,QDir::SortFlag::NoSort);
    //-------------------------------------

    QStringList txtFilter; txtFilter<<".txt";
    referencesDir.setNameFilters(txtFilter);
    QFileInfoList txtList = referencesDir.entryInfoList();
    QString str;
    qDebug()<<"fab"<<txtList.length();
    for(int i =0;i<txtList.size();i++){
        QFileInfo txtInfo = txtList.at(i);
        str = txtInfo.fileName();
        qDebug()<<"huihu"<<str;
    }

    //-------------------------------------
    datasetstreeItem = new QTreeWidgetItem(centerlineTreeWidget,QStringList(dir));
    datasetstreeItem->setIcon(0,QIcon(":/images/Disk.png"));
    datasetstreeItem->setCheckState(0,Qt::Unchecked);

    mhdfilewidgetItem = new QTreeWidgetItem(datasetstreeItem,QStringList("mhd"));
    mhdfilewidgetItem->setIcon(0,QIcon(":/images/init.png"));
    referenceswidgetItem = new QTreeWidgetItem(datasetstreeItem,QStringList(QString("references")));
    referenceswidgetItem->setIcon(0,QIcon(":/images/plotting.png"));
    datasetstreeItem->addChild(mhdfilewidgetItem);
    datasetstreeItem->addChild(referenceswidgetItem);
    centerlineTreeWidget->expandAll();
}

//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::SlotItemClicked
//! \param item \param column
//!
void MainWidget::SlotItemClicked(QTreeWidgetItem *item, int column){
    if( qApp->mouseButtons() == Qt::LeftButton){return ;}
    if( qApp->mouseButtons() == Qt::RightButton){
        if(item->childCount()>0){return ;}
        ShowMhdMenu();
    }
}


//!---------------------------------------------------------------------------------
//!
//! \brief MainWidget::ShowMhdMenu
//!
void MainWidget::ShowMhdMenu(){
    QPoint pos;
    QMenu menu(centerlineTreeWidget);
    QIcon myIcon1(":/images/image_zoomin.png");
    QIcon myIcon2(":/images/image_zoomout.png");
    menu.addAction(myIcon1,tr("Add mhd"));
    menu.addAction(myIcon2,tr("Delete mhd"));
    menu.exec(QCursor::pos());
}

//!-----------------------------------------------------------------------------------------------------------
//!
//! \brief MainWidget::straightedCPR_implementation
//! a judgetment method
//!
void MainWidget::straightedCPR_implementation(){
    if(fs->getVolumeVisualization_Object()->getmhdfilename().isEmpty()&&
            fs->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().size()<=0){
        QMessageBox message(QMessageBox::Warning,"Information","please choose a mhd file and centerline?",QMessageBox::Yes|QMessageBox::No,NULL);
        if (message.exec()==QMessageBox::Yes){
            this->mhdfileChoose();
            this->straightedCPR_implementation();
        } else { return ;}
    }else if(fs->getVolumeVisualization_Object()->getmhdfilename().isEmpty()){
        QMessageBox message(QMessageBox::Warning,"Information","please choose mhdfile?",QMessageBox::Yes|QMessageBox::No,NULL);
        if (message.exec()==QMessageBox::Yes){
            this->mhdfileChoose();
            this->straightedCPR_implementation();
        } else { return ;}
    }else if(fs->getCenterLineVisualization_Object()->get_centerLineProcess()->get_vesselsPoints().size()<=0){
        QMessageBox message(QMessageBox::Warning,"Information","please choose a centerline?", QMessageBox::Yes|QMessageBox::No,NULL);
        if (message.exec()==QMessageBox::Yes){
            this->centerfileChoose();
            this->straightedCPR_implementation();
        } else { return ;}
    }else {
        fs->StraightedCPR_mathdisplay();
    }
}
