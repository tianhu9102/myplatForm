#include "CenterLinePoint.h"


/**
 * @brief CenterLinePoint::CenterLinePoint
 * @param parent
 */
CenterLinePoint::CenterLinePoint()
{
    pos_x = 0.0;
    pos_y = 0.0;
    pos_z = 0.0;

    xdiff = 0.0;
    ydiff = 0.0;
    zdiff = 0.0;
    radius = 0.0;

    vector[0] = 1.0;
    vector[1] = 1.0;
    vector[2] = 1.0;

    acquisition_vector[0] = 1.0;
    acquisition_vector[1] = 1.0;
    acquisition_vector[2] = 1.0;

    acquisition_radius = 40;
    acquisition_frequence = 40;
}

void CenterLinePoint::printAcquisitionPoints(){
    for(int cpt=0; cpt<acquisitionPoints.size();cpt++){
        std::cout<<"    -------------- "<<cpt<<" ------------"<<std::endl;
        std::cout<<"      "<<acquisitionPoints.at(cpt)->getAbscissa()<<","<<acquisitionPoints.at(cpt)->getOrdinate()<<","<<acquisitionPoints.at(cpt)->getIsometric()<<std::endl;
    }
}

void CenterLinePoint::appendAcquisitionPoints(AcquisitionPoint *acqPoint){
    this->acquisitionPoints.append(acqPoint);
}

AcquisitionPoint * CenterLinePoint::getAcquisitionPointAt(int index){
    return this->acquisitionPoints.at(index);
}

void CenterLinePoint::print(){
    std::cout<<"coordinates :"<<this->pos_x<< "  "<<this->pos_y<< "  "<<this->pos_z<<std::endl;
    std::cout<<"vector      :"<<vector[0]<< "  "<<vector[1]<< "  "<<vector[2]<<std::endl;
    std::cout<<"cos_sigma   :"<<this->get_cos_sigma()<<std::endl;
    std::cout<<"cos_theta   :"<<this->get_cos_theta()<<std::endl;
    std::cout<<"uvw         :"<<this->get_acquisition_vector_u()<< " "<<this->get_acquisition_vector_v()<< " "<<this->get_acquisition_vector_w()<<std::endl;
}

void CenterLinePoint::normalize(){
    vtkMath::Normalize(vector);
}

void CenterLinePoint::update(){
    vector[0] = this->xdiff;
    vector[1] = this->ydiff;
    vector[2] = this->zdiff;
    normalize();
}

void CenterLinePoint::normalize_uvw(){
    vtkMath::Normalize(acquisition_vector);
}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLinePoint::set_cos_sigma
//! \param cos_sigma
//!
void CenterLinePoint::set_cos_sigma(double cos_sigma){
    this->cos_sigma = cos_sigma;
    this->set_cos_theta(sqrt((1 + cos_sigma)/2));
}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLinePoint::set_cos_theta
//! \param cos_theta
//!
void CenterLinePoint::set_cos_theta(double cos_theta){
    this->cos_theta = cos_theta;
}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLinePoint::set_acquisition_k
//! \param constant_k , it is one when normalized
//!
void CenterLinePoint::set_acquisition_k(double constant_k){
    this->constant_k = constant_k;
}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLinePoint::get_acquisition_k
//! \return
//!
double CenterLinePoint::get_acquisition_k(){
    return this->constant_k;
}

//!---------------------------------------------------------------------------
//! \brief CenterLinePoint::set_abscissa
//! \param pos_x
void CenterLinePoint::set_abscissa(double pos_x){
    this->pos_x = pos_x;
}

//!---------------------------------------------------------------------------
//! \brief CenterLinePoint::set_ordinate
//! \param pos_y
void CenterLinePoint::set_ordinate(double pos_y){
    this->pos_y = pos_y;
}

//!---------------------------------------------------------------------------
//! \brief CenterLinePoint::set_isometric
//! \param pos_z
void CenterLinePoint::set_isometric(double pos_z){
    this->pos_z = pos_z;
}

void CenterLinePoint::set_acquisition_vector_u(double u){
    this->acquisition_vector[0] = u;
}

void CenterLinePoint::set_acquisition_vector_v(double v){
    this->acquisition_vector[1] = v;
}

void CenterLinePoint::set_acquisition_vector_w(double w){
    this->acquisition_vector[2] = w;
}

void CenterLinePoint::set_acquisition_radius(double r){
   this->acquisition_radius = r;
}

void CenterLinePoint::set_acquisition_frequence(int frequence){
    this->acquisition_frequence = frequence;
}

double CenterLinePoint::get_acquisition_vector_u(){
    return this->acquisition_vector[0];
}

double CenterLinePoint::get_acquisition_vector_v(){
    return this->acquisition_vector[1];
}

double CenterLinePoint::get_acquisition_vector_w(){
    return this->acquisition_vector[2];
}

double CenterLinePoint::get_acquisition_radius(){
    return this->acquisition_radius;
}

int CenterLinePoint::get_acquisition_frequence(){
    return this->acquisition_frequence;
}


//!---------------------------------------------------------------------------
//!
//! \brief CenterLinePoint::set_xdiff
//! \param xdiff
//!
void CenterLinePoint::set_xdiff(double xdiff){
     this->xdiff = xdiff;
}

void CenterLinePoint::set_ydiff(double ydiff){
    this->ydiff = ydiff;
}

void CenterLinePoint::set_zdiff(double zdiff){
    this->zdiff = zdiff;
}


void CenterLinePoint::set_radius(double radius){
    this->radius = radius;
}

double CenterLinePoint::get_abscissa(){
    return this->pos_x;
}

double CenterLinePoint::get_ordinate(){
    return this->pos_y;
}

double CenterLinePoint::get_isometric(){
    return this->pos_z;
}

double CenterLinePoint::get_xdiff(){
    return vector[0];
}
double CenterLinePoint::get_ydiff(){
    return vector[1];
}
double CenterLinePoint::get_zdiff(){
    return vector[2];
}

double CenterLinePoint::get_radius(){
    return this->radius;
}

double CenterLinePoint::get_cos_sigma(){
    return this->cos_sigma;
}
double CenterLinePoint::get_cos_theta(){
    return this->cos_theta;
}
