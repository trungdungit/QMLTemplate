pragma Singleton

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

import QMLTemplate 1.0
import QMLTemplate.SettingsManager 1.0

Item {
    id: _screenTools

    property real defaultFontPointSize: 10
    property real platformFontPointSize: 10
    property real defaultFontPixelHeight: 10
    property real defaultFontPixelWidth: 10
    property real maxToolbarHeight: 63

    property real maxResetPromptWidth: 300
    property real maxResetPromptHeight: 200

    property real smallFontPointSize: 10
    property real mediumFontPointSize: 15
    property real largeFontPointSize: 20

    property real toolbarHeight: 0

    property real smallSpacing: 5
    property real normalSpacing: 10
    property real mediumSpacing: 15
    property real largeSpacing: 20

    property real smallPadding: 0.5
    property real normalPadding: 1
    property real mediumPadding: 2
    property real largePadding: 3

    property real smallRadius: 1
    property real normalRadius: 2
    property real mediumRadius: 4
    property real largeRadius: 5

    property real smallWidthBorder: 1
    property real normalWidthBorder: 2
    property real mediumWidthBorder: 3
    property real largeWidthBorder: 4

    readonly property real smallFontPointRatio: 0.75
    readonly property real mediumFontPointRatio: 1.25
    readonly property real largeFontPointRatio: 1.5

    // The implicit heights/widths for our custom control set
    property real implicitButtonWidth: Math.round(defaultFontPixelWidth * 5.0)
    property real implicitButtonHeight: Math.round(defaultFontPixelHeight * 1.6)
    property real implicitCheckBoxHeight: Math.round(
                                              defaultFontPixelHeight * 1.0)
    property real implicitRadioButtonHeight: implicitCheckBoxHeight
    property real implicitTextFieldHeight: Math.round(
                                               defaultFontPixelHeight * 1.6)
    property real implicitComboBoxHeight: Math.round(
                                              defaultFontPixelHeight * 1.6)
    property real implicitComboBoxWidth: Math.round(defaultFontPixelWidth * 5.0)
    property real comboBoxPadding: defaultFontPixelWidth
    property real implicitSliderHeight: defaultFontPixelHeight
    // It's not possible to centralize an even number of pixels, checkBoxIndicatorSize should be an odd number to allow centralization
    property real checkBoxIndicatorSize: 2 * Math.floor(
                                             defaultFontPixelHeight / 2) + 1
    property real radioButtonIndicatorSize: checkBoxIndicatorSize


    /* This mostly works but for some reason, reflowWidths() in SetupView doesn't change size.
       I've disabled (in release builds) until I figure out why. Changes require a restart for now.
    */
    Connections {
        target: QMLTemplate.settingsManager.appSettings.appFontPointSize
        function onValueChanged(value) {
            _setBasePointSize(value)
        }
    }

    /// \private
    function _setBasePointSize(pointSize) {
        _textMeasure.font.pointSize = pointSize
        defaultFontPointSize = pointSize
        defaultFontPixelHeight = Math.round(_textMeasure.fontHeight / 2.0) * 2
        defaultFontPixelWidth = Math.round(_textMeasure.fontWidth / 2.0) * 2
        smallFontPointSize = defaultFontPointSize * _screenTools.smallFontPointRatio
        mediumFontPointSize = defaultFontPointSize * _screenTools.mediumFontPointRatio
        largeFontPointSize = defaultFontPointSize * _screenTools.largeFontPointRatio
        toolbarHeight = defaultFontPixelHeight * 3
    }

    Text {
        id: _defaultFont
        text: "X"
    }

    Text {
        id: _textMeasure
        text: "X"
        font.family: UIConstants.customFont
        property real fontWidth: contentWidth
        property real fontHeight: contentHeight
        Component.onCompleted: {
            platformFontPointSize = _defaultFont.font.pointSize
            //-- See if we are using a custom size
            var _appFontPointSizeFact = QMLTemplate.settingsManager.appSettings.appFontPointSize
            var baseSize = _appFontPointSizeFact.value
            //-- Sanity check
            if (baseSize < _appFontPointSizeFact.min
                || baseSize > _appFontPointSizeFact.max) {
                baseSize = platformFontPointSize
                _appFontPointSizeFact.value = baseSize
            }
            //-- Set size saved in settings
            _screenTools._setBasePointSize(baseSize)
        }
    }
}
