#include "CenterLineDisplayMath.h"

//!------------------------------------------------------------------------------
//! \brief CenterLineDisplayMath::CenterLineDisplayMath
//!  this class is used to display a cloud point in reference file
//!
//!  ! test successfully !
//!  date: 2016-05-11    add: ShenZhen
//!------------------------------------------------------------------------------

CenterLineDisplayMath::CenterLineDisplayMath()
{
    centerLinePr = new CenterLineProcess;

    points = vtkPoints::New();
    poly = vtkPolyVertex::New();
    grid = vtkUnstructuredGrid::New();
    xSpline = vtkSCurveSpline::New();
    ySpline = vtkSCurveSpline::New();
    zSpline = vtkSCurveSpline::New();
    spline = vtkParametricSpline::New();
    functionSource = vtkParametricFunctionSource::New();

    //!  3-D Reconstruction
    reconstructionActor = vtkActor::New();
    reconstructionPoints = vtkPoints::New();
    reconstructionLines = vtkCellArray::New();
    reconstructionPolyData = vtkPolyData::New();
    tubeRadius = vtkDoubleArray::New();
    reconstructionColors = vtkUnsignedCharArray::New();
    reconstructionTube  = vtkTubeFilter::New();
    reconstructionMapper = vtkPolyDataMapper::New();
}

//!------------------------------------------------------------------------------
//!
//! \brief CenterLineDisplayMath::displayCenterLineData
//! \param render   \param filepath    \param pointColor
//!  pointColor can be  "r", "g", "b" or others
//!
void CenterLineDisplayMath::displayCenterLineData(vtkRenderer *render,
                                                  QString filepath,
                                                  QString pointColor){

    mapper = vtkDataSetMapper::New();
    actor = vtkActor::New();
    this->centerLinePr->referenceReader(filepath.toLocal8Bit());//! file path

    int totalPoints = centerLinePr->get_vesselsPoints().length();
    if(totalPoints <= 0){
        qDebug()<<"no points found!";
    }
    poly->GetPointIds()->SetNumberOfIds(totalPoints);
    for(int cpt=0; cpt < totalPoints; cpt++){
        double p[3] = {centerLinePr->get_vesselsPoints().at(cpt)->get_abscissa(),
                       centerLinePr->get_vesselsPoints().at(cpt)->get_ordinate(),
                       centerLinePr->get_vesselsPoints().at(cpt)->get_isometric()};
        points->InsertPoint(cpt,p[0],p[1],p[2]);
        poly->GetPointIds()->SetId(cpt,cpt);
    }
    grid->SetPoints(points);
    grid->InsertNextCell(poly->GetCellType(),poly->GetPointIds());
    mapper->SetInputData(grid);
    this->actor->SetMapper(mapper);
    this->actor->GetProperty()->SetOpacity(0.5);
    this->actor->GetProperty()->SetPointSize(1);
    this->colorChoice(this->actor,pointColor);

    render->AddActor(actor);
}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLineDisplayMath::displayVesselThreeDimReconstruction
//! \param render \param filepath \param pointColor
//!
void CenterLineDisplayMath::displayVesselThreeDimReconstruction(vtkRenderer *render,
                                         QString filepath,
                                         QString pointColor){

    //this->centerLinePr->referenceReader(filepath.toLocal8Bit());//! file path

    // Spiral tube
    unsigned int nV = centerLinePr->get_vesselsPoints().size();      // No. of vertices
    unsigned int nTv = 100;       // No. of surface elements for each tube vertex

    int cpt;
    for( cpt = 0; cpt < nV  ; cpt++)
    {
        // Spiral coordinate
        reconstructionPoints->InsertPoint(cpt, centerLinePr->get_vesselsPoints().at(cpt)->get_abscissa(),
                                          centerLinePr->get_vesselsPoints().at(cpt)->get_ordinate(),
                                          centerLinePr->get_vesselsPoints().at(cpt)->get_isometric());
    }

    reconstructionLines->InsertNextCell(nV);
    for (cpt = 0; cpt < nV ; cpt++)
    {
        reconstructionLines->InsertCellPoint(cpt);
    }

    reconstructionPolyData->SetPoints( reconstructionPoints);
    reconstructionPolyData->SetLines(reconstructionLines);

    // Varying  radius
    tubeRadius->SetName("TubeRadius");
    tubeRadius->SetNumberOfTuples(nV);
    for (cpt=0 ;cpt<nV  ; cpt++){
        if(centerLinePr->get_vesselsPoints().at(cpt)->get_radius() == NULL){
            tubeRadius->SetTuple1(cpt, 0.5);
        }else{
            tubeRadius->SetTuple1(cpt,centerLinePr->get_vesselsPoints().at(cpt)->get_radius());
        }
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
    //reconstructionPolyData->GetPointData()->AddArray(reconstructionColors);


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
    reconstructionMapper->SelectColorArray("Colors");
    reconstructionActor->SetMapper(reconstructionMapper);
    this->colorChoice(reconstructionActor,pointColor);

    render->AddActor(reconstructionActor);
}

//!------------------------------------------------------------------------------
//!
//! \brief CenterLineDisplayMath::colorChoice
//! \param actor \param str
//!
void CenterLineDisplayMath::colorChoice(vtkActor *actor, QString str){
    if(str.contains("r")){
        actor->GetProperty()->SetColor(255,0,0);
    }else if(str.contains("g")){
        actor->GetProperty()->SetColor(0,255,0);
    }else if(str.contains("b")){
        actor->GetProperty()->SetColor(0,0,255);
    }else {
        actor->GetProperty()->SetColor(0.9,0.4,0.6);
    }
}


void CenterLineDisplayMath::typeConvert(){
    spline->SetXSpline(xSpline);    spline->SetYSpline(ySpline);   spline->SetZSpline(zSpline);
    spline->SetPoints(points);
    functionSource->SetParametricFunction(spline);
    functionSource->Update();
}

 CenterLineProcess *CenterLineDisplayMath::getCenterLinePr(){
     return this->centerLinePr;
 }

 vtkPoints *CenterLineDisplayMath::getAllpoints(){
     return this->points;
 }

 vtkPolyData* CenterLineDisplayMath::ribbonFilter(){
    vtkCellArray* lines = vtkCellArray::New();
    lines->InsertNextCell(centerLinePr->getReferencecount());
    for(int cpt=0;cpt<centerLinePr->getReferencecount();cpt++){
        lines->InsertCellPoint(cpt);
    }
    vtkPolyData* polyData = vtkPolyData::New();
    polyData->SetPoints(points);
    polyData->SetLines(lines);

    vtkRibbonFilter* ribbonFilter = vtkRibbonFilter::New();
    ribbonFilter->SetInputData(polyData);
    ribbonFilter->SetWidth(4);
    ribbonFilter->GetOutput();
    ribbonFilter->Update();

    return ribbonFilter->GetOutput();
 }
