#include "variantchoisewidget.h"
#include "ui_variantchoisewidget.h"

VariantChoiseWidget::VariantChoiseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VariantChoiseWidget)
{
    ui->setupUi(this);
}

VariantChoiseWidget::~VariantChoiseWidget()
{
    delete ui;
}
