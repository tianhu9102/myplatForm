#ifndef ANALYSEWIDGET_H
#define ANALYSEWIDGET_H

#include "FourViewWidget.h"
#include "NavigationPointActor.h"
#include "InterestedFrameActor.h"

#include "TextActor.h"

class vtkWidgetCallsR : public vtkCommand
{
public:
 static vtkWidgetCallsR *New()
 {
  return new vtkWidgetCallsR;
 }
public:
 virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData){
    vtkPlaneWidget *pWidget = vtkPlaneWidget::SafeDownCast(caller);
    pWidget->GetPlane(pPlane);

    pWidget->UpdatePlacement();   
   if( pWidget->GetPickingManaged()){
    qDebug()<<"the planeWidget Normal(x,y,z)--"
           <<"("<<pPlane->GetNormal()[0]
             <<","<<pPlane->GetNormal()[1]
             <<","<<pPlane->GetNormal()[2]<<")";
    qDebug()<<"the place Origin(x,y,z)--"
           <<"("<<pPlane->GetOrigin()[0]
             <<","<<pPlane->GetOrigin()[1]
             <<","<<pPlane->GetOrigin()[2]<<")";
   }
 }
public:
    vtkPlane *pPlane ;
};


class AnalyseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnalyseWidget(FourViewWidget *myFourv, int wid, int heig);
    void initVariable();
    void constructIHM(int w, int h);
    void setconnections();
    void multiView();
    void ThreeDimensionReconstruction();
    bool source3DVolumeDisplay();
    void centerCutting(int pos);
    void extractInterstedSection();
    void newextractInterstedSection();
    void lastWidgetFunction();

    double *getPixel(QString filePath, int pos[3]);

    vtkRenderer*get_Srenderer();
    vtkRenderer*get_CenterCuttingrenderer();

    QVTKWidget *getcenterCuttingQVTKWidget();
    QSlider *getSlider();
    QLineEdit *getMaxValuelineEdit();

    QSpinBox *getMinValueSpinBox();
    QSpinBox *getMaxValueSpinBox();
    QSpinBox *getCurrentValueSpinBox();


    void flyThrough(double foc_x, double foc_y, double foc_z, double pos_x, double pos_y, double pos_z, double vie_x, double vie_y, double vie_z);
    vtkActor *getPActor();

    vtkActor2D *getLabeledPointActor();

    double getnavigationPX();
      double getnavigationPY();
        double getnavigationPZ();

        vtkColorTransferFunction* getColorTran();



private:
    TextActor*  txActor;

    InterestedFrameActor*  myIntersedFrameActor;
    NavigationPointActor *naviPointActor;

    int theWid;
    int theHeigh;

    vtkMetaImageReader *mhdReader;
    QString mymhdfilename;
    QGridLayout *qGridLayout;
    QVTKWidget *qVTKWidget[4];
    vtkRenderer *irenderer[4];
    vtkRenderWindow *irenderWindow[4];
    FourViewWidget *fws;
    QWidget *funtionBarWidget;
    QWidget *MPRWidget;
    QHBoxLayout *funtionBarLayout;
    QVBoxLayout *mainLayout;
    vtkImageActor* imageActor;

    vtkImageShiftScale *shift;
    vtkFixedPointVolumeRayCastMapper *fixedMapper;
    vtkColorTransferFunction* colorTran;
    vtkPiecewiseFunction* piceFun;
    vtkVolumeProperty* volumeProperty;
    vtkVolume* pVolume;
    vtkPlaneWidget* planeWidget;
    vtkRenderer* srenderer;      //!qVTKWidget[0]
    vtkCamera* activeCamera;
    vtkRenderWindow *srenderWindow;
    vtkRenderWindowInteractor *pInt;

    vtkPlane *pPlane;
    vtkCutter *pCut;
    vtkActor *pActor;
    vtkWidgetCallsR *pCall;
    vtkPolyDataMapper *selectMapper;
    vtkRenderer *centerCuttingrenderer;   //!qVTKWidget[1]
    vtkRenderWindow *centerCuttingrenderWindow;

    vtkRenderer *interstedSectionrenderer;  //!qVTKWidget[2]
    vtkRenderWindow *interstedSectionrenderWindow;

    vtkRenderer *lastWidgetrenderer;  //!qVTKWidget[3]
    vtkRenderWindow *lastWidgetrenderWindow;

    vtkXYPlotActor *plotActor;

    vtkLabelPlacementMapper *labeledPointPolyMapper;
    vtkActor2D *labeledPointActor;

    vtkActor* actorX;
    vtkActor* actorY;
    vtkActor* actorZ;


    QTimer *updateTimer;
    QLabel *minValueLabel;
    QLineEdit *minValuelineEdit;
    QLabel *maxValueLabel;
    QLineEdit *maxValuelineEdit;
    QLabel *currentValueLabel;
    QLineEdit *currentValuelineEdit;
    QSlider *slider;
    int maxValue;
    QSpacerItem *hSpaceItem;
    QPushButton *movingButton;

    QTimer *dynamiclyShowSliceTimer;
    QWidget *dynamicChangeWidget;
    QGridLayout *dynamicChangeLayout;
    QStackedWidget *stackedWidget;
    QLabel *dyminValueLabel;
    QLabel *dymaxValueLabel;
    QLabel *dycurrentValueLabel;

    QGroupBox *controlGroup;
    QCheckBox *invertedAppearance;
    QCheckBox *invertedKeyBindings;
    QSpinBox *minValueSpinBox;
    QSpinBox *maxValueSpinBox;
    QSpinBox *currentValueSpinBox;
    QComboBox *orientationCombo;

    double navigationPX;
    double navigationPY;
    double navigationPZ;
    vtkImageAppend *append;


    int cptTim;

protected:


signals:

public slots:
    void updatecenterCuttingQVTKWidget();
    void setLineEditValue(int);
    void dynamiclyShowSlice();
    void movingExecute();

};

#endif // ANALYSEWIDGET_H
