#ifndef GENERALINFORMATIONANALYSER_H
#define GENERALINFORMATIONANALYSER_H

#include <vtkImageData.h>
#include <QString>
#include <QVector>
#include "HistogramPoint.h"

class GeneralInformationAnalyser
{
public:
    GeneralInformationAnalyser();
    ~GeneralInformationAnalyser();

    QVector<HistogramPoint*> extractFrequency(vtkImageData *mraImage);
    QStringList extractHistogramStatistics(vtkImageData* mraImage);
    long getTotalGrayscaleValueNumber(vtkImageData* mraImage);
    double getGrayscaleValueMean(vtkImageData* mraImage);
};

#endif // GENERALINFORMATIONANALYSER_H
