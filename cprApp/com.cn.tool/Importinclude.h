#ifndef IMPORTINCLUDE_H
#define IMPORTINCLUDE_H

//! ******************************************************************
//!  Readme   to be imported in some other classes easily
//!  @yue du  2016/3/30
//! ******************************************************************

#include <QtSql/QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QWidget>
#include <qdebug.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QPalette>
#include <QTimer>
#include <vtkSQLDatabase.h>
#include <vtkSQLQuery.h>
#include <vtkSQLiteDatabase.h>
#include <vtkSQLiteQuery.h>
#include <vtkArrowSource.h>
#include <vtkGlyph2D.h>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QtGui>
#include <vtkXYPlotActor.h>
#include <vtkChartXY.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkPen.h>
#include <vtkFloatArray.h>
#include <vtkTable.h>
#include <vtkPlotPoints.h>

#include <vtkCubeAxesActor2D.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackball.h>
#include <vtkSimplePointsReader.h>
#include <vtkWarpScalar.h>
#include <vtkAxisActor2D.h>
#include <vtkMatrix4x4.h>
#include <vtkVolumeTextureMapper2D.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkPlaneSource.h>
#include <vtkJPEGReader.h>
#include <vtkImageShrink3D.h>
#include <vtkImageMagnify.h>
#include <vtkPointData.h>

#include  <QSplashScreen>
#include <QPixmap>
#include <QDateTime>
#include <QTextEdit>
#include <QCoreApplication>
#include <QFileInfo>
#include <QFileInfoList>

#include <vtkWindowLevelLookupTable.h>
#include <vtkProbeFilter.h>
#include <vtkSplineFilter.h>

#include <vtkImageReslice.h>
#include <vtkImageMapToColors.h>
#include <vtkSphere.h>

//! in CenterLineProcess.cpp
#include <QFile>
#include <QByteArray>
#include <QStringList>
#include <QDebug>
#include <QVector>
#include <QDir>
#include <QStringList>
#include <QtCore/qmath.h>
#include <qmath.h>



//! in CenterLineVisualization.cpp
#include <QVTKWidget.h>
#include <vtkPoints.h>
#include <vtkPolyVertex.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <QFileDialog>
#include <vtkPlane.h>
#include <vtkSCurveSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricSpline.h>
#include <vtkCamera.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRibbonFilter.h>
#include <vtkRegularPolygonSource.h>
#include <vtkMath.h>
#include <time.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkCylinderSource.h>
#include <vtkTupleInterpolator.h>

//! in VolumeVisualization.cpp
#include <vtkInformation.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkMetaImageReader.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkPolyDataReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkInteractorStyleImage.h>

//! in StraightedVisualization.cpp
#include <vtkSplineDrivenImageSlicer.h>
#include <vtkImageAppend.h>
#include <vtkExtractVOI.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor2D.h>
#include <vtkSmartPointer.h>
#include <vtkImageShiftScale.h>
#include <vtkCutter.h>
#include <vtkTextActor.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>

//! in AnalyseWidget.cpp
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPlaneWidget.h>
#include "vtkMath.h"
#include <QLineEdit>
#include <QSlider>
#include <QDialog>
#include <QCheckBox>
#include <QSpinBox>
#include <QStackedWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QScrollBar>
#include <QAbstractSlider>
#include <QAbstractSpinBox>
#include <vtkImageCacheFilter.h>
#include <vtkImageCast.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkVersion.h>
#include <vtkCellData.h>
#include <vtkUnsignedCharArray.h>
#include <vtkDoubleArray.h>
#include <vtkTransform.h>
#include <vtkLabeledDataMapper.h>
#include <vtkLabelPlacementMapper.h>
#include <vtkConeSource.h>



//! in BasicParameters.cpp
#include <QTableWidget>
#include <QHeaderView>
#include <QColor>
#include <QTableWidgetItem>

//! in MainWidget.cpp
#include <QFileInfo>
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMouseEvent>
#include <QMenu>
#include <QTabWidget>
#include <QSpacerItem>
#include <QLCDNumber>
#include <QTime>
#include <QPushButton>
#include <QLabel>


#include <vtkImageMandelbrotSource.h>


class Importinclude
{
public:
    Importinclude();
};

#endif // IMPORTINCLUDE_H
