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

import QtQuick 2.0
import HelperWidgets 2.0
import QtQuick.Layouts 1.0

Section {
    anchors.left: parent.left
    anchors.right: parent.right
    caption: qsTr("Advanced")

    SectionLayout {
        rows: 4

        OriginControl {
            backendValue: backendValues.transformOrigin
        }

        SecondColumnLayout {
        }

        Label {
            text: qsTr("Scale")
        }

        SecondColumnLayout {
            SpinBox {
                backendValue: backendValues.scale
                hasSlider: true
                decimals: 2
                minimumValue: 0.01
                stepSize: 0.1
                maximumValue: 10
                Layout.preferredWidth: 80
            }
            ExpandingSpacer {
            }
        }
        Label {
            text: qsTr("Rotation")
        }
        SecondColumnLayout {
            SpinBox {
                backendValue: backendValues.rotation
                hasSlider: true
                decimals: 2
                minimumValue: -360
                maximumValue: 360
                Layout.preferredWidth: 80
            }
            ExpandingSpacer {
            }
        }
        Label {
            text: "Z"
        }
        SecondColumnLayout {
            SpinBox {
                backendValue: backendValues.z
                hasSlider: true
                minimumValue: -100
                maximumValue: 100
                Layout.preferredWidth: 80
            }
            ExpandingSpacer {
            }
        }

        Label {
            visible: majorQtQuickVersion > 1
            text: qsTr("Enabled")
        }
        SecondColumnLayout {
            visible: majorQtQuickVersion > 1
            CheckBox {
                backendValue: backendValues.enabled
                text: qsTr("Accept mouse and keyboard events")
            }
            ExpandingSpacer {
            }
        }

        Label {
            visible: majorQtQuickVersion > 1
            text: qsTr("Smooth")
        }
        SecondColumnLayout {
            visible: majorQtQuickVersion > 1
            CheckBox {
                backendValue: backendValues.smooth
                text: qsTr("Smooth sampling active")
            }
            ExpandingSpacer {
            }
        }

        Label {
            visible: majorQtQuickVersion > 1
            text: qsTr("Antialiasing")
        }
        SecondColumnLayout {
            visible: majorQtQuickVersion > 1
            CheckBox {
                backendValue: backendValues.antialiasing
                text: qsTr("Anti-aliasing active")
            }
            ExpandingSpacer {
            }
        }

    }
}