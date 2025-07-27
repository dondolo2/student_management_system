#include "student.h"
#include <QVBoxLayout>
#include <QLabel>

Student::Student(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Student Panel");

    infoLabel = new QLabel("Welcome, Student. Your results will appear here.");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(infoLabel);

    setLayout(layout);
}
