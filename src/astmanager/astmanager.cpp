
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

}

void AstManager::connect(QString host, int port) {
  
  tcpSocket->abort();
  tcpSocket->connectToHost(host, port);

  if (tcpSocket->waitForConnected(1000)) {
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
  tcpSocket->flush();
  QStringList lines;
  bool endofconv=false;
  QRegExp rexEoc(".*\n\n$");
  rexEoc.setPatternSyntax(QRegExp::RegExp2);
  QTextCodec *codec = QTextCodec::codecForName("IBM 850");

  while(tcpSocket->waitForReadyRead(3000) || endofconv) {
    qDebug () << tcpSocket->bytesAvailable();

    QByteArray encodedString = tcpSocket->readAll();
    encodedString.replace("\r","");
    QString line = codec->toUnicode(encodedString);
    lines << line;
    endofconv=rexEoc.exactMatch(line);

    //    QRegExp rx("^(.*):(.*)$");
    //if (rx.exactMatch(line)){
    //  qDebug() << rx.pos(0);
    //  qDebug() << rx.pos(1);
    //  state = logedin;
    //}
  }
  //  delete codec;
    qDebug() << lines;
    qDebug() << endofconv;
 
}


void AstManager::logoff() {
  state = logedoff;
  tcpSocket->write("Action: logoff\r\n");
  tcpSocket->write("\r\n");
}

