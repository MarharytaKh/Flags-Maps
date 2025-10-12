#include "flags.h"
#include <iostream>
#include <filesystem>
#include "ui_flags.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDir>
#include <ctime>
#include "DialogStart.h"
#include "GameEndAndSave.h"

flags::flags(QWidget* parent, int gameType)
    : QMainWindow(parent),
    ui(new Ui::flags), gameType(gameType)
{
    ui->setupUi(this);
    
    buttons[0] = ui->pushButton_0;
    buttons[1] = ui->pushButton_1;
    buttons[2] = ui->pushButton_2;
    buttons[3] = ui->pushButton_3;
    Score = 0;
    AllTries = 0;

    if (gameType == 1) {
        imagesPath = "C:\\Users\\salle\\source\\repos\\flags\\images\\flags";
    }
    else if (gameType == 2) {
        imagesPath = "C:\\Users\\salle\\source\\repos\\flags\\images\\maps";
    }

    loadFiles();

    for (int i = 0; i < 4; ++i) {
        connect(buttons[i], &QPushButton::clicked, this, &flags::onAnyButtonClicked);
    }
    sec = 0;
    min = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(1000);

    connect(ui->commandLinkButtonNext, &QPushButton::clicked, this, &flags::onButtonNextClicked);
    connect(ui->buttonEnd, &QPushButton::clicked, this, &flags::ifendButtonClicked);
    changeFlags();
}
void flags::loadFiles()
{
    files.clear();

    std::string way = imagesPath.toStdString();

    for (const auto& entry : std::filesystem::directory_iterator(way)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            if (ext == ".jpg" || ext == ".png") {
                FileName fi;
                fi.name = entry.path().filename().stem().string();
                files.push_back(fi);
            }
        }
    }
}

void flags::changeFlags() {
    isArrowOn = 0;

    size_t count = files.size();
    std::srand(std::time(nullptr));
    randomNumberOfWrightButton = std::rand() % 4;
    randomNumberOfWrightFlag = std::rand() % count;
    

    buttons[randomNumberOfWrightButton]->setText(QString::fromStdString(files[randomNumberOfWrightFlag].name));

    int x = 0; int randomNumberOfFlag = 0;
    int numbersOfUsedFlags[4];

    numbersOfUsedFlags[randomNumberOfWrightButton] = randomNumberOfWrightFlag;
    for (int i = 0; i < 4; i++) {
        if (i == randomNumberOfWrightButton) continue;
        int x = 1;
        while (x == 1) {
            x = 0;
            randomNumberOfFlag = std::rand() % count;
            for (int y = 0; y < 4; y++) {
                if (randomNumberOfFlag == numbersOfUsedFlags[y]) {
                    x = 1;
                }
            }

        }
        buttons[i]->setText(QString::fromStdString(files[randomNumberOfFlag].name));
        numbersOfUsedFlags[i] = randomNumberOfFlag;
    }
    QString folderPath = imagesPath;
    QString fileName = QString::fromStdString(files[randomNumberOfWrightFlag].name + ".jpg");
    QString fullPath = QDir(folderPath).filePath(fileName);

    QPixmap pixmap(fullPath);

    ui->labelPictureOfFlag->setPixmap(pixmap.scaled(
        ui->labelPictureOfFlag->size(),
        Qt::KeepAspectRatio
    ));
}
    void flags::onAnyButtonClicked() {
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
        if (!clickedButton) return;

        buttons[randomNumberOfWrightButton]->setStyleSheet("background-color: green; color: white;");

        if (clickedButton != buttons[randomNumberOfWrightButton]) {
            clickedButton->setStyleSheet("background-color: red; color: white;");
        }
        else Score++;
        AllTries++;
        ui->labelScore->setText(QString::number(Score)+"/"+ QString::number(AllTries));
    }

    void flags::onButtonNextClicked()
    {
        for (int i = 0; i < 4; ++i) {
            buttons[i]->setStyleSheet("");
        }
        changeFlags();
    }
    void flags::ifendButtonClicked() {
        timer->stop();
        this->close();    
        if (parentWidget())
            parentWidget()->show();
    }
    void flags::timerSlot() {
        sec++;
        if (sec >= 60) {
            min++;
            sec = 0;
        }
        ui->timer->setText(QString::number(min)+" : "+ QString::number(sec));
        if (min == 1) {
            timer->stop();
            this->close();

            if (parentWidget()){
                DialogStart* startWindow = qobject_cast<DialogStart*>(parentWidget());
            if (startWindow)
                startWindow->ChangeScore();
                parentWidget()->show();
            }
            GameEndAndSave* windowEnd = new GameEndAndSave(this, gameType);
            windowEnd->setResults(Score, AllTries);
            windowEnd->show();
        }

        
    }
flags::~flags()
{
    delete ui;
}
