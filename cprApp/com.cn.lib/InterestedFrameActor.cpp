#include "InterestedFrameActor.h"

//!---------------------------------------------------------------------------
//!
//! \brief InterestedFrameActor::InterestedFrameActor
//!  this class is used to diaplay a 3D frame
//!
//!  ! test successfully !
//!  date: 2016-05-10    add: ShenZhen
//!---------------------------------------------------------------------------

InterestedFrameActor::InterestedFrameActor()
{
    cross = new CrossMath;
    mapper = vtkPolyDataMapper::New();
    actor = vtkActor::New();
}

//!-------------------------------------------------------------------------------------------------------
//!
//! \brief InterestedFrameActor::getInterestedActor
//! \param origin_x  \param origin_y  \param origin_z
//! \param vector1_x \param vector1_y \param vector1_z
//! \param vector2_x \param vector2_y \param vector2_z
//! \return
//!
void InterestedFrameActor::displayInterestedFrame(vtkRenderer *renderer,
                                                  double origin_x, double origin_y, double origin_z,
                                                  double vector1_x, double vector1_y, double vector1_z,
                                                  double vector2_x, double vector2_y, double vector2_z){

    this->cross->frenetSerretFrame(vector1_x,vector1_y,vector1_z,vector2_x,vector2_y,vector2_z);

    vtkPolyData *linePolyData = vtkPolyData::New();
    double origin[3] = {origin_x,origin_y,origin_z};     //! param origin_x,origin_y，origin_z
    double amplifer = 30;
    double pt[3] = {origin_x+cross->get_tangent_i()*amplifer,
                    origin_y+cross->get_tangent_j()*amplifer,
                    origin_z+cross->get_tangent_k()*amplifer};
    double pn[3] = {origin_x+cross->get_normal_i()*amplifer,
                    origin_y+cross->get_normal_j()*amplifer,
                    origin_z+cross->get_normal_k()*amplifer};
    double pb[3] = {origin_x+cross->get_binormal_i()*amplifer,
                    origin_y+cross->get_binormal_j()*amplifer,
                    origin_z+cross->get_binormal_k()*amplifer};
    std::cout<<"InterestedFrameActor::getInterestedActor()  pt: "<<pt[0]-origin_x<<" "<<pt[1]-origin_y<<" "<<pt[2]-origin_z<<std::endl;
    std::cout<<"                                            pn: "<<pn[0]-origin_x<<" "<<pn[1]-origin_y<<" "<<pn[2]-origin_z<<std::endl;
    std::cout<<"                                            pb: "<<pb[0]-origin_x<<" "<<pb[1]-origin_y<<" "<<pb[2]-origin_z<<std::endl;

    vtkPoints *pts = vtkPoints::New();
    pts->InsertNextPoint(origin);
    pts->InsertNextPoint(pt);
    pts->InsertNextPoint(pn);
    pts->InsertNextPoint(pb);
    linePolyData->SetPoints(pts);

    vtkLine *line1 =vtkLine::New();
    line1->GetPointIds()->SetId(0,0);
    line1->GetPointIds()->SetId(1,1);
    vtkLine *line2 =vtkLine::New();
    line2->GetPointIds()->SetId(0,0);
    line2->GetPointIds()->SetId(1,2);
    vtkLine *line3 =vtkLine::New();
    line3->GetPointIds()->SetId(0,0);
    line3->GetPointIds()->SetId(1,3);

    vtkCellArray *cellArray = vtkCellArray::New();
    cellArray->InsertNextCell(line1);
    cellArray->InsertNextCell(line2);
    cellArray->InsertNextCell(line3);

    linePolyData->SetLines(cellArray);

    unsigned char red[3] = { 255, 0, 0 };   //!line color
    unsigned char green[3] = { 0, 255, 0 }; //!line color
    unsigned char blue[3] = { 0, 0 ,255};   //!line color
    vtkUnsignedCharArray *colors = vtkUnsignedCharArray::New();
    colors->SetNumberOfComponents(3);

#if VTK_MAJOR_VERSION <7
    colors->InsertNextTupleValue(red);
    colors->InsertNextTupleValue(green);
    colors->InsertNextTupleValue(blue);
#else
    colors->InsertNextTypedTuple(red);
    colors->InsertNextTypedTuple(green);
    colors->InsertNextTypedTuple(blue);
#endif
    linePolyData->GetCellData()->SetScalars(colors);
    mapper->SetInputData(linePolyData);
    actor->SetMapper(mapper);

    renderer->AddActor(actor);
}
