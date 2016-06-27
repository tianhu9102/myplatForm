#include "ProjectionImpl.h"

int ProjectionImpl::implate(){

    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer.Get());
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow.Get());

    vtkNew< vtkDiskSource> source;
    vtkNew<vtkPolyDataMapper> mapper1;
    mapper1->SetInputConnection(source->GetOutputPort());

    vtkNew<vtkActor> actor1;
    actor1->SetMapper(mapper1.Get());
    actor1->GetProperty()->SetInterpolationToFlat();
    renderer->AddActor(actor1.Get());

    vtkNew<vtkCamera> camera1;
    vtkCamera* activeCamera = renderer->GetActiveCamera();
    camera1->DeepCopy(activeCamera);

    for (int i = 0; i < 3; ++i) {
        double position[] = {-2, -2, -2};
        double focalPoint[] = {0, 0, 0};
        position[i] *= 10;
        focalPoint[i] = 1;

        activeCamera->SetPosition(position);
        activeCamera->SetFocalPoint(focalPoint);
        activeCamera->ParallelProjectionOn();

        vtkNew<vtkPolyDataSilhouette> silhouette;
        silhouette->SetInputConnection(source->GetOutputPort());
        silhouette->SetCamera(activeCamera);
        silhouette->BorderEdgesOn();
        silhouette->SetEnableFeatureAngle(0);
        silhouette->Update();

        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        points->DeepCopy(silhouette->GetOutput()->GetPoints());
        vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
        lines->DeepCopy(silhouette->GetOutput()->GetLines());

        double point[3];
        for (vtkIdType j = 0; j < points->GetNumberOfPoints(); ++j) {
            points->GetPoint(j, point);
            point[i] = 2;
            points->SetPoint(j, point);
        }

        vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
        polydata->SetPoints(points);
        polydata->SetLines(lines);

        vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper2->SetInputData(polydata);
        mapper2->Update();

        vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
        actor2->SetMapper(mapper2);
        actor2->GetProperty()->SetColor(1.0, 0.3882, 0.2784);
        actor2->GetProperty()->SetLineWidth(5);
        renderer->AddActor(actor2);
    }

    renderer->SetBackground(.3, .6, .3);

    vtkNew<vtkCubeAxesActor> axes;
    axes->SetCamera(activeCamera);
    axes->DrawXGridlinesOn();
    axes->DrawYGridlinesOn();
    axes->DrawZGridlinesOn();
    axes->SetBounds(-2, 2, -2, 2, -2, 2);

    axes->XAxisMinorTickVisibilityOn();
    axes->YAxisMinorTickVisibilityOn();
    axes->ZAxisMinorTickVisibilityOn();

    axes->GetXAxesGridlinesProperty()->SetLineWidth(3);
    axes->GetYAxesGridlinesProperty()->SetLineWidth(3);
    axes->GetZAxesGridlinesProperty()->SetLineWidth(3);

    axes->GetXAxesLinesProperty()->SetLineWidth(5);
    axes->GetYAxesLinesProperty()->SetLineWidth(5);
    axes->GetZAxesLinesProperty()->SetLineWidth(5);

    axes->SetFlyModeToOuterEdges();
    axes->SetGridLineLocation(2);
    renderer->AddActor(axes.Get());

    activeCamera->DeepCopy(camera1.Get());
    renderer->ResetCamera();
    renderWindowInteractor->Start();
    return 1;
}
