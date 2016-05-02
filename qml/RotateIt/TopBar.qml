import QtQuick 1.1
import com.nokia.symbian 1.1

Item {
    id: root

    width: 100
    height: (screen.width < screen.height)
            ? privateStyle.toolBarHeightPortrait
            : privateStyle.toolBarHeightLandscape

    property string text: "text"
    property string background

    Image {
        id: backgroundImage
        anchors.fill: root
        source: root.background
    }

    ProgressBar {
        id: progressBar
        indeterminate: true
        anchors.left: root.left
        anchors.leftMargin: platformStyle.paddingMedium
        anchors.verticalCenter: root.verticalCenter
        width: root.width - textString.width - 3 * platformStyle.paddingMedium
    }

    Text {
        id: textString
        text: root.text
        color: "grey"
        font.pixelSize: 20
        anchors.right: root.right
        anchors.verticalCenter: root.verticalCenter
        anchors.rightMargin: platformStyle.paddingMedium
    }
}
