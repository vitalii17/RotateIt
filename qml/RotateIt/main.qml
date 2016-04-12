import QtQuick 1.1
import com.nokia.symbian 1.1
import imagefetcher 1.0
import imageview 1.0

PageStackWindow {
    id: window
    showStatusBar: false
    showToolBar: false

    property string currentImagePath
    onCurrentImagePathChanged: {
        if(pageStack.currentPage !== mainPage) {
            pageStack.push(mainPage)
        }
    }

    Page {
        id: startPage
        orientationLock: PageOrientation.Automatic

        Connections {
            target: imageFetcher
            onFetchedChanged: {
                startPage.orientationLock = imageFetcher.fetched ?
                            PageOrientation.LockLandscape :
                            PageOrientation.Automatic
            }
        }

        Button {
            id: openButton
            text: qsTr("Open Image")
            anchors.centerIn: parent
            anchors.bottomMargin: mainToolBar.height
            onClicked: openMethodMenu.open()
        }

        tools: ToolBarLayout {
            id: startPageToolBarLayout
            ToolButton {
                iconSource: "toolbar-back"
                onClicked: Qt.quit()
            }
            ToolButton {
                iconSource: "toolbar-menu"
                onClicked: startPageMenu.open()
            }
        }

        Menu {
            id: startPageMenu
            MenuLayout {
                MenuItem {
                    text: qsTr("About")
                    onClicked: pageStack.push(aboutPage)
                }
                MenuItem {
                    text: qsTr("Exit")
                    onClicked: Qt.quit()
                }
            }
        }
    }

    Page {
        id: mainPage
        orientationLock: PageOrientation.LockLandscape

        Connections {
            target: imageFetcher
            onFetchedChanged: {
                mainPage.orientationLock = imageFetcher.fetched ?
                            PageOrientation.LockLandscape :
                            PageOrientation.Automatic
            }
        }

        ImageView {
            id: imageView
            anchors.fill: parent
            //onSourceDataChanged: console.log("123")
        }

        Rectangle {
            id: horizontCorsor
            color: "white"
            height: 2
            opacity: 0.4
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
            ToolButton {
                iconSource: "toolbar-menu"
                onClicked: mainPageMenu.open()
            }
        }

        Menu {
            id: mainPageMenu
            MenuLayout {
                MenuItem {
                    text: qsTr("Open")
                    platformSubItemIndicator: true
                    onClicked: openMethodMenu.open()
                }
                MenuItem {
                    text: qsTr("Save")
                    onClicked: {}
                }
                MenuItem {
                    text: qsTr("About")
                    onClicked: pageStack.push(aboutPage)
                }
            }
        }
    }

    AboutPage {
        id: aboutPage
        onBack: pageStack.pop()
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

    ImageFetcher {
        id: imageFetcher
        onFetchedChanged: {
            if(fetched) {
                //                pageStack.push(mainPage)
            }
        }
    }

    ContextMenu {
        id: openMethodMenu
        MenuLayout {
            MenuItem {
                text: qsTr("From Gallery")
                onClicked: currentImagePath = imageFetcher.fetchImage(ImageFetcher.Gallery)
            }
            MenuItem {
                text: qsTr("File Manager")
                onClicked: currentImagePath = imageFetcher.fetchImage(ImageFetcher.FileManager)
            }
        }
    }
}
