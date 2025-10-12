#pragma once

#include <QDialog>  

QT_BEGIN_NAMESPACE
namespace Ui { class GameEndAndSave; }
QT_END_NAMESPACE


class GameEndAndSave : public QDialog
{
    Q_OBJECT

public:
    explicit GameEndAndSave(QWidget* parent = nullptr, int gameType=1);
    void setResults(int score, int tries);
    ~GameEndAndSave();

private:
    int oldScore, oldTries;
    int gameType;
    Ui::GameEndAndSave* ui;
};