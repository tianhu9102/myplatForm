#include "May.h"

May::May()
{
    volumeDisM = new VolumeDisplayMath;
    centLineM = new CenterLineDisplayMath;
    goldSlicer = new GoldReslicer;

    interactor = vtkRenderWindowInteractor::New();
    render = vtkRenderer::New();
    renderWindow = vtkRenderWindow::New();
    renderWindow->AddRenderer(render);
    renderWindow->SetInteractor(interactor);

    interactor1 = vtkRenderWindowInteractor::New();
    render1 = vtkRenderer::New();
    renderWindow1 = vtkRenderWindow::New();
    renderWindow1->AddRenderer(render1);
    renderWindow1->SetInteractor(interactor1);

    probeFilter = vtkProbeFilter::New();
    wlLut = vtkWindowLevelLookupTable::New();
    mapper = vtkDataSetMapper::New();
    actor = vtkActor::New();
}

void May::straightenedMath(QString mhdfile,QString txtfile){
    volumeDisM->displayVolumeData(render1,mhdfile);
    centLineM->displayCenterLineData(render,txtfile,"b");
    centLineM->displayVesselThreeDimReconstruction(render,txtfile,"r");
    goldSlicer->displaySlicer(render1,volumeDisM->getReader()->GetOutput(),
                              centLineM->getCenterLinePr()->get_vesselsPoints().at(5)->get_abscissa(),
                              centLineM->getCenterLinePr()->get_vesselsPoints().at(5)->get_ordinate(),
                              centLineM->getCenterLinePr()->get_vesselsPoints().at(5)->get_isometric());

//    goldSlicer->displayCutterImg(render1,
//                                 volumeDisM->getReader()->GetOutput(),
//                                 centLineM->getCenterLinePr());

   // this->test(render1,volumeDisM->getReader(),centLineM->ribbonFilter());
    this->updateWindow();
}

GoldReslicer* May::getGoldSlicer(){
    return this->goldSlicer;
}
vtkRenderer* May::getRender1(){
    return this->render1;
}

void May::updateWindow(){
    renderWindow->Render();
    renderWindow1->Render();
    interactor->Start();
    interactor1->Start();
}

void May::test(vtkRenderer* render,
               vtkMetaImageReader* imgReader,
               vtkPolyData* polydata){

    probeFilter->SetInputConnection(1,imgReader->GetOutputPort());
    probeFilter->SetInputData(0,polydata);
    probeFilter->Update();

    double range = imgReader->GetOutput()->GetScalarRange()[1] -
            imgReader->GetOutput()->GetScalarRange()[0];
    double level = (imgReader->GetOutput()->GetScalarRange()[1] +
            imgReader->GetOutput()->GetScalarRange()[0]) / 2.0;
    wlLut->SetWindow(range);
    wlLut->SetLevel(level);

    mapper->SetInputData(probeFilter->GetOutput());
    mapper->SetLookupTable(wlLut);
    mapper->SetScalarRange(0, 1255);

    actor->SetMapper(mapper);
    render->AddActor(actor);
}
