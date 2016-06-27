#ifndef HISTOGRAMPOINT_H
#define HISTOGRAMPOINT_H


class HistogramPoint
{
public:
    HistogramPoint();
    ~HistogramPoint();
    void setAbscissaValue(int abscissaValue);
    void setOrdinateValue(int ordinateValue);
    int getAbscissaValue();
    int getOrdinateValue();
private:
    int abscissaValue = 0;
    int ordinateValue = 0;
};

#endif // HISTOGRAMPOINT_H
