import QtQuick
import QtQuick.Effects
import msm_project
import "./"

Rectangle {
    id: rpm

    Themes {
        id: theme
        current_theme: QtScreenTheme.theme
        onCurrent_themeChanged: apply_theme(current_theme)
    }

    Sensors {
        id: sensors
        gauge_rpm: QtScreenSensors.rpm
    }

    width: 400
    height: 400
    radius: 200
    color: theme.tacho_meter_rpm_color
    // property int speed: 0
    property real startAngle: -210
    property real stepAngle: 27

    Repeater {
        model: 9
        Text {
            font.bold: true
            font.pixelSize: 22
            color: theme.tacho_meter_rpm_model_13_color
            text: (index * 1).toString()
            property real angle: (-210 + index * 20) * Math.PI / 180
            x: parent.width / 2 + Math.cos(angle) * 150 - width / 2
            y: parent.height / 2 + Math.sin(angle) * 150 - height / 2
        }
    }

    Rectangle {
        id: needle
        width: 5
        height: 120
        radius: 2
        color: theme.tacho_meter_needle_color
        anchors.centerIn: parent

        transform: Rotation {
            origin.x: needle.width / 2
            origin.y: needle.height
            // angle: 0 + (speed / 8) * 8
            angle: (sensors.gauge_rpm * 15) - 90
            Behavior on angle {
                NumberAnimation {
                    duration: 400
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 75
        text: sensors.gauge_rpm + " RPM"
        font.pixelSize: 24
        font.bold: true
        color: theme.speedo_meter_text_color
    }
}
