#include <cstdlib>
#include <cstring>

#include <QClipboard>
#include <QGuiApplication>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QPixmap>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QVBoxLayout>
#include <Qt>

#include "MainWindow.h"

#define IMAGE_WIDTH 75
#define SETTINGS_KEY_MOCKIFY_CLIPBOARD_SHORTCUT "shortcuts/mockify_clipboard"
#define WINDOW_HEIGHT 200
#define WINDOW_WIDTH 200

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

  registerSettings();
  hotkeyMockifyClipboard = new QHotkey(keySequenceMockifyClipboard, true, this);
  connect(hotkeyMockifyClipboard, &QHotkey::activated, this, &MainWindow::handleHotkeyMockifyClipboard);

  keySequenceEditMockifyClipboard = new QKeySequenceEdit(keySequenceMockifyClipboard, this);
  connect(keySequenceEditMockifyClipboard, &QKeySequenceEdit::keySequenceChanged, this, &MainWindow::handleKeySequenceMockifyClipboardChanged);

  QPixmap image(":/res/icon.png");
  QLabel *labelImage = new QLabel();
  labelImage->setPixmap(image.scaledToWidth(IMAGE_WIDTH));

  QLabel *labelVersion = new QLabel((std::string("Version ") + VERSION).c_str(), this);
  QLabel *labelMockifiyClipboard = new QLabel("Keyboard Shortcut", this);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(labelImage);
  layout->addWidget(labelVersion);
  layout->addWidget(labelMockifiyClipboard);
  layout->addWidget(keySequenceEditMockifyClipboard);

  QWidget *window = new QWidget();
  window->setLayout(layout);

  setCentralWidget(window);

  QMenu *trayMenu = new QMenu("Clipboard Mockifier", this);
  trayMenuActionSettings = trayMenu->addAction("Settings");
  trayMenuActionQuit = trayMenu->addAction("Quit");
  connect(trayMenu, &QMenu::triggered, this, &MainWindow::handleTrayMenuTriggered);

  QSystemTrayIcon *trayIcon = new QSystemTrayIcon(QIcon(":/res/icon.png"), this);
  trayIcon->setContextMenu(trayMenu);
  trayIcon->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  hide();
  event->ignore();
}

void MainWindow::handleHotkeyMockifyClipboard()
{
  QClipboard *clipboard = QGuiApplication::clipboard();
  QString originalText = clipboard->text();
  QString newText;

  for (int i = 0; i < originalText.length(); i++) {
    bool uppercase = rand() % 2 == 0;
    QChar character = originalText.at(i);
    QChar transformedCharacter = uppercase ? character.toUpper() : character.toLower();
    newText.append(transformedCharacter);
  }

  clipboard->setText(newText);
}

void MainWindow::handleKeySequenceMockifyClipboardChanged(const QKeySequence keySequence)
{
  settings->setValue(SETTINGS_KEY_MOCKIFY_CLIPBOARD_SHORTCUT, keySequence.toString());
  keySequenceMockifyClipboard = *(const_cast<QKeySequence *>(&keySequence));
  keySequenceEditMockifyClipboard->setKeySequence(keySequenceMockifyClipboard);
  hotkeyMockifyClipboard->setShortcut(keySequenceMockifyClipboard, true);
}

void MainWindow::handleTrayMenuTriggered(QAction *action)
{
  if (action == trayMenuActionSettings) {
    show();
  } else if (action == trayMenuActionQuit) {
    QCoreApplication *qCoreApplication = QCoreApplication::instance();
    qCoreApplication->quit();
  }
}

void MainWindow::registerSettings()
{
  settings = new QSettings("Dean Levinson", "Clipboard Mockifier");

  if (settings->contains(SETTINGS_KEY_MOCKIFY_CLIPBOARD_SHORTCUT)) {
    QString keySequenceString = settings->value(SETTINGS_KEY_MOCKIFY_CLIPBOARD_SHORTCUT).toString();
    keySequenceMockifyClipboard = QKeySequence::fromString(keySequenceString);
  } else {
    keySequenceMockifyClipboard = QKeySequence("ctrl+alt+Y");
  }
}
