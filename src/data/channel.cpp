
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
#include <QDebug>
#include "channel.h"

Channel::Channel()
{
  connectionPtr = 0;
  name.clear();
  uniqueid.clear();
  state = undef;
}

Channel::~Channel() {
  if ( connectionPtr != 0 ) {
    delete connectionPtr;
  }
  emit stateChanged();
  qDebug() << "Hangup    : " <<  uniqueid;
}
void Channel::setName(QString lname) {
  name = lname;
  qDebug() << "setName    : " <<  name;

}

QString Channel::getName() {  
  return name;
}

void Channel::setState(ChannelState lstate) {
  state = lstate;
}

ChannelState Channel::getState() {
  return state;
}

void Channel::newConnection(Channel *sourceChannel, ConnectionNsp::state mystate ) {
  connectionPtr = new Connection( sourceChannel, this, mystate );
}

Connection *Channel::getConnectionPtr() {
  return connectionPtr;
}

void Channel::setUniqueID(QString luniqueid) {
  uniqueid = luniqueid;
  qDebug() << "Uniqueid    : " <<  uniqueid;
}

QString Channel::getUniqueID() {
  return uniqueid;
}

void Channel::setCallerIDName(QString lname){
  callerIDName = lname;
  qDebug() << "CallerIDName    : " <<  callerIDName;
}

QString Channel::getCallerIDName() {
  return callerIDName;
}

void Channel::setCallerID(QString lname){
  callerID=lname;
  qDebug() << "CallerID    : " <<  callerID;
  
}

QString Channel::getCallerID() {
  return callerID;
}

QString Channel::getStateString(){
  QString mystateString="";
  if (state == rsrvd) {
    mystateString = tr("rsrvd");
  } else if (state == dailing) {
    mystateString = tr("dailing");
  } else if (state == ringing) {
    mystateString = tr("ringing");
  } else if (state == up) {
    mystateString = tr("up");
  } else if (state == down) {
    mystateString = tr("down");
  } else {
    qWarning() << "unknown ChannelState " << state;
  } 

  return mystateString;
}
