#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>

class QLabel;

class Student : public QWidget {
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);

private:
    QLabel *infoLabel;
};

#endif // STUDENT_H
