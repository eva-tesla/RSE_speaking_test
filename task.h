#pragma once

#include <QString>

struct Question {
    int time{90};
    QString imagePath;
};

struct Task {
    QString name;
    QString imagePath;
    QString text;
    int time{90};
};
