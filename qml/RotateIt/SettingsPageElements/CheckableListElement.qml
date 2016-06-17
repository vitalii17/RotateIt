import QtQuick 1.1
import com.nokia.symbian 1.1

ListItem {
    id: root

    property string titleText
    property string subTitleText
    property bool checked
    onCheckedChanged: switchElement.checked = checked

    Column {
        anchors.top: root.paddingItem.top
        anchors.left: root.paddingItem.left
        anchors.bottom: root.paddingItem.bottom
        width: root.width * 3 / 4
        ListItemText {
            role: "Title"
            text: root.titleText
        }
        ListItemText {
            role: "SubTitle"
            text: root.subTitleText
        }
    }
    Switch {
        id: switchElement
        anchors.verticalCenter: root.paddingItem.verticalCenter
        anchors.right: root.paddingItem.right
        onCheckedChanged: root.checked = checked
    }
}
