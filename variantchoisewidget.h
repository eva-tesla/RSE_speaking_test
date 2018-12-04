#ifndef VARIANTCHOISEWIDGET_H
#define VARIANTCHOISEWIDGET_H

#include <QWidget>

namespace Ui {
class VariantChoiseWidget;
}

class VariantChoiseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VariantChoiseWidget(QWidget *parent = nullptr);
    ~VariantChoiseWidget();

signals:
    void showNextWidget();

private:
    Ui::VariantChoiseWidget *ui;
};

#endif // VARIANTCHOISEWIDGET_H
