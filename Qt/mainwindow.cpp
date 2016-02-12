#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    debug = new QDebugStream(std::cout, ui->textEdit);
    configDir.setPath(configFilePath);

    QIcon icon("icon.png");
    this->setWindowIcon(icon);

    if(!controlKey.Init(controllerDB.toStdString()))
    {
        QMessageBox::critical(this, "Error", "Failed To Initialize ControlKey");
        throw std::exception();
    }

//Get input string list from platform to use for combo boxes
    QStringList list;
    QStringListModel *itemModel = new QStringListModel(this);

    list.push_back(QString::fromStdString("none"));
    for(auto &i: controlKey.platform.GetInputList())
    {
        list.append(QString::fromStdString(i));
    }

    itemModel->setStringList(list);

//Map key must match the SDL2 string names for buttons and axes
//however, the "+" and "-" on the end of the analogs is custom
    comboBoxMappings["a"] = ui->comboBox_a;
    comboBoxMappings["b"] = ui->comboBox_b;
    comboBoxMappings["x"] = ui->comboBox_x;
    comboBoxMappings["y"] = ui->comboBox_y;
    comboBoxMappings["leftshoulder"] = ui->comboBox_lshoulder;
    comboBoxMappings["rightshoulder"] = ui->comboBox_rshoulder;
    comboBoxMappings["leftstick"] = ui->comboBox_lstick;
    comboBoxMappings["rightstick"] = ui->comboBox_rstick;
    comboBoxMappings["dpup"] = ui->comboBox_dpup;
    comboBoxMappings["dpdown"] = ui->comboBox_dpdown;
    comboBoxMappings["dpleft"] = ui->comboBox_dpleft;
    comboBoxMappings["dpright"] = ui->comboBox_dpright;
    comboBoxMappings["start"] = ui->comboBox_start;
    comboBoxMappings["back"] = ui->comboBox_back;
    comboBoxMappings["guide"] = ui->comboBox_guide;
    comboBoxMappings["lefty-"] = ui->comboBox_leftyup;
    comboBoxMappings["lefty+"] = ui->comboBox_leftydown;
    comboBoxMappings["leftx-"] = ui->comboBox_leftxleft;
    comboBoxMappings["leftx+"] = ui->comboBox_leftxright;
    comboBoxMappings["righty-"] = ui->comboBox_rightyup;
    comboBoxMappings["righty+"] = ui->comboBox_rightydown;
    comboBoxMappings["rightx-"] = ui->comboBox_rightxleft;
    comboBoxMappings["rightx+"] = ui->comboBox_rightxright;
    comboBoxMappings["lefttrigger"] = ui->comboBox_ltrigger;
    comboBoxMappings["righttrigger"] = ui->comboBox_rtrigger;

    //Set the combobox model
    for(auto &i: comboBoxMappings)
    {
        i.second->setModel(itemModel);
    }

    //fresh start
    ResetOptions();
    on_pushButton_Refresh_clicked();
    UpdateConfigList();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MainLoop()));
    timer->start(0);
}

void MainWindow::MainLoop()
{
    //TODO: Better Loop

    static bool toggle = false;
    if(controlKey.controller.Quit() && !toggle)
    {
        toggle = true;
    }

    if(!controlKey.controller.Quit() && toggle)
    {
        toggle = false;
        controlKey.controller.sendEvents = !controlKey.controller.sendEvents;
        controlKey.platform.ClearEvents();
    }

    controlKey.Update();
    SDL_Delay(8);//Works a lot better than qtimer delay
}

void MainWindow::UpdateConfigList()
{
    //save current text index on the filename combobox
    QString cur = ui->comboBox_configfiles->currentText();

    configDir.refresh();
    QStringList qlist = configDir.entryList();

    ui->comboBox_configfiles->clear();
    ui->comboBox_configfiles->addItem("");
    for(auto &i : qlist)
    {
        //Add only ".conf" files and ignore the extension name in the combobox
        if(i.endsWith(".conf"))
            ui->comboBox_configfiles->addItem(i.split(".").at(0));
    }

    //Set the combobox index to the saved qstring from earlier
    ui->comboBox_configfiles->setCurrentText(cur);
}

void MainWindow::ResetOptions()
{
    controlKey.ClearConfig();

    //default positions
    for(auto &i : comboBoxMappings)
    {
        i.second->setCurrentIndex(0);
    }

    ui->comboBox_mouselook->setCurrentIndex(1);
    ui->spinBox_leftAnalogDZ->setValue(25);
    ui->spinBox_rightAnalogDZ->setValue(25);
    ui->spinBox_triggerDZ->setValue(10);
    ui->doubleSpinBox_mouseSensitivity->setValue(1);
    ui->checkBox_invertmouse->setChecked(false);
    ui->checkBox_dblscroll->setChecked(false);
}

QString MainWindow::GetFilePath()
{
    return configDir.path() + "/" + ui->comboBox_configfiles->currentText() + ".conf";
}

bool MainWindow::IsNameVaild()
{
    QString name = ui->comboBox_configfiles->currentText();
    std::size_t found = name.toStdString().find_first_not_of(validChars);

    if(name.isEmpty())
    {
        QMessageBox::critical(this, "Invalid File Name", "Your File Name Is Empty");
        return false;
    }

    if(name.startsWith(" ") || name.endsWith(" "))
    {
        QMessageBox::critical(this, "Invalid File Name", "File Names May Not Start Or End With A Blank Space");
        return false;
    }

    if(found != std::string::npos)
    {
        QMessageBox::critical(this, "Invalid File Name", "Your File Name Contains An Invalid Character " + QString(name.at(found)));
        return false;
    }

    return true;
}

