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

#ifndef ASTMANAGER_H
#define ASTMANAGER_H
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include "astmanagerreadthread.h"
#include "channel.h"
#include "connection.h"

enum StateType
  {
    logedoff,
    logedin
  };

class AstManager : public QObject
{
  Q_OBJECT;
 public:
   AstManager();
 signals:
   void writeString(QString);
   void newChannel();
   void newState();
   void newextension();
   void dial(QString);
   void link(QString);
   void hangup(QString);
   void somethingChanged();
   void connectChange(QString,int);  
 public slots:
   void connectAst(QString , int );
   void login( QString , QString );
   void setEventFilter(QString );
   void processAstData(QString);
   QHash<QString,Channel*> getChannelHash();
   void logoff();
 private:
   ChannelState convertToChannelState(QString mystateString);

   QHash<QString,Channel*> channelsHash;
   QHash<QString,Connection*> connectionsHash;
   StateType state;
   QTcpSocket *tcpSocket;
   AstManagerReadThread *astReadThread;
  
};

#endif
