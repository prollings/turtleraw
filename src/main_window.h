// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QPointer>
#include <QStringList>

#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QLabel>

#include <QVBoxLayout>

#include <QScrollArea>
#include <QPushButton>

#include "image_viewer.h"
#include "settings.h"
#include "settings_dialog.h"
#include "folder_browser.h"

#include "tr_image.h"

namespace turtleraw {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void create();

    QToolBar *m_toolBar;

    QPointer<ImageViewerWidget> m_imageViewerWidget;

    QPointer<QScrollArea> folderBrowserScroll;
    QPointer<FolderBrowser> folderBrowserView;
    bool m_folderBrowserShown;

    void carrySettings(Settings *s) {
        m_settings = s;
    }

    // No inline function because we need to check if we got a valid path.
    void checkArguments(const QStringList &l);

    void fillInformativeLabels(TRImage img);
    
protected:
    TRImage m_currentImage;

    // Toolbar buttons
    void createToolBarButton(QPushButton *btn, QToolBar *tb, const QString &shortcut, const QString &tipText, bool checkable);
    void createMenuAction(QAction *act, QMenu *m, const QString &shortcut, bool checkable, bool enabledByDefault);
    QPushButton *m_previousBtn;
    QPushButton *m_nextBtn;
    QPushButton *m_metaDataBtn;
    QPushButton *m_deleteBtn;

    QLabel *m_pathLbl;
    QLabel *m_mimeTypeLbl;
    QLabel *m_lastModifiedLbl;

    QPushButton *m_scriptsBtn;
    QPushButton *m_menuBtn;
    QMenu *m_menu;
    
    QMenu *m_fileMenu;
    QAction *m_closeAction;

    QMenu *m_editMenu;
    QAction *m_editPreferencesAction;
    
    QMenu *m_viewMenu;
    QMenu *m_toolsMenu;
    QMenu *m_helpMenu;
    // todo: logoBtn?
    QList<QPushButton*> m_toolBarBtns;
    void fillToolBar();

    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_showFolderBrowserBtn;

    QWidget* createLayout();

    Settings *m_settings;
    QPointer<SettingsDialog> settingsDlg;

    QStringList m_startupArguments;
    QString m_startupImagePath;

private:
    QStringList m_args;

public slots:
    void onCloseAction_Triggered();

    void onShowFolderBrowserBtn_Clicked();
    void settingsDialogRequired();
};

} // namespace