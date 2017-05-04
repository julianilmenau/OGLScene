#include "res/window/headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

#include "res/util/input.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::update()
{
  // Update input
  Input::update();


  // Schedule a redraw
  ui->widget->update();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat())
  {
    event->ignore();
  }
  else
  {
    Input::registerKeyPress(event->key());
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat())
  {
    event->ignore();
  }
  else
  {
    Input::registerKeyRelease(event->key());
  }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  Input::registerMousePress(event->button());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  Input::registerMouseRelease(event->button());
}

