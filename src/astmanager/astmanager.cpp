
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

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QTextCodec>
#include <QRegExp>
#include "astmanager.h"


AstManager::AstManager()
{
  state = logedoff;
  tcpSocket = new QTcpSocket(this);
  astReadThread = new AstManagerReadThread(tcpSocket);
  QObject::connect(astReadThread,SIGNAL(astDataRecieved(QString)),this,SLOT(processAstData(QString)));
}

void AstManager::connect(QString host, int port) {
  
  tcpSocket->abort();
  tcpSocket->connectToHost(host, port);

  if (tcpSocket->waitForConnected(1000)) {
    astReadThread->start();
    qDebug("Connected!");
  } else {
    qDebug("Connection failed!");
  }

}

void AstManager::login(QString username, QString secret){
  tcpSocket->write("Action: login\r\n");
  tcpSocket->write(QString("Username: "+username+"\r\n").toAscii());
  tcpSocket->write(QString("Secret: "+secret+"\r\n").toAscii());
  tcpSocket->write("\r\n");
}

void AstManager::setEventFilter(QString eventmask){
  tcpSocket->write("Action: events\r\n");
  tcpSocket->write(QString("Eventmask: "+eventmask+"\r\n").toAscii());
  tcpSocket->write("\r\n");
}


void AstManager::logoff() {
  tcpSocket->write("Action: logoff\r\n");
  tcpSocket->write("\r\n");
}


void AstManager::processAstData(QString str) {
  
  qDebug () << "AstData: " << str;
  

}
