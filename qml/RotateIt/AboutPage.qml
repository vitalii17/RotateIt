import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    id: root
    orientationLock: PageOrientation.Automatic

    signal back

    Flickable {
        id: flickArea
        anchors.fill: parent
        anchors.topMargin: platformStyle.paddingSmall
        anchors.leftMargin: platformStyle.paddingMedium
        anchors.rightMargin: platformStyle.paddingMedium
        anchors.bottomMargin: platformStyle.paddingSmall
        contentWidth: width
        contentHeight: column.height + 4 * aboutPageToolBarLayout.height

        Column {
            id: column
            width: parent.width
            spacing: 10

            Text {
                id: text
                width: parent.width
                textFormat: Text.RichText
                wrapMode: Text.WordWrap
                color: "white"
                onLinkActivated: Qt.openUrlExternally(link)

                text: qsTr("<h2><p align = \"center\">Rotate It</p></h2>\
    <p>Fix your photos directly on your smartphone. Correct the \
    \"littered horizon\" has never been so easy!</p>\
    <p>Developer: <a href=\"http://m.vk.com/vitalis17\">Vitalii Shunkov</a> \
    (mail: Shynkov@bigmir.net)</p>\
    <p>Special thanks: <a href=\"http://m.vk.com/symbian_zone\">\"Symbian Zone\"</a> and \
    <a href=\"http://forum.dailymobile.net\">\"dailymobile.net\"</a></p>\
    <h3><p align = \"center\">License</p></h3>\
    <h4><p align = \"center\">The MIT License (MIT)</p></h4>\
    <p alifn = \"center\">Copyright (c) 2016 Vitalii Shunkov</p>\
    <p>Permission is hereby granted, free of charge, to any person obtaining a copy \
    of this software and associated documentation files (the \"Software\"), to deal \
    in the Software without restriction, including without limitation the rights \
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell \
    copies of the Software, and to permit persons to whom the Software is \
    furnished to do so, subject to the following conditions:</p>\
    <p>The above copyright notice and this permission notice shall be included in all \
    copies or substantial portions of the Software.<p/>\
    <p>THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR \
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE \
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, \
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE \
    SOFTWARE.</p>")
            }
            // Here next item
        }
    }

    Rectangle {
        id: toolBarSubstrate
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: root.bottom
        height: aboutPageToolBarLayout.height
        opacity: 0.5
        color: "grey"
    }

    tools: ToolBarLayout {
        id: aboutPageToolBarLayout
        ToolButton {
            iconSource: "toolbar-back"
            onClicked: {
                back()
                root.destroy()
            }
        }
        ToolButton {
            iconSource: "toolbar-menu"
            onClicked: aboutPageMenu.open()
        }
    }

    Menu {
        id: aboutPageMenu
        MenuLayout {
            MenuItem {
                text: qsTr("Back")
                onClicked: {
                    back()
                    root.destroy()
                }
            }
        }
    }
}
