#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about())); //Connects buttons and actions to slots
    connect(ui->pushButtonDisplayReport, SIGNAL(clicked()), this, SLOT(displayReport()));
    connect(ui->pushButtonSave, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newReport()));

    comboBox(); //Applies attributes defined in comboBox function
}

void MainWindow::comboBox()
{
    //Adds items to favorite color drop down menu
    ui->colorComboBox->addItem("Red");
    ui->colorComboBox->addItem("Blue");
    ui->colorComboBox->addItem("Green");
    ui->colorComboBox->addItem("Purple");
    ui->colorComboBox->addItem("Pink");
    ui->colorComboBox->addItem("Yellow");
    ui->colorComboBox->addItem("Orange");
}

void MainWindow::newReport() //Overwrites existing data stored in surveydata file
{
    QMessageBox::StandardButton reply; //Warns user about deletion via messagebox
    reply = QMessageBox::question(this,"Warning",
                          "Are you sure you want to clear all current records?",
                          QMessageBox::Yes | QMessageBox::No );
    if(reply == QMessageBox::Yes)
    {
    QString filename = ("/surveydata");     //Users file path for surveydata
    QString dir = QDir::currentPath() + filename;
    QFile file(dir);
   if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
   QMessageBox::warning(this, tr("Warning"),
                        tr("File: surveydata is missing from root dir")
                        .arg(filename));
   statusBar()->showMessage(tr("Cannot find file"), 2000);
   return;
   }
   statusBar()->showMessage(tr("Records cleared..."), 2000);
    }
}

void MainWindow::displayReport() //Opens DataTable and displays surveydata
{
    showReport = new DataTable(this);
    showReport->show();
}


void MainWindow::save() //Appends newely entered data to surveydata file
{
    QString filename = ("/surveydata");     //Users file path for surveydata
    QString dir = QDir::currentPath() + filename;
    QFile file(dir);
    if (!file.open(QIODevice::Append|QIODevice::Text))
    {
            QMessageBox::warning(this, tr("Warning"),
                                    tr("Save failed")
                                    .arg(filename));
            statusBar()->showMessage(tr("Save failed..."), 2000);
            return;
            //If surveydata can't be found in specified filepath, the user is informed via message box and status bar that the save has failed
    }

   if(ui->firstNameEdit->text().isEmpty()) //Checks that data was actually entered
   {
       QMessageBox::warning(this, "Warning", "You must enter a first name"); //User is will receive prompt to enter data if none is found
       return;
   }

   if (ui->lastNameEdit->text().isEmpty())
   {
           QMessageBox::warning(this, "Warning", "You must enter a last name");
           return;
   }

   if (ui->ageSpinBox->text() == "0")
    {
               QMessageBox::warning(this, "Warning", "You must enter an age > than 0");
               return;
           }

    QTextStream out(&file); //User data is sent out to surveydata file. Each attribute is seperated by ',' and each entry is seperated by a new line.
    out << ui->firstNameEdit->text() << ",";
    out << ui->lastNameEdit->text() << ",";
    out << ui->ageSpinBox->text() << ",";
    out << ui->colorComboBox->currentText() << "," << endl;
    statusBar()->showMessage(tr("Record Saved..."), 2000); //User is informed via status bar that the save was successful
    file.close();

}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("Mycoal Campo -- June 9, 2015"));
}


MainWindow::~MainWindow()
{
    delete ui;
}

