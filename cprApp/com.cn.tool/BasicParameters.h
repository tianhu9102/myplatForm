#ifndef BASICPARAMETERS_H
#define BASICPARAMETERS_H

#include "FourViewWidget.h"

class BasicParameters : public QWidget
{
    Q_OBJECT
public:
    explicit BasicParameters(FourViewWidget *basicParametersFourview);

    void initVariable();
    void constructIHM();
    QTableWidget *getParatableWidget();

    void mhdfileparameterItem();
    void centerlineparameterItem();



private:
    FourViewWidget *fourViewWidget;
    QGridLayout *qGridLayout;
    QTableWidget *paratableWidget;


signals:

public slots:
};

#endif // BASICPARAMETERS_H
