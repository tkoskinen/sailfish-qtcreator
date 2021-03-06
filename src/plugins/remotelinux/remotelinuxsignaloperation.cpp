/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "remotelinuxsignaloperation.h"

#include <ssh/sshremoteprocessrunner.h>
#include <ssh/sshconnection.h>
#include <utils/qtcassert.h>

using namespace RemoteLinux;
using namespace ProjectExplorer;

RemoteLinuxSignalOperation::RemoteLinuxSignalOperation(
        const QSsh::SshConnectionParameters sshParameters)
    : DeviceProcessSignalOperation()
    , m_sshParameters(sshParameters)
    , m_runner(0)
{}

RemoteLinuxSignalOperation::~RemoteLinuxSignalOperation()
{
    if (m_runner) {
        connect(m_runner, SIGNAL(processClosed(int)), m_runner, SLOT(deleteLater()));
        connect(m_runner, SIGNAL(connectionError()), m_runner, SLOT(deleteLater()));
    }
}

static QString signalProcessByPidCommandLine(int pid, int signal)
{
    return QString::fromLatin1("kill -%1 %2").arg(signal).arg(pid);
}

void RemoteLinuxSignalOperation::run(const QString command)
{
    QTC_ASSERT(!m_runner, return);
    m_runner = new QSsh::SshRemoteProcessRunner();
    connect(m_runner, SIGNAL(processClosed(int)), SLOT(runnerProcessFinished()));
    connect(m_runner, SIGNAL(connectionError()), SLOT(runnerConnectionError()));
    m_runner->run(command.toLatin1(), m_sshParameters);
}

void RemoteLinuxSignalOperation::finish()
{
    delete m_runner;
    m_runner = 0;
    emit finished(m_errorMessage);
}

static QString signalProcessByNameCommandLine(const QString &filePath, int signal)
{
    return QString::fromLatin1(
                "cd /proc; for pid in `ls -d [0123456789]*`; "
                "do "
                "if [ \"`readlink /proc/$pid/exe`\" = \"%1\" ]; then "
                "    kill -%2 $pid;"
                "fi; "
                "done").arg(filePath).arg(signal);
}

QString RemoteLinuxSignalOperation::killProcessByNameCommandLine(const QString &filePath) const
{
    return QString::fromLatin1("%1; %2").arg(signalProcessByNameCommandLine(filePath, 15),
                                             signalProcessByNameCommandLine(filePath, 9));
}

QString RemoteLinuxSignalOperation::interruptProcessByNameCommandLine(const QString &filePath) const
{
    return signalProcessByNameCommandLine(filePath, 2);
}

void RemoteLinuxSignalOperation::killProcess(int pid)
{
    run(signalProcessByPidCommandLine(pid, 9));
}

void RemoteLinuxSignalOperation::killProcess(const QString &filePath)
{
    run(killProcessByNameCommandLine(filePath));
}

void RemoteLinuxSignalOperation::interruptProcess(int pid)
{
    run(signalProcessByPidCommandLine(pid, 2));
}

void RemoteLinuxSignalOperation::interruptProcess(const QString &filePath)
{
    run(interruptProcessByNameCommandLine(filePath));
}

void RemoteLinuxSignalOperation::runnerProcessFinished()
{
    m_errorMessage.clear();
    if (m_runner->processExitStatus() != QSsh::SshRemoteProcess::NormalExit) {
        m_errorMessage = m_runner->processErrorString();
    } else if (m_runner->processExitCode() != 0) {
        m_errorMessage = tr("Exit code is %1. stderr:").arg(m_runner->processExitCode())
                + QLatin1Char(' ')
                + QString::fromLatin1(m_runner->readAllStandardError());
    }
    finish();
}

void RemoteLinuxSignalOperation::runnerConnectionError()
{
    m_errorMessage = m_runner->lastConnectionErrorString();
    finish();
}
