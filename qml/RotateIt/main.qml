import QtQuick 1.1
import com.nokia.symbian 1.1
import imagefetcher 1.0
import imageview 1.0
import engine 1.0

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

    StartPage {
        id: startPage
        onOpen: openMethodMenu.open()
        onAbout: {
            var aboutPageObject = object.create("AboutPage.qml")
            pageStack.push(aboutPageObject)
            aboutPageObject.back.connect(pageStack.pop)
        }

        onBack: Qt.quit()
    }

    Page {
        id: mainPage
        orientationLock: PageOrientation.LockLandscape

        property int previewWidth: imageView.width
        property int previewHeight: imageView.height

        Connections {
            target: imageFetcher
            onFetchedChanged: {
                mainPage.orientationLock = imageFetcher.fetched ?
                            PageOrientation.LockLandscape :
                            PageOrientation.Automatic
            }
        }
        Connections {
            target: window
            onCurrentImagePathChanged: slider.reset()
        }

        ImageView {
            id: imageView
            anchors.fill: parent
            Connections {
                target: engine
//                onPreviewImageChanged: imageView.sourceImage = engine.previewImage
                onPreviewImageChanged: {
//                    var startTime = new Date().getTime()
                    imageView.sourceImage = engine.previewImage
                    gc()
//                    var stopTime = new Date().getTime()
//                    console.log(stopTime - startTime)
                }
            }
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
            amplitude: 10
            onYChanged: reset()
            onPressed: mainToolBar.shown = false
            onValueChanged: engine.rotation = value
        }

        tools: ToolBarLayout {
            id: mainToolBarLayout
            ToolButton {
                iconSource: "toolbar-back"
                onClicked: Qt.quit()
            }
            ToolButton {
                iconSource: "qrc:///qml/RotateIt/images/open.png"
                onClicked: openMethodMenu.open()
            }
            ToolButton {
                iconSource: "qrc:///qml/RotateIt/images/save.svg"
                onClicked: console.log("clicked 'save'")
            }
            ToolButton {
                iconSource: "toolbar-menu"
                onClicked: mainPageMenu.open()
            }
        }

        TopBar {
            id: mainTopBar
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
//            visible: false
            Connections {
                target: engine
                onStateChanged: {
                    switch(engine.state) {
                    case Engine.Opening:
                        mainTopBar.text = qsTr("Opening")
                        mainTopBar.visible = true
                        break
                    case Engine.Passive:
                        mainTopBar.visible = false
                        break
                    case Engine.FinalRendering:
                        mainTopBar.text = qsTr("Rendering")
                        mainTopBar.visible = true
                        break
                    case Engine.Saving:
                        mainTopBar.text = qsTr("Saving")
                        mainTopBar.visible = true
                        break
                    default:
                        mainTopBar.visible = false
                        break
                    }
                }
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
                    onClicked: {
                        var aboutPageObject = object.create("AboutPage.qml")
                        pageStack.push(aboutPageObject)
                        aboutPageObject.back.connect(pageStack.pop)
                    }
                }
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
        //background: "qrc:///qml/RotateIt/images/toolbar-background.svg"
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
    }

    Engine {
        id: engine
        previewWidth: mainPage.previewWidth * 1.0
        previewHeight: mainPage.previewHeight * 1.0
        imagePath: window.currentImagePath
        onStateChanged: {

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

    QtObject {
        id: object
        function create(obj) {
            return Qt.createComponent(obj).createObject(window)
        }
    }
}
