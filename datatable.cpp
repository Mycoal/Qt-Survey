#include <QtWidgets>

#include "datatable.h"
#include "ui_datatable.h"

DataTable::DataTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataTable)
{
    ui->setupUi(this);
    setupModal();
    setupView();
    //Setup Ui and apply attributes defined in setupModal and setupView functions

    QString filename = ("/surveydata");     //Users file path for surveydata
    QString dir = QDir::currentPath() + filename;
    openFile(dir); //Users file path for surveydata
    //Opens table data file
}

void DataTable::setupView() //Table view attributes
{
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->setEditTriggers(0); //Disables editing of data from table
    tableView->verticalHeader()->setVisible(false); // Hides vertical headers (default would be numbered rows)
    tableView->setAutoScrollMargin(1); //Enables auto scroll
    tableView->setFixedWidth(450); //Applies a set width to table
    tableView->setFixedHeight(350); // Applies a set height to table

    setWindowTitle(tr("Survey Data")); //Applies window title
    this->setFixedSize(450, 350); //Apples a fixed size to window
    setCentralWidget(tableView); //Sets the given widget to be the Main Window's central widget
}

void DataTable::setupModal() //Table model attributes
{
    model = new QStandardItemModel(10,4,this);
    model->setHeaderData(0, Qt::Horizontal, tr("First Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Last Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Age"));
    model->setHeaderData(3, Qt::Horizontal, tr("Favorite Color"));
}

void DataTable::openFile(const QString &path) //Opens file and reads in data to specifed rows
{
    QString fileName;
    fileName = path;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) //Checks if surveydata is being read
        QMessageBox::warning(this, tr("Warning"),
                             tr("Failed to open ")
                             .arg(fileName));
        statusBar()->showMessage(tr("Open file failed..."), 2000);

    QTextStream stream(&file);
    QString line;

    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex()); //Removes excess rows

    int row = 0;
    do {
        line = stream.readLine();
        if (!line.isEmpty()) {
            model->insertRows(row, 1, QModelIndex());

            QStringList pieces = line.split(",", QString::SkipEmptyParts); //Strings are split into pieces by ','
            model->setData(model->index(row, 0, QModelIndex()), //Reads data pieces into given row
                           pieces.value(0));
            model->setData(model->index(row, 1, QModelIndex()),
                           pieces.value(1));
            model->setData(model->index(row, 2, QModelIndex()),
                           pieces.value(2));
            model->setData(model->index(row, 3, QModelIndex()),
                           pieces.value(3));
            model->setData(model->index(row, 3, QModelIndex()),
                           QColor(pieces.value(3)), Qt::DecorationRole);
            row++;
        }
    } while (!line.isEmpty());

    file.close();
    statusBar()->showMessage(tr("Loaded %1").arg(fileName), 2000); //Success feedback for user
}


DataTable::~DataTable()
{
    delete ui;
}
