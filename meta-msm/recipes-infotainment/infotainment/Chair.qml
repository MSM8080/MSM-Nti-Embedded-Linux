import QtQuick
import QtQuick.Controls
import msm_project
import "./"

Item {

    Themes {
        id: theme
        current_theme: QtScreenTheme.theme
        onCurrent_themeChanged: apply_theme(current_theme)
    }

    Sensors {
        id: sensors
        chair_angle: QtScreenSensors.angle
    }

    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.leftMargin: 0 // تقليل الهامش إلى 0 للاقتراب من الحافة اليسرى
    anchors.bottomMargin: 0 // تقليل الهامش إلى 0 للاقتراب من الحافة السفلية

    //width: 400 // عرض كافٍ لاحتواء الكرسي
    //height: 300 // ارتفاع كافٍ لاحتواء الكرسي
    Rectangle {
        id: verticalLine
        width: 25
        height: 120
        radius: 7
        color: theme.chair_vertical_line_Color
        x: 150
        y: parent.height - height - 100
        // rotation: -angle
        rotation: sensors.chair_angle
        transformOrigin: Item.Bottom

        // Back cushion as a child of verticalLine
        Rectangle {
            id: topCushion
            width: 20
            height: 50
            radius: 5
            color: theme.chair_top_cushion_color

            x: verticalLine.width + 5
            y: -height - 5

            transformOrigin: Item.BottomLeft
        }
    }

    // Horizontal line (chair seat)
    Rectangle {
        id: horizontalLine
        width: 100
        height: 25
        radius: 7
        color: theme.chair_horizontal_line_color
        anchors.left: verticalLine.right
        anchors.bottom: verticalLine.bottom
        anchors.margins: -10
    }

    // Small circular joint connecting both lines
    Rectangle {
        id: joint
        width: 30
        height: 30
        radius: 15
        color: theme.chair_joint_color
        x: verticalLine.x
        y: verticalLine.y + verticalLine.height - 15
    }

    // === Right Button (→) ===
    Rectangle {
        id: rightButton
        width: 50
        height: 50
        radius: 25
        color: theme.chair_right_button_color
        border.color: theme.chair_right_button_border_color
        border.width: 4

        x: horizontalLine.x + horizontalLine.width + 50
        y: verticalLine.y + verticalLine.height + 40

        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                // ctx.strokeStyle = "#4CAF50"
                ctx.strokeStyle = theme.chair_right_button_arrow_color
                ctx.lineWidth = 5
                ctx.beginPath()
                ctx.moveTo(width * 0.3, height * 0.25)
                ctx.lineTo(width * 0.7, height * 0.5)
                ctx.lineTo(width * 0.3, height * 0.75)
                ctx.stroke()
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                // angle -= 2
                sensors.chair_angle += 2
                QtScreenSensors.set_angle(sensors.chair_angle)
            }
        }
    }

    // === Left Button (←) ===
    Rectangle {
        id: leftButton
        width: 50
        height: 50
        radius: 25
        color: theme.chair_left_button_color
        border.color: theme.chair_left_button_border_color
        border.width: 4

        x: verticalLine.x - width - 50
        y: verticalLine.y + verticalLine.height + 40

        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                // ctx.strokeStyle = "#2196F3"
                ctx.strokeStyle = theme.chair_left_button_arrow_color
                ctx.lineWidth = 5
                ctx.beginPath()
                ctx.moveTo(width * 0.7, height * 0.25)
                ctx.lineTo(width * 0.3, height * 0.5)
                ctx.lineTo(width * 0.7, height * 0.75)
                ctx.stroke()
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                // angle += 2
                sensors.chair_angle -= 2
                QtScreenSensors.set_angle(sensors.chair_angle)
            }
        }
    }

    // === Angle Display Box ===
    Rectangle {
        id: angleDisplay
        width: 70
        height: 40
        radius: 10
        color: theme.chair_angle_box_color
        border.color: theme.chair_angle_box_border_color
        border.width: 2

        x: leftButton.x + (rightButton.x - leftButton.x) / 2 - 10
        y: leftButton.y + 5

        Text {
            anchors.centerIn: parent
            // text: angle + "°"
            text: sensors.chair_angle + "°"
            font.pixelSize: 24
            font.bold: true
            color: theme.chair_angle_text_color
        }
    }
}
