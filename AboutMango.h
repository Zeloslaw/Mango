#ifndef ABOUTMANGO_H
#define ABOUTMANGO_H

#include <QtGui>

class AboutMango : public QDialog
{
    public:
        AboutMango(QWidget *parent = 0);
        QLabel *getLabelAboutMango();

    private:
        QPushButton *close;
        QLabel *aboutMango;
};

#endif // ABOUTMANGO_H
