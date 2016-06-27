#include "CenterLineVisualization.h"

CenterLineVisualization::CenterLineVisualization(QWidget *parent) : QWidget(parent)
{
    this->initVariable();
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::initVariable
//!
void CenterLineVisualization::initVariable(){

    centerLineProcess = new CenterLineProcess();
    points = vtkPoints::New();
    writefilePoints = vtkPoints::New();

    poly = vtkPolyVertex::New();
    grid = vtkUnstructuredGrid::New();

    spline = vtkParametricSpline::New();
    functionSource = vtkParametricFunctionSource::New();
    renderer0 = vtkRenderer::New();
    renderwindow0 =  vtkRenderWindow::New();

    subProjectedPlaneSource = vtkPlaneSource::New();
    subProjectedPlaneMapper = vtkPolyDataMapper::New();
    subProjectedPlaneActor = vtkActor::New();

    acquisitionCenterPoints = new TestMath();

    //!bloodThreeDimensionReconstruction
    reconstructionActor = vtkActor::New();
    reconstructionPoints = vtkPoints::New();
    reconstructionLines = vtkCellArray::New();
    reconstructionPolyData = vtkPolyData::New();
    tubeRadius = vtkDoubleArray::New();
    reconstructionColors = vtkUnsignedCharArray::New();
    reconstructionTube  = vtkTubeFilter::New();
    reconstructionMapper = vtkPolyDataMapper::New();
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::constructIHM
//!
void CenterLineVisualization::constructIHM(){
    QPalette pal =this->palette();
    pal.setColor(QPalette::Background,QColor(100,100,100,50));
    this->setPalette(pal);
    this->setAutoFillBackground(true);

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
//! \brief CenterLineVisualization::mathdisplay
//!
void CenterLineVisualization::mathdisplay(){  
    if(this->mathdisplayofmath()== true)
        this->mathdisplayofQVTKWidget();
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::mathdisplayofmath
//!
bool CenterLineVisualization::mathdisplayofmath(){
    mapper = vtkDataSetMapper::New();
    actor = vtkActor::New();
    axesActor = vtkAxesActor::New();
    tranForm = vtkTransform::New();
    renderer = vtkRenderer::New();
    renderwindow =  vtkRenderWindow::New();
    int poSize = centerLineProcess->get_vesselsPoints().size();
    this->poSize = poSize;
    if(poSize <=0){
        qDebug()<<"No points found";
    }
    poly->GetPointIds()->SetNumberOfIds(poSize);

    for(unsigned int i=0;i<poSize;i++){
        double p[3] = {centerLineProcess->get_vesselsPoints().at(i)->get_abscissa(),
                       centerLineProcess->get_vesselsPoints().at(i)->get_ordinate(),
                       centerLineProcess->get_vesselsPoints().at(i)->get_isometric()};
        points->InsertPoint(i,p[0],p[1],p[2]); // used to show the centerLine
        poly->GetPointIds()->SetId(i,i);

        writefilePoints->InsertNextPoint(p[0],p[1],p[2]);

    }
    grid->SetPoints(points);
    grid->InsertNextCell(poly->GetCellType(),poly->GetPointIds());
    mapper->SetInputData(grid);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.9,0.4,0.6);
    actor->GetProperty()->SetOpacity(0.5);
    actor->GetProperty()->SetPointSize(3);

    axesActor->SetTotalLength(5,5,5);
    tranForm->Translate(0,0,0);
    axesActor->SetUserTransform(tranForm);

    renderer->AddActor(actor);
    renderer->SetBackground(55.0/255,85.0/255,95.0/255);

    return true;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::get_ProjectedpointActor
//! \param originX originY originZ normalX normalY normalZ
//!
vtkActor* CenterLineVisualization::get_ProjectedpointActor(double originX,double originY,double originZ,
                                                           double normalX,double normalY, double normalZ){

    vtkPlane *plane = vtkPlane::New();
    vtkPolyVertex *projectedPoly = vtkPolyVertex::New();
    vtkPoints *projectedPoints = vtkPoints::New();
    vtkUnstructuredGrid *projectedGrid = vtkUnstructuredGrid::New();
    vtkDataSetMapper *projectedMapper = vtkDataSetMapper::New();
    vtkActor *projectedActor = vtkActor::New();


    plane->SetOrigin(0.0,0.0,0.0);
    plane->SetNormal(0.0,1.0,1.0);

    double origin[3] = {originX, originY, originZ };
    double normal[3] = {normalX,normalY,normalZ};
    double projected[3];
    projectedPoly->GetPointIds()->SetNumberOfIds(poSize);

    for(unsigned int i=0;i<poSize;i++){
        double p[3] = {centerLineProcess->get_vesselsPoints().at(i)->get_abscissa(),
                       centerLineProcess->get_vesselsPoints().at(i)->get_ordinate(),
                       centerLineProcess->get_vesselsPoints().at(i)->get_isometric()};
        plane->ProjectPoint(p,origin,normal,projected);
        projectedPoints->InsertPoint(i,projected[0],projected[1],projected[2]);
        projectedPoly->GetPointIds()->SetId(i,i);
    }

    projectedGrid->SetPoints(projectedPoints);
    projectedGrid->InsertNextCell(projectedPoly->GetCellType(),projectedPoly->GetPointIds());
    projectedMapper->SetInputData(projectedGrid);

    projectedActor->SetMapper(projectedMapper);
    projectedActor->GetProperty()->SetColor(0,0,1);
    projectedActor->GetProperty()->SetOpacity(0.5);
    projectedActor->GetProperty()->SetPointSize(1);

    this->copyProjectedPoints = projectedPoints;
    this->copyProjectedActor = projectedActor;
    return projectedActor;
}

vtkActor *CenterLineVisualization::getProjectedCenterlineActor(){
    return this->copyProjectedActor;
}

vtkPoints* CenterLineVisualization::getProjectedPoints(){
    return this->copyProjectedPoints;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::mathdisplayofQVTKWidget
//!
bool CenterLineVisualization::mathdisplayofQVTKWidget(){
    renderwindow->AddRenderer(renderer);
    qVTKWidget->SetRenderWindow(renderwindow);
    qVTKWidget->update();
    return true;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::writePolyFile
//! \param poins
//!
void CenterLineVisualization::writePolyFile(vtkPoints *poins){
    vtkPolyData *polyData = vtkPolyData::New();
    polyData->SetPoints(poins);
    vtkXMLPolyDataWriter *writer = vtkXMLPolyDataWriter::New();
    writer->SetFileName("F:\\points.vtp");
    writer->SetInputData(polyData);
    writer->Write();
    qDebug()<<"write polydata finished!";
    this->update();
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::bloodThreeDimensionReconstruction
//!  function: vessel blood 3D Reconstruction
//!
vtkActor* CenterLineVisualization::bloodThreeDimensionReconstruction(){

    unsigned int nV = centerLineProcess->get_vesselsPoints().size();
    unsigned int nTv = 100;

    int cpt;
    for( cpt = 0; cpt < nV  ; cpt++)
    {
        reconstructionPoints->InsertPoint(cpt, centerLineProcess->get_vesselsPoints().at(cpt)->get_abscissa(),
                                          centerLineProcess->get_vesselsPoints().at(cpt)->get_ordinate(),
                                          centerLineProcess->get_vesselsPoints().at(cpt)->get_isometric());
    }

    reconstructionLines->InsertNextCell(nV);
    for (cpt = 0; cpt < nV ; cpt++)
    {
        reconstructionLines->InsertCellPoint(cpt);
    }
    reconstructionPolyData->SetPoints( reconstructionPoints);
    reconstructionPolyData->SetLines(reconstructionLines);

    tubeRadius->SetName("TubeRadius");
    tubeRadius->SetNumberOfTuples(nV);
    for (cpt=0 ;cpt<nV  ; cpt++){
       tubeRadius->SetTuple1(cpt,centerLineProcess->get_vesselsPoints().at(cpt)->get_radius());
    }
    reconstructionPolyData->GetPointData()->AddArray(tubeRadius);
    reconstructionPolyData->GetPointData()->SetActiveScalars("TubeRadius");

    // RBG array (could add Alpha channel too I guess...)
    // Varying from blue to red
    reconstructionColors->SetName("Colors");
    reconstructionColors->SetNumberOfComponents(3);
    reconstructionColors->SetNumberOfTuples(nV);
    for (cpt = 0; cpt < nV ;cpt++){
        reconstructionColors->InsertTuple3(cpt,int(255 * cpt/ (nV - 1)), int(25 * cpt/ (nV - 1)), int(255* (nV - 1 - cpt)/(nV - 1)) );
    }
    reconstructionPolyData->GetPointData()->AddArray(reconstructionColors);
#if VTK_MAJOR_VERSION <= 5
    reconstructionTube->SetInput(reconstructionPolyData);
#else
    reconstructionTube->SetInputData(reconstructionPolyData);
#endif
    reconstructionTube->SetNumberOfSides(nTv);
    reconstructionTube->SetVaryRadiusToVaryRadiusByAbsoluteScalar();

    reconstructionMapper->SetInputConnection(reconstructionTube->GetOutputPort());
    reconstructionMapper->ScalarVisibilityOn();
    reconstructionMapper->SetScalarModeToUsePointFieldData();

    reconstructionActor->SetMapper(reconstructionMapper);
    reconstructionActor->GetProperty()->SetColor(1,0,0);

    return  this->reconstructionActor;
}



//!------------------------------------------------------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::coremath
//! ****************************************************************************************************************
//!   function: set the values of xdiff,ydiff,zdiff.used in CenterLineVisualization::mathdisplay()
//!   Attention << this method may exited unexcepted when implemented,so I have give up using it.
//!                even so, it can be used to cout the diffs if necessary >>  2016/4/4
//!   it is very important to do math computation and accurately show slices along the centerline path.
//!   @ 2016/3/30    have been abandoned,still useful
//! ****************************************************************************************************************
//!
void CenterLineVisualization::coremath(){
    //    std::cout<<"CenterLineVisualization::coremath()---pointSize:"<<centerLineProcess->get_vesselsPoints().size()<<std::endl;
    centerLineProcess->get_vesselsPoints().at(0)->set_xdiff(1.0);
    centerLineProcess->get_vesselsPoints().at(0)->set_ydiff(1.0);
    centerLineProcess->get_vesselsPoints().at(0)->set_zdiff(1.0);
    centerLineProcess->get_vesselsPoints().at(centerLineProcess->get_vesselsPoints().size())->set_xdiff(1.0);
    centerLineProcess->get_vesselsPoints().at(centerLineProcess->get_vesselsPoints().size())->set_ydiff(1.0);
    centerLineProcess->get_vesselsPoints().at(centerLineProcess->get_vesselsPoints().size())->set_zdiff(1.0);

    for(int i=0;i<centerLineProcess->get_vesselsPoints().size();i++){
        //std::cout<<"CenterLineVisualization::coremath()" <<i<<"*******"<<std::endl;  // to find the error
        centerLineProcess->get_vesselsPoints().at(centerLineProcess->get_vesselsPoints().size())->set_xdiff(1);
        centerLineProcess->get_vesselsPoints().at(centerLineProcess->get_vesselsPoints().size())->set_ydiff(1);
        centerLineProcess->get_vesselsPoints().at(centerLineProcess->get_vesselsPoints().size())->set_zdiff(1);
        // std::cout<<"CenterLineVisualization::coremath()" <<i<<"---"<<std::endl;    // to find the error
        centerLineProcess->get_vesselsPoints().at(i)->set_xdiff(centerLineProcess->get_vesselsPoints().at(i+1)->get_abscissa()
                                                                -centerLineProcess->get_vesselsPoints().at(i)->get_abscissa());
        centerLineProcess->get_vesselsPoints().at(i)->set_ydiff(centerLineProcess->get_vesselsPoints().at(i+1)->get_ordinate()
                                                                -centerLineProcess->get_vesselsPoints().at(i)->get_ordinate());
        centerLineProcess->get_vesselsPoints().at(i)->set_zdiff(centerLineProcess->get_vesselsPoints().at(i+1)->get_isometric()
                                                                -centerLineProcess->get_vesselsPoints().at(i)->get_isometric());
    }
}


//!-----------------------------------------------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::centerlineChoose
//!
void CenterLineVisualization::centerlineChoose(){
    QString filename = QFileDialog::getOpenFileName(this,tr("Load File"),"D:\\school\\dataset\\CoronaryData_CTA\\",tr("txt(*.txt*);;allfile(*.*)"));
    if(filename==NULL){
        return ;
    }else
    {
        this->centerLineProcess->referenceReader(filename);
        this->update();
        this->mathdisplay();
        // this->writePolyFile(this->getWritefilePoints());
    }
    qDebug()<<"CenterLineVisualization::centerlineChoose()-filepath: "<<filename;
    qDebug()<<"CenterLineVisualization::centerlineChoose()-ferencecount: "<<centerLineProcess->getReferencecount();
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::typeconvert
//!
void CenterLineVisualization::typeconvert(int resolution){
    spline->SetPoints(points);
    functionSource->SetParametricFunction(spline);
    functionSource->SetUResolution(resolution);
    functionSource->SetVResolution(resolution);
    functionSource->SetWResolution(resolution);
    functionSource->Update();
}

vtkPolyData* CenterLineVisualization::typeconvert1(){
    vtkPolyData* poll = vtkPolyData::New();
    poll->SetPoints(points);
    return poll;
}


vtkParametricSpline *CenterLineVisualization::get_spline(){
    return this->spline;
}
//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::get_actor
//! \return
//!
vtkActor* CenterLineVisualization::get_actor(){
    return this->actor;
}


//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::get_grid
//! \return
//!
vtkUnstructuredGrid*CenterLineVisualization::get_grid(){
    return this->grid;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::get_centerLineProcess
//! \return
//!
CenterLineProcess* CenterLineVisualization::get_centerLineProcess(){
    return this->centerLineProcess;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::get_functionSource
//! \return
//!
vtkParametricFunctionSource* CenterLineVisualization::get_functionSource(){
    return this->functionSource;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::get_renderer
//! \return
//!
vtkRenderer* CenterLineVisualization::get_renderer(){
    return this->renderer;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::get_renderWindow
//! \return
//!
vtkRenderWindow* CenterLineVisualization::get_renderWindow(){
    return this->renderwindow;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::getPointSource
//! \return
//!
vtkPoints *CenterLineVisualization::getPointSource(){
    return this->points;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::getWritefilePoints
//! \return
//!
vtkPoints *CenterLineVisualization::getWritefilePoints(){
    return this->writefilePoints;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::getAcquisitionActor
//! \return
//!
vtkActor* CenterLineVisualization::getAcquisitionActor(){
    acquisitionCenterPoints->centerlineProcess(centerLineProcess->GetFileName());
    return acquisitionCenterPoints->get_actor();
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::getAcquisitioncenterlineActor
//! \return
//!
vtkActor* CenterLineVisualization::getAcquisitioncenterlineActor(){
    return acquisitionCenterPoints->get_actorcenterline();
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::get_QVTKWidget
//! \return
//!
QVTKWidget *CenterLineVisualization::get_QVTKWidget(){
    return this->qVTKWidget;
}

//!---------------------------------------------------------------------------------
//!
//! \brief CenterLineVisualization::getReconstructionActor
//! \return
//!
vtkActor* CenterLineVisualization::getReconstructionActor(){
    return this->bloodThreeDimensionReconstruction();
}

