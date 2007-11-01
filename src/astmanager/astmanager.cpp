
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
  //qDebug () << "AstData: " << str;

    QStringList lines = str.split("\n");
    //qDebug() << lines;

    QHash<QString, QString> strHash;
    QStringListIterator linesIterator(lines);
    while (linesIterator.hasNext()) {
       QStringList fields = linesIterator.next().split(": ");
       if (fields.size() == 2) {
	 strHash[fields.at(0).toLower()]= fields.at(1).toLower();
       }
    }
      
    //  qDebug() << "Hash: " << strHash;

    if (strHash.contains("event")) {
      if (strHash.value("event") == "newchannel") {
	channelsHash.insert(strHash.value("uniqueid"), new Channel(strHash));
	emit newChannel();
	qDebug() << "Newchannel: " <<  strHash.value("uniqueid");
      } else if (strHash.value("event") == "newstate") {
	emit newState();
	qDebug() << "Newstate  : " <<  strHash.value("uniqueid");
      } else if (strHash.value("event") == "newexten") {
	emit newextension();
	qDebug() << "Newextension : " <<  strHash.value("newexten");
      } else if (strHash.value("event") == "dial") {
	Channel *srcchannel = channelsHash.value(strHash.value("srcuniqueid"));
	Channel *destchannel = channelsHash.value(strHash.value("destuniqueid"));
						 
	emit dial(srcchannel->getName() + " ruft " + destchannel->getName());
	qDebug() << "Dial      : " << strHash.value("srcuniqueid") 
                           << "->" << strHash.value("destuniqueid");
	qDebug() <<              srcchannel->getName() + "(" +srcchannel->getCallerid() + ") ruft " + destchannel->getName() + "(" +destchannel->getCallerid() + ")";
      } else if (strHash.value("event") == "link") {
	emit link("");
	qDebug() << "Link      : " << strHash.value("uniqueid1") << "->" << strHash.value("Uniqueid2");
      } else if (strHash.value("event") == "hangup") {
	Channel *channel = channelsHash.value(strHash.value("uniqueid"));
	channelsHash.remove(strHash.value("uniqueid"));
	delete channel;
	emit hangup("");
	qDebug() << "Hangup    : " <<  strHash.value("uniqueid");
      }
    }  
}


