#include "login.h"
#include "mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include "admin.h"
#include "student.h"

Login::Login(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Login");

    usernameInput = new QLineEdit;
    usernameInput->setPlaceholderText("Username");

    passwordInput = new QLineEdit;
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login");

    errorLabel = new QLabel;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addWidget(loginButton);
    layout->addWidget(errorLabel);

    setLayout(layout);

    connect(loginButton, &QPushButton::clicked, this, &Login::handleLogin);
}

void Login::handleLogin()
{
    QString user = usernameInput->text();
    QString pass = passwordInput->text();

    if (user == "admin" && pass == "admin") {
        MainWindow *mainWin = new MainWindow;
        mainWin->show();

        this->close();
        Admin *adminPanel = new Admin;
        adminPanel->show();
    } else if (user == "student" && pass == "student") {
        this->hide();
        Student *studentPanel = new Student;
        studentPanel->show();
    } else {
        errorLabel->setText("Invalid Credentials");
    }
}


