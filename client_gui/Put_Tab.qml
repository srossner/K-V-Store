import QtQuick 2.4
import QtQuick.Controls 1.2


Item {
    id: put_tab
    width: 500
    height: 500
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 8
    anchors.right: parent.right
    anchors.rightMargin: 8
    anchors.top: parent.top
    anchors.topMargin: 8
    anchors.leftMargin: 8
    anchors.left: parent.left

    TextField {
        id: textField_key
        width: 150
        height: 50
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        placeholderText: qsTr("Key")
    }

    TextField {
        id: textField_value
        anchors.bottom: textField_key.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: button_submit_put.left
        anchors.rightMargin: 8
        anchors.left: textField_key.right
        anchors.leftMargin: 8
        placeholderText: qsTr("Value")
    }

    Button {
        id: button_submit_put
        text: qsTr("Submit")
        anchors.bottom: textField_key.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 0
        onClicked: {
            rest_client.put(textField_key.text, textField_value.text)
            text_response_put.text =  qsTr("Respons: ") + rest_client.getPUT();
        }
    }

    Text {
        id: text_response_put_title
        text: qsTr("Respons PUT")
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: textField_key.bottom
        anchors.bottomMargin: -40
        anchors.top: textField_key.bottom
        anchors.topMargin: 8
        font.pixelSize: 24
    }

    Text {
        id: text_response_put
        text: qsTr("Respons")
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: text_response_put_title.bottom
        anchors.topMargin: 8
        font.pixelSize: 12
    }
}

