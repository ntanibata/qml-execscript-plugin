import QtQuick 2.0
import execScript 1.0

Item {
    id: root

    Rectangle {
        width: 1024
        height: 768

        Rectangle {
            width: 100
            height: 50
            color: "#228b22"

            Text {
                text: "execute script"
            }

            MouseArea {
                anchors.fill: parent
                property string file : "script/test.sh"
                onClicked: { execscript.execute(file) }
            }
        }
    }

    ExecScript { id:execscript }
}
