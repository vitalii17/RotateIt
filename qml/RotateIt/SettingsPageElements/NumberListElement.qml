import QtQuick 1.1
import com.nokia.symbian 1.1
import "UiConstants.js" as UiConstants

BaseListElement {
    id: root

    property string dialogTitleText
    property int minimumValue
    property int maximumValue
    property int stepSize
    property bool isDefault
    property int defaultValue
    property int value

    onValueChanged: slider.value = value
    onIsDefaultChanged: checkBox.checked = isDefault

    TextField {
        text: root.value
        width: UiConstants.listControlsWidth
        readOnly: true
        anchors.verticalCenter: root.paddingItem.verticalCenter
        anchors.right: root.paddingItem.right
        MouseArea {
            anchors.fill: parent
            onClicked: dialog.open()
        }
    }

    CommonDialog {
        id: dialog
        titleText: root.dialogTitleText + ": " + slider.value
        buttonTexts: [qsTr("OK"), qsTr("Cancel")]
        onButtonClicked: {
            if(index === 0){
                root.isDefault = checkBox.checked
                root.value = slider.value
            }
            else {
                checkBox.checked = root.isDefault
                slider.value = root.value
            }
        }

        content: Column {
            id: column
            width: parent.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: platformStyle.paddingMedium
            anchors.rightMargin: platformStyle.paddingMedium

            Item {
                id: topPadding
                width: parent.width
                height: platformStyle.paddingMedium
            }

            CheckBox {
                id: checkBox
                text: qsTr("Default")
                onCheckedChanged: {
                    slider.enabled = checked ? false : true
                    slider.opacity = checked ? 0.5 : 1
                }
            }

            Slider {
                id: slider
                width: parent.width
                orientation: Qt.Horizontal
                minimumValue: root.minimumValue
                maximumValue: root.maximumValue
                stepSize: root.stepSize
                onEnabledChanged: value = enabled ? value : root.defaultValue
            }
        }
    }
}
