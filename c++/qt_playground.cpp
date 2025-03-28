
#include <qt/QtWidgets/QStyleFactory>
#include <QtCore/QDebug>
#include <QtGui/QWindow>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGridLayout>
#include <QtGui/QGuiApplication>
#include <QtWidgets/QPushButton>
// #include <QPluginLoader>
// #include "/usr/include/qt/QtCore/5.15.2/QtCore/private/qglobal_p.h"
// #include <QtCore/private/qglobal_p.h>
// #include <QtThemeSupport/QtThemeSupport>

// #include <QtGui/private/qguiapplication_p.h>
// #include <QtGui/qpa/qplatformthemefactory_p.h>
// #include <QtGui/qpa/qplatformtheme.h>

/*
  clang++ qt_playground.cpp -I"/usr/include/qt/QtGui/5.15.2/QtGui" -I"/usr/include/qt/QtGui/5.15.2" -I"/usr/include/qt/QtCore/5.15.2" -I/usr/include/qt -I /usr/include/qt/QtCore -o build/qt_playground -lQt5Core -lQt5Widgets  -lQt5Gui
*/

int main( int argc, char** argv )
{
    auto output = QStyleFactory::keys();
    qDebug() << output;
    for (auto& x : output)
    {
        qDebug() << x;
    }

    QApplication main_application( argc, argv );
    auto widgets = main_application.allWidgets();
    // QWindow main_window( main_application.primaryScreen() );
    QDialog root_window;
    QFrame frame( &root_window);
    // root_window.setCentralWidget( &frame );
    frame.setFrameShape(QFrame::Box);
    frame.setFrameShadow(QFrame::Raised);
    frame.setLineWidth(2);
    frame.setFrameRect( QRect { 0, 0, 1280, 720 } );
    // root_window.setWindowTitle( "a" );
    root_window.resize( 1280, 720 );
    frame.resize( 1280, 720 );
    frame.show();
    // main_window.resize( 400, 400 );

    // main_window.create();
    root_window.show();
    root_window.show();
    QGridLayout button_grid( &frame );

    QPushButton button ("Hello world !");
    button_grid.addWidget( &button );
    button_grid.addWidget( &button );
    button_grid.addWidget( &button );
    button.show();

    QLabel *label = new QLabel( "This is inside the QFrame", &frame );
    label->move(20, 20);
    QFileDialog::Options flags;
    // flags |= QFileDialog::DontUseNativeDialog;
    QString fileName = QFileDialog::getOpenFileName(
        &frame,
        "Open Image", "/home/jana", "Image Files (*.png *.jpg *.bmp)",
        nullptr,
        0 );

    // QPlatformTheme* theme = QGuiApplicationPrivate::platformTheme();
    // qDebug() << QPlatformThemeFactory::keys();

    return main_application.exec();
}
