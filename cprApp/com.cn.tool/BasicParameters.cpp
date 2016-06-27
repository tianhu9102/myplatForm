#include "BasicParameters.h"

BasicParameters::BasicParameters(FourViewWidget *basicParametersFourview) : QWidget(basicParametersFourview)
{
    this->fourViewWidget = basicParametersFourview;
    this->initVariable();
    this->constructIHM();
}

void BasicParameters::initVariable(){


}

//!-----------------------------------------------------------------------------------------------
//!
//! \brief BasicParameters::constructIHM
//!
void BasicParameters::constructIHM(){
    paratableWidget = new QTableWidget(8,1);  //新建一8行1列的表格
    paratableWidget->setStyleSheet("background-color:transparent");
    paratableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    paratableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    paratableWidget->horizontalHeader()->setStretchLastSection(true);

    QString headerStylesheet("QHeaderView::section{border:1px solid #6c6c6c;border-radius:2px;padding:2px 4px;padding-left: 4px;color: black;background-color:skyblue;font: 12pt '宋体'}");
    paratableWidget->verticalHeader()->setStyleSheet(headerStylesheet);
    paratableWidget->horizontalHeader()->setStyleSheet(headerStylesheet);

    QStringList verticalHeader;
    verticalHeader<<"mhdfile"<<"dims"<<"origin"<<"spacing" <<"centerline"<<"pointsize"<<"vesselsize"<<"poo";
    QStringList horzionHeader;
    horzionHeader<<"parameters";
    paratableWidget->setVerticalHeaderLabels(verticalHeader);
    paratableWidget->setHorizontalHeaderLabels(horzionHeader); 

    //!---------------------------------------------------------------
    qGridLayout = new QGridLayout(this);
    qGridLayout->addWidget(paratableWidget,0,0);

    qGridLayout->setSpacing(0);
    qGridLayout->setMargin(0);
}


//!-----------------------------------------------------------------------------------------------------
//!
//! \brief BasicParameters::mhdfileparameterItem
//!  used in MainWidget::anaylse()
//!  in fact these basic parameters are set in VolumeVisualization::mhdpipeline(QString mhdFile)
//!
void BasicParameters::mhdfileparameterItem(){
    QString mhdfileItem(fourViewWidget->getMhdfile());
    QString dimsItem("X: "+QString::number(fourViewWidget->getXDimisions())+
                     "   Y: "+QString::number(fourViewWidget->getYDimisions())+
                     "   Z: "+QString::number(fourViewWidget->getZDimisions()));
    QString originItem("X: "+QString::number(fourViewWidget->getXOrigin())+
                       "  Y: "+QString::number(fourViewWidget->getYOrigin())+
                       "  Z: "+QString::number(fourViewWidget->getZOrigin()));
    QString spacingItem("X: "+QString::number(fourViewWidget->getXSpacing())+
                        "  Y: "+QString::number(fourViewWidget->getYSpacing())+
                        "  Z: "+QString::number(fourViewWidget->getZSpacing()));
    paratableWidget->setItem(0,0,new QTableWidgetItem(mhdfileItem));
    paratableWidget->setItem(1,0,new QTableWidgetItem(dimsItem));
    paratableWidget->setItem(2,0,new QTableWidgetItem(originItem));
    paratableWidget->setItem(3,0,new QTableWidgetItem(spacingItem));
}

//!-----------------------------------------------------------------------------------------------------
//!
//! \brief BasicParameters::centerlineparameterItem
//!  used in MainWidget::anaylse()
//!
void BasicParameters::centerlineparameterItem(){
    QString centerlineItem(fourViewWidget->getCenterlinefile());
    QString pointssizeItem(QString::number(fourViewWidget->getCenterlinepointsize())); //typeconvert
    QString vesselcountItem("1");
    QString pooItem("Not used");
    paratableWidget->setItem(4,0,new QTableWidgetItem(centerlineItem));
    paratableWidget->setItem(5,0,new QTableWidgetItem(pointssizeItem));
    paratableWidget->setItem(6,0,new QTableWidgetItem(vesselcountItem));
    paratableWidget->setItem(7,0,new QTableWidgetItem(pooItem));
}

//!-----------------------------------------------------------------------------------------------------
//!
//! \brief BasicParameters::getParatableWidget
//!
QTableWidget *BasicParameters::getParatableWidget(){
    return this->paratableWidget;
}
