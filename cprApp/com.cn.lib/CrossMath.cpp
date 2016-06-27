#include "CrossMath.h"

//!---------------------------------------------------------------------------
//!
//! \brief CrossMath::CrossMath
//!
//!  this class is used to compute two vectors' cross, and then normalized
//!  it can also be used to compute frenet-serret frame.
//!
//!  vector a = (x1,y1,z1) , vector b = (x2,y2,z2)   then  a × b = (i,j,k)
//!  for example: a = (1,2,3)  b = (4,5,6).   a × b = (i,j,k) = (-3,6,-3)
//!               after normalize  a × b = (-0.408248, 0.816497, -0.408248)
//!
//!  ! test successfully !
//!  date: 2016-05-10    add: ShenZhen
//!---------------------------------------------------------------------------

CrossMath::CrossMath(){
    tangent[0] = 1.0;
    tangent[1] = 1.0;
    tangent[2] = 1.0;

    binormal[0] = 1.0;
    binormal[1] = 1.0;
    binormal[2] = 1.0;

    normal[0] = 1.0;
    normal[1] = 1.0;
    normal[2] = 1.0;

}

//!---------------------------------------------------------------------------
//!
//! \brief CrossMath::crossCore
//! \param x1  \param y1  \param z1
//! \param x2  \param y2  \param z2
//!
void CrossMath::crossCore(double x1,double y1,double z1,
                          double x2,double y2,double z2){
    double i = y1 * z2 - y2 * z1;
    double j = z1 * x2 - z2 * x1;
    double k = x1 * y2 - x2 * y1;

    arry[0] = i;
    arry[1] = j;
    arry[2] = k;

    //!normalize
    arry[0] = i/sqrt(i*i +j*j + k*k);
    arry[1] = j/sqrt(i*i +j*j + k*k);
    arry[2] = k/sqrt(i*i +j*j + k*k);
}

//!---------------------------------------------------------------------------
//!
//! \brief CrossMath::frenetSerretFrame
//! \param x1  \param y1  \param z1
//! \param x2  \param y2  \param z2
//!
void CrossMath::frenetSerretFrame(double x1, double y1, double z1,
                                  double x2, double y2, double z2){
     //! compute binormal
     this->crossCore(x1, y1, z1, x2, y2, z2);
     binormal[0] = this->get_i();
     binormal[1] = this->get_j();
     binormal[2] = this->get_k();

     //! compute tangent
     double a = (x1 + x2)/2;
     double b = (y1 + y2)/2;
     double c = (z1 + z2)/2;

     //! normalize tangent
     tangent[0] = a /sqrt(a*a + b*b + c*c);
     tangent[1] = b /sqrt(a*a + b*b + c*c);
     tangent[2] = c /sqrt(a*a + b*b + c*c);

     //! compute normal
     this->crossCore(binormal[0],binormal[1],binormal[2],tangent[0],tangent[1],tangent[2]);
     normal[0] = this->get_i();
     normal[1] = this->get_j();
     normal[2] = this->get_k();

     this->printOut();
}

void CrossMath::crossNormalize(double m, double n, double p){
     m/sqrt(m*m+n*n+p*p);
     n/sqrt(m*m+n*n+p*p);
     p/sqrt(m*m+n*n+p*p);
}

void CrossMath::printOut(){
    std::cout<<"CrossMath::frenetSerretFrame()  tangent  :  "
            <<this->get_tangent_i()<<" "<<this->get_tangent_j()<<" "<<this->get_tangent_k()<<" "<<this->get_tangent_i()/this->get_tangent_j()<<std::endl;
    std::cout<<"                                binormal :  "
            <<this->get_binormal_i()<<" "<<this->get_binormal_j()<<" "<<this->get_binormal_k()<<" "<<get_binormal_i()/get_binormal_j()<<std::endl;
    std::cout<<"                                normal   :  "
            <<this->get_normal_i()<<" "<<this->get_normal_j()<<" "<<this->get_normal_k()<<" "<<get_normal_i()/get_normal_j()<<std::endl;
}

double CrossMath::get_i(){
    return this->arry[0];
}
double CrossMath::get_j(){
    return this->arry[1];
}
double CrossMath::get_k(){
    return this->arry[2];
}

double CrossMath::get_tangent_i(){
    return this->tangent[0];
}
double CrossMath::get_tangent_j(){
    return this->tangent[1];
}
double CrossMath::get_tangent_k(){
    return this->tangent[2];
}

double CrossMath::get_normal_i(){
    return this->normal[0];
}
double CrossMath::get_normal_j(){
    return this->normal[1];
}
double CrossMath::get_normal_k(){
    return this->normal[2];
}

double CrossMath::get_binormal_i(){
    return this->binormal[0];
}
double CrossMath::get_binormal_j(){
    return this->binormal[1];
}
double CrossMath::get_binormal_k(){
    return this->binormal[2];
}
