#include "BreakTimer.h"
#include "ui_breaktimer.h"
#include <QMessageBox>
#include <QProcess>
#include <QSystemTrayIcon>

// Constructor
BreakTimer::BreakTimer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BreakTimer), breakTime(0), timerId(-1) {
    ui->setupUi(this);

    // Connect button signals to slots
    connect(ui->startButton, &QPushButton::clicked, this, &BreakTimer::startTimer);
    connect(ui->stopButton, &QPushButton::clicked, this, &BreakTimer::stopTimer);

    // Connect spin box signal to the checkValue slot
    connect(ui->breakTimeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(checkValue(int)));

    // Initial check of the spin box value
    checkValue();
}

// Destructor
BreakTimer::~BreakTimer() {
    delete ui;
}

// Slot to start the timer
void BreakTimer::startTimer() {
    breakTime = ui->breakTimeSpinBox->value() * minToMill; // Convert minutes to milliseconds

    if (timerId == -1) {
        // Start the timer only if it's not already running
        timerId = QObject::startTimer(breakTime);
        ui->startButton->setEnabled(false);
        ui->breakTimeSpinBox->setEnabled(false);
        ui->stopButton->setEnabled(true);
    }
}

// Slot to stop the timer
void BreakTimer::stopTimer() {
    if (timerId != -1) {
        // Stop the timer only if it's running
        killTimer(timerId);
        timerId = -1;
        ui->startButton->setEnabled(true);
        ui->breakTimeSpinBox->setEnabled(true);
        ui->stopButton->setEnabled(false);
    }
}

// Slot to show a break message
void BreakTimer::showBreakMessage() {
    ui->startButton->setEnabled(true);
    ui->breakTimeSpinBox->setEnabled(true);
    ui->stopButton->setEnabled(false);

    // Use GNotification for Wayland (GNOME)
    QProcess::startDetached("notify-send", {"--expire-time=0", "Break Time", "It's time for a break!"});
}

// Overridden function for handling timer events
void BreakTimer::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timerId) {
        stopTimer();  // Stop the timer after one cycle
        showBreakMessage();
    }
}

// Slot to check the value of the spin box
void BreakTimer::checkValue(int value) {
    Q_UNUSED(value)

    if (ui->breakTimeSpinBox->value() > 1) {
        ui->startButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
    } else {
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(false);
    }
}
