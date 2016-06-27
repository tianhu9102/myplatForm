#include "FourViewWidget.h"

FourViewWidget::FourViewWidget(QWidget *parent) : QWidget(parent)
{
    this->initVariable();
    this->constructIHM();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::initVariable
//!
void FourViewWidget::initVariable(){
    vvz = new VolumeVisualization();vvz->constructIHM();
    clz = new CenterLineVisualization();clz->constructIHM();
    shz = new StraightedVisualization();

    reslicer = vtkSplineDrivenImageSlicer::New();
    append = vtkImageAppend::New();
    m_pShift = vtkImageShiftScale::New();
    extractVOI = vtkExtractVOI::New();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::constructIHM
//!
void FourViewWidget::constructIHM(){
    qGridLayout = new QGridLayout(this);
    qGridLayout->addWidget(vvz,0,0);
    qGridLayout->addWidget(clz,0,1);
    qGridLayout->addWidget(shz,1,0);
    qGridLayout->setMargin(0);
    qGridLayout->setSpacing(0);

    QPalette palette;
    palette.setColor(QPalette::Background,QColor(192,253,123));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::function
//!
void FourViewWidget::function(){
    if(!vvz->getmhdfilename().isEmpty()){
       vvz->get_renderer()->AddActor(clz->get_actor());
//       vvz->get_renderer()->AddActor(clz->getAcquisitionActor());
//       vvz->get_renderer()->AddActor(clz->getAcquisitioncenterlineActor());
       //vvz->get_renderer()->AddActor(clz->get_ribbonActor());
    }else if(!clz->get_centerLineProcess()->GetFileName().isEmpty()){
        clz->get_renderer()->AddVolume(vvz->getVolume());

    }else if(!vvz->getmhdfilename().isEmpty()&&!clz->get_centerLineProcess()->GetFileName().isEmpty()){

    }else
        return ;
}

void FourViewWidget::ProjectedCPR_mathdisplay(){
    // TODO............
}


//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getStraightedVisualization
//! \return
//!
vtkImageAppend* FourViewWidget::getStraightedVisualization(){
    if(vvz->getmhdfilename().isEmpty()&&
       clz->get_centerLineProcess()->get_vesselsPoints().size()<=0){
        qDebug()<<"please choose mhdfile and a centerline!";
        return EXIT_SUCCESS;
    }else if(vvz->getmhdfilename().isEmpty()||
             clz->get_centerLineProcess()->get_vesselsPoints().size()<=0){
       qDebug()<<"lose mhdfile or a centerline!";
    }else{

        //clz->get_functionSource()->SetNthInputConnection();
        clz->typeconvert(400);
        reslicer->SetInputConnection(vvz->get_volumeReader()->GetOutputPort());
        reslicer->SetPathConnection(clz->get_functionSource()->GetOutputPort());

        reslicer->SetSliceThickness(0.6 );

        reslicer->SetSliceSpacing( 0.3,0.3 );
        reslicer->SetSliceExtent(250,250 );
        reslicer->SetOffsetPoint( 30 );

        clz->getPointSource()->GetNumberOfPoints();
        int nbPoints = clz->get_functionSource()->GetOutput()->GetNumberOfPoints();
        qDebug()<<"nbPoints:::"<<nbPoints;
        for(int ptId = 0; ptId < nbPoints; ptId++){
            reslicer->SetOffsetPoint(ptId);
            reslicer->Update();

            vtkImageData *tempSlice= vtkImageData::New();
            tempSlice->DeepCopy( reslicer->GetOutput(0));
            append->AddInputData(tempSlice);
        }
        append->SetAppendAxis(2);
        append->Update( );
        shz->reconstructedmathdisplay(append->GetOutputPort());
    }
    return append;
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getStraightedVisualization1
//!
void FourViewWidget::getStraightedVisualization1(){

}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::StraightedCPR_mathdisplay
//!
void FourViewWidget::StraightedCPR_mathdisplay(){

    double range[2];
    vvz->get_volumeReader()->GetOutput()->GetScalarRange(range);
    m_pShift->SetShift(-1.0*range[0]);
    m_pShift->SetScale(255.0/(range[1]-range[0]));
    m_pShift->SetOutputScalarTypeToUnsignedChar();
    m_pShift->SetInputConnection(this->getStraightedVisualization()->GetOutputPort());
    m_pShift->ReleaseDataFlagOff();
    m_pShift->Update();

    for(int i=0;i<8;i++){
        pCut[i] = vtkCutter::New();
        pPlane[i] = vtkPlane::New();
   }

    pPlane[0]->SetOrigin(this->append->GetOutput()->GetCenter()); pPlane[1]->SetOrigin(this->append->GetOutput()->GetCenter());
    pPlane[2]->SetOrigin(this->append->GetOutput()->GetCenter()); pPlane[3]->SetOrigin(this->append->GetOutput()->GetCenter());
    pPlane[4]->SetOrigin(this->append->GetOutput()->GetCenter()); pPlane[5]->SetOrigin(this->append->GetOutput()->GetCenter());
    pPlane[6]->SetOrigin(this->append->GetOutput()->GetCenter()); pPlane[7]->SetOrigin(this->append->GetOutput()->GetCenter());

    double came0[]={0, 400}; double came1[]={-20, 346.41};
    double came2[]={-346.41, 20};double came3[]={-400, 0};
    double came4[]={-346.41, -20}; double came5[]={-20, -346.41};
    double came6[]={0, -400};double came7[]={-346.41,20 };
    pPlane[0]->SetNormal(came0[0],came0[1],0);pPlane[1]->SetNormal(came1[0],came1[1],0);
    pPlane[2]->SetNormal(came2[0],came2[1],0);pPlane[3]->SetNormal(came3[0],came3[1],0);
    pPlane[4]->SetNormal(came4[0],came4[1],0);pPlane[5]->SetNormal(-came5[0],came5[1],0);
    pPlane[6]->SetNormal(came6[0],came6[1],0);pPlane[7]->SetNormal(came7[0],came7[1],0);
    pCut[0]->SetCutFunction(pPlane[0]);pCut[1]->SetCutFunction(pPlane[1]);
    pCut[2]->SetCutFunction(pPlane[2]);pCut[3]->SetCutFunction(pPlane[3]);
    pCut[4]->SetCutFunction(pPlane[4]);pCut[5]->SetCutFunction(pPlane[5]);
    pCut[6]->SetCutFunction(pPlane[6]);pCut[7]->SetCutFunction(pPlane[7]);
    pCut[0]->SetInputConnection(m_pShift->GetOutputPort());pCut[1]->SetInputConnection(m_pShift->GetOutputPort());
    pCut[2]->SetInputConnection(m_pShift->GetOutputPort());pCut[3]->SetInputConnection(m_pShift->GetOutputPort());
    pCut[4]->SetInputConnection(m_pShift->GetOutputPort());pCut[5]->SetInputConnection(m_pShift->GetOutputPort());
    pCut[6]->SetInputConnection(m_pShift->GetOutputPort());pCut[7]->SetInputConnection(m_pShift->GetOutputPort());
    pCut[0]->Update();pCut[1]->Update();pCut[2]->Update();pCut[3]->Update();
    pCut[4]->Update();pCut[5]->Update();pCut[6]->Update();pCut[7]->Update();

    double *center = append->GetOutput()->GetCenter();
    shz->selectedmathdisplay(0,pCut[0]->GetOutputPort(),came0,center);shz->getActivecamera()->Azimuth(30);
    shz->selectedmathdisplay(30,pCut[1]->GetOutputPort(),came1,center);shz->getActivecamera()->Azimuth(30);
    shz->selectedmathdisplay(60,pCut[2]->GetOutputPort(),came2,center);shz->getActivecamera()->Azimuth(30);
    shz->selectedmathdisplay(90,pCut[3]->GetOutputPort(),came3,center);shz->getActivecamera()->Azimuth(30);
    shz->selectedmathdisplay(120,pCut[4]->GetOutputPort(),came4,center);shz->getActivecamera()->Azimuth(30);
    shz->selectedmathdisplay(150,pCut[5]->GetOutputPort(),came5,center);shz->getActivecamera()->Azimuth(30);
    shz->selectedmathdisplay(180,pCut[6]->GetOutputPort(),came6,center);shz->getActivecamera()->Azimuth(30);
    shz->selectedmathdisplay(210,pCut[7]->GetOutputPort(),came7,center);shz->getActivecamera()->Azimuth(30);
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getYSpacing
//! \return
//!
double FourViewWidget::getYSpacing(){
    return this->getVolumeVisualization_Object()->getySpacing();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getZSpacing
//! \return
//!
double FourViewWidget::getZSpacing(){
    return this->getVolumeVisualization_Object()->getzSpacing();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getCenterlinefile
//! \return
//!
QString FourViewWidget::getCenterlinefile(){
    return this->getCenterLineVisualization_Object()->get_centerLineProcess()->GetFileName();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getCenterlinepointsize
//! \return
//!
int FourViewWidget::getCenterlinepointsize(){
    return this->getCenterLineVisualization_Object()->get_centerLineProcess()->getReferencecount();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getVolumeVisualization
//! \return
//!
void FourViewWidget::getVolumeVisualization(){
    return this->vvz->mhdfileChoose();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getCenterLineVisualization
//!
void FourViewWidget::getCenterLineVisualization(){
    return this->clz->centerlineChoose();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getVolumeVisualization_Object
//! \return
//!
VolumeVisualization *FourViewWidget::getVolumeVisualization_Object(){
    return this->vvz;
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getCenterLineVisualization_Object
//! \return
//!
CenterLineVisualization *FourViewWidget::getCenterLineVisualization_Object(){
    return this->clz;
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getStraightedVisualization_Object
//! \return
//!
StraightedVisualization* FourViewWidget::getStraightedVisualization_Object(){
    return this->shz;
}


//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getVolumeOriginCenter
//! \return
//!
 double* FourViewWidget::getVolumeOriginCenter(){
    return this->append->GetOutput()->GetCenter();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getextractVOI
//! \return
//!
vtkExtractVOI* FourViewWidget::getextractVOI(){
    return this->extractVOI;
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::get_MpShift
//! \return
//!
vtkImageShiftScale* FourViewWidget::get_MpShift(){
    return this->m_pShift;
}


void FourViewWidget::StretchedCPR_mathdisplay(){
    // TODO............
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getMhdfile
//! \return
//!
QString FourViewWidget::getMhdfile(){
    return this->getVolumeVisualization_Object()->getmhdfilename();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getXDimisions
//! \return
//!
int FourViewWidget::getXDimisions(){
    return this->getVolumeVisualization_Object()->getxDimsion();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getYDimisions
//! \return
//!
int FourViewWidget::getYDimisions(){
    return this->getVolumeVisualization_Object()->getyDimsion();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getZDimisions
//! \return
//!
int FourViewWidget::getZDimisions(){
    return this->getVolumeVisualization_Object()->getzDimsion();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getXOrigin
//! \return
//!
double FourViewWidget::getXOrigin(){
    return this->getVolumeVisualization_Object()->getxOrigin();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getYOrigin
//! \return
//!
double FourViewWidget::getYOrigin(){
    return this->getVolumeVisualization_Object()->getyOrigin();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getZOrigin
//! \return
//!
double FourViewWidget::getZOrigin(){
    return this->getVolumeVisualization_Object()->getzOrigin();
}

//!---------------------------------------------------------------------------------
//!
//! \brief FourViewWidget::getXSpacing
//! \return
//!
double FourViewWidget::getXSpacing(){
    return this->getVolumeVisualization_Object()->getxSpacing();
}
