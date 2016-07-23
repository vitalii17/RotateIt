import QtQuick 1.1
import com.nokia.symbian 1.1
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

            CheckableListElement {
                titleText: qsTr("Vibrate after saving")
                subTitleText: qsTr("It helps wait until the image is saved")
                checked: settings.vibraOn
                onCheckedChanged: settings.vibraOn = checked
            }

            CheckableListElement {
                titleText: qsTr("Landscape mode")
                subTitleText: qsTr("Enable for auto-rotate to landscape")
                checked: settings.landscapeMode
                onCheckedChanged: settings.landscapeMode = checked
            }

            NumberListElement {
                titleText: qsTr("Quality of final JPEG")
                subTitleText: qsTr("Set 90 or more for better quality")
                dialogTitleText: qsTr("Quality")
                minimumValue: 0
                maximumValue: 100
                stepSize: 1
                defaultValue: 96
                onIsDefaultChanged: settings.isDefaultQuality = isDefault
                onValueChanged: settings.quality = value
                Component.onCompleted: {
                    isDefault = settings.isDefaultQuality
                    value = settings.quality
                }
            }

            CheckableListElement {
                titleText: qsTr("Slider arrows")
                subTitleText: qsTr("Click to disable")
                checked: settings.sliderArrowsEnabled
                onCheckedChanged: settings.sliderArrowsEnabled = checked
            }
        }
    }

    tools: ToolBarLayout {
        id: settingsPageToolBarLayout
        CustomToolButton {
            iconSource: "toolbar-back"
            toolTip: toolTip
            toolTipText: qsTr("Back")
            onClicked: {
                back()
                root.destroy()
            }
        }
        CustomToolButton {
            iconSource: "toolbar-menu"
            toolTip: toolTip
            toolTipText: qsTr("Menu")
            onClicked: settingsPageMenu.open()
        }
    }

    ToolTip {
        id: toolTip
        visible: false
    }

    Menu {
        id: settingsPageMenu
        MenuItem {
            text: qsTr("Back")
            onClicked: {
                back()
                root.destroy()
            }
        }
    }
}
