#pragma once

#include <QString>
#include <QVector>

#include "task.h"

struct Variant {
    QString name;
    QVector<Task> tasks;
};
