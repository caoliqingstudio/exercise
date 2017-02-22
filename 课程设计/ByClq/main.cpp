#include <QApplication>
#include <QCommandLineParser>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(sdi);
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("By CaoLiqing");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file(s) to open.");
    parser.process(app);

    MainWindow *mainWin = Q_NULLPTR;
    foreach (const QString &file, parser.positionalArguments()) {
        MainWindow *newWin = new MainWindow(file);
        newWin->tile(mainWin);
        newWin->show();
        mainWin = newWin;
    }

    if (!mainWin)
        mainWin = new MainWindow;
    mainWin->show();

    return app.exec();
}
