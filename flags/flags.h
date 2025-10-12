#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <vector>
#include <string>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class flags; }
QT_END_NAMESPACE

struct FileName {
    std::string name;
};

class flags : public QMainWindow
{
    Q_OBJECT

public:
    int Score; int AllTries;
    explicit flags(QWidget* parent = nullptr, int gameType=1);
    ~flags();
private:
    int sec; int min;
    void changeFlags();
    QTimer* timer;
    Ui::flags* ui;
    int randomNumberOfWrightFlag;
    int randomNumberOfWrightButton;
    QPushButton* buttons[4];
    std::vector<FileName> files;
    int isArrowOn;
   
    int gameType;
    QString imagesPath;

    void loadFiles();
private slots:
    void timerSlot();
    void ifendButtonClicked();
    void onAnyButtonClicked();
    void onButtonNextClicked();

};

