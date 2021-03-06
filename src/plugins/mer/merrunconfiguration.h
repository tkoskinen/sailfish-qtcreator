/****************************************************************************
**
** Copyright (C) 2012 - 2014 Jolla Ltd.
** Contact: http://jolla.com/
**
** This file is part of Qt Creator.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Digia.
**
****************************************************************************/

#ifndef MERRUNCONFIGURATION_H
#define MERRUNCONFIGURATION_H

#include <remotelinux/remotelinuxrunconfiguration.h>

namespace Mer {
namespace Internal {

class MerRunConfiguration : public RemoteLinux::RemoteLinuxRunConfiguration
{
    Q_OBJECT
public:
    MerRunConfiguration(ProjectExplorer::Target *parent, const Core::Id id,
                        const QString &proFilePath);
    bool isEnabled() const;

    Utils::Environment environment() const;
    QString defaultRemoteExecutableFilePath() const;
    QString disabledReason() const;
protected:
    friend class MerRunConfigurationFactory;

    MerRunConfiguration(ProjectExplorer::Target *parent,
                        MerRunConfiguration *source);    
    void ctor();
private:
    mutable QString m_disabledReason;
};

} // namespace Internal
} // namespace Mer

#endif // MERRUNCONFIGURATION_H
