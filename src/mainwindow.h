#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include "datatable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void about();
    void displayReport();
    void save();
    void newReport();
    void comboBox();

private:
    Ui::MainWindow *ui;
    DataTable *showReport;

};


#endif // MAINWINDOW_H
