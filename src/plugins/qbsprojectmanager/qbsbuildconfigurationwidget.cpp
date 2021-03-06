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

#include "qbsbuildconfigurationwidget.h"

#include "qbsbuildconfiguration.h"

#include <projectexplorer/target.h>
#include <projectexplorer/project.h>
#include <utils/detailswidget.h>
#include <utils/pathchooser.h>

#include <QGridLayout>
#include <QLabel>
#include <QWidget>

namespace QbsProjectManager {
namespace Internal {

QbsBuildConfigurationWidget::QbsBuildConfigurationWidget(QbsProjectManager::Internal::QbsBuildConfiguration *bc) :
    m_buildConfiguration(bc),
    m_ignoreChange(false)
{
    connect(bc, SIGNAL(buildDirectoryChanged()), this, SLOT(buildDirectoryChanged()));
    connect(bc, SIGNAL(environmentChanged()), this, SLOT(environmentHasChanged()));

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setMargin(0);
    Utils::DetailsWidget *container = new Utils::DetailsWidget(this);
    container->setState(Utils::DetailsWidget::NoSummary);
    vbox->addWidget(container);

    QWidget *details = new QWidget(container);
    container->setWidget(details);

    QGridLayout *layout = new QGridLayout(details);
    layout->setMargin(0);
    layout->addWidget(new QLabel(tr("Build directory:"), 0, 0));

    m_buildDirChooser = new Utils::PathChooser;
    m_buildDirChooser->setExpectedKind(Utils::PathChooser::Directory);
    m_buildDirChooser->setBaseDirectory(bc->target()->project()->projectDirectory());
    m_buildDirChooser->setEnvironment(bc->environment());
    layout->addWidget(m_buildDirChooser, 0, 1);

    connect(m_buildDirChooser, SIGNAL(changed(QString)), this, SLOT(buildDirEdited()));

    buildDirectoryChanged();
}

void QbsBuildConfigurationWidget::buildDirEdited()
{
    m_ignoreChange = true;
    m_buildConfiguration->setBuildDirectory(m_buildDirChooser->fileName());
}

void QbsBuildConfigurationWidget::buildDirectoryChanged()
{
    if (m_ignoreChange)
        return;

    m_buildDirChooser->setPath(m_buildConfiguration->rawBuildDirectory().toString());
}

void QbsBuildConfigurationWidget::environmentHasChanged()
{
    m_buildDirChooser->setEnvironment(m_buildConfiguration->environment());
}

} // namespace Internal
} // namespace QbsProjectManager
