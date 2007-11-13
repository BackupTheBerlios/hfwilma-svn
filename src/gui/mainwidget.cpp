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
#include <QCoreApplication>
#include <QSettings>

MainWidget::MainWidget()
{
  QCoreApplication::setOrganizationName("hfeld");
  QCoreApplication::setOrganizationDomain("hfeld.de");
  QCoreApplication::setApplicationName("hfwilma");
  
  textedit = new QTextEdit(this);
  textedit->setLineWrapMode(QTextEdit::NoWrap);
  textedit->setReadOnly(true);
  connect(this,SIGNAL(newToolTip(QString)),textedit,SLOT(setText(QString)));
  setCentralWidget (textedit);

  readSettings();
  trayIcon = new QSystemTrayIcon(this);
  setIcon(5);
  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

  closeApp = new QAction ("Schliessen",this);
  connect(closeApp,SIGNAL(triggered()),this,SLOT(close()));
  trayMenu = new QMenu(this);
  trayMenu->addAction(closeApp);
  trayIcon->setContextMenu(trayMenu);

  trayIcon->show();
  astmanager = new AstManager();

  QSettings settings;
  settings.beginGroup("AstManager");
  astmanager->connectAst(settings.value("host").toString(),settings.value("port").toInt());
  astmanager->login(settings.value("username").toString(),settings.value("password").toString());
  settings.endGroup();

  astmanager->setEventFilter("on");
  
  connect(astmanager,SIGNAL(somethingChanged()),this,SLOT(genToolTip()),Qt::DirectConnection);
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
  
     if (isVisible() && trayIcon->isVisible()) {
         QMessageBox::information(this, tr("Systray"),
                                  tr("The program will keep running in the "
                                     "system tray. To terminate the program, "
                                     "choose <b>Quit</b> in the context menu "
                                     "of the system tray entry."));
         writeSettings();
         hide();
         event->ignore();
     } 

   //  if (userReallyWantsToQuit()) {
	 //      event->accept();
	 // } else {
	 // event->ignore();
	 //}

}

QString MainWidget::collectToolTipData() {
  
  QString tooltip;
  QHash<QString,Channel*> channelHash = astmanager->getChannelHash();
  
  QHashIterator<QString,Channel*> i(channelHash);
  
  while (i.hasNext()) {
    i.next();
    //    cout << i.key() << ": " << i.value() << endl;
    Channel *channel = i.value();
    Connection *connection = channel->getConnectionPtr();

    tooltip += channel->getCallerID() + " / " + channel->getName() + " ";
    
    if (connection != 0) {
      tooltip += tr(" is called by ");
      tooltip += connection->getSourceChannelPtr()->getCallerID();
      
    } 
      
    tooltip += " ("+channel->getStateString()+")";
    
    tooltip += "\n";

  }
  qDebug()<< "Tooltip" << tooltip;
 
  return tooltip;
}

void MainWidget::genToolTip() {
  QString tooltip=collectToolTipData();
  emit newToolTip(tooltip);
  trayIcon->setToolTip(tooltip);
  //if (!tooltip.isEmpty())
   // trayIcon->showMessage("Änderung",tooltip);
}


 void MainWidget::writeSettings()
 {
     QSettings settings;

     settings.beginGroup("MainWindow");
     settings.setValue("size", size());
     settings.setValue("pos", pos());
     settings.endGroup();
 }

 void MainWidget::readSettings()
 {
     QSettings settings;

     settings.beginGroup("MainWindow");
     resize(settings.value("size", QSize(400, 400)).toSize());
     move(settings.value("pos", QPoint(200, 200)).toPoint());
     settings.endGroup();
 }


 
