import QtQuick 1.1

Item {
    id: root

    signal pressed
    signal released

    height: 50

    property real amplitude: 1
    property real stepSize: 0.1
    property real value: privateFunctions.round((((slider.x + slider.width / 2 -
                                                   containerItem.width / 2) /
                                                  containerItem.width / 2) * 4) *
                                                amplitude + offset, stepSize)
    property real offset: 0

    onOffsetChanged: {
        if(offset >= 360) {
            while(offset >= 360) {
                offset = offset - 360
            }
        }
        if(offset <= -360) {
            while(offset <= -360) {
                offset = offset + 360
            }
        }
    }

    function reset() {
        slider.x = containerItem.width / 2 - slider.width / 2 + offset
    }

    function blink() {
        borderAnimation.start()
    }

    QtObject {
        id: privateFunctions
        function round(value, stepSize) {
            return Math.ceil(value / stepSize) * stepSize
        }
    }

    Item {
        id: containerItem

        height: root.height
        width: root.width - slider.width
        anchors.centerIn: root

        Rectangle {
            id: slider
            color: "grey"
            opacity: 0.5
            width: 75
            height: root.height
            x: containerItem.width / 2 - width / 2
            border.color: color
            border.width: 3

            Text {
                text: root.value
                color: "white"
                font.pixelSize: 35
                anchors.centerIn: parent
            }

            SequentialAnimation {
                id: borderAnimation
                PropertyAnimation {
                    target: slider
                    property: "border.color"
                    to: "blue"
                }
                PropertyAnimation {
                    target: slider
                    property: "border.color"
                    to: target.color
                }
            }
        }

        MouseArea {
            id: mouseArea
            anchors.left: containerItem.left
            anchors.leftMargin: -slider.width / 2
            anchors.right: containerItem.right
            anchors.rightMargin: -slider.width / 2
            anchors.verticalCenter: slider.verticalCenter
            height: slider.height
            drag.target: slider
            drag.axis: Drag.XAxis
            drag.minimumX: 0 - drag.target.width / 2
            drag.maximumX: parent.width - drag.target.width / 2
            onPressed: {
                root.pressed()
                blink()
            }
            onReleased: {
                root.released()
            }
        }
    }
}