import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    id: startPage
    orientationLock: PageOrientation.Automatic

    signal open
    signal back
    signal about

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
        ToolButton {
            iconSource: "toolbar-back"
            onClicked: Qt.quit()
        }
        ToolButton {
            iconSource: "toolbar-menu"
            onClicked: startPageMenu.open()
        }
    }

    Menu {
        id: startPageMenu
        MenuLayout {
            MenuItem {
                text: qsTr("Exit")
                onClicked: Qt.quit()
            }
        }
    }
}
