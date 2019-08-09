/*
  selectionmodelserver.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2013-2018 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "selectionmodelserver.h"
#include "server.h"

#include <QTimer>

using namespace GammaRay;

SelectionModelServer::SelectionModelServer(const QString &objectName, QAbstractItemModel *model,
                                           QObject *parent)
    : NetworkSelectionModel(objectName, model, parent)
    , m_timer(new QTimer(this))
    , m_monitored(false)
{
    // We do use a timer to group requests to avoid network overhead
    m_timer->setSingleShot(true);
    m_timer->setInterval(125);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    m_myAddress = Server::instance()->registerObject(objectName, this, Server::ExportNothing);
    Server::instance()->registerMessageHandler(m_myAddress, this, "newMessage");
    Server::instance()->registerMonitorNotifier(m_myAddress, this, "modelMonitored");
    connect(Endpoint::instance(), SIGNAL(disconnected()), this, SLOT(modelMonitored()));
}

SelectionModelServer::~SelectionModelServer()
{
}

bool SelectionModelServer::isConnected() const
{
    return NetworkSelectionModel::isConnected() && m_monitored;
}

void SelectionModelServer::timeout()
{
    sendSelection();
}

void SelectionModelServer::modelMonitored(bool monitored)
{
    if (m_monitored == monitored)
        return;
    if (m_monitored)
        disconnectModel();
    m_monitored = monitored;
    if (m_monitored)
        connectModel();
}

void SelectionModelServer::connectModel()
{
    Q_ASSERT(model());
    connect(model(), SIGNAL(modelReset()),
            m_timer, SLOT(start()));
    connect(model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            m_timer, SLOT(start()));
    connect(model(), SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),
            m_timer, SLOT(start()));
    connect(model(), SIGNAL(columnsInserted(QModelIndex,int,int)),
            m_timer, SLOT(start()));
    connect(model(), SIGNAL(columnsMoved(QModelIndex,int,int,QModelIndex,int)),
            m_timer, SLOT(start()));
    connect(model(), SIGNAL(layoutChanged()),
            m_timer, SLOT(start()));
}

void SelectionModelServer::disconnectModel()
{
    if (!model())
        return;

    disconnect(model(), SIGNAL(modelReset()),
               m_timer, SLOT(start()));
    disconnect(model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
               m_timer, SLOT(start()));
    disconnect(model(), SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),
               m_timer, SLOT(start()));
    disconnect(model(), SIGNAL(columnsInserted(QModelIndex,int,int)),
               m_timer, SLOT(start()));
    disconnect(model(), SIGNAL(columnsMoved(QModelIndex,int,int,QModelIndex,int)),
               m_timer, SLOT(start()));
    disconnect(model(), SIGNAL(layoutChanged()), m_timer, SLOT(start()));
}