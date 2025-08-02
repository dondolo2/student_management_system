#include "database_viewer.h"
#include "database.h"
#include <QApplication>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView>

DatabaseViewer::DatabaseViewer(QWidget *parent)
    : QWidget(parent)
{
    // Set up the main window
    setWindowTitle("PostgreSQL Database Viewer");
    resize(1000, 600);

    QSqlDatabase db = QSqlDatabase::database("school_management_connection");
    if (!db.isOpen()) {
        QMessageBox::warning(this, "Error", "Database connection is not open!");
        return;
    }

    // Create the tab widget to hold table views
    tabWidget = new QTabWidget(this);

    // Create layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);

    // Get list of tables from the database
    QStringList tables = getDatabaseTables();
    if (tables.isEmpty()) {
        QMessageBox::warning(this, "Error", "No tables found in the database!");
        return;
    }

    // Create a model and view for each table
    for (const QString &tableName : tables) {
        QSqlTableModel *model = new QSqlTableModel(this);
        model->setTable(tableName);
        model->select();

        QTableView *tableView = new QTableView;
        tableView->setModel(model);
        tableView->setSortingEnabled(true);
        tableView->resizeColumnsToContents();
        tableView->horizontalHeader()->setStretchLastSection(true);

        tabWidget->addTab(tableView, tableName);
    }
}

QStringList DatabaseViewer::getDatabaseTables()
{
    QStringList tables;
    QSqlQuery query("SELECT table_name FROM information_schema.tables "
                    "WHERE table_schema = 'public' AND table_type = 'BASE TABLE' "
                    "ORDER BY table_name");

    while (query.next()) {
        tables << query.value(0).toString();
    }

    return tables;
}

// Standalone function to display the database viewer
void displayDatabaseViewer() {
    DatabaseViewer *viewer = new DatabaseViewer();
    viewer->show();
}
