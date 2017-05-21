import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    id: qml_window
    visible: true

    //signal qmlSignal(Boolean off)

    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
      //      qml_window.qmlSignal(true);

            Qt.quit();
        }
    }
}

