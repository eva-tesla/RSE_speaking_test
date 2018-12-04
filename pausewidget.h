#ifndef PAUSEWIDGET_H
#define PAUSEWIDGET_H

#include <QWidget>

namespace Ui {
class PauseWidget;
}

class QTimer;

class PauseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PauseWidget(QWidget *parent = nullptr);
    ~PauseWidget();

signals:
    void showNextWidget();

protected:
    void showEvent(QShowEvent *event);

private:
    Ui::PauseWidget *ui;
    int time_;
};

#endif // PAUSEWIDGET_H
