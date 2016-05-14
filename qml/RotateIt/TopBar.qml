import QtQuick 1.1
import com.nokia.symbian 1.1

Item {
    id: root

    width: 100
    height: (screen.width < screen.height)
            ? ((privateStyle.toolBarHeightPortrait / 4) * 3)
            : ((privateStyle.toolBarHeightLandscape / 4) * 3)

    property string text: "text"
    property string backgroundColor: "grey"

    Rectangle {
        id: background
        anchors.fill: root
        color: backgroundColor
        opacity: 0.4
    }

    Text {
        id: textString
        text: root.text
        color: "white"
        font.pixelSize: root.height / 3 * 2
        anchors.left: root.left
        anchors.leftMargin: platformStyle.paddingMedium
        anchors.verticalCenter: root.verticalCenter
    }

    ProgressBar {
        id: progressBar
        indeterminate: true
        anchors.right: root.right
        anchors.rightMargin: platformStyle.paddingMedium
        anchors.verticalCenter: root.verticalCenter
        width: root.width - textString.width - 3 * platformStyle.paddingMedium
    }
}
