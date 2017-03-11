import QtQuick 1.1

Item {
    id: root

    signal pressed
    signal released

    height: 55

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

    Rectangle {
        id: leftLineRect
        anchors.left: parent.left
        width: slider.x + slider.width / 2
        anchors.verticalCenter: parent.verticalCenter
        height: 2
        color: "grey"
        opacity: 0.5
    }
    Rectangle {
        id: rightLineRect
        width: parent.width - leftLineRect.width - slider.width - slider.border.width
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: 2
        color: "grey"
        opacity: 0.5
    }

    Item {
        id: containerItem

        height: root.height
        width: root.width - slider.width - slider.border.width
        anchors.centerIn: root

        Rectangle {
            id: slider
            anchors.verticalCenter: parent.verticalCenter
            color: "grey"
            radius: width / 2
            opacity: 0.5
            width: 85
            height: width
            smooth: true
            x: containerItem.width / 2 - width / 2
            border.color: color
            border.width: 3

            Text {
                text: root.value
                color: "white"
                smooth: true
                font.pixelSize: (Math.abs(root.value) <= 10) ? slider.width / 2 :
                                                               slider.width / 3
                anchors.centerIn: parent
            }

            ParallelAnimation {
                id: borderAnimation
                SequentialAnimation {
                    PropertyAnimation {
                        targets: [leftLineRect, rightLineRect]
                        properties: "border.color"
                        to: "blue"
                    }
                    PropertyAnimation {
                        targets: [leftLineRect, rightLineRect]
                        properties: "border.color"
                        to: leftLineRect.color
                    }
                }
                SequentialAnimation {
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
