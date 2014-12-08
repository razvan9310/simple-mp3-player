#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("Simple MP3 Player");

  player = new QMediaPlayer;
  player->setVolume(70);
  connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
  connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
  connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));

  slider = findChild<QSlider *>("slider");
  slider->setRange(0, 0);
  title = findChild<QLabel *>("title");
  current_time = findChild<QLabel *>("current_time");
  duration = findChild<QLabel *>("duration");
}

MainWindow::~MainWindow() {
  delete duration;
  delete current_time;
  delete title;
  delete slider;
  delete player;
  delete ui;
}

void MainWindow::on_openFileButton_clicked() {
  song_path = QFileDialog::getOpenFileName(this,tr("Choose Song"),
      song_path.isNull() ? QDir::currentPath() : song_path,
      tr("MP3 Files (*.mp3)"));
  if (song_path == 0) {
    return;
  }
  player->setMedia(QUrl::fromLocalFile(song_path));
  player->play();
  paused = false;
  title->setText(simple_file_name(song_path));
  slider->setValue(0);
}

void MainWindow::on_playPauseButton_clicked() {
    if (player->state() != QMediaPlayer::PlayingState) {
      player->setPosition(slider->value() * 1000);
      player->play();
      paused = false;
    } else {
      player->pause();
      paused = true;
    }
}

void MainWindow::durationChanged(qint64 new_duration) {
  slider->setRange(0, new_duration / 1000);
  QString duration_string = " /  ";
  duration_string.append(time_string_from_millis(new_duration));
  duration->setText(duration_string);
}

void MainWindow::on_slider_sliderMoved(int seconds) {
  player->setPosition(seconds * 1000);
}

void MainWindow::on_slider_sliderPressed() {
  player->pause();
}

void MainWindow::on_slider_sliderReleased() {
  if (!paused) {
    player->play();
  }
}

QString MainWindow::simple_file_name(const QString &file_path) {
  std::string file_path_string = file_path.toStdString();
  int pos = file_path_string.size() - 1;
  while (pos >= 0 && file_path_string[pos] != '/'
         && file_path_string[pos] != '\\') {
    --pos;
  }
  return QString::fromStdString(file_path_string.substr(pos + 1));
}

void MainWindow::stateChanged(QMediaPlayer::State state) {
  switch (state) {
    case QMediaPlayer::StoppedState:
      slider->setValue(0);
      current_time->setText("00:00:00");
      break;
    default:
      return;
  }
}

QString MainWindow::time_string_from_millis(const qint64 &millis) {
  unsigned seconds = millis / 1000;
  unsigned hh = seconds / 3600;
  unsigned mm =(seconds % 3600) / 60;
  unsigned ss = (seconds % 3600) % 60;
  QString duration_string = QString("");
  if (hh < 10) {
    duration_string.append('0');
  } else {
    duration_string.append(hh / 10 + '0');
  }
  duration_string.append(hh % 10 + '0');
  duration_string.append(':');
  if (mm < 10) {
    duration_string.append('0');
  } else {
    duration_string.append(mm / 10 + '0');
  }
  duration_string.append(mm % 10 + '0');
  duration_string.append(':');
  if (ss < 10) {
    duration_string.append('0');
  } else {
    duration_string.append(ss / 10 + '0');
  }
  duration_string.append(ss % 10 + '0');
  return duration_string;
}

void MainWindow::positionChanged(qint64 position) {
  slider->setValue(position / 1000);
  current_time->setText(time_string_from_millis(position));
}

void MainWindow::on_slider_actionTriggered(int action) {
  switch (action) {
    case QAbstractSlider::SliderPageStepAdd:
      player->setPosition(player->position() + slider->pageStep() * 1000);
      break;
    case QAbstractSlider::SliderPageStepSub:
      player->setPosition(player->position() - slider->pageStep() * 1000);
      break;
    default:
      return;
  }
}
