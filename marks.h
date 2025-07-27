#ifndef MARKS_H
#define MARKS_H

#include <QWidget>

class QLabel;
class QTableWidget;

class Marks : public QWidget {
    Q_OBJECT

public:
    explicit Marks(QWidget *parent = nullptr);

private:
    QLabel *title;
    QTableWidget *marksTable;
};

#endif // MARKS_H
