import QtQuick
import QtQuick.Controls

import QMLTemplate		1.0
import QMLTemplate.ScreenTools	1.0
import QMLTemplate.Controls	1.0
import QMLTemplate.Palette	1.0

/// This is an example Qml file which is used to describe the QGroundControl coding style.
/// In general almost everything in here has some coding style meaning including order of
/// code. Not all style choices are explained. If there is any confusison please ask
/// and we'll answer and update style as needed.
Item {
    // Property binding to item properties
    width:  ScreenTools.defaultFontPixelHeight * 10 // No hardcoded sizing. All sizing must be relative to a ScreenTools font size
    height: ScreenTools.defaultFontPixelHeight * 20

    // Property definitions available to consumers of this Qml Item come first
    property int    myIntProperty:  10
    property real   myRealProperty: 20.0

    // Property definitions which are internal to the item are prepending with an underscore
    // to signal private and come second
    readonly property real _rectWidth:  ScreenTools.defaultFontPixelWidth * 10  // Use readonly appropriately to increase binding performance
    readonly property real _rectHeight: ScreenTools.defaultFontPixelWidth * 10

    function myFunction() {
        console.log("myFunction was called")
    }

    QMLPalette {
        id:                 qgcPal  // Note how id does not use an underscore
        colorGroupEnabled:  enabled
    }

    // You should always use the QML provided variants of base control since they automatically support
    // our theming and font support.
    QMLButton {
        // Also not how there is no id: specified for this control. Only add id: if it is needed.
        text: "Button"

        onClicked: myFunction()
    }

    Rectangle {
        width:  _rectWidth
        height: _rectHeight
        color:  qmlPal.window   // Use QML palette colors for everything, no hardcoded colors
    }

    // For scoped blocks which are long include a comment so you can tell what the brace is matching.
    // This is very handy when the top level brace scrolls off the screen. The endbrace comment in this
    // specific file is only included as style info. This example code is not long enough to really need it.
} // Item - CodingStyle
