#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "variantchoisewidget.h"
#include "startwidget.h"
#include "pausewidget.h"
#include "examinatewidget.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadVariants();

    connect(ui->variantChoiseWidget, &VariantChoiseWidget::showNextWidget, [this]{
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    });
    connect(ui->startWidget, &StartWidget::showNextWidget, [this]{
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    });
    connect(ui->pauseWidget, &PauseWidget::showNextWidget, [this]{
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadVariants()
{
    qDebug() << QDir::currentPath();
    QFile loadFile(QStringLiteral("variant.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return false;
    }

    auto loadDoc = QJsonDocument::fromJson(loadFile.readAll());

    read(loadDoc.object());

    return true;
}

void MainWindow::read(const QJsonObject &json)
{
    QMap<QString, Task> taskMap;

    if (json.contains("tasks") && json["tasks"].isArray()) {
        auto tasks = json["tasks"].toArray();
        for (const QJsonValueRef t : tasks) {
            auto obj = t.toObject();
            auto task = readTask(obj);
            taskMap.insert(obj["name"].toString(), task);
        }
    }

    if (json.contains("variants") && json["variants"].isArray()) {
        auto variants = json["variants"].toArray();
        for (const QJsonValueRef variant : variants) {
            readVariant(variant.toObject(), taskMap);
        }
    }
}

Variant MainWindow::readVariant(const QJsonObject &obj, QMap<QString, Task> taskMap)
{
    Variant variant;
    variant.name = obj["name"].toString();
    auto tasks = obj["tasks"].toArray();
    for (const QJsonValueRef t : tasks) {
        if (auto it = taskMap.find(t.toString()); it != taskMap.end())
            variant.tasks.push_back(*it);
    }
    return variant;
}

Task MainWindow::readTask(const QJsonObject &obj)
{
    Task task;
    task.name = obj["name"].toString();
    return task;
}
