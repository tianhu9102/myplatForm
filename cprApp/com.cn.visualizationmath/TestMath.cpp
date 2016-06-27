#include "TestMath.h"

TestMath::TestMath()
{
    this->initialize();
    // this->centerlineProcess();
    // this->test();
}

//!---------------------------------------------------------------------------
//!
//! \brief TestMath::centerlineProcess
//! \param str
//!
void TestMath::centerlineProcess(QString str){
    //! process vessel file
    vesselReader->referenceReader(str.toLocal8Bit());

    //! fecth point sequence
    QVector<CenterLinePoint*> points = vesselReader->get_vesselsPoints();

    //qDebug()<<"compute vector for each point";
    for(int cpt_1 = 0; cpt_1 < points.length() - 1; cpt_1++){
        points.at(cpt_1)->set_xdiff(points.at(cpt_1 + 1)->get_abscissa() - points.at(cpt_1)->get_abscissa());
        points.at(cpt_1)->set_ydiff(points.at(cpt_1 + 1)->get_ordinate() - points.at(cpt_1)->get_ordinate());
        points.at(cpt_1)->set_zdiff(points.at(cpt_1 + 1)->get_isometric() - points.at(cpt_1)->get_isometric());
        points.at(cpt_1)->update();
    }

    //! compute the target acquisition vector
    for(int cpt_2 = 1; cpt_2 < points.length() - 1; cpt_2++){
        points.at(cpt_2)->set_cos_sigma((-points.at(cpt_2-1)->get_xdiff())*points.at(cpt_2)->get_xdiff() +
                                        (-points.at(cpt_2-1)->get_ydiff())*points.at(cpt_2)->get_ydiff() +
                                        (-points.at(cpt_2-1)->get_zdiff())*points.at(cpt_2)->get_zdiff());

        //! compute uvw
        double a1 = -points.at(cpt_2-1)->get_xdiff();
        double a2 = -points.at(cpt_2-1)->get_ydiff();
        double a3 = -points.at(cpt_2-1)->get_zdiff();
        double b1 = points.at(cpt_2)->get_xdiff();
        double b2 = points.at(cpt_2)->get_ydiff();
        double b3 = points.at(cpt_2)->get_zdiff();
        double c1 = points.at(cpt_2 + 1)->get_xdiff();
        double c2 = points.at(cpt_2 + 1)->get_ydiff();
        double c3 = points.at(cpt_2 + 1)->get_zdiff();

        double im = a2*(a3 - b3) + a3 * (b2 - a2);
        double in = a2*(a1 - b1) + a2 * (b2 - a2);
        double ik = (a2 - b2) *(a2 - b2)  + (a3 - b3) *(a3 - b3);
        double il = 2*(a1 - b1)*(a3 - b3);
        double ip = (a1 - b1)*(a1 - b1)+ (b2 - a2)*(b2 - a2);

        double xa = im *im / points.at(cpt_2)->get_cos_theta()*points.at(cpt_2)->get_cos_theta() - ik;
        double xb = 2*im *in/ points.at(cpt_2)->get_cos_theta()*points.at(cpt_2)->get_cos_theta() - il;
        double xc = in *in / points.at(cpt_2)->get_cos_theta()*points.at(cpt_2)->get_cos_theta() - ip;

        double w = (-xb + sqrt(xb*xb - 4*xa*xc)) / 2*xa;
        double v = ((a3 - b3) *w +(a1 - b1)) /(b2 - a2);

        double binormal_1 = a2 *b3 - a3 * b2;
        double binormal_2 = a3 *b1 - a1 * b3;
        double binormal_3 = a1 *b2 - a2 * b1;

        double normal_1 = (-a2+b2)/2 * binormal_3 - (-a3+b3)/2 * binormal_2 ;
        double normal_2 = (-a3+b3)/2 * binormal_1 - (-a1+b1)/2  * binormal_3;
        double normal_3 = (-a1+b1)/2  * binormal_2 - (-a2+b2)/2 * binormal_1;

        points.at(cpt_2)->set_acquisition_vector_u(1);
        points.at(cpt_2)->set_acquisition_vector_w(0);
        points.at(cpt_2)->set_acquisition_vector_v(0);

        points.at(cpt_2)->normalize_uvw();  //normalize
   }

    //! constuct acquisition area
    for(int cpt_3 = 1; cpt_3 < points.length() - 1; cpt_3++){
        for(int w = 0 ; w < points.at(cpt_3)->get_acquisition_frequence()/2; w++ ){
            AcquisitionPoint *p1 = new AcquisitionPoint();
            p1->setAbscissa(points.at(cpt_3)->get_abscissa()+ points.at(cpt_3)->get_acquisition_vector_u()*(w*points.at(cpt_3)->get_acquisition_radius()/ points.at(cpt_3)->get_acquisition_frequence()));
            p1->setOrdinate(points.at(cpt_3)->get_ordinate()+ points.at(cpt_3)->get_acquisition_vector_v()*(w*points.at(cpt_3)->get_acquisition_radius()/ points.at(cpt_3)->get_acquisition_frequence()));
            p1->setIsometric(points.at(cpt_3)->get_isometric()+ points.at(cpt_3)->get_acquisition_vector_w()*(w*points.at(cpt_3)->get_acquisition_radius()/ points.at(cpt_3)->get_acquisition_frequence()));
            points.at(cpt_3)->appendAcquisitionPoints(p1);

            if(w == 0){
                continue;
            }
            AcquisitionPoint *p2 = new AcquisitionPoint();
            p2->setAbscissa(points.at(cpt_3)->get_abscissa()- points.at(cpt_3)->get_acquisition_vector_u()*(w*points.at(cpt_3)->get_acquisition_radius()/ points.at(cpt_3)->get_acquisition_frequence()));
            p2->setOrdinate(points.at(cpt_3)->get_ordinate()- points.at(cpt_3)->get_acquisition_vector_v()*(w*points.at(cpt_3)->get_acquisition_radius()/ points.at(cpt_3)->get_acquisition_frequence()));
            p2->setIsometric(points.at(cpt_3)->get_isometric()- points.at(cpt_3)->get_acquisition_vector_w()*(w*points.at(cpt_3)->get_acquisition_radius()/ points.at(cpt_3)->get_acquisition_frequence()));
            points.at(cpt_3)->appendAcquisitionPoints(p2);
        }
    }

    std::cout<<"insert acquisitionPoints to pointset"<<std::endl;
    poly->GetPointIds()->SetNumberOfIds(points.at(0)->get_acquisition_frequence()*(points.length() - 1));
    int count = 0;
    for(int cpt_5 = 1; cpt_5 < points.length() - 1; cpt_5++){
//        std::cout<<"      "<<std::endl;
//        std::cout<<"--------------------- "<<cpt_5<<"--------------------- "<<std::endl;

        for(int cpt_6 = 0; cpt_6 < points.at(cpt_5)->get_acquisition_frequence()-1; cpt_6++){  
//            std::cout<<"      "<<cpt_6<<":  "<<
//                      points.at(cpt_5)->getAcquisitionPointAt(cpt_6)->getAbscissa()<<" "<<
//                      points.at(cpt_5)->getAcquisitionPointAt(cpt_6)->getOrdinate()<<" "<<
//                      points.at(cpt_5)->getAcquisitionPointAt(cpt_6)->getIsometric()<<std::endl;

            pointset->InsertPoint(count, points.at(cpt_5)->getAcquisitionPointAt(cpt_6)->getAbscissa(),
                                         points.at(cpt_5)->getAcquisitionPointAt(cpt_6)->getOrdinate(),
                                         points.at(cpt_5)->getAcquisitionPointAt(cpt_6)->getIsometric());
            poly->GetPointIds()->SetId(count,count);
            count++;
        }
    }
    std::cout<<"finish insert acquisitionPoints to pointset"<<std::endl;
    grid->SetPoints(pointset);
    grid->InsertNextCell(poly->GetCellType(),poly->GetPointIds());
    mapper->SetInputData(grid);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.6,0.5,0.4);  //.9,.4,.5
    actor->GetProperty()->SetOpacity(1);
    actor->GetProperty()->SetPointSize(1);


    //! centerline points in green color
    polycenterline->GetPointIds()->SetNumberOfIds(points.size());
    for(int cpt_7 = 0 ;cpt_7 <points.size();cpt_7++){
        pointsetcenterline->InsertPoint(cpt_7, points.at(cpt_7)->get_abscissa(),
                                               points.at(cpt_7)->get_ordinate(),
                                               points.at(cpt_7)->get_isometric());
        polycenterline->GetPointIds()->SetId(cpt_7,cpt_7);
    }
    gridcenterline->SetPoints(pointsetcenterline);
    gridcenterline->InsertNextCell(polycenterline->GetCellType(),polycenterline->GetPointIds());
    mappercenterline->SetInputData(gridcenterline);
    actorcenterline->SetMapper(mappercenterline);
    actorcenterline->GetProperty()->SetColor(0,255,0);  //.9,.4,.5
    actorcenterline->GetProperty()->SetOpacity(1);
    actorcenterline->GetProperty()->SetPointSize(3);


    //!-----------------------------------------------------------------------
    //!-----------------------------------------------------------------------

