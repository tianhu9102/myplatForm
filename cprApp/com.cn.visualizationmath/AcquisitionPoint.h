#ifndef ACQUISITIONPOINT_H
#define ACQUISITIONPOINT_H


class AcquisitionPoint
{
public:
    void setGrayScaleValue(unsigned short _gsv);
    void setAbscissa(double _abs);
    void setOrdinate(double _ord);
    void setIsometric(double _iso);


    double getAbscissa();
    double getOrdinate();
    double getIsometric();
    unsigned short getGrayScaleValue();

private:
    double coordinates[3];
    unsigned short gsv; // grayscale value

public:
    AcquisitionPoint();
};

#endif // ACQUISITIONPOINT_H
