#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QLabel;

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private slots:
    void handleLogin();

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QLabel *errorLabel;
};

#endif // LOGIN_H
