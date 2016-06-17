import QtQuick 1.1
import com.nokia.symbian 1.1
import settings 1.0
import "SettingsPageElements"

Page {
    id: root
    orientationLock: PageOrientation.Automatic

    signal back

    Flickable{
        anchors.fill: parent
        contentWidth: width
        contentHeight: column.height + settingsPageToolBarLayout.height

        Column {
            id: column
            width: parent.width

            CheckableListElement {
                titleText: "Anti-aliasing in preview"
                subTitleText: "Disable if you have a low-performance CPU"
                checked: settings.spthPreview
                onCheckedChanged: settings.spthPreview = checked
            }
        }
    }

    tools: ToolBarLayout {
        id: settingsPageToolBarLayout
        ToolButton {
            iconSource: "toolbar-back"
            onClicked: {
                back()
                root.destroy()
            }
        }
        ToolButton {
            iconSource: "toolbar-menu"
            onClicked: settingsPageMenu.open()
        }
    }

    Menu {
        id: settingsPageMenu
        MenuItem {
            text: qsTr("Exit")
            onClicked: Qt.quit()
        }
    }

    Settings {
        id: settings
    }
}
