#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QLabel>
#include <QTime>
#include <QDate>
#include <QFont>
#include <QRect>
#include <QSize>
#include <QTime>
#include <QPoint>
#include <QString>

MainWindow::MainWindow (QWidget *parent) : QMainWindow (parent), ui (new Ui::MainWindow)
{
  ui->setupUi(this);

  /* Узнаем размер монитора и считаем его центр */
  QRect screenSize = QGuiApplication::primaryScreen()->geometry();
  int screenCenterX = screenSize.width() / 2;
  int screenCenterY = screenSize.height() / 2;

  /* Устанавливаем в текст лейбла текущее время и дату */
  QString dateTime = QTime::currentTime().toString("hh:mm:ss") + '\n' + QDate::currentDate().toString("dd.MM.yyyy");
  ui->timeLabel->setText(dateTime);

  /* Узнаем размер лейбла */
  QSize timeLabelSize = ui->timeLabel->size();

  /* Перемещаем лейбл в середину экрана */
  ui->timeLabel->move(screenCenterX - timeLabelSize.width() / 2,
                      screenCenterY -  timeLabelSize.height() / 2);

  /* Устанавливаем таймер для обновления времени и к событию стечения времени
  привязываем слот обновления текущего времени в лейбле */
  updateTimeLabelTimer = new QTimer(this);
  connect(updateTimeLabelTimer, &QTimer::timeout, this, &MainWindow::updateCurrentTime);
  updateTimeLabelTimer->start(1000);

  moveTimeLabelTimer = new QTimer(this);
  connect(moveTimeLabelTimer, &QTimer::timeout, this, &MainWindow::moveTimeLabel);
  moveTimeLabelTimer->start(16);
}

MainWindow::~MainWindow () {
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  /* Закрываем программу при нажатии ESC */
  if (event->key() == Qt::Key_Escape) this->close();
}

void MainWindow::updateCurrentTime()
{
  /* Обновляем время и дату в лейбле */
  QString dateTime = QTime::currentTime().toString("hh:mm:ss") + '\n' + QDate::currentDate().toString("dd.MM.yyyy");
  ui->timeLabel->setText(dateTime);
}

void MainWindow::moveTimeLabel()
{
  /* Получаем позицию и размер лейбла */
  QPoint labelPos = ui->timeLabel->pos();
  QSize labelSize = ui->timeLabel->size();

  /* Проверяем горизонтальные рамки. Если лейбл вышел за левую или правую рамку, то меняем направление движения по X */
  if (labelPos.x() <= 0 || labelPos.x() + labelSize.width() >= this->width()) timeLable_dx = -timeLable_dx;
  /* Проверяем вертикальные рамки. Если лейбл вышел за верхнюю или нижнюю рамку, то меняем направление движения по Y */
  if (labelPos.y() <= 0 || labelPos.y() + labelSize.height() >= this->height()) timeLable_dy = -timeLable_dy;
  /* В обоих случаях правую/нижнюю границы проверяем с учетом ширины/высоты самого лейбла, чтобы не ждать, когда
  левый край достигнет крайнего положения */

  /* Перемещаем лейбл в новую позицию */
  ui->timeLabel->move(labelPos.x() + timeLable_dx, labelPos.y() + timeLable_dy);
}