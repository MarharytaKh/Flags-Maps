#include "GameEndAndSave.h"
#include "ui_GameEndAndSave.h"
#include "DialogStart.h"
#include <fstream>
#include "flags.h"
#include <QDir>
#include <QtWidgets/QApplication>

GameEndAndSave::GameEndAndSave(QWidget* parent, int gameType)
    : QDialog(parent),
    ui(new Ui::GameEndAndSave), gameType(gameType)
{
    ui->setupUi(this);
    QString folderPath = "C:\\Users\\salle\\source\\repos\\flags\\images";

    QString fileName = "catSticker.jpg";
    QString fullPath = QDir(folderPath).filePath(fileName);
    QPixmap pixmap(fullPath);

    ui->labelSticker->setPixmap(
        pixmap.scaled(
            ui->labelSticker->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        )
    );
}

GameEndAndSave::~GameEndAndSave()
{
    delete ui;
}
void GameEndAndSave::setResults(int score, int tries)
{
    ui->labelScore->setText(QString::number(score) + "/" + QString::number(tries));
    oldScore = 0, oldTries = 0;
    bool isNewRecord = false;
    if (gameType == 1) {
        std::ifstream in("bestScF.txt");
        if (in.is_open()) {
            in >> oldScore >> oldTries;
            in.close();
        }
    }
    else if (gameType == 2) {
        std::ifstream in("bestScM.txt");
        if (in.is_open()) {
            in >> oldScore >> oldTries;
            in.close();
        }
    }
    if (static_cast<double>(score) / tries > static_cast<double>(oldScore) / oldTries && score>oldScore) {
        isNewRecord = true;
        if (gameType == 1) {
            std::ofstream out("bestScF.txt");
            if (out.is_open()) {
                out << score << " " << tries;
                out.close();
            }
        }
        if (gameType == 2) {
            std::ofstream out("bestScM.txt");
            if (out.is_open()) {
                out << score << " " << tries;
                out.close();
            }
        }
        QString folderPath = "C:/Users/salle/source/repos/flags/images";
        QString fileName = "catStickerHappy.jpg";
        QString fullPath = QDir(folderPath).filePath(fileName);
        QPixmap pixmap(fullPath);
        if (pixmap.isNull()) {
            qDebug() << "There is no such image" << fullPath;
        }
        ui->labelSticker->setPixmap(
            pixmap.scaled(
                ui->labelSticker->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            )
        );
        ui->labelGreat->setText("You have set a new record!");
    }
    if (isNewRecord) {
        oldScore = score;
        oldTries = tries;
    }
    ui->labelBestScore->setText(QString::number(oldScore) + "/" + QString::number(oldTries));
}