#ifndef VOLUMEVISUALIZATION_H
#define VOLUMEVISUALIZATION_H

#include "Importinclude.h"

class VolumeVisualization : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeVisualization(QWidget *parent = 0);
    void initVariable();
    void constructIHM();
    void mathdisplay(QString filename);
    void mathdisplayofmath(QString filename);
    void mathdisplayofQVTKWidget();
    void mhdfileChoose();
    void mhdpipeline(QString mhdFile);
    void dcmpipeline(QString dcmFile);
    void vtkpipeline(QString vtkFile);
    void vtppipeline(QString vtpFile);
    void mhapipeline(QString mhaFile);
    void matpipeline(QString matFile);

    QString getmhdfilename();
    vtkRenderer* get_renderer();
    vtkRenderWindow* get_rendererWindow();
    vtkMetaImageReader* get_volumeReader();
    vtkColorTransferFunction *get_colorTranFun();
    QVTKWidget* get_qvtkWidget();
    vtkVolume *get_volume();
    int getxDimsion();
    int getyDimsion();
    int getzDimsion();
    double getxOrigin();
    double getyOrigin();
    double getzOrigin();
    double getxSpacing();
    double getySpacing();
    double getzSpacing();


    vtkVolume *getVolume();

private:
    int xdim,ydim,zdim;
    double xorigin,yorigin,zorigin;
    double xspacing,yspacing,zspacing;
    QString filepathname;

    QHBoxLayout *qHboxLayout;
    QVTKWidget *qVTKWidget;

    vtkMetaImageReader *volumeReader;
    vtkFixedPointVolumeRayCastMapper *mapper;
    vtkVolumeRayCastMapper *volumeRaycastmapper;
    vtkColorTransferFunction *colorTranFun;
    vtkPiecewiseFunction *pieceFun;
    vtkPiecewiseFunction *gradientFun;
    vtkVolumeProperty *volumeProperty;
    vtkVolume *volume;
    vtkRenderer *renderer;
    vtkRenderer *renderer0;
    vtkRenderWindow *renderwindow;
    vtkRenderWindow *renderwindow0;

signals:

public slots:
};

#endif // VOLUMEVISUALIZATION_H
