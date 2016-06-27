#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkInteractionStyle_AUTOINIT 1(vtkInteractionStyle)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)
#define vtkRenderingOpenGL_AUTOINIT 1(vtkRenderingOpenGL)
#define vtkRenderingFreeTypeOpenGL_AUTOINIT 1(vtkRenderingFreeTypeOpenGL)
#define vtkRenderingContext2D_AUTOINIT 1(vtkRenderingContextOpenGL)

#include <QApplication>
#include "MainWidget.h"
#include "ProjectionImpl.h"
#include "TestMath.h"
#include "SoftwareTool.h"
#include "May.h"
#include "CrossMath.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget mainWidget;
    mainWidget.show();
    return a.exec();
}


