#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "FourViewWidget.h"
#include "AnalyseWidget.h"
#include "BasicParameters.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void initVariable();
    void constructIHM();
    void setconnections();
    FourViewWidget *getFourViewWidget();

private slots:
    void mhdfileChoose();
    void centerfileChoose();

    void reconstructed();
    void straightedCPR();
    void straightedCPR_implementation();

    void projected_Centerline();

    void anaylse(); //???
    AnalyseWidget *anaylseofAnaylse();
    BasicParameters *anaylseofBasicParameters();

    void volumeRenderingfunction();

    void addreference();
    void SlotItemClicked(QTreeWidgetItem *item, int column);
    void ShowMhdMenu();
    void getSystemTime();

    void addnavigationActor();
    void deletenavigationActor();
    void addgridActor();
    void deletegridActor();
    void bloodThreeDimensionReconstuction();
    void deletebloodThreeDimensionReconstuction();

    void addprojectedCenterline();
    void deleteprojectedCenterline();
    void on_addcurvePlaneBtn();
    void on_deletecurvePlaneBtn();

private:
    AnalyseWidget *analyseWidget;
     BasicParameters *basicParameters;

    QDesktopWidget *desktop;
    int width;
    int height;

    QVBoxLayout *qGridLayout;
    QWidget *toolBarWidget;
    QWidget *toolBar;
    QHBoxLayout *toolBarLayout;

    QPushButton *firstBtn;
    QPushButton *secondBtn;
    QPushButton *mhdfileloadBtn;
    QPushButton *centerfileloadBtn;
    QPushButton *cprBtn;
    QPushButton *projected_CenterlineBtn;
    QPushButton *anaylseBtn;
    QPushButton *volumeRenderingBtn;
    QSpacerItem *datasetSpaceItem;
    QSpacerItem *pushBtnSpaceItem;

    QWidget *middleWidget;
    QHBoxLayout *middleLayout;

    QWidget *subtoolWidget;
    QVBoxLayout *subtoolWidgetLayout;
    QTreeWidget *centerlineTreeWidget;
    QTreeWidgetItem *datasetstreeItem;
    QTreeWidgetItem *mhdfilewidgetItem;
    QTreeWidgetItem *referenceswidgetItem;

    QWidget *waitingWidget;
    QGridLayout *waitingWidgetLayout;
    QSpacerItem *vSpaceItem1;
    QTabWidget *qTabWidget;
    FourViewWidget *fs;


    QWidget *statusBarWidget;
    QHBoxLayout *statusBarLayout;

    vtkColorTransferFunction* colorTran;
    vtkColorTransferFunction* colorTranofStraight;
     vtkColorTransferFunction* colorTranofAnaly;

    QLCDNumber *timeLCD;
    QTimer *updatetimer;


    QPushButton *addnavigationActorBtn;
    QPushButton *deletenavigationActorBtn;
    QPushButton *addgridActorBtn;
    QPushButton *deletegridActorBtn;

    QPushButton *addprojectedBtn;
    QPushButton *deleteprojectedBtn;
    QPushButton *bloodThreeDimensionReconstuctionBtn;
    QPushButton *deletebloodThreeDimensionReconstuctionBtn;
    QPushButton *addcurvePlaneBtn;
    QPushButton *deletecurvePlaneBtn;


};

#endif // MAINWIDGET_H
