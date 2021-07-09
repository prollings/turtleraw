// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "main_window.h"
#include "hella.h"

#include <QApplication>

namespace turtleraw {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_toolBar = new QToolBar(this);
    {
        m_toolBar->setObjectName("WindowToolBar");
        // Fixed to top
        m_toolBar->setFloatable(false);
        m_toolBar->setMovable(false);

        // Fill the toolbar with actions
        fillToolBar();
    }
    addToolBar(Qt::TopToolBarArea, m_toolBar);

    setCentralWidget(createLayout());
}

MainWindow::~MainWindow() {
}

void MainWindow::createToolBarButton(QPushButton *btn, QToolBar *tb, const QString &shortcut, const QString &tipText) {
    tb->addWidget(btn);
    btn->setShortcut(QKeySequence(shortcut));
    if (!shortcut.isEmpty())
        btn->setToolTip(tipText + " (" + QKeySequence(btn->shortcut()).toString() + ")");
    else
        btn->setToolTip(tipText);
}

void MainWindow::fillToolBar() {
    m_previousBtn = new QPushButton("\uE5C4", m_toolBar);
    createToolBarButton(m_previousBtn, m_toolBar, "Ctrl+Left", tr("Previous"));
    m_toolBarBtns.append(m_previousBtn);

    m_nextBtn = new QPushButton("\uE5C8", m_toolBar);
    createToolBarButton(m_nextBtn, m_toolBar, "Ctrl+Right", tr("Next"));
    m_toolBarBtns.append(m_nextBtn);

    m_metaDataBtn = new QPushButton("\uE88E", m_toolBar);
    createToolBarButton(m_metaDataBtn, m_toolBar, "Alt+M", tr("Show metadata"));
    m_toolBarBtns.append(m_metaDataBtn);

    m_toolBar->addSeparator();

    m_deleteBtn = new QPushButton("\uE872", m_toolBar);
    createToolBarButton(m_deleteBtn, m_toolBar, "Del", tr("Delete"));
    m_toolBarBtns.append(m_deleteBtn);

    QWidget *_toolBarSpacer = new QWidget(m_toolBar);
    _toolBarSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_toolBar->addWidget(_toolBarSpacer);

    m_menuBtn = new QPushButton("\uE5D2", m_toolBar);
    createToolBarButton(m_menuBtn, m_toolBar, "", tr("Menu"));
    m_toolBarBtns.append(m_menuBtn);
    {
        m_headMenu = new QMenu(m_toolBar);
        m_helpMenu = m_headMenu->addMenu(tr("Help"));
        m_menuBtn->setMenu(m_headMenu);
    }

    foreach(QPushButton *tbBtn, m_toolBarBtns) {
        tbBtn->setObjectName("ToolBarButton");
        tbBtn->setFont(QFont("Material Design Sharp", 16));
    }
}

QWidget* MainWindow::createLayout() {
    m_centralWidget = new QWidget(this);

    m_mainLayout = new QVBoxLayout(m_centralWidget);
    {
        m_mainLayout->setMargin(0);
        m_mainLayout->setSpacing(0);
    }

    // todo, we currently show an empty placeholder
    QWidget *__p =  new QWidget;
    __p->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_showFolderBrowserBtn = new QPushButton(m_centralWidget);
    {
        connect(m_showFolderBrowserBtn, SIGNAL(clicked()), this, SLOT(onShowFolderBrowserBtn_Clicked()));
        m_showFolderBrowserBtn->setObjectName("ShowFolderBrowserButton");
        m_showFolderBrowserBtn->setToolTip(tr("Display folder contents"));
        // Initial state, folder browser not shown.
        m_showFolderBrowserBtn->setFont(QFont("Material Design Sharp", 16));
        m_showFolderBrowserBtn->setText("\uE5CE");
        m_folderBrowserShown = false;
    }

    m_mainLayout->addWidget(__p);
    m_mainLayout->addWidget(m_showFolderBrowserBtn);

    if (!folderBrowserScroll)
        folderBrowserScroll = new QScrollArea(m_centralWidget);
    if (!folderBrowserView)
        folderBrowserView = new FolderBrowser(m_centralWidget);
    folderBrowserScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    folderBrowserScroll->setStyleSheet("background-color: rgb(60, 60, 60);");
    folderBrowserScroll->setWidget(folderBrowserView);

    // Not shown by default.
    m_mainLayout->addWidget(folderBrowserScroll);
    folderBrowserScroll->setMaximumHeight(0);

    m_centralWidget->setLayout(m_mainLayout);
    return m_centralWidget;
}

void MainWindow::onShowFolderBrowserBtn_Clicked() {
    if (!m_folderBrowserShown) {
        propAnimation(folderBrowserScroll, "maximumHeight", 100, 0, 230);
        m_folderBrowserShown = true;
        m_showFolderBrowserBtn->setText("\uE5CF");
    } else {
        propAnimation(folderBrowserScroll, "maximumHeight", 100, 230, 0);
        m_folderBrowserShown = false;
        m_showFolderBrowserBtn->setText("\uE5CE");
    }
}

} // namespace