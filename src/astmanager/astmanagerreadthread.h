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

#ifndef ASTMANAGERREADTHREAD_H
#define ASTMANAGERREADTHREAD_H
#include <QThread>
#include <QString>
#include <QTcpSocket>


class AstManagerReadThread : public QThread
{
  Q_OBJECT;
 public:
   AstManagerReadThread(QTcpSocket *);
 signals:
   void astDataRecieved(QString);
 public slots:
   void run( );
 private:
  void processString(QString);
  QString cacheString;
  QTcpSocket *tcpSocket;
  
};

#endif
