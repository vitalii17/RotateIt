import QtQuick 1.1
import "UiConstants.js" as UiConstants

Item {
    id: root
    width: (parent.height > parent.width) ? parent.width / 3 * 2 : parent.width / 2
    height: (parent.height > parent.width) ? width / 2 : parent.height / 4
    y: (parent.height - sourceY) / 2 - (height / 2)
    anchors.horizontalCenter: parent.horizontalCenter
    opacity: 0

    property string text
    property int sourceY: 100 // Will be changed in 'show' function

    Component.onCompleted: {
        if (visible)
            show(text)
    }

    onOpacityChanged: {
        if (opacity == 0) {
            visible = false
        }
        else {
            visible = true
        }
    }

    function show(text, sourceItem) {
        opacity = 1
        visible = true
        root.text = text
        sourceY = sourceItem.mapToItem(sourceItem.parent, 0, 0).y
    }

    function hide() {
        opacity = 0
    }

    Rectangle {
        id: backgroundRect
        radius: UiConstants.rectRadiusMedium
        opacity: UiConstants.dialogBackOpacity
        anchors.fill: parent
        color: "black"
    }
    Text {
        id: text
        text: root.text
        color: "white"
        smooth: true
        anchors.centerIn: backgroundRect
        font.pointSize: 14
    }

    Behavior on opacity {
        PropertyAnimation {}
    }
}

