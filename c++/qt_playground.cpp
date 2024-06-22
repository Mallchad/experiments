
#include <qt/QtWidgets/QStyleFactory>
#include <QtCore/QDebug>
#include <QtGui/QWindow>
#include <QtWidgets/QApplication>
#include <QtGui/QGuiApplication>
#include <QtWidgets/QPushButton>
#include "QtGui/qpa/qplatformthemefactory_p.h"

// clang++ /local/repos/experiments/qt_playground.cpp -I /usr/include/qt -o build/qt_playground -lQt5Core -lQt5Widgets && build/qt_playground
// clang++ /local/repos/experiments/qt_playground.cpp -I /usr/include/qt -o build/qt_playground -lQt5Core -lQt5Widgets -l Qt5Gui -I/usr/include/qt/QtGui/5.15.2/ -I/usr/include/qt/QtCore/5.15.2/ -I/usr/include/qt/QtCore

int main( int argc, char** argv )
{
    auto output = QStyleFactory::keys();
    // qDebug() << output;
    // for (auto& x : output)
    // {
    //     qDebug() << x;
    // }

    QApplication main_application( argc, argv );
    // QWindow main_window( main_application.primaryScreen() );

    // main_window.create();
    // QPushButton button ("Hello world !");
    // button.show();
    qDebug() << QPlatformThemeFactory::keys();

    return main_application.exec();
}