/*
    vtkMetaImageReader *reader = vtkMetaImageReader::New();
    reader->SetFileName("E:\\dataset00\\image00.mhd");
    reader->SetDataScalarTypeToUnsignedChar();
    reader->Update();
    volumeData = reader->GetOutput();

    //! genrate result
    int newDim[3];
    newDim[0] = vesselReader->getReferencecount() - 2;
    newDim[1] = vesselReader->get_vesselsPoints().at(4)->get_acquisition_frequence();
    newDim[2] = 1;

    vtkImageData *img= vtkImageData::New();
    img->SetDimensions(newDim[0],newDim[1],newDim[2]);
    img->SetSpacing(0.5,0.5,0);
    img->AllocateScalars(VTK_UNSIGNED_CHAR,1);

    for(int cpt_9 = 1; cpt_9 < points.length() - 1; cpt_9++){
        for(int w = 0 ; w < points.at(cpt_9)->get_acquisition_frequence() - 1; w++ ){
            unsigned char *pixel = (unsigned char *)volumeData->GetScalarPointer(double(points.at(cpt_9)->getAcquisitionPointAt(w)->getAbscissa()),
                                                                                 double(points.at(cpt_9)->getAcquisitionPointAt(w)->getOrdinate()),
                                                                                 double(points.at(cpt_9)->getAcquisitionPointAt(w)->getIsometric()));

            unsigned char *g = (unsigned char *)(img->GetScalarPointer(cpt_9-1,w,0));
            *g = *pixel;
        }
    }
        vtkImageViewer2 *view = vtkImageViewer2::New();
        view->SetInputData(img);
        view->Render();
        view->GetRenderWindow()->SetSize(800,600);
        vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
        view->SetupInteractor(interactor);
        view->SetColorWindow(2000);
        view->SetColorLevel(100);
        interactor->Start();*/


