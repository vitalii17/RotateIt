import QtQuick 1.1
import com.nokia.symbian 1.1

PageStackWindow {
    id: window
    showStatusBar: false
    showToolBar: false

    Page {
        id: startPage
        orientationLock: PageOrientation.LockLandscape

        Button {
            id: openButton
            text: qsTr("Open Image")
            anchors.centerIn: parent
            anchors.bottomMargin: mainToolBar.height
            onClicked: console.log("Clicked")
        }

        tools: ToolBarLayout {
            id: startPageToolBarLayout
            ToolButton {
                iconSource: "toolbar-back"
                onClicked: Qt.quit()
            }
        }
    }

    Page {
        id: mainPage
        orientationLock: PageOrientation.LockLandscape

        Rectangle {
            id: horizontCorsor
            color: "white"
            height: 2
            opacity: 0.5
            width: parent.width
            y: parent.height / 2
        }

        MouseArea {
            anchors.fill: parent
            drag.target: horizontCorsor
            drag.axis: Drag.YAxis
            drag.minimumY: 0
            drag.maximumY: parent.height - horizontCorsor.height
            onClicked: mainToolBar.shown = false
        }

        CustomSlider {
            id: slider
            anchors.left: parent.left
            anchors.right: parent.right
            y: (parent.height / 3) * 2
            onPressed: mainToolBar.shown = false
        }

        tools: ToolBarLayout {
            id: mainToolBarLayout
            ToolButton {
                iconSource: "toolbar-back"
                onClicked: Qt.quit()
            }
        }

        ToolBarLayout {
            id: rotationToolBarLayout
            ToolButton {
                iconSource: "toolbar-menu"
                onClicked: {}
            }
        }
    }

    PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: push(startPage)
    }

    CustomToolBar {
        id: mainToolBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        z: 1
        tools: pageStack.currentPage.tools
        background: "qrc:///qml/RotateIt/images/toolbar-background.svg"
    }

    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: mainToolBar.height
        onPressed: mainToolBar.shown = true
    }
}
