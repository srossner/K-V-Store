import QtQuick 2.4
import QtQuick.Controls 1.4

Item {
    id: test_tab
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
        id: textField_number_start
        width: 150
        height: 50
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        placeholderText: qsTr("Start")
    }

    TextField {
        id: textField_number_end
        anchors.bottom: textField_number_start.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: button_submit_test.left
        anchors.rightMargin: 8
        anchors.left: textField_number_start.right
        anchors.leftMargin: 8
        placeholderText: qsTr("End")
    }

    Button {
        id: button_submit_test
        text: qsTr("Submit")
        anchors.bottom: textField_number_start.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 0
        onClicked: {

            for( var i =  textField_number_start.text; i <= textField_number_end.text; i++  )
            {
                rest_client.put(i, i)
            }

            rest_client.get( "", true);

            text_response_test.text =  qsTr("Response: ") + rest_client.getGET();;
        }
    }

    Text {
        id: text_response_test_title
        text: qsTr("Response test")
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: textField_number_start.bottom
        anchors.bottomMargin: -40
        anchors.top: textField_number_start.bottom
        anchors.topMargin: 8
        font.pixelSize: 24
    }

    TextArea {
        id: text_response_test
        text: qsTr("Response: ")
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: text_response_test_title.bottom
        anchors.topMargin: 8
        font.pixelSize: 12
    }
}