//    vtkImageActor * actor = vtkImageActor::New();
//    vtkRenderer *render = vtkRenderer::New();
//    vtkRenderWindow *renderWindow = vtkRenderWindow::New();
//    vtkRenderWindowInteractor  *inter = vtkRenderWindowInteractor::New();
//    vtkInteractorStyleImage *ds = vtkInteractorStyleImage::New();

//    actor->SetInputData(img);
//    render->AddActor(actor);
//    renderWindow->AddRenderer(render);

//    inter->SetInteractorStyle(ds);
//    inter->SetRenderWindow(renderWindow);
//    inter->Initialize();
//    inter->Start();


    //!-----------------------------------------------------------------------
    //!-----------------------------------------------------------------------

}



//!---------------------------------------------------------------------------
//!
//! \brief TestMath::test
//!
void TestMath::test(){
   // this->centerlineProcess("E:\\dataset00\\vessel0\\reference.txt");
    this->centerlineProcess("E:\\dataset00\\q.txt");

    renderer->AddActor(actor);
    renderer->AddActor(actorcenterline);
    renderwindow->AddRenderer(renderer);
    renderwindow->SetInteractor(interactor);
    renderwindow->Start();


}

//!---------------------------------------------------------------------------
//!
//! \brief TestMath::createNewImg
//!
void TestMath::createNewImg(QString sourcemhdfile){
    vtkMetaImageReader *reader = vtkMetaImageReader::New();
    reader->SetFileName(sourcemhdfile.toLocal8Bit());
    reader->SetDataScalarTypeToUnsignedChar();
    reader->Update();
    volumeData = reader->GetOutput();

    /*
    int dims[3];
    reader->GetOutput()->GetDimensions(dims);
    for(int k = 0;k<dims[2];k++){
        for(int j = 0;j<dims[1];j++){
            for(int i = 0;i<dims[0];i++){
                unsigned char *pixel = (unsigned char *)(reader->GetOutput()->GetScalarPointer(i,j,k));
            }
        }
    }

    for(int cpt_3 = 1; cpt_3 < points.length() - 1; cpt_3++){
        for(int w = 0 ; w < points.at(cpt_3)->get_acquisition_frequence()/2; w++ ){

            points.at(cpt_3)->
        }
    }*/
    int newDim[3];
    newDim[0] = vesselReader->getReferencecount();
    newDim[1] = vesselReader->get_vesselsPoints().at(4)->get_acquisition_frequence();
    newDim[2] = 1;

    vtkImageData *img= vtkImageData::New();
    img->SetDimensions(newDim[0],newDim[1],newDim[2]);
    img->SetSpacing(0.5,1.5,0.5);
    img->AllocateScalars(VTK_UNSIGNED_CHAR,1);
    for(int p = 0;p<newDim[2];p++){
        for(int n = 0;n<newDim[1];n++){
            for(int m = 0;m<newDim[0];m++){
                unsigned char *pixel = (unsigned char *)(img->GetScalarPointer(m,n,p));
                *pixel = m*m*m;
                *(pixel+1) = m*m;
                *(pixel+2)  = m;
            }
        }
    }
    std::cout<<img->GetCenter()[0]<<" "<<img->GetCenter()[1]<<" "<<img->GetCenter()[2]<<std::endl;
    std::cout<<img->GetOrigin()[0]<<" "<<img->GetOrigin()[1]<<" "<<img->GetOrigin()[2]<<std::endl;

//    vtkImageViewer2 *view = vtkImageViewer2::New();
//    view->SetInputData(img);
//    view->Render();
//    view->GetRenderWindow()->SetSize(800,600);
//    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
//    view->SetupInteractor(interactor);
//    view->SetColorWindow(2000);
//    view->SetColorLevel(500);
//    interactor->Start();


}


//!---------------------------------------------------------------------------
//!
//! \brief TestMath::initialize
//!
void TestMath::initialize(){
    vesselReader = new CenterLineProcess();
    pointset = vtkPoints::New();
    poly = vtkPolyVertex::New();
    grid = vtkUnstructuredGrid::New();
    mapper = vtkDataSetMapper::New();
    actor = vtkActor::New();

    pointsetcenterline = vtkPoints::New();
    polycenterline = vtkPolyVertex::New();
    gridcenterline = vtkUnstructuredGrid::New();
    mappercenterline = vtkDataSetMapper::New();
    actorcenterline = vtkActor::New();

    renderer = vtkRenderer::New();
    renderwindow =  vtkRenderWindow::New();
    interactor = vtkRenderWindowInteractor::New();
}


//!---------------------------------------------------------------------------
//!
//! \brief TestMath::get_actor
//! \return
//!
vtkActor *TestMath::get_actor(){
    return this->actor;
}

//!---------------------------------------------------------------------------
//!
//! \brief TestMath::get_actorcenterline
//! \return
//!
vtkActor *TestMath::get_actorcenterline(){
    return this->actorcenterline;
}
