#include "SoftwareTool.h"

SoftwareTool::SoftwareTool()
{
    this->initVariable();
   // this->displaySplashScreen();
    this->connectDataBase();
}

void SoftwareTool::initVariable(){
    QPixmap pixmap(":/images/splash.png");
    splashscreen = new QSplashScreen(pixmap);
    splashscreen->setFixedSize(600,35);
    splashscreen->move(450,430);
    splashFont.setFamily("Arial");
    splashFont.setBold(true);
    splashFont.setPixelSize(28);
    splashFont.setStretch(125);
    topRight = Qt::AlignCenter;
    dateTime = QDateTime::currentDateTime();

//    QApplication::addLibraryPath("D:\\windowsQt\\5.5\\msvc2013_64\\plugins\\sqldrivers\\qsqlmysql.dll");
//    QApplication::addLibraryPath(" C:\\Program Files (x86)\\MySQL\\MySQL Connector C 6.1\\lib\\libmysql.dll");
    drivers = QSqlDatabase::drivers();
    db=QSqlDatabase::addDatabase("QSQLITE");

}

void SoftwareTool::connectDataBase(){

    qDebug()<<"drivers:"<<drivers;

    db.setHostName("duyue");
    db.setDatabaseName("imageprocess.db");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open()){
        // QMessageBox::warning(this,"warning!","failure");
        std::cout<<"SoftwareTool::connectDataBase()      failure connect database!"<<std::endl;

    }else{
        std::cout<<"SoftwareTool::connectDataBase()     success connect database!"<<std::endl;

        QSqlQuery query(db);
        query.exec("create table patient(id int primary key,name varchar(20),sex varchar(20))");
        query.exec("insert into patient values(0,'宋小宝','male')");
        query.exec("insert into patient values(1,'陈世美','male')");
        query.exec("insert into patient values(2,'潘金莲','female')");
        query.exec("insert into patient values(3,'张三','male')");
        query.exec("insert into patient values(4,'李四','male')");
        query.exec("insert into patient values(5,'赵钱','male')");
        query.exec("insert into patient values(6,'孙俪','female')");

        query.exec("select * from patient");
        while(query.next()){
            int value0 = query.value(0).toInt();
            QString value1 = query.value(1).toString();
            QString value2 = query.value(2).toString();
            qDebug()<<value0<<value1<<value2;
        }
    }
}

void SoftwareTool::displaySplashScreen(){
    splashscreen->show();
    splashscreen->setFont(splashFont);

    QString messageStylesheet("welcome to cpr platform!");
    splashscreen->showMessage(messageStylesheet,topRight,Qt::green);

    QDateTime now;
    do{
        now = QDateTime::currentDateTime();
    }while(dateTime.secsTo(now)<=1);//delay six seconds
}

QSplashScreen *SoftwareTool::get_splashscreen(){
   return this->splashscreen;
}
