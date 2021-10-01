#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowTitle("To List Manager");
  init();
  createSignalsSlots();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::onAdd()
{
  ui->leftListView->model()->insertRow(ui->leftListView->model()->rowCount());
  QModelIndex index = ui->leftListView->model()->index(
                        ui->leftListView->model()->rowCount() - 1, 0);
  ui->leftListView->edit(index);
}

void MainWindow::onRemove()
{
  QModelIndex index = ui->leftListView->currentIndex();
  ui->leftListView->model()->removeRow(index.row());
}

void MainWindow::onSave()
{
  m_todoList = m_todoModel->stringList();
  m_doneList = m_doneModel->stringList();

  QFile todoFile("todo.td");
  QFile doneFile("done.td");

  if (!todoFile.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    QMessageBox::critical(this, "Error", todoFile.errorString());
    return;
  }

  QTextStream todoOut(&todoFile);

  if (!doneFile.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    QMessageBox::critical(this, "Error", doneFile.errorString());
    return;
  }

  QTextStream doneOut(&doneFile);

  foreach (const auto& todo, m_todoList)
  {
    todoOut << todo << "\n";
  }

  foreach (const auto& done, m_doneList)
  {
    doneOut << done << "\n";
  }

  todoFile.close();
  doneFile.close();
  QMessageBox::information(this, "Save", "Everything saved");
}

void MainWindow::onLoad()
{
  m_todoList = m_todoModel->stringList();
  m_doneList = m_doneModel->stringList();

  QFile todoFile("todo.td");
  QFile doneFile("done.td");

  if (!todoFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QMessageBox::critical(this, "Error", todoFile.errorString());
    return;
  }

  QTextStream todoIn(&todoFile);

  if (!doneFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QMessageBox::critical(this, "Error", doneFile.errorString());
    return;
  }

  QTextStream doneIn(&doneFile);

  while (!todoIn.atEnd())
  {
    QString line = todoIn.readLine();
    m_todoList.append(line);
  }

  while (!doneIn.atEnd())
  {
    QString line = doneIn.readLine();
    m_doneList.append(line);
  }

  todoFile.close();
  doneFile.close();

  m_todoModel->setStringList(m_todoList);
  m_doneModel->setStringList(m_doneList);
  QMessageBox::information(this, "Load", "Everything load");
}

void MainWindow::init()
{
  ui->leftListView->setDragEnabled(true);
  ui->leftListView->setAcceptDrops(true);
  ui->leftListView->setDropIndicatorShown(true);
  ui->leftListView->setDefaultDropAction(Qt::MoveAction);

  ui->rightListView->setDragEnabled(true);
  ui->rightListView->setAcceptDrops(true);
  ui->rightListView->setDropIndicatorShown(true);
  ui->rightListView->setDefaultDropAction(Qt::MoveAction);

  m_todoModel = new QStringListModel(this);
  m_doneModel = new QStringListModel(this);
  ui->leftListView->setModel(m_todoModel);
  ui->rightListView->setModel(m_doneModel);

  ui->leftListView->setStyleSheet(
    "QListView { font-size: 20pt; font-weight: bold; }"
    "QListView::item { background-color: #BF0A30; padding: 10%; border: 1px solid #8D021F }"
    "QListView::item::hover { background-color: #8D021F}"
  );

  ui->rightListView->setStyleSheet(
    "QListView { font-size: 20pt; font-weight: bold; }"
    "QListView::item { background-color: #2ECC71; padding: 10%; border: 1px solid #27AE60 }"
    "QListView::item::hover { background-color: #27AE60}"
  );
}

void MainWindow::createSignalsSlots()
{
  connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::onAdd);
  connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::onRemove);
  connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSave);
  connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoad);
}

