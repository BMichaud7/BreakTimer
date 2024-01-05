#ifndef BREAKTIMER_H
#define BREAKTIMER_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class BreakTimer;
}
QT_END_NAMESPACE

class BreakTimer : public QMainWindow {
    Q_OBJECT

public:
    BreakTimer(QWidget *parent = nullptr);
    ~BreakTimer();

private slots:
    void startTimer();
    void stopTimer();
    void showBreakMessage();
    void timerEvent(QTimerEvent *event);

private:
    Ui::BreakTimer *ui;
    int breakTime;
    int timerId;
};

#endif // BREAKTIMER_H
