import QtQuick
import msm_project
import "./"

Rectangle {
    id: speedometer

    Themes {
        id: theme
        current_theme: QtScreenTheme.theme
        onCurrent_themeChanged: apply_theme(current_theme)
    }

    Sensors {
        id: sensors
        gauge_speed: QtScreenSensors.speed
    }

    width: 400
    height: 400
    radius: 200
    color: theme.speedo_meter_color

    Repeater {
        model: 13
        Text {
            font.bold: true
            font.pixelSize: 22
            color: theme.speedo_meter_model_13_color
            text: (index * 20).toString()
            property real angle: (-210 + index * 18) * Math.PI / 180
            x: parent.width / 2 + Math.cos(angle) * 150 - width / 2
            y: parent.height / 2 + Math.sin(angle) * 150 - height / 2
        }
    }

    Rectangle {
        id: needle
        width: 5
        height: 120
        radius: 2
        color: theme.speedo_meter_needle_color
        anchors.centerIn: parent

        transform: Rotation {
            origin.x: needle.width / 2
            origin.y: needle.height
            // angle: -120 + (speed / 240) * 240
            angle: (sensors.gauge_speed * 0.69) - 98
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
        text: sensors.gauge_speed + " km/h"
        font.pixelSize: 24
        font.bold: true
        color: theme.speedo_meter_text_color
    }
}
