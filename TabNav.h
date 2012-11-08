#ifndef TABNAV_H
#define TABNAV_H

#include <QtGui>

class TabNav : public QTabWidget
{
    public:
        TabNav();
        QPushButton *getButtonNewTab();

        // Events
        void keyPressEvent(QKeyEvent *event);

    private:
        QPushButton *newTab;
};

#endif // TABNAV_H
