import QtQuick 1.1
import com.nokia.symbian 1.1
import "UiConstants.js" as UiConstants

BaseListElement {
    id: root

    property bool checked
    onCheckedChanged: switchElement.checked = checked

    onClicked: checked = !checked

    Switch {
        id: switchElement
        anchors.verticalCenter: root.paddingItem.verticalCenter
        anchors.right: root.paddingItem.right
        onCheckedChanged: root.checked = checked
    }
}
