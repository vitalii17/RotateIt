import QtQuick 1.1
import "UiConstants.js" as UiConstants

Item {
    id: root
    width: 80
    height: 80

    property string text
    property string iconSource

    signal clicked
    signal pressed
//    signal pressedAndHold(string text, int x, int y)
    signal pressedAndHold(string text)
    signal released

    onPressed: internal.animatePress()
    onReleased: internal.animateRelease()

    Item {
        id: iconItem
        anchors.horizontalCenter: root.horizontalCenter
        width: height
//        height: root.height - text.height
        height: root.height
        Rectangle {
            anchors.fill: parent
            radius: UiConstants.rectRadiusSmall
            opacity: 0.55
            color: "black"
            smooth: root.pressed ? true : false
        }
        Image {
            id: image
            anchors.fill: parent
            sourceSize.width: parent.width
            sourceSize.height: parent.height
            anchors.margins: 5
            source: root.iconSource
            smooth: root.pressed ? true : false
        }
    }

//    Text {
//        id: text
//        text: root.text
//        anchors.horizontalCenter: iconItem.horizontalCenter
//        anchors.top: iconItem.bottom
//        anchors.topMargin: 5
//        color: "white"
//        smooth: root.pressed ? true : false
//        font.pointSize: UiConstants.toolBoardFontPixelSize
//    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
            internal.animateClick()
        }
        onPressAndHold: {
//            var mappedCoordinates = root.mapToItem(root.parent, 0, 0)
//            root.pressedAndHold(root.text, mappedCoordinates.x, mappedCoordinates.y)
            root.pressedAndHold(root.text)
        }
        onReleased: root.released()
        onPressed: root.pressed()
        onExited: root.released()
    }

    QtObject {
        id: internal
        function animateClick() {
            clickAnimation.start()
        }

        function animatePress() {
            pressAnimation.start()
        }

        function animateRelease() {
            releaseAnimation.start()
        }
    }

    SequentialAnimation{
        id: clickAnimation
        PropertyAnimation {
            target: root
            property: "scale"
            to: 0.9
            duration: 50
        }
        PropertyAnimation {
            target: root
            property: "scale"
            to: 1.0
            duration: 50
        }
    }
    PropertyAnimation {
        id: pressAnimation
        target: root
        property: "scale"
        to: 0.9
        duration: 50
    }
    PropertyAnimation {
        id: releaseAnimation
        target: root
        property: "scale"
        to: 1.0
        duration: 50
    }
}
