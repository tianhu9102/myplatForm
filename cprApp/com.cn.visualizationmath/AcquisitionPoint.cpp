#include "AcquisitionPoint.h"

AcquisitionPoint::AcquisitionPoint()
{

}

//!---------------------------------------------------------------------------
//!
//! \brief AcquisitionPoint::setGrayScaleValue
//! \param _gsv
//!
void AcquisitionPoint::setGrayScaleValue(unsigned short _gsv){
    this->gsv = _gsv;
}

//!---------------------------------------------------------------------------
//!
//! \brief AcquisitionPoint::setAbscissa
//! \param _abs
//!
void AcquisitionPoint::setAbscissa(double _abs){
    this->coordinates[0] = _abs;
}

//!---------------------------------------------------------------------------
//!
//! \brief AcquisitionPoint::setOrdinate
//! \param _ord
//!
void AcquisitionPoint::setOrdinate(double _ord){
    this->coordinates[1] = _ord;
}

//!---------------------------------------------------------------------------
//!
//! \brief AcquisitionPoint::setIsometric
//! \param _iso
//!
void AcquisitionPoint::setIsometric(double _iso){
    this->coordinates[2] = _iso;
}

//!---------------------------------------------------------------------------
//!
//! \brief AcquisitionPoint::getAbscissa
//! \return
//!
double AcquisitionPoint::getAbscissa(){
    return this->coordinates[0];

}

//!---------------------------------------------------------------------------
//!
//! \brief AcquisitionPoint::getOrdinate
//! \return
//!
double AcquisitionPoint::getOrdinate(){
    return this->coordinates[1];
}

//!---------------------------------------------------------------------------
//!
//! \brief AcquisitionPoint::getIsometric
//! \return
//!
double AcquisitionPoint::getIsometric(){
    return this->coordinates[2];
}

//!---------------------------------------------------------------------------
//!
//! \brief AcquisitionPoint::getGrayScaleValue
//! \return
//!
unsigned short AcquisitionPoint::getGrayScaleValue(){
    return this->gsv;
}
