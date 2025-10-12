#include "DialogStart.h"
#include "ui_DialogStart.h"
#include "flags.h"
#include <fstream>
#include <QDir>
#include <QtWidgets/QApplication>

DialogStart::DialogStart(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::DialogStart)
{
    ui->setupUi(this);

    QString folderPath = "C:/Users/salle/source/repos/flags/images";
    QString fileName = "wallp.jpg";

    QString fullPath = QDir(folderPath).filePath(fileName);
    QPixmap pixmap(fullPath);

    if (pixmap.isNull()) {
        qDebug() << "There is no such image:" << fullPath;
    }

    ui->labelWallpaper->setPixmap(
        pixmap.scaled(
            ui->labelWallpaper->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        )
    );
    oldScore = 0;
    oldTries = 0;
    connect(ui->ButtonStartFlags, &QPushButton::clicked, this, &DialogStart::ifButtonFlagsClicked);
    connect(ui->ButtonStartMaps, &QPushButton::clicked, this, &DialogStart::ifButtonMapsClicked);
    ChangeScore();
}
void DialogStart::ChangeScore() {
    std::ifstream in("bestSc.txt");
    if (in.is_open()) {
        in >> oldScore;
        in >> oldTries;
        in.close();
    }
}
DialogStart::~DialogStart()
{
    delete ui;
}
void DialogStart::ifButtonFlagsClicked() {
    int x = 1;
    flags* windowGame = new flags(this, x);
    windowGame->show();
    this->hide();
}
void DialogStart::ifButtonMapsClicked() {
    int x = 2;
    flags* windowGame = new flags(this, x);
    windowGame->show();
    this->hide();
}