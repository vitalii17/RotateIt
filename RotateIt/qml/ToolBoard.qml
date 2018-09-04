import QtQuick 1.1
import "ToolBoard.js" as Js

Item {
    id: root

    property string backgroundColor: "grey"
    property int offsetY: 0

    property int  topPadding: 25
    property int  bottomPadding: 25
    property int  leftPadding: 25
    property int  rightPadding: 25
    property int  spacing: 35
    property bool shown: (state === "shown") ? true : false

    property Item toolTip

    anchors.left: parent.left
    anchors.right: parent.right

    state: "hidden"

    signal showToolTip(string text)
    signal hideToolTip

    function open() {
        state = "shown"
    }

    function hide() {
        state = "hidden"
    }

    Component.onCompleted: {
        for(var i = 0; i < root.children.length; i++) {
            if(root.children[i] !== backgroundrect) {
                Js.items.push(root.children[i])
                root.children[i].pressedAndHold.connect(showToolTip)
                root.children[i].released.connect(hideToolTip)
            }
        }
        Js.layout()
    }

    onWidthChanged: Js.layout()

    Rectangle {
        id: backgroundrect
        anchors.fill: parent
        color: root.backgroundColor
        opacity: 0.55
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {}
        }
    }

    states: [
        State {
            name: "shown"
            PropertyChanges {
                target: root
                anchors.bottomMargin: offsetY
                visible: true
            }
        },
        State {
            name: "hidden"
            PropertyChanges {
                target: root
                anchors.bottomMargin: -root.height - offsetY
                visible: false
            }
        }
    ]

    transitions: [
        Transition {
            from: "shown"
            to: "hidden"
            SequentialAnimation{
                PropertyAnimation {
                    target: root
                    property: "anchors.bottomMargin"
                    easing.type: Easing.InQuad
                }
                PropertyAnimation {
                    target: root
                    property: "visible"
                    duration: 0
                }
            }
        },
        Transition {
            from: "hidden"
            to: "shown"
            PropertyAnimation {
                target: root
                property: "anchors.bottomMargin"
                easing.type: Easing.OutQuad
            }
        }
    ]
}
