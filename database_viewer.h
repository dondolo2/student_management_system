#ifndef DATABASE_VIEWER_H
#define DATABASE_VIEWER_H

#include <QWidget>
#include <QSqlTableModel>

class QTabWidget;
class QTableView;
class QPushButton;

class DatabaseViewer : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseViewer(QWidget *parent = nullptr);
    static void displayDatabaseViewer();

private:
    QStringList getDatabaseTables();
    QTabWidget *tabWidget;
};

#endif // DATABASE_VIEWER_H
