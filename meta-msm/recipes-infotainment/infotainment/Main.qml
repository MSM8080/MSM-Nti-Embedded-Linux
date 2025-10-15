import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Effects
import QtQuick.Controls
import msm_project
import "./"

// first update test
Window {
    id: window
    visibility: window.FullScreen

    Themes {
        id: theme
        current_theme: QtScreenTheme.theme
        onCurrent_themeChanged: apply_theme(current_theme)
    }

    width: Screen.width
    height: Screen.height
    visible: true
    color: theme.window_background_color

    // property int angle: 0
    // property int speed: 0
    // property int temperature: 90
    Chair {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: 400
        height: 300
    }

    Momrec {
        id: dashboard
        anchors.centerIn: parent
        // speed: window.speed
        // temperature: window.temperature
        scale: 1.8
    }

    Button {
        id: arcane_button
        Text {
            text: "Arcane Theme"
            color: "black"
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 20
        }
        x: 1600
        y: 0
        width: 200
        height: 50
        background: Rectangle {
            color: theme.right_button_color
        }
        onClicked: QtScreenTheme.set_theme("Arcane")
    }
    Button {
        id: nature_button
        Text {
            text: "Natural Theme"
            color: "black"
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 20
        }
        x: 1350
        y: 0
        width: 200
        height: 50
        background: Rectangle {
            color: theme.left_button_color
        }
        onClicked: QtScreenTheme.set_theme("Natural")
    }
    Button {
        id: galaxy_button
        Text {
            text: "Galaxy Theme"
            color: "black"
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 20
        }
        x: 1100
        y: 0
        width: 200
        height: 50
        background: Rectangle {
            color: theme.left_button_color
        }
        onClicked: QtScreenTheme.set_theme("Galaxy")
    }
    Button {
        id: kali_button
        Text {
            text: "Kali Theme"
            color: "black"
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 20
        }
        // anchors.left: arcane_button.right
        x: 850
        y: 0
        width: 200
        height: 50
        background: Rectangle {
            color: theme.left_button_color
        }
        onClicked: QtScreenTheme.set_theme("Kali")
    }
}
