
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


AstManagerReadThread::AstManagerReadThread()
{
  tcpSocket = new QTcpSocket(this);
  connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readString()));

  qDebug() << "renderthread";
  cacheString.clear();
}




void AstManagerReadThread::readString() {
  //qDebug () << "Size" << str.size();
  QByteArray str = tcpSocket->readAll();
  str.replace("\r","");

  for (int i = 0; i < str.size(); ++i) {
    if (cacheString.endsWith("\n") && str.at(i) == QChar('\n')){
      //qDebug() << cacheString;
      emit astDataRecieved(cacheString);
      cacheString.clear();
    } else {
      cacheString += str.at(i);
    }
  }
}

void AstManagerReadThread::writeString(QString str) {
  tcpSocket->write(str.toAscii());
}

void AstManagerReadThread::connectAst(QString host, int port) {
  
  tcpSocket->abort();
  tcpSocket->connectToHost(host, port);

  if (tcpSocket->waitForConnected(1000)) {
    qDebug("Connected!");
  } else {
    qDebug("Connection failed!");
  }

}



void AstManagerReadThread::run(){
 

  exec();
 
}

/*{
  qDebug() << "blub";
  qDebug() << tcpSocket->readBufferSize ();
  while(tcpSocket->waitForReadyRead(-1)) {
      //qDebug () << tcpSocket->bytesAvailable();
      

      //QString decodedString = codec->toUnicode(encodedString);
      
      processString(encodedString);
      
    }
*/
