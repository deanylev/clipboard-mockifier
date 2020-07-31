#include "MainWindow.h"

#include <QClipboard>
#include <QCoreApplication>
#include <QGuiApplication>

#define SETTINGS_KEY_MOCKIFY_CLIPBOARD_SHORTCUT "shortcuts/mockify_clipboard"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  registerSettings();
  this->hotkeyMockifyClipboard = new QHotkey(keySequenceMockifyClipboard, true, this);
  connect(hotkeyMockifyClipboard, &QHotkey::activated, this, &MainWindow::handleHotkeyMockifyClipboard);

  this->keySequenceEditMockifyClipboard = new QKeySequenceEdit(keySequenceMockifyClipboard, this);
  keySequenceEditMockifyClipboard->show();
  connect(keySequenceEditMockifyClipboard, &QKeySequenceEdit::keySequenceChanged, this, &MainWindow::handleKeySequenceMockifyClipboardChanged);
}

void MainWindow::handleHotkeyMockifyClipboard()
{
  QClipboard *clipboard = QGuiApplication::clipboard();
  QString originalText = clipboard->text();
  QString newText;

  for (int i = 0; i < originalText.length(); i++)
  {
    bool uppercase = rand() % 2 == 0;
    QChar character = originalText.at(i);
    QChar transformedCharacter = uppercase ? character.toUpper() : character.toLower();
    newText.append(transformedCharacter);
  }

  clipboard->setText(newText);
}

void MainWindow::handleKeySequenceMockifyClipboardChanged(const QKeySequence keySequence)
{
  this->settings->setValue(SETTINGS_KEY_MOCKIFY_CLIPBOARD_SHORTCUT, keySequence.toString());
  this->keySequenceMockifyClipboard = *(const_cast<QKeySequence *>(&keySequence));
  keySequenceEditMockifyClipboard->setKeySequence(keySequenceMockifyClipboard);
  hotkeyMockifyClipboard->setShortcut(keySequenceMockifyClipboard, true);
}

void MainWindow::registerSettings()
{
  this->settings = new QSettings("Dean Levinson", "Clipboard Mockifier");

  if (settings->contains(SETTINGS_KEY_MOCKIFY_CLIPBOARD_SHORTCUT))
  {
    QString keySequenceString = settings->value(SETTINGS_KEY_MOCKIFY_CLIPBOARD_SHORTCUT).toString();
    this->keySequenceMockifyClipboard = QKeySequence::fromString(keySequenceString);
  }
  else
  {
    this->keySequenceMockifyClipboard = QKeySequence("ctrl+alt+Y");
  }
}
