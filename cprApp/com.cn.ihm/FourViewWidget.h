#ifndef FOURVIEWWIDGET_H
#define FOURVIEWWIDGET_H

#include "CenterLineVisualization.h"
#include "VolumeVisualization.h"
#include "StraightedVisualization.h"
#include <vtkPolyData.h>

class FourViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FourViewWidget(QWidget *parent = 0);

    void initVariable();
    void constructIHM();

    void function();
    void getVolumeVisualization();
    void getCenterLineVisualization();
    VolumeVisualization* getVolumeVisualization_Object();
    CenterLineVisualization* getCenterLineVisualization_Object();
    StraightedVisualization* getStraightedVisualization_Object();
    vtkImageAppend* getStraightedVisualization();
    void getStraightedVisualization1();

    void StraightedCPR_mathdisplay();
    void ProjectedCPR_mathdisplay();
    void StretchedCPR_mathdisplay();

    vtkImageShiftScale* get_MpShift();
    double* getVolumeOriginCenter();
    QString getMhdfile();
    int getXDimisions();
    int getYDimisions();
    int getZDimisions();
    double getXOrigin();
    double getYOrigin();
    double getZOrigin();
    double getXSpacing();
    double getYSpacing();
    double getZSpacing();
    QString getCenterlinefile();
    int getCenterlinepointsize();
    vtkExtractVOI* getextractVOI();

private:
    QGridLayout *qGridLayout;
    CenterLineVisualization *clz;
    VolumeVisualization *vvz;
    StraightedVisualization *shz;

    vtkSplineDrivenImageSlicer *reslicer;
    vtkImageAppend *append;

    vtkImageShiftScale *m_pShift;
    vtkPlane *pPlane[10];
    vtkCutter *pCut[10];

    vtkExtractVOI* extractVOI;

signals:

public slots:
};

#endif // FOURVIEWWIDGET_H
