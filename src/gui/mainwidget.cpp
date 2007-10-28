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

#include "mainwidget.h"
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPixmap>
#include <QIcon>
#include <QPainter>


MainWidget::MainWidget()
{
  
 trayIcon = new QSystemTrayIcon(this);
 setIcon(5);
 connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
 trayIcon->show();

 
}


void MainWidget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason) {
  case QSystemTrayIcon::Trigger:
    if (!isVisible()) {
      show();
    } else {
      hide();
    }
    break;
  case QSystemTrayIcon::DoubleClick:
    //  iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1)
    //				  % iconComboBox->count());
    break;
  case QSystemTrayIcon::MiddleClick:
    //showMessage();
    break;
  default:
    ;
  }
}

void MainWidget::setIcon(int index)
{
   QIcon icon(QPixmap(":hfWilma"));
   trayIcon->setIcon(icon);
   setWindowIcon(icon);
   
   trayIcon->setToolTip("hfWilma");
}

void MainWidget::closeEvent(QCloseEvent *event)
{
     if (trayIcon->isVisible()) {
         QMessageBox::information(this, tr("Systray"),
                                  tr("The program will keep running in the "
                                     "system tray. To terminate the program, "
                                     "choose <b>Quit</b> in the context menu "
                                     "of the system tray entry."));
         hide();
         event->ignore();
     }
}
