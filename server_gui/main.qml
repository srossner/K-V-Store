import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Window {
    id: the_window
    visible: true
    height: 160
    width: 400


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
        anchors.bottom: sliderHorizontal_numberofElements.top
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

        Text {

            id: text1
            text: qsTr("Number of Elements: " + sliderHorizontal_numberofElements.value)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
            visible: group.current != radioButton_all
        }

    }

    Slider {
        id: sliderHorizontal_numberofElements
        anchors.bottom: close.top
        anchors.bottomMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        minimumValue: 10
        maximumValue: 1000
        stepSize: 1.0
        enabled: group.current != radioButton_all
        onValueChanged: controller.setMAX_SIZE(value)
    }

    Button{
        id:close
        text: "Close"
        anchors.top: parent.bottom
        anchors.topMargin: -50
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

