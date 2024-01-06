/**
 * @file BreakTimer.h
 * @brief Definition of the BreakTimer class.
 */

#ifndef BREAKTIMER_H
#define BREAKTIMER_H

#include <QMainWindow>
#include <QTimer>

const unsigned int minToMill = 1000 * 60;

/**
 * @brief Namespace containing the UI-related classes.
 */
QT_BEGIN_NAMESPACE
namespace Ui {
class BreakTimer;
}
QT_END_NAMESPACE

/**
 * @class BreakTimer
 * @brief A simple timer application for taking breaks.
 */
class BreakTimer : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor for the BreakTimer class.
     * @param parent The parent widget.
     */
    BreakTimer(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the BreakTimer class.
     */
    ~BreakTimer();

private slots:
    /**
     * @brief Slot function to start the timer.
     */
    void startTimer();

    /**
     * @brief Slot function to stop the timer.
     */
    void stopTimer();

    /**
     * @brief Slot function to display a break message.
     */
    void showBreakMessage();

    /**
     * @brief Overridden function for handling timer events.
     * @param event The timer event.
     */
    void timerEvent(QTimerEvent *event);

    /**
     * @brief Slot function to check the value of the spin box.
     * @param value The current value of the spin box. Default is 0.
     */
    void checkValue(int value = 0);

private:
    Ui::BreakTimer *ui; ///< The UI object.

    int breakTime; ///< Break time duration in milliseconds.
    int timerId;   ///< Timer ID for managing the timer.
};

#endif // BREAKTIMER_H
