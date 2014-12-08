#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QFileDialog>
#include <QString>
#include <QSlider>
#include <QLabel>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_openFileButton_clicked();
  void on_playPauseButton_clicked();
  void durationChanged(qint64);
  void on_slider_sliderMoved(int);
  void on_slider_sliderPressed();
  void on_slider_sliderReleased();
  void stateChanged(QMediaPlayer::State);
  void positionChanged(qint64);

  void on_slider_actionTriggered(int action);

private:
  QString simple_file_name(const QString &);
  QString time_string_from_millis(const qint64 &);

  Ui::MainWindow *ui;
  QMediaPlayer *player;
  QSlider *slider;
  QLabel *title;
  QLabel *current_time;
  QLabel *duration;
  QString song_path;
  bool paused;
};

#endif // MAINWINDOW_H
