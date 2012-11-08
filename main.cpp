#include <QApplication>
#include <QtGui>
#include <QtWebKit>
#include "BrowserApplication.h"

int main(int argc, char *argv[])
{
    BrowserApplication app(argc, argv);

    // Translation of the Qt strings in the system language
    QString locale = QLocale::system().name();
    QTranslator translator;
    //translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    translator.load(QString("qt_") + "en", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    // Cache folder
    QDir cacheDir(QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
    if (cacheDir.mkpath("."))
    {
        QWebSettings::setIconDatabasePath(cacheDir.path());
    }

    return app.exec();
}
