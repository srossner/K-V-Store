import QtQuick 2.0
import QtQuick.Controls 2.1


Rectangle {
    id:k_v_Item
    width: 400
    height: 50
    color: "#ffffff"

    property string key: "key"
    property string value: "value"

    Row {
        anchors.fill: parent
        spacing: 8

        Text {
            id: text_key
            height: parent.height
            width:(parent.width - parent.spacing)/2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: (height-8 )/2
            wrapMode: Text.WordWrap
            clip: true

            text: qsTr(key + " :")
        }

        Text {
            id: test_value
            height: parent.height
            width:(parent.width - parent.spacing)/2
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: (height-8 )/2
            wrapMode: Text.WordWrap
            clip: true

            text: qsTr(value)
        }
    }


}

