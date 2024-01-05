#include "BreakTimer.h"
#include "ui_breaktimer.h"
#include <QMessageBox>
#include <QProcess>
#include <QSystemTrayIcon>
BreakTimer::BreakTimer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BreakTimer), breakTime(0), timerId(-1) {
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &BreakTimer::startTimer);
    connect(ui->stopButton, &QPushButton::clicked, this, &BreakTimer::stopTimer);
}

BreakTimer::~BreakTimer() {
    delete ui;
}

void BreakTimer::startTimer() {
    breakTime = ui->breakTimeSpinBox->value() * 1000 * 60; // Convert minutes to milliseconds

    if (timerId == -1) {
        // Start the timer only if it's not already running
        timerId = QObject::startTimer(breakTime);
    }
}

void BreakTimer::stopTimer() {
    if (timerId != -1) {
        // Stop the timer only if it's running
        killTimer(timerId);
        timerId = -1;
    }
}

void BreakTimer::showBreakMessage() {


        // Use GNotification for Wayland (GNOME)
        QProcess::startDetached("notify-send", {"--expire-time=0", "Break Time", "It's time for a break!"});
}

void BreakTimer::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timerId) {
        stopTimer();  // Stop the timer after one cycle
        showBreakMessage();
    }
}
