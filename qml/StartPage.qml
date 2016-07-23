import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    id: startPage
    orientationLock: PageOrientation.Automatic

    signal open
    signal back
    signal about
    signal settings

    Button {
        id: openButton
        text: qsTr("Open Image")
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -height / 1.5
        Component.onCompleted: width = Math.max(openButton.width, aboutButton.width)
        onClicked: open()
    }

    Button {
        id: aboutButton
        text: qsTr("About")
        anchors.centerIn: parent
        anchors.verticalCenterOffset: height / 1.5
        Component.onCompleted: width = Math.max(openButton.width, aboutButton.width)
        onClicked: about()
    }

    tools: ToolBarLayout {
        id: startPageToolBarLayout
        CustomToolButton {
            iconSource: "toolbar-back"
            onClicked: Qt.quit()
            toolTip: toolTip
            toolTipText: qsTr("Exit")
        }
        CustomToolButton {
            iconSource: "toolbar-menu"
            onClicked: startPageMenu.open()
            toolTip: toolTip
            toolTipText: qsTr("Menu")
        }
    }

    ToolTip {
        id: toolTip
        visible: false
    }

    Menu {
        id: startPageMenu
        MenuLayout {
            MenuItem {
                text: qsTr("Settings")
                onClicked: settings()
            }

            MenuItem {
                text: qsTr("Exit")
                onClicked: Qt.quit()
            }
        }
    }
}
