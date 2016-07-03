import QtQuick 1.1
import com.nokia.symbian 1.1

ListItem {
    id: root

    property string titleText
    property string subTitleText

    Column {
        anchors.top: root.paddingItem.top
        anchors.left: root.paddingItem.left
        anchors.bottom: root.paddingItem.bottom
        width: root.width * 3 / 4
        ListItemText {
            role: "Title"
            text: root.titleText
            width: parent.width
        }
        ListItemText {
            role: "SubTitle"
            text: root.subTitleText
            width: parent.width
        }
    }
}
