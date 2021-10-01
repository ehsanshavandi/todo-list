#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QIODevice>
#include <QStringListModel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void onAdd();
  void onRemove();
  void onSave();
  void onLoad();

 private:
  Ui::MainWindow* ui;
  QStringList m_todoList;
  QStringList m_doneList;
  QStringListModel* m_todoModel;
  QStringListModel* m_doneModel;
  void init();
  void createSignalsSlots();
};
#endif // MAINWINDOW_H
