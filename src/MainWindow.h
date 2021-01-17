#pragma once

#include <QCloseEvent>
#include <QHotkey>
#include <QKeySequenceEdit>
#include <QMainWindow>
#include <QSettings>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

private slots:
  void handleHotkeyMockifyClipboard();
  void handleKeySequenceMockifyClipboardChanged(const QKeySequence keySequence);
  void handleTrayMenuTriggered(QAction *action);

private:
  QHotkey *hotkeyMockifyClipboard;
  QKeySequenceEdit *keySequenceEditMockifyClipboard;
  QKeySequence keySequenceMockifyClipboard;
  QSettings *settings;
  QAction *trayMenuActionQuit;
  QAction *trayMenuActionSettings;
  void closeEvent(QCloseEvent *event);
  void registerSettings();
};
