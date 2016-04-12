import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    id: aboutPage
    orientationLock: PageOrientation.Automatic

    signal back

    tools: ToolBarLayout {
        id: startPageToolBarLayout
        ToolButton {
            iconSource: "toolbar-back"
            onClicked: back()
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
                text: qsTr("Exit")
                onClicked: Qt.quit()
            }
        }
    }
}
