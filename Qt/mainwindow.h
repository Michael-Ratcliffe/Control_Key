#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QFile>
#include <QStringListModel>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>
#include <SDL2/SDL.h>
#include <map>
#include <fstream>
#include "qdebugstream.h"
#include "../src/controlkey.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void MainLoop();
    void UpdateConfigList();
    void ResetOptions();
    QString GetFilePath();
    bool IsNameVaild();

    void on_pushButton_save_clicked();
    void on_comboBox_configfiles_currentIndexChanged(const QString &arg1);
    void on_pushButton_new_clicked();
    void on_pushButton_Refresh_clicked();
    void on_comboBox_Controllers_currentIndexChanged(int index);
    void on_comboBox_mouselook_currentIndexChanged(int index);
    void on_pushButton_delete_clicked();
    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QDebugStream *debug;
    QDir configDir;
    ControlKey controlKey;
    std::map<std::string, QComboBox*> comboBoxMappings;
    std::string validChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_ ";
    const QString configFilePath = "config";
    const QString controllerDB = configFilePath + "/gamecontrollerdb.txt";
};

#endif // MAINWINDOW_H
