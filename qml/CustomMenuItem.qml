import QtQuick 1.1
import com.nokia.symbian 1.1

MenuItem {
    id: root

    signal clicked
    property bool disabled: false
    property alias text: textArea.text

    property real platformLeftMargin: platformStyle.paddingLarge

    Text {
        id: textArea
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: platformLeftMargin
        anchors.right: parent.right
        anchors.rightMargin: platformStyle.paddingSmall
        z: 1

        font.family: platformStyle.fontFamilyRegular
        font.pixelSize: platformStyle.fontSizeLarge

        color: internal.textColor()
        horizontalAlignment: Text.AlignLeft
        elide: Text.ElideRight
    }

    QtObject {
        id: internal

        function bg_postfix() {
            if (mouseArea.pressed && mouseArea.containsMouse)
                return "pressed"
            else
                return "popup_normal"
        }

        function textColor() {
            if (disabled)
                return root.platformInverted ? platformStyle.colorDisabledLightInverted
                                             : platformStyle.colorDisabledLight
//            else if (activeFocus && symbian.listInteractionMode == Symbian.KeyNavigation)
//                return root.platformInverted ? platformStyle.colorHighlightedInverted
//                                             : platformStyle.colorHighlighted
            else if (mouseArea.pressed && mouseArea.containsMouse)
                return root.platformInverted ? platformStyle.colorPressedInverted
                                             : platformStyle.colorPressed
            else
                return root.platformInverted ? platformStyle.colorNormalLightInverted
                                             : platformStyle.colorNormalLight
        }
    }

    BorderImage {
        source: privateStyle.imagePath("qtg_fr_list_" + internal.bg_postfix(), root.platformInverted)
        border { left: 20; top: 20; right: 20; bottom: 20 }
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: root
        onClicked: root.clicked()
    }
}

