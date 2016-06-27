#ifndef STRAIGHTEDVISUALIZATION_H
#define STRAIGHTEDVISUALIZATION_H

#include "Importinclude.h"

class StraightedVisualization : public QWidget
{
    Q_OBJECT
public:
    explicit StraightedVisualization(QWidget *parent = 0);

    void initVariable();
    void constructIHM();
    void mathdisplay();
    void reconstructedmathdisplay(vtkAlgorithmOutput *outputport);
    void selectedmathdisplay(int angel, vtkAlgorithmOutput *outputport, double arr[], double *center);
    void extractVOI(vtkImageData *outputport);
    vtkVolume *get_volume();
    QVTKWidget *getQVTKWidget();
    //vtkRenderWindow *getSRenderWindow();
    vtkCamera* getActivecamera();
    vtkColorTransferFunction *get_colorTranFun();

private:
    QHBoxLayout *qHboxLayout;
    QVTKWidget *qVTKWidget;

    vtkFixedPointVolumeRayCastMapper *mapper;
    vtkColorTransferFunction *colorTranFun;
    vtkPiecewiseFunction *pieceFun;
    vtkVolumeProperty *volumeProperty;
    vtkVolume *volume;
    vtkRenderer *renderer;
    vtkRenderWindow *renderwindow;
    vtkCamera *camera;




   // QVTKWidget *sqVTKWidget;


signals:

public slots:
};

#endif // STRAIGHTEDVISUALIZATION_H
