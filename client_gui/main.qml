import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Window {
    id: window1
    visible: true
    height: 800
    width: 800

    Text {
        id: heading
        height: 20
        text: qsTr("Rest Client")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    Button{
        id: button_close
        text: "Close"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8

        onClicked: {
            Qt.quit();
        }
    }

    TabView {
        id: tabView1
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: button_close.top
        anchors.bottomMargin: 8
        anchors.top: heading.bottom
        anchors.topMargin: 8

        Tab {
            title: "PUT"
            anchors.rightMargin: 16
            anchors.leftMargin: 16
            anchors.bottomMargin: 16
            anchors.topMargin: 16
            Put_Tab{
                id:put_tab
                anchors.right: parent.right
                anchors.rightMargin: 1
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.fill: parent
            }
        }

        Tab {
            title: "GET"
            anchors.rightMargin: 16
            anchors.leftMargin: 16
            anchors.bottomMargin: 16
            anchors.topMargin: 16
            Get_Tab{
                id:get_tab
                anchors.right: parent.right
                anchors.rightMargin: 1
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.fill: parent
            }
        }
        Tab {
            title: "DELETE"
            anchors.rightMargin: 16
            anchors.leftMargin: 16
            anchors.bottomMargin: 16
            anchors.topMargin: 16
            Delete_Tab{
                id:delete_tab
                anchors.right: parent.right
                anchors.rightMargin: 1
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.fill: parent
            }
        }
        Tab {
            title: "Test"
            anchors.rightMargin: 16
            anchors.leftMargin: 16
            anchors.bottomMargin: 16
            anchors.topMargin: 16
            Test_Tab{
                id:test_tab
                anchors.right: parent.right
                anchors.rightMargin: 1
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.fill: parent
            }
        }
    }
}

