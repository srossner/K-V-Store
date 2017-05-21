import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2


Window {
    id: the_window
    visible: true
    height: 100
    width: 300


    Text {
        id: heading
        text: "K-V-Server"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
    }


    Button{
        id:close
        text: "Close"
        anchors.top: heading.bottom
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        onClicked: {
            Qt.quit();
        }
    }







}

