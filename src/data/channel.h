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

#ifndef CHANNEL_H
#define CHANNEL_H
#include <QObject>
#include <QString>
#include "connection.h"

enum ChannelState
  {
    undef,
    rsrvd,
    dailing,
    ringing,
    up,
    down
  };

class Channel : public QObject
{
  Q_OBJECT;
 public:
  Channel();
  ~Channel();
  void setName(QString lname);
  QString getName();

  void setUniqueID(QString lname);
  QString getUniqueID();

  void setCallerIDName(QString lname);
  QString getCallerIDName();

  void setCallerID(QString lname);
  QString getCallerID();

  void setState(ChannelState );
  ChannelState getState();
  QString getStateString();
  void newConnection(Channel *, ConnectionNsp::state );
  Connection *getConnectionPtr();
 signals:
  void stateChanged();

 private:
  QString name;
  QString uniqueid;
  QString callerIDName;
  QString callerID;
  QString privilege;
  ChannelState state;
  Connection *connectionPtr;
};

#endif
