import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import com.waterloop.websockets 1.0
import com.waterloop.brakehandler 1.0
import com.waterloop.limhandler 1.0
import com.waterloop.commandLogger 1.0

Window {
    visible: true
    width: 960
    height: 640
    title: qsTr("Websockets Button")
    color: "black"

    Websockets {
        id: websockets
    }

    BrakeHandler {
        id: brakeHandler
    }

    LIMHandler {
        id: limhandler
    }

    CommandLogger {
        id: commandLogger
    }

    RowLayout {
        width: parent.width
        height: parent.height
        spacing: 0

        Rectangle {
            id: infoPanel
            Layout.preferredWidth: parent.width * .60
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "black";
        }

        Rectangle {
            Layout.preferredWidth: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#9B9B9B"
        }

        ColumnLayout {
            Layout.preferredWidth: parent.width * .40
            height: parent.height
            spacing: 0

            Rectangle {
                Layout.topMargin: 10
                id: configPanel
                Layout.preferredHeight: parent.height * .40
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "black";

                ColumnLayout {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button {
                        id: brakeButton
                        Layout.alignment: Qt.AlignHCenter
                        text: "Brake"

                        onClicked: {
                            brakeHandler.sendBrake(websockets, commandLogger)
                        }
                    }
                    RowLayout {
                        Layout.alignment: Qt.AlignHCenter
                        Label {
                            text: "LIM Speed"
                            color: "white"
                        }

                        Slider {
                            id: propulsionSlider
                            snapMode: Slider.SnapAlways
                            stepSize: 1
                            to: 100

                            onPressedChanged: {
                                limhandler.sendSpeed(websockets, commandLogger, value)
                            }
                        }
                        TextArea {
                            text: propulsionSlider.value
                            color: "white"
                        }
                    }
                    RoundButton {
                        id: emergencyStopBtn

                        font.pointSize: 60
                        Layout.alignment: Qt.AlignHCenter
                        text: "STOP"

                        onClicked: {
                            brakeHandler.sendBrake(websockets, commandLogger)
                        }
                    }
                }
            }

            Rectangle {
                Layout.preferredHeight: 3
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#9B9B9B"
            }

            Rectangle {
                id: connectionPanel
                Layout.preferredHeight: parent.height * .20
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "black";

                ColumnLayout {
                    width: parent.width
                    antialiasing: false
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 5

                    TextField {
                        Layout.alignment: Qt.AlignHCenter
                        id: connectionAddress
                        text: "ws://localhost:8080"
                    }

                    Button {
                        Layout.alignment: Qt.AlignHCenter
                        text: websockets.isConnected ? "Disconnect" : "Connect"

                        onClicked: {
                            if (websockets.isConnected) {
                                websockets.closeClient(commandLogger)
                            } else {
                                websockets.connectClient(connectionAddress.text, commandLogger)
                            }
                        }
                    }
                }
            }

            Rectangle {
                Layout.preferredHeight: 3
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#9B9B9B"
            }

            Rectangle {
                Layout.preferredHeight: parent.height * .40
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "black";

                Flickable {
                    height: parent.height
                    width: parent.width

                    contentWidth: parent.width
                    contentHeight: logsText.implicitHeight

                    TextArea.flickable: TextArea {
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: parent.height
                        id: logsText
                        color: "white"
                        text: commandLogger.log
                        wrapMode: Text.WordWrap
                    }
                    ScrollBar.vertical: ScrollBar {}
                }
            }
        }
    }
}




