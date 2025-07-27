#include"marks.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>


Marks::Marks(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Manage Student Marks");

    title = new QLabel("Student Marks");

    marksTable = new QTableWidget(3, 3) //dummy table for now
    marksTable->setHorizontalHeaderLabels({"Name", "Subject", "Mark"});

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(marksTable);

    setLayout(layout);

}
