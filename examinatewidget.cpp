#include "examinatewidget.h"
#include "ui_examinatewidget.h"

#include <QAudioRecorder>
#include <QAudioEncoderSettings>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QTimeLine>
#include <QPropertyAnimation>
#include <QUrl>

ExaminateWidget::ExaminateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExaminateWidget),
    preparationTime_(9),
    recordingTime_(20)
{
    ui->setupUi(this);

    audioRecorder = new QAudioRecorder(this);

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/mpeg");
    audioSettings.setQuality(QMultimedia::HighQuality);

    QFile loadFile(QDir::currentPath() + "/" + QStringLiteral("variants/task1/1.png"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
    }

    auto pixmap = new QPixmap(QDir::currentPath() + "/" + QStringLiteral("variants/task1/1.png"), "PNG");

    auto scene = new QGraphicsScene(this);
    scene->addPixmap(*pixmap);

    ui->graphicsView->setScene(scene);
}

ExaminateWidget::~ExaminateWidget()
{
    delete ui;
}

void ExaminateWidget::showEvent(QShowEvent *)
{
    using namespace std::chrono_literals;
    updateHelper(std::chrono::seconds(preparationTime_), [this]{
        ui->statusLabel->setText("Recording");
        recording();
        updateHelper(std::chrono::seconds(recordingTime_), [this]{
            stopRecording();
        });
    });
}

void ExaminateWidget::updateTime(int64_t time) {
    auto secs = time / 1000;
    auto mins = (secs / 60) % 60;
    secs = secs % 60;
    ui->timeLabel->setText(QString("%1:%2")
                       .arg(mins, 2, 10, QLatin1Char('0'))
                           .arg(secs, 2, 10, QLatin1Char('0')));
}

void ExaminateWidget::recording()
{
    audioRecorder->setOutputLocation(QUrl::fromLocalFile("fileName.mpeg"));
    audioRecorder->record();
}

void ExaminateWidget::stopRecording()
{
    audioRecorder->stop();
}

template<typename F>
void ExaminateWidget::updateHelper(std::chrono::milliseconds duration, F &&onDone)
{
    auto dur = duration.count();

    updateTime(dur);

    ui->progressBar->setMinimum(dur/1000);
    ui->progressBar->setMaximum(dur);

    elapsedTimer_.restart();
    connect(&timer_, &QTimer::timeout, [this, dur, onDone{std::move(onDone)}]{
        auto timeout = dur - elapsedTimer_.elapsed();
        ui->progressBar->setValue(elapsedTimer_.elapsed());
        updateTime(timeout);

        if(timeout <= 0) {
            timer_.stop();
            timer_.disconnect();
            onDone();
        }
    });
    timer_.start(100);
}
