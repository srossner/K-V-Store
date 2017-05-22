import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Window {
    id: the_window
    visible: true
    height: 120
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

    Row {
        id: row_radioButtons
        spacing: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: close.top
        anchors.bottomMargin: 8
        anchors.top: heading.bottom
        anchors.topMargin: 8

        ExclusiveGroup {
            id: group

            onCurrentChanged: {
                switch(current)
                {
                case radioButton_all:
                    controller.setMemoryStrategy(0/*ALL*/);
                    break;
                case radioButton_FIFO:
                    controller.setMemoryStrategy(1/*FIFO*/);
                    break;
                case radioButton_LRU:
                     controller.setMemoryStrategy(2/*LRU*/);
                    break;
                }
            }
        }

        RadioButton {
            id: radioButton_all
            text: qsTr("All")
            checked: true
            anchors.verticalCenter: parent.verticalCenter
            exclusiveGroup: group
        }

        RadioButton {
            id: radioButton_FIFO
            text: qsTr("FIFO")
            anchors.verticalCenter: parent.verticalCenter
            exclusiveGroup: group
        }

        RadioButton {
            id: radioButton_LRU
            text: qsTr("LRU")
            anchors.verticalCenter: parent.verticalCenter
            exclusiveGroup: group
        }
    }

    Button{
        id:close
        text: "Close"
        anchors.top: heading.bottom
        anchors.topMargin: 50
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

