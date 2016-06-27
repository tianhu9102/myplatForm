#ifndef CENTERLINEVISUALIZATION_H
#define CENTERLINEVISUALIZATION_H

#include "Importinclude.h"
#include "CenterLineProcess.h"
#include <QtCore/qmath.h>
#include <QtMath>

#include "TestMath.h"
#include <vtkPolyLine.h>
#include <vtkTubeFilter.h>

class CenterLineVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit CenterLineVisualization(QWidget *parent = 0);

    void initVariable();
    void constructIHM();
    void mathdisplay();
    bool mathdisplayofmath();
    bool mathdisplayofQVTKWidget();

    void centerlineChoose();
    void typeconvert(int resolution);
    vtkPolyData *typeconvert1();
    void coremath();
    vtkActor *bloodThreeDimensionReconstruction();

    vtkPoints *getPointSource();
    vtkPoints *getWritefilePoints();
    vtkActor* get_actor();
    vtkUnstructuredGrid* get_grid();
    CenterLineProcess* get_centerLineProcess();
    vtkParametricFunctionSource* get_functionSource();
    vtkRenderer* get_renderer();
    vtkRenderWindow* get_renderWindow();

    vtkActor* get_ProjectedpointActor(double originX, double originY, double originZ, double normalX, double normalY, double normalZ);
    vtkPoints* getProjectedPoints();
    void writePolyFile(vtkPoints *poins);
    vtkActor *getProjectedCenterlineActor();


    vtkActor* getAcquisitionActor();
    vtkActor* getAcquisitioncenterlineActor();
    vtkActor* getReconstructionActor();


    vtkParametricSpline *get_spline();
    QVTKWidget *get_QVTKWidget();

private:
    QHBoxLayout *qHboxLayout;
    QVTKWidget *qVTKWidget;
    CenterLineProcess *centerLineProcess;
    vtkPolyVertex *poly;

    vtkUnstructuredGrid *grid;
    vtkPoints *points;
    vtkPoints *writefilePoints;

    vtkAxesActor *axesActor;
    vtkTransform *tranForm;
    vtkDataSetMapper *mapper;
    vtkActor *actor;
    vtkRenderer *renderer;
    vtkRenderWindow *renderwindow;
    vtkRenderer *renderer0;
    vtkRenderWindow *renderwindow0;

    vtkParametricSpline *spline;
    vtkParametricFunctionSource *functionSource;

   int poSize;
   vtkPoints *copyProjectedPoints;
   vtkActor *copyProjectedActor;
   vtkPlaneSource *subProjectedPlaneSource;
   vtkPolyDataMapper *subProjectedPlaneMapper;
   vtkActor *subProjectedPlaneActor;

   TestMath *acquisitionCenterPoints;


   //! bloodThreeDimensionReconstruction
   vtkPoints* reconstructionPoints;
   vtkCellArray* reconstructionLines ;
   vtkPolyData* reconstructionPolyData;
   vtkDoubleArray* tubeRadius;
   vtkUnsignedCharArray *reconstructionColors;
   vtkTubeFilter* reconstructionTube ;
   vtkPolyDataMapper *reconstructionMapper ;
   vtkActor* reconstructionActor ;


signals:

public slots:

};

#endif // CENTERLINEVISUALIZATION_H
