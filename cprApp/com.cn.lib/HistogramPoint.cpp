#include "HistogramPoint.h"

HistogramPoint::HistogramPoint()
{

}

HistogramPoint::~HistogramPoint()
{

}

void HistogramPoint::setAbscissaValue(int abscissaValue){
    this->abscissaValue = abscissaValue;
}

void HistogramPoint::setOrdinateValue(int ordinateValue){
    this->ordinateValue = ordinateValue;
}

int HistogramPoint::getAbscissaValue(){
    return this->abscissaValue;
}

int HistogramPoint::getOrdinateValue(){
    return this->ordinateValue;
}
