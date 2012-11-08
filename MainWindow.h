#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWebKit>
#include <QFile>
#include "TabNav.h"
#include "WebPage.h"
#include "AddressField.h"
#include "AboutMango.h"
#include "PreferencesWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        QIcon getFavicon();
        void showWindowFindText();
        void hideWindowFindText();

    private:
        // GUI Methods
        void createActions();
        void createMenu();
        void createToolbar();
        void createStatusBar();
        void getPreferences();
        void prepareButtons();

        // Usefull methods
        QWidget *createNewTabWeb(QString url = "");
        WebPage *currentPage();

        // Events
        void keyPressEvent(QKeyEvent *event);

    public slots:
        void getSourceCode();
        void toggleFullScreen();
        void openLink(QUrl url);
        void saveCurrentPage();

        // Edit slots
        void copy();
        void paste();
        void cut();
        void selectAllWebView();
        void toggleWindowFindText();
        void highlightText();

        // Browsing slots
        void newTab(QString url = "");
        void closeTab(int index = -1);
        void back();
        void forward();
        void stop();
        void reload();
        void home();

        // Refresh slots
        void loadPage(QString url = "");
        void switchTabs(int index);

        void changeTitle(const QString & fullTitle);
        void changeUrl(const QUrl & url);
        void changeIcon();

        // Zoom
        void zoom();
        void unZoom();
        void setDefaultZoom();

        // Preferences
        void showPreferences();
        void togglePrivateBrowsing();

        void printPage();
        void printPreview();

    private slots:
        void loadBegin();
        void loading(int pourcentage);
        void loadComplete(bool ok);
        void showLink(const QString & link, const QString & title, const QString & textContent);

        void about();

        void showSourceCode();

        // Download
        void downloadFileAuto(QNetworkReply *reponse);
        void downloadFinished();
        void cancelDownload();
        void downloading(qint64 downloaded, qint64 total);

        // Error handler
        void checkError(QNetworkReply *reply);

    private:
        TabNav *tabs;

        // File actions
        QAction *actionNewTab;
        QAction *actionCloseTab;
        QAction *actionPrintPreview;
        QAction *actionPrintPage;
        QAction *actionExit;
        QAction *actionSaveCurrentPage;

        // Edit actions
        QAction *actionFind;
        QAction *actionCut;
        QAction *actionCopy;
        QAction *actionPaste;
        QAction *actionSelectAll;
        QAction *actionHighlighText;

        // Browser actions
        QAction *actionBack;
        QAction *actionForward;
        QAction *actionStop;
        QAction *actionReload;
        QAction *actionHome;
        QAction *actionGo;
        QAction *actionSourceCode;

        // View actions
        QAction *actionZoom;
        QAction *actionUnZoom;
        QAction *actionFullScreen;
        QAction *actionDefaultZoom;

        // Tools actions
        QAction *actionPreferences;
        QAction *actionPrivateBrowsing;

        // ? Actions
        QAction *actionAbout;
        QAction *actionAboutQt;


        // Preferences        
        QString fileHomePage;
        QString fileSearchEngine;
        QString fileDownloadPath;
        bool isZoomEnabled;
        bool isFlashEnabled;
        bool isJsEnabled;

        AddressField *addressField;
        AboutMango *aboutWindow;
        QProgressBar *progressionBar;
        QLineEdit *findTextField;
        QPushButton *buttonSubmitFind;
        QLabel *findLabel;
        QPushButton *nothingFound;
        QLabel *privateBrowsingIcon;

        // Download
        QFile fileToDownload;
        QNetworkReply *reply;
        QProgressDialog *downloadDialog;
        QString downloadedFileName;
        bool isDownloading;
        bool hasCanceledDownload;
};

#endif
