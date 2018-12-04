#include "pausewidget.h"
#include "ui_pausewidget.h"

#include <QTimer>

PauseWidget::PauseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PauseWidget),
    time_(5)
{
    ui->setupUi(this);

    ui->label->setText(QString::number(time_));
}

PauseWidget::~PauseWidget()
{
    delete ui;
}

void PauseWidget::showEvent(QShowEvent *event)
{
    auto timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [this, timer_]{
        if (--time_ <= 0) {
            timer_->stop();
            emit showNextWidget();
        }
        ui->label->setText(QString::number(time_));
    });
    timer_->start(1000);
}
