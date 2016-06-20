#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QMainWindow>


namespace Ui {
class DataTable;
}

class DataTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataTable(QWidget *parent = 0);
    ~DataTable();

private:
    Ui::DataTable *ui;
    QAbstractItemModel *model;

private slots:
    void openFile(const QString &path = QString());
    void setupModal();
    void setupView();
};

#endif // NEWWINDOW_H
