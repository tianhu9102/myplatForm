#include "CenterLineProcess.h"


//!---------------------------------------------------------------------------
/**
 * @brief CenterLineProcess::CenterLineProcess
 */
//!---------------------------------------------------------------------------
CenterLineProcess::CenterLineProcess()
{
    crosMs = new CrossMath;
}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLineProcess::referenceReader
//! \param referencePath
//!
void CenterLineProcess::referenceReader(QString referencePath){
    this->referencefilePath =referencePath;
    QFile referenceFilename(referencePath);
    if(!referenceFilename.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"sorry,can't open the file!"<<endl;
        return ;
    }
    int refercountpri = 0;

    //!  1.set coordinate x,y,z value
    while(!referenceFilename.atEnd()){
        QByteArray line=referenceFilename.readLine();
        QString str(line);
        QStringList parame=str.split(" ");
        //! axis_x,axis_y,axis_z values are set here
        CenterLinePoint *p = new CenterLinePoint();
        p->set_abscissa(parame[0].toDouble(0));
        p->set_ordinate(parame[1].toDouble(0));
        p->set_isometric(parame[2].toDouble(0));
        p->set_radius(parame[3].toDouble(0));

        vesselsPoints.append(p);
        refercountpri ++;
    }
    this->referencecount = refercountpri;
    std::cout<<"CenterLineProcess::referenceReader  1.set reference x y z successfully!  "<<"total point size: "<<vesselsPoints.length()<<std::endl;


    //!  2.set x_diff, y_diff, z_diff
    for(int cpt = 0;cpt < vesselsPoints.length();cpt++){
        if(cpt < vesselsPoints.length()-1){
            vesselsPoints.at(cpt)->set_xdiff(vesselsPoints.at(cpt+1)->get_abscissa() - vesselsPoints.at(cpt)->get_abscissa());
            vesselsPoints.at(cpt)->set_ydiff(vesselsPoints.at(cpt+1)->get_ordinate() - vesselsPoints.at(cpt)->get_ordinate());
            vesselsPoints.at(cpt)->set_zdiff(vesselsPoints.at(cpt+1)->get_isometric() - vesselsPoints.at(cpt)->get_isometric());
            vesselsPoints.at(cpt)->update();
        } else
            if(cpt = vesselsPoints.length()-1){
            vesselsPoints.at(cpt)->set_xdiff(vesselsPoints.at(cpt-1)->get_xdiff());
            vesselsPoints.at(cpt)->set_ydiff(vesselsPoints.at(cpt-1)->get_ydiff());
            vesselsPoints.at(cpt)->set_zdiff(vesselsPoints.at(cpt-1)->get_zdiff());
            vesselsPoints.at(cpt)->update();
        }
    }
    std::cout<< vesselsPoints.at(0)->get_xdiff()<<vesselsPoints.at(0)->get_ydiff()<<vesselsPoints.at(0)->get_zdiff()<<std::endl;

    std::cout<<"CenterLineProcess::referenceReader  2.set x_diff y_diff z_diff successfully!  "<<"total point size: "<<vesselsPoints.length()<<std::endl;

    //!  3.set u v w value
    //!  TODO...

}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLineProcess::getReferencecount
//!
int CenterLineProcess::getReferencecount(){
    return this->referencecount;    //get in method CenterLineProcess::referenceReader(QString referencePath)
}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLinePro   cess::GetFileName
//!
QString CenterLineProcess::GetFileName(){
    return this->referencefilePath;
}

//!---------------------------------------------------------------------------
//!
//! \brief CenterLineProcess::get_vesselsPoints
//!
QVector<CenterLinePoint*> CenterLineProcess::get_vesselsPoints(){
    return this->vesselsPoints;
}

