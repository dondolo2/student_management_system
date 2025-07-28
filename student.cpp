#include "student.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextStream>
#include <QMessageBox>

Student::Student(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void Student::setupUI() {
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollAreaContent = new QWidget();
    scrollArea->setWidget(scrollAreaContent);

    mainLayout = new QVBoxLayout(scrollAreaContent);

    setupPersonalDetails();
    setupCourseDetails();
    setupUnitSelector();
    setupTranscript();
    setupButtons();

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->addWidget(scrollArea);
    setLayout(outerLayout);
}

void Student::setupPersonalDetails() {
    QVBoxLayout *section = new QVBoxLayout();
    section->addWidget(new QLabel("1. Personal Details"));

    studentIdInput = new QLineEdit();
    firstNameInput = new QLineEdit();
    surnameInput = new QLineEdit();
    addressInput = new QLineEdit();
    genderInput = new QComboBox();
    genderInput->addItems({"Male", "Female", "Other"});
    dobInput = new QLineEdit();
    mobileInput = new QLineEdit();
    emailInput = new QLineEdit();
    parentName = new QLineEdit();
    parentPhone = new QLineEdit();
    parentEmail = new QLineEdit();
    nextOfKinName = new QLineEdit();
    nextOfKinPhone = new QLineEdit();

    QFormLayout *form = new QFormLayout();
    form->addRow("Student ID:", studentIdInput);
    form->addRow("First Name:", firstNameInput);
    form->addRow("Surname:", surnameInput);
    form->addRow("Address:", addressInput);
    form->addRow("Gender:", genderInput);
    form->addRow("DOB:", dobInput);
    form->addRow("Mobile:", mobileInput);
    form->addRow("Email:", emailInput);
    form->addRow("Parent/Guardian Full Name:", parentName);
    form->addRow("Parent/Guardian Phone:", parentPhone);
    form->addRow("Parent/Guardian Email:", parentEmail);
    form->addRow("Next of Kin Name:", nextOfKinName);
    form->addRow("Next of Kin Phone:", nextOfKinPhone);

    section->addLayout(form);
    mainLayout->addLayout(section);
}

void Student::setupCourseDetails() {
    QVBoxLayout *section = new QVBoxLayout();
    section->addWidget(new QLabel("2. Course Details"));

    courseNameInput = new QLineEdit();
    courseCodeInput = new QLineEdit();
    yearInput = new QLineEdit();
    facultyInput = new QLineEdit();
    deanInput = new QLineEdit();
    programLeaderInput = new QLineEdit();
    tutorInput = new QLineEdit();

    QFormLayout *form = new QFormLayout();
    form->addRow("Course Name:", courseNameInput);
    form->addRow("Course Code:", courseCodeInput);
    form->addRow("Year of Study:", yearInput);
    form->addRow("Faculty:", facultyInput);
    form->addRow("Dean of Faculty:", deanInput);
    form->addRow("Program Leader:", programLeaderInput);
    form->addRow("Course Tutor:", tutorInput);

    section->addLayout(form);
    mainLayout->addLayout(section);
}

void Student::setupUnitSelector() {
    QVBoxLayout *section = new QVBoxLayout();
    section->addWidget(new QLabel("3. Unit Selector"));

    unitLayout = new QVBoxLayout();

    moduleList = {"Math101", "CompSci202", "Physics303", "Chem204"};

    for (int i = 0; i < 3; ++i) addModuleRow();

    averageLabel = new QLabel("Average: ");
    rankingLabel = new QLabel("Ranking: ");
    dateLabel = new QLabel("Date: " + QDate::currentDate().toString());

    section->addLayout(unitLayout);
    section->addWidget(averageLabel);
    section->addWidget(rankingLabel);
    section->addWidget(dateLabel);

    mainLayout->addLayout(section);
}

void Student::addModuleRow() {
    QHBoxLayout *row = new QHBoxLayout();

    QComboBox *moduleDropdown = new QComboBox();
    moduleDropdown->addItems(moduleList);
    moduleSelectors.append(moduleDropdown);

    QLineEdit *score = new QLineEdit();
    scoreInputs.append(score);

    row->addWidget(new QLabel(QString::number(moduleSelectors.size()) + "."));
    row->addWidget(moduleDropdown);
    row->addWidget(score);

    unitLayout->addLayout(row);
}

void Student::saveModules()
{

}

void Student::resetModules() {
    // Clear all line edits (adjust names accordingly)
    moduleList.clear();
    for (QComboBox* combo : moduleSelectors) {
        if (combo) combo->setCurrentIndex(0);  // Or -1 if you want it completely unselected
    }

    for (QLineEdit* input : scoreInputs) {
        if (input) input->clear();
    }

    if (averageLabel) averageLabel->clear();
    if (rankingLabel) rankingLabel->clear();



    // Using a QTableWidget to show modules
    transcriptTable->clearContents();
    transcriptTable->setRowCount(0);
    transcriptHeader->clear();  //


    QMessageBox::information(this, "Reset", "All module information has been cleared.");
}

void Student::showTranscript() {
    QString transcript;

    transcript += "Transcript for: " + firstNameInput->text()+ " " + surnameInput->text() + "\n";
    transcript += "Student Number: " + studentIdInput->text() + "\n\n";

    transcript += QString("==========================================================\n\n");

    transcript += "Modules:\n";
    for (int row = 0; row < transcriptTable->rowCount(); ++row) {
        QString code = transcriptTable->item(row, 0)->text();
        QString name = transcriptTable->item(row, 1)->text();
        QString mark = transcriptTable->item(row, 2)->text();

        transcript += code + " - " + name + " : " + mark + "\n";
    }

    transcript += QString("==========================================================\n\n");

    // Show in a new dialog or QTextEdit
    QMessageBox::information(this, "Transcript", transcript);
}



void Student::setupTranscript() {
    QVBoxLayout *section = new QVBoxLayout();
    transcriptHeader = new QLabel("Transcript:");
    transcriptTable = new QTableWidget();
    transcriptTable->setColumnCount(3);
    transcriptTable->setHorizontalHeaderLabels({"Module No.", "Module Name", "Score"});

    section->addWidget(transcriptHeader);
    section->addWidget(transcriptTable);

    mainLayout->addLayout(section);
    transcriptTable->hide();  // Hidden by default
    transcriptHeader->hide();
}

#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

void Student::printTranscript() {
    QString transcript;
    transcript += QString("<h2>Student Transcript</h2><br>");
    transcript += "<b>Student Number:</b> " + studentIdInput->text() + "<br>";
    transcript += "<b>Name:</b> " + firstNameInput->text() + "<br>";
    transcript += "<b>Name:</b> " + surnameInput->text() + "<br>";
    transcript += "<b>Student Address:</b> " + addressInput->text() + "<br><br>";
    transcript += "<b>Modules:</b><br><ul>";

    for (int row = 0; row < transcriptTable->rowCount(); ++row) {
        QString code = transcriptTable->item(row, 0)->text();
        QString name = transcriptTable->item(row, 1)->text();
        QString mark = transcriptTable->item(row, 2)->text();

        transcript += "<li>" + code + " - " + name + " : " + mark + "</li>";
    }

    transcript += "</ul>";

    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QTextDocument doc;
        doc.setHtml(transcript);
        doc.print(&printer);
    }
}


void Student::setupButtons() {
    QVBoxLayout *section = new QVBoxLayout();

    resetBtn = new QPushButton("Reset");
    transcriptBtn = new QPushButton("Transcript");
    printBtn = new QPushButton("Print");
    logoutBtn = new QPushButton("Logout");

    connect(saveBtn, &QPushButton::clicked, this, &Student::saveModules);
    connect(resetBtn, &QPushButton::clicked, this, &Student::resetModules);
    connect(transcriptBtn, &QPushButton::clicked, this, &Student::showTranscript);
    connect(printBtn, &QPushButton::clicked, this, &Student::printTranscript);

    section->addWidget(saveBtn);
    section->addWidget(resetBtn);
    section->addWidget(transcriptBtn);
    section->addWidget(printBtn);
    section->addWidget(logoutBtn);

    mainLayout->addLayout(section);
}


