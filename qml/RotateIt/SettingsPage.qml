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
                subTitleText: "It has not affect the final image"
                checked: settings.spthPreview
                onCheckedChanged: settings.spthPreview = checked
            }

            CheckableListElement {
                titleText: "Anti-aliasing in final"
                subTitleText: "True is recommended! It will be saved in file"
                checked: settings.spthFinal
                onCheckedChanged: settings.spthFinal = checked
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
