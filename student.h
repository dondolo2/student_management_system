#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QTableWidget>


class Student : public QWidget {
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);

private slots:
    void addModuleRow();
    void loadModules();
    void saveModules();
    void resetModules();
    void showTranscript();
    void printTranscript();

private:
    QWidget *scrollAreaContent;
    QVBoxLayout *mainLayout;

    // 1. Personal Details
    QLineEdit *studentIdInput, *firstNameInput, *surnameInput, *addressInput;
    QComboBox *genderInput;
    QLineEdit *dobInput, *mobileInput, *emailInput;
    QLineEdit *parentName, *parentPhone, *parentEmail, *nextOfKinName, *nextOfKinPhone;

    // 2. Course Details
    QLineEdit *courseNameInput, *courseCodeInput, *yearInput;
    QLineEdit *facultyInput, *deanInput, *programLeaderInput, *tutorInput;

    // 3. Unit Selector
    QVBoxLayout *unitLayout;
    QList<QString> moduleList;
    QList<QComboBox*> moduleSelectors;
    QList<QLineEdit*> scoreInputs;
    QLabel *averageLabel, *rankingLabel, *dateLabel;

    // 4. Transcript
    QTableWidget *transcriptTable;
    QLabel *transcriptHeader;

    // 5. Buttons
    QPushButton *loadBtn, *saveBtn, *resetBtn, *transcriptBtn, *printBtn, *logoutBtn;

    void setupUI();
    void setupPersonalDetails();
    void setupCourseDetails();
    void setupUnitSelector();
    void setupTranscript();
    void setupButtons();

    void updateAverage();
};

#endif // STUDENT_H
