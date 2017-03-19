import QtQuick 1.1
import com.nokia.symbian 1.1

ToolButton {
    id: root

    property variant toolTip: null
    property string toolTipText: ""

    onPlatformPressAndHold: {
        if(toolTip) {
            toolTip.target = root
            toolTip.text = root.toolTipText
            toolTip.show()
        }
    }

    onPlatformReleased: {
        if(toolTip) {
            toolTip.hide()
        }
    }
}