void MainWindow::on_pushButton_save_clicked()
{
    //Check If The Name Is Valid
    if(!IsNameVaild())
        return;

    QString fp = GetFilePath();
    QFileInfo file(fp);
    // check if file exists and if yes: Is it really a file and not a directory?
    if(file.exists() && file.isFile())
    {
        QString text = "\"" + ui->comboBox_configfiles->currentText() + "\" Already Exists: Do You Want To Overwrite This File?";
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Overwrite Config File?", text);

        if(reply != QMessageBox::StandardButton::Yes)
            return;

        std::cout << "Going to overwrite " << fp.toStdString() << std::endl;
    }

    std::cout << "Saving Config " << fp.toStdString() << std::endl;

    std::ofstream oFile;
    oFile.open(fp.toStdString());

    if(oFile.is_open())
    {
        std::map<std::string, float> config;
        config["doublescroll"] = (int)ui->checkBox_dblscroll->isChecked();
        config["mousesensitivity"] = ui->doubleSpinBox_mouseSensitivity->value();
        config["leftaxisdz"] = ui->spinBox_leftAnalogDZ->value()/100.f;
        config["rightaxisdz"] = ui->spinBox_rightAnalogDZ->value()/100.f;
        config["triggerdz"] = ui->spinBox_triggerDZ->value()/100.f;
        config["mouselookanalog"] = ui->comboBox_mouselook->currentIndex();

        oFile << "[Config]" << std::endl;
        for(auto &i : config)
        {
            oFile << i.first << " " << i.second << std::endl;
        }

        oFile << "[Mappings]" << std::endl;
        for(auto &i : comboBoxMappings)
        {
            if(i.second->currentText() != "none" && i.second->isEnabled())
            {
                oFile << i.first << " " << i.second->currentText().toStdString() << std::endl;
            }
        }
        oFile.close();
        controlKey.LoadConfig(fp.toStdString());
    }

    else
        QMessageBox::critical(this, "Error", "Failed To Save File");

    UpdateConfigList();
}

void MainWindow::on_comboBox_configfiles_currentIndexChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        return;

    //Clear previous config
    ResetOptions();
    controlKey.LoadConfig(GetFilePath().toStdString());

    //update the combo boxes to match our opened config
    for(auto &i: controlKey.controller.GetAllMappings())
    {
        if(comboBoxMappings.find(i.first) != comboBoxMappings.end())
            comboBoxMappings[i.first]->setCurrentText(QString::fromStdString(i.second));
    }

    ui->spinBox_leftAnalogDZ->setValue(controlKey.controller.leftAxisDZ*100.f);
    ui->spinBox_rightAnalogDZ->setValue(controlKey.controller.rightAxisDZ*100.f);
    ui->spinBox_triggerDZ->setValue(controlKey.controller.triggerDZ*100.f);

    ui->comboBox_mouselook->setCurrentIndex(controlKey.controller.mouseLookAnalog);
    ui->checkBox_dblscroll->setChecked(controlKey.platform.doubleScroll);
    ui->doubleSpinBox_mouseSensitivity->setValue(controlKey.platform.mouseSensitivity);
}

void MainWindow::on_pushButton_new_clicked()
{
    ui->comboBox_configfiles->setCurrentIndex(0);
    ResetOptions();
}

void MainWindow::on_pushButton_delete_clicked()
{
    QFileInfo info(GetFilePath());
    if(!info.exists() && !info.isFile())
        return;

    QString text = "Are You Sure You Want To Delete \"" + ui->comboBox_configfiles->currentText() + "\"";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Config File?", text);

    if(reply != QMessageBox::StandardButton::Yes)
        return;

    std::cout << "Deleting " << GetFilePath().toStdString() << std::endl;

    QFile file(GetFilePath());
    file.remove();
    UpdateConfigList();
}

void MainWindow::on_pushButton_Refresh_clicked()
{
    ui->comboBox_Controllers->clear();

    for(auto &i : Controller::GetContollerNames())
    {
        ui->comboBox_Controllers->addItem(QString::fromStdString(i));
    }
}

void MainWindow::on_comboBox_Controllers_currentIndexChanged(int index)
{
    controlKey.controller.Open(index);
}

void MainWindow::on_comboBox_mouselook_currentIndexChanged(int index)
{
    if(index == ANALOG_LEFT)
    {
        ui->comboBox_leftxleft->setEnabled(false);
        ui->comboBox_leftxright->setEnabled(false);
        ui->comboBox_leftyup->setEnabled(false);
        ui->comboBox_leftydown->setEnabled(false);

        ui->comboBox_rightxleft->setEnabled(true);
        ui->comboBox_rightxright->setEnabled(true);
        ui->comboBox_rightyup->setEnabled(true);
        ui->comboBox_rightydown->setEnabled(true);
    }

    if(index == ANALOG_RIGHT)
    {
        ui->comboBox_leftxleft->setEnabled(true);
        ui->comboBox_leftxright->setEnabled(true);
        ui->comboBox_leftyup->setEnabled(true);
        ui->comboBox_leftydown->setEnabled(true);

        ui->comboBox_rightxleft->setEnabled(false);
        ui->comboBox_rightxright->setEnabled(false);
        ui->comboBox_rightyup->setEnabled(false);
        ui->comboBox_rightydown->setEnabled(false);
    }
}

void MainWindow::on_textEdit_textChanged()
{
    std::ofstream logFile("log.txt");
    logFile << ui->textEdit->toPlainText().toStdString();
}

MainWindow::~MainWindow()
{
    delete debug;
    delete ui;
}
