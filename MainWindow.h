#pragma once

#include <QHotkey>
#include <QKeySequence>
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

private:
  QHotkey *hotkeyMockifyClipboard;
  QKeySequenceEdit *keySequenceEditMockifyClipboard;
  QKeySequence keySequenceMockifyClipboard;
  QSettings *settings;
  void registerSettings();
};
