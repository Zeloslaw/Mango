#ifndef ADDRESSFIELD_H
#define ADDRESSFIELD_H

#include <QtGui>

class AddressField : public QLineEdit
{
    Q_OBJECT

    public:
        AddressField();

    public slots:
        void isCleared();
        void initUrlField();
        void resetUrlField();

    signals:
        void cleared();

    protected:
        void resizeEvent(QResizeEvent *);

    private:
        QPushButton *clearButton;
        int frameWidth;
        QString cssStyle;
};

#endif // ADDRESSFIELD_H
