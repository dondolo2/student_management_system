#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

class QPushButton;
class QLabel;

class Admin : public QWidget {
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);

private slots:
    void manageTeachers();

private:
    QLabel *title;
    QPushButton *teacherButton;
};

#endif // ADMIN_H
