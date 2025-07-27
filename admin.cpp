#include "admin.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "marks.h"

Admin::Admin(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Admin Panel");

    title = new QLabel("Admin Dashboard");
    teacherButton = new QPushButton("Manage Marks");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(teacherButton);

    setLayout(layout);

    connect(teacherButton, &QPushButton::clicked, this, &Admin::manageTeachers);


}

void Admin::manageTeachers()
{
    Marks *marksWindow = new Marks;
    marksWindow->show();
}
