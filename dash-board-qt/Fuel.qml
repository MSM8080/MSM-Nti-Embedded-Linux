import QtQuick
import msm_project
import "./"

Rectangle {

    Themes {
        id: theme
        current_theme: QtScreenTheme.theme
        onCurrent_themeChanged: apply_theme(current_theme)
    }

    Sensors {
        id: sensors
        gauge_fuel: QtScreenSensors.fuel
    }

    id: fuel
    width: 200
    height: 200
    radius: 100
    color: theme.fuel_color

    // property int speed: 0
    Repeater {
        model: 7
        Text {
            font.bold: true
            font.pixelSize: 16
            color: theme.fuel_model_7_color
            text: (index * 10).toString()
            property real angle: (-200 + index * 30) * Math.PI / 180
            x: parent.width / 2 + Math.cos(angle) * 70 - width / 2
            y: parent.height / 2 + Math.sin(angle) * 70 - height / 2
        }
    }

    Rectangle {
        id: needle
        width: 3
        height: 60
        radius: 2
        color: theme.fuel_needle_color
        anchors.centerIn: parent

        transform: Rotation {
            origin.x: needle.width / 2
            origin.y: needle.height
            // angle: -90 + (gauge_fuel / 240) * 180
            angle: (sensors.gauge_fuel * 2.6) - 90
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
        anchors.bottomMargin: 35
        text: sensors.gauge_fuel + " L"
        font.pixelSize: 18
        font.bold: true
        color: theme.fuel_text_color
    }
}
