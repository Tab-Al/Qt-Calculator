#ifndef CALCWINDOW_H
#define CALCWINDOW_H

#include <QMainWindow>

namespace Ui {
class CalcWindow;
}

class CalcWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalcWindow(QWidget *parent = nullptr);
    ~CalcWindow();

private:
    Ui::CalcWindow *ui;

private slots:
    void NumPressed();
    void ArithmaticPressed();
    void EqualPressed();
    void ClearPressed();
};

#endif // CALCWINDOW_H
