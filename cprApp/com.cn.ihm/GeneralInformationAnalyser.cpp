#include "GeneralInformationAnalyser.h"
#include <QDebug>
#include <vtkImageExtractComponents.h>
#include <vtkSmartPointer.h>
#include <vtkImageAccumulate.h>
#include <vtkImageHistogramStatistics.h>
#include <vtkIdTypeArray.h>


GeneralInformationAnalyser::GeneralInformationAnalyser(){}

GeneralInformationAnalyser::~GeneralInformationAnalyser(){}

QVector<HistogramPoint*> GeneralInformationAnalyser::extractFrequency(vtkImageData *mraImage){
    vtkImageHistogramStatistics *statistics = vtkImageHistogramStatistics::New();
    statistics->SetInputData(mraImage);
    statistics->GenerateHistogramImageOff();
    statistics->Update();

    double range[2];
    mraImage->GetScalarRange(range);

    vtkIdTypeArray *histogram = statistics->GetHistogram();

    QVector<HistogramPoint*> frequency;

    for(vtkIdType  i = range[0]; i < range[1]; i++){
        vtkIdType count = histogram->GetValue(i);
        if(count > 0){
            HistogramPoint *p =  new HistogramPoint();
            p->setAbscissaValue(i);
            p->setOrdinateValue(count);
            frequency.append(p);
        }
    }
    return frequency;
}

QStringList GeneralInformationAnalyser::extractHistogramStatistics(vtkImageData* mraImage){
    QStringList statisticsList;
    vtkImageHistogramStatistics *statistics = vtkImageHistogramStatistics::New();
    statistics->SetInputData(mraImage);
    statistics->GenerateHistogramImageOff();
    statistics->Update();
    statisticsList<<QString::number(statistics->GetMaximum())
                  <<QString::number(statistics->GetMinimum())
                  <<QString::number(statistics->GetMean())
                  <<QString::number(statistics->GetMedian())
                  <<QString::number(statistics->GetStandardDeviation());

    return statisticsList;
}

long GeneralInformationAnalyser::getTotalGrayscaleValueNumber(vtkImageData* mraImage){
    int dim = mraImage->GetDataDimension();
    int *dimensions = mraImage->GetDimensions();

    long totalNumber = 1;

    for(unsigned char cpt = 0; cpt < dim; cpt++){
        totalNumber *= dimensions[cpt];
    }
    return totalNumber;
}


double GeneralInformationAnalyser::getGrayscaleValueMean(vtkImageData* mraImage){
    long totalNumber = getTotalGrayscaleValueNumber(mraImage);

    double mean = 0.0;
    int dim = mraImage->GetDataDimension();
    int *dimensions = mraImage->GetDimensions();
    if(dim == 3){
        for(int i = 0; i < dimensions[0]; i++){
          for(int j = 0; j < dimensions[1]; j++){
              for(int k = 0; k < dimensions[2]; k++){
                unsigned short* pixel = static_cast<unsigned short*>(mraImage->GetScalarPointer(i,j,k));
                mean += (*pixel);
              }
          }
        }
    }
    return mean/totalNumber;;
}

