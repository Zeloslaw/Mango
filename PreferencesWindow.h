#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QtGui>

class PreferencesWindow : public QDialog
{
    Q_OBJECT

    public:
        PreferencesWindow(QWidget *parent = 0);

    private:
        QString checkHomePage();
        QString checkDefaultSearchEngine();
        QString checkDownloadPath();
        bool isZoomTextOnlyEnabled();
        bool isJsEnabled();
        bool isFlashEnabled();

    public slots:
        void chooseDirDownload();

        // Main slots
        void submitPreferences();

    private:
        QLineEdit *urlHomePage;
        QLineEdit *urlDownloadPath;
        QComboBox *searchEngineComboBox;
        QCheckBox *zoomCheckBox;
        QCheckBox *disableJsCheckBox;
        QCheckBox *disableFlashCheckBox;
};

#endif // PREFERENCESWINDOW_H
