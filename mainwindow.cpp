#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("Simple Media Player");

  player = new QMediaPlayer;
  player->setVolume(70);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_openFileButton_clicked() {
  song_path = QFileDialog::getOpenFileName(this,tr("Choose Song"),
      QDir::currentPath(),
      tr("MP3 Files (*.mp3)"));
  player->setMedia(QUrl::fromLocalFile(song_path));
}

void MainWindow::on_playPauseButton_clicked() {
    if (player->state() == QMediaPlayer::PausedState
        || player->state() == QMediaPlayer::StoppedState) {
      player->play();
    } else {
      player->pause();
    }
}
