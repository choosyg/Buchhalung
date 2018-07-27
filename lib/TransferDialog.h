#pragma once

#include "Model.h"
#include "Transfer.h"

#include <QDialog>

namespace Ui {
class TransferDialog;
}

class TransferDialog : public QDialog {
    Q_OBJECT

public:
    explicit TransferDialog( TransferConstPtr transfer, Model& model, QWidget* parent = 0 );
    ~TransferDialog();

    void accept() override;

private slots:
    void on_deleteButton_clicked();

    void on_internalAccountBox_currentTextChanged( const QString& text );

private:
    Ui::TransferDialog* ui;
    Model& model_;
    TransferConstPtr transfer_;
};
