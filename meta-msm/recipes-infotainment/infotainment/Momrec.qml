import QtQuick
import QtQuick.Layouts
import msm_project
import "./"

Item {
    id: dashboard

    // property int speed: 0
    // property int temperature: 90
    Themes {
        id: theme
        current_theme: QtScreenTheme.theme
        onCurrent_themeChanged: apply_theme(current_theme)
    }

    Sensors {
        id: sensors
        gauge_speed: QtScreenSensors.speed
        gauge_rpm: QtScreenSensors.rpm
        temperature: QtScreenSensors.temp
        gauge_fuel: QtScreenSensors.fuel
    }

    Rectangle {
        id: gaugeCircle
        width: parent.width
        height: parent.height
        color: theme.momrec_gauge_circle_color

        RowLayout {
            id: gaugesRow
            anchors.centerIn: parent
            spacing: 100
            Tachometer {
                id: rpmGauge
                Layout.preferredWidth: 400
                Layout.preferredHeight: 400
            }
            Speedometer {
                id: speedGauge
                Layout.preferredWidth: 400
                Layout.preferredHeight: 400
            }
        }

        Fuel {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 80
            width: 200
            height: 200
        }
        Text {
            text: "Temp: " + sensors.temperature + " °C"
            color: theme.momrec_gauge_circle_text_color
            font.pixelSize: 30
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 130
        }
    }
}
