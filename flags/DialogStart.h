#pragma once
#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class DialogStart; }
QT_END_NAMESPACE

class DialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStart(QWidget* parent = nullptr);
    ~DialogStart();
    void ChangeScore();
private:
    int oldScore = 0, oldTries = 0;
    Ui::DialogStart* ui;
private slots:
    void ifButtonFlagsClicked();
    void ifButtonMapsClicked();
};