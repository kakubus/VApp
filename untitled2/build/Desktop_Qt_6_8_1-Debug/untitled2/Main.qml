import QtQuick

Window {
    width: 860
    height: 480
    visible: true
    title: qsTr("Learn - Classes")


    Rectangle {
        width: 100; height: 100; color: "yellow"
        MouseArea {
            cursorShape: clicked
            anchors.fill: parent
            onClicked: console.log("Rectangle clicked!")
        }
    }


}


