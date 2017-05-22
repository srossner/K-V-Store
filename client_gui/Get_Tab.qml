import QtQuick 2.4
import QtQuick.Controls 1.2


Item {
    id: get_tab
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

    CheckBox {
        id: checkBox_all
        text: qsTr("get All")
        anchors.right: button_submit_get.left
        anchors.rightMargin: 142
        anchors.left: textField_key.right
        anchors.leftMargin: 20
        anchors.bottom: text_response_get_title.top
        anchors.bottomMargin: 22
        anchors.top: parent.top
        anchors.topMargin: 22
        onCheckedChanged: {
            if(checked)
                textField_key.enabled = false
            else
                textField_key.enabled = true

        }
    }

    Button {
        id: button_submit_get
        text: qsTr("Submit")
        anchors.bottom: textField_key.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 0
        onClicked: {
            rest_client.get(textField_key.text, checkBox_all.checked )
            text_response_get.text =  qsTr("Respons: ") + rest_client.getGET();
        }
    }

    Text {
        id: text_response_get_title
        text: qsTr("Respons GET")
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
        id: text_response_get
        text: qsTr("Respons: ")
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: text_response_get_title.bottom
        anchors.topMargin: 8
        font.pixelSize: 12
    }
}

