#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QFileDialog>
#include <QString>

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

private:
  Ui::MainWindow *ui;
  QMediaPlayer *player;
  QString song_path;
};

#endif // MAINWINDOW_H
