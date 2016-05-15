import QtQuick 1.1

Item {
    id: root

    signal pressed

    height: 50

    property real amplitude: 1
    property real stepSize: 0.1
    property real value: privateFunctions.round((((slider.x + slider.width / 2 - containerItem.width / 2) /
                          containerItem.width / 2) * 4) * amplitude, stepSize)

    function reset() {
        slider.x = containerItem.width / 2 - slider.width / 2
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
                onRunningChanged: slider.border.width = running ? 3 : 0
            }
        }

        MouseArea {
            id: mouseArea
            anchors.left: containerItem.left
            anchors.right: containerItem.right
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
        }
    }
}
