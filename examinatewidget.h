#ifndef EXAMINATEWIDGET_H
#define EXAMINATEWIDGET_H

#include <chrono>

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>

namespace Ui {
class ExaminateWidget;
}

class QAudioRecorder;

class ExaminateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExaminateWidget(QWidget *parent = nullptr);
    ~ExaminateWidget();

protected:
    void showEvent(QShowEvent *);

private:
    void updateTime(int64_t );

    void recording();

    void stopRecording();

    template <typename F>
    void updateHelper(std::chrono::milliseconds duration, F&& onDone);

private:
    Ui::ExaminateWidget *ui;
    QAudioRecorder *audioRecorder;
    int preparationTime_;
    int recordingTime_;
//    QTime *startTime_;
//    QTime runningTime_;
    int startTime_;
    QTimer timer_;
    QElapsedTimer elapsedTimer_;
};

#endif // EXAMINATEWIDGET_H
