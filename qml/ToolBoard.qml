import QtQuick 1.1
import "ToolBoard.js" as Js

Item {
    id: root

    property string backgroundColor: "black"
    property int offsetY: 0
    property bool shown: false

    property int topPadding: 25
    property int bottomPadding: 25
    property int leftPadding: 30
    property int rightPadding: 30
    property int spacing: 30

    anchors.left: parent.left
    anchors.right: parent.right

    Component.onCompleted: {
        for(var i = 0; i < root.children.length; i++) {
            if(root.children[i] !== backgroundrect) {
                Js.items.push(root.children[i])
            }
        }
        Js.layout()
    }

    onWidthChanged: Js.layout()

    state: shown ? "shown" : "hidden"

    Rectangle {
        id: backgroundrect
        anchors.fill: parent
        color: root.backgroundColor
        opacity: 0.6
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
            }
        },
        State {
            name: "hidden"
            PropertyChanges {
                target: root
                anchors.bottomMargin: -root.height - offsetY
            }
        }
    ]

    transitions: [
        Transition {
            from: "shown"
            to: "hidden"
            PropertyAnimation {
                target: root
                property: "anchors.bottomMargin"
                easing.type: Easing.InQuad
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
