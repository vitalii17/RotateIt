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
                titleText: qsTr("Anti-aliasing in preview")
                subTitleText: qsTr("Disable to speed up GUI")
                checked: settings.spthPreview
                onCheckedChanged: settings.spthPreview = checked
            }

            NumberListElement {
                titleText: qsTr("Quality of final JPEG")
                subTitleText: qsTr("Set 90 or more for better quality")
                dialogTitleText: qsTr("Quality")
                minimumValue: 0
                maximumValue: 100
                stepSize: 1
                defaultValue: 95
                onIsDefaultChanged: settings.isDefaultCompression = isDefault
                onValueChanged: settings.compression = 100 - value
                Component.onCompleted: {
                    isDefault = settings.isDefaultCompression
                    value = 100 - settings.compression
                }
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
