#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow (QWidget *parent = nullptr);
  ~MainWindow ();

  void keyPressEvent(QKeyEvent *event);

private slots:
  void updateCurrentTime();
  void moveTimeLabel();

private:
  Ui::MainWindow *ui;
  QTimer *updateTimeLabelTimer;
  QTimer *moveTimeLabelTimer;
  int timeLable_dx = 5;
  int timeLable_dy = 5;
};

#endif // MAINWINDOW_H
