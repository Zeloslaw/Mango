#include "TabNav.h"

TabNav::TabNav() : QTabWidget()
{
    setTabsClosable(true);
    QString style = "QTabBar::tab:selected { margin-left: -2px; margin-right: -2px; } QTabBar::tab:first:selected { margin-left: 0; } QTabBar::tab:last:selected { margin-right: 0; } ";
    style += "QTabBar::tab:only-one { margin: 0; } QTabWidget::pane { border-top: 2px solid #C2C7CB; } QTabWidget::tab-bar { left: 5px; } ";
    style += "QTabBar::tab { font-size: 13px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); border: 1px solid #C4C4C3; border-bottom-color: #C2C7CB; border-top-left-radius: 4px; border-top-right-radius: 4px; min-width: 150px; padding: 5px; }";
    style += "QTabBar::tab:selected, QTabBar::tab:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #fafafa, stop: 0.4 #f4f4f4, stop: 0.5 #e7e7e7, stop: 1.0 #fafafa); } QTabBar::tab:selected { border-color: #9B9B9B; border-bottom-color: #C2C7CB; } QTabBar::tab:!selected { margin-top: 2px; }";
    setStyleSheet(style);
    setElideMode(Qt::ElideRight);
    setMovable(true);
    // New Tab button
    newTab = new QPushButton;
    newTab->setIcon(QIcon(QCoreApplication::applicationDirPath()+"/data/newTab.png"));
    newTab->setFlat(true);
    setCornerWidget(newTab);
}

QPushButton *TabNav::getButtonNewTab()
{
    return newTab;
}

// Events

void TabNav::keyPressEvent(QKeyEvent *event)
{
    QTabWidget::keyPressEvent(event);
}

