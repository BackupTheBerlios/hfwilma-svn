/*
    hfWilma, connecting the desktop with asterisk 
    Copyright (C) 2007 Marc Feld

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/   

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include "astmanager.h"
#include <QTextEdit>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
//class QSystemTrayIcon;

class MainWidget : public QMainWindow
{
  Q_OBJECT;

 public:
  MainWidget();
 signals:
  void newToolTip(QString);
  private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
  void genToolTip();
 private:
  QSystemTrayIcon * trayIcon;
  void closeEvent(QCloseEvent *event);
  void writeSettings();
  void readSettings();
  QTextEdit *textedit;
  QString collectToolTipData();
  void setIcon(int index);
  AstManager *astmanager;
  QAction *closeApp;
  QMenu *trayMenu;
};

#endif // MAINWIDGET_H
