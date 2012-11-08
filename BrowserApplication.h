#ifndef BROWSERAPPLICATION_H
#define BROWSERAPPLICATION_H

#include <QtGui>
#include "MainWindow.h"

class BrowserApplication : public QApplication
{
    public:
        BrowserApplication();
        BrowserApplication(int argc, char *argv[]);
};

#endif // BROWSERAPPLICATION_H
