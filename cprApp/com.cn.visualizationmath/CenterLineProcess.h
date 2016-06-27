#ifndef CENTERLINEPROCESS_H
#define CENTERLINEPROCESS_H

#include "CenterLinePoint.h"
#include "Importinclude.h"
#include "CrossMath.h"

class CenterLineProcess
{
public:
    CenterLineProcess();
    void referenceReader(QString referencePath);
    QString GetFileName();
    QVector<CenterLinePoint*> get_vesselsPoints();
    int getReferencecount();

private:
    QString referencefilePath;
    QVector<CenterLinePoint*> vesselsPoints;
    int referencecount;

    CrossMath* crosMs;
};

#endif // CENTERLINEPROCESS_H
