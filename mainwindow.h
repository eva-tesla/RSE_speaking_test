#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "variant.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool loadVariants();
    void read(const QJsonObject &json);
    Variant readVariant(const QJsonObject &json, QMap<QString, Task> tasks);
    Task readTask(const QJsonObject &json);

private:
    Ui::MainWindow *ui;
    QVector<Variant> variants;
};

#endif // MAINWINDOW_H
