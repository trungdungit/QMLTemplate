#include "QmlPalette.h"
#include "QMLApplication.h"
#include "QMLCorePlugin.h"

#include <QDebug>

QList<QMLPalette*>   QMLPalette::_paletteObjects;

QMLPalette::Theme QMLPalette::_theme = QMLPalette::Dark;

QMap<int, QMap<int, QMap<QString, QColor>>> QMLPalette::_colorInfoMap;

QStringList QMLPalette::_colors;

QMLPalette::QMLPalette(QObject* parent) :
    QObject(parent),
    _colorGroupEnabled(true)
{
    if (_colorInfoMap.isEmpty()) {
        _buildMap();
    }

    // We have to keep track of all QMLPalette objects in the system so we can signal theme change to all of them
    _paletteObjects += this;
}

QMLPalette::~QMLPalette()
{
    bool fSuccess = _paletteObjects.removeOne(this);
    if (!fSuccess) {
        qWarning() << "Internal error";
    }
}

void QMLPalette::_buildMap()
{
    //                                      Light                 Dark
    //                                      Disabled   Enabled    Disabled   Enabled
    DECLARE_QML_COLOR(window,               "#ffffff", "#ffffff", "#222222", "#222222")
    DECLARE_QML_COLOR(windowShadeLight,     "#909090", "#828282", "#707070", "#626262")
    DECLARE_QML_COLOR(windowShade,          "#d9d9d9", "#d9d9d9", "#333333", "#333333")
    DECLARE_QML_COLOR(windowShadeDark,      "#bdbdbd", "#bdbdbd", "#282828", "#282828")
    DECLARE_QML_COLOR(text,                 "#9d9d9d", "#000000", "#707070", "#ffffff")
    DECLARE_QML_COLOR(warningText,          "#cc0808", "#cc0808", "#f85761", "#f85761")
    DECLARE_QML_COLOR(button,               "#ffffff", "#ffffff", "#707070", "#626270")
    DECLARE_QML_COLOR(buttonBorder,         "#ffffff", "#d9d9d9", "#707070", "#adadb8")
    DECLARE_QML_COLOR(buttonText,           "#9d9d9d", "#000000", "#A6A6A6", "#ffffff")
    DECLARE_QML_COLOR(buttonHighlight,      "#e4e4e4", "#946120", "#3a3a3a", "#fff291")
    DECLARE_QML_COLOR(buttonHighlightText,  "#2c2c2c", "#ffffff", "#2c2c2c", "#000000")
    DECLARE_QML_COLOR(primaryButton,        "#585858", "#8cb3be", "#585858", "#8cb3be")
    DECLARE_QML_COLOR(primaryButtonText,    "#2c2c2c", "#000000", "#2c2c2c", "#000000")
    DECLARE_QML_COLOR(textField,            "#ffffff", "#ffffff", "#707070", "#ffffff")
    DECLARE_QML_COLOR(textFieldText,        "#808080", "#000000", "#000000", "#000000")
    DECLARE_QML_COLOR(mapButton,            "#585858", "#000000", "#585858", "#000000")
    DECLARE_QML_COLOR(mapButtonHighlight,   "#585858", "#be781c", "#585858", "#be781c")
    DECLARE_QML_COLOR(mapIndicator,         "#585858", "#be781c", "#585858", "#be781c")
    DECLARE_QML_COLOR(mapIndicatorChild,    "#585858", "#766043", "#585858", "#766043")
    DECLARE_QML_COLOR(colorGreen,           "#009431", "#009431", "#00e04b", "#00e04b")
    DECLARE_QML_COLOR(colorOrange,          "#b95604", "#b95604", "#de8500", "#de8500")
    DECLARE_QML_COLOR(colorRed,             "#ed3939", "#ed3939", "#f32836", "#f32836")
    DECLARE_QML_COLOR(colorGrey,            "#808080", "#808080", "#bfbfbf", "#bfbfbf")
    DECLARE_QML_COLOR(colorBlue,            "#1a72ff", "#1a72ff", "#536dff", "#536dff")
    DECLARE_QML_COLOR(alertBackground,      "#eecc44", "#eecc44", "#eecc44", "#eecc44")
    DECLARE_QML_COLOR(alertBorder,          "#808080", "#808080", "#808080", "#808080")
    DECLARE_QML_COLOR(alertText,            "#000000", "#000000", "#000000", "#000000")
    DECLARE_QML_COLOR(missionItemEditor,    "#585858", "#dbfef8", "#585858", "#585d83")
    DECLARE_QML_COLOR(toolStripHoverColor,  "#585858", "#9D9D9D", "#585858", "#585d83")
    DECLARE_QML_COLOR(statusFailedText,     "#9d9d9d", "#000000", "#707070", "#ffffff")
    DECLARE_QML_COLOR(statusPassedText,     "#9d9d9d", "#000000", "#707070", "#ffffff")
    DECLARE_QML_COLOR(statusPendingText,    "#9d9d9d", "#000000", "#707070", "#ffffff")
    DECLARE_QML_COLOR(toolbarBackground,    "#ffffff", "#ffffff", "#222222", "#222222")
    DECLARE_QML_COLOR(groupBorder,          "#bbbbbb", "#bbbbbb", "#707070", "#707070")

    // Colors not affecting by theming
    //                                              Disabled    Enabled
    DECLARE_QML_NONTHEMED_COLOR(brandingPurple,     "#4A2C6D", "#4A2C6D")
    DECLARE_QML_NONTHEMED_COLOR(brandingBlue,       "#48D6FF", "#6045c5")
    DECLARE_QML_NONTHEMED_COLOR(toolStripFGColor,   "#707070", "#ffffff")

    // Colors not affecting by theming or enable/disable
    DECLARE_QML_SINGLE_COLOR(mapWidgetBorderLight,          "#ffffff")
    DECLARE_QML_SINGLE_COLOR(mapWidgetBorderDark,           "#000000")
    DECLARE_QML_SINGLE_COLOR(mapMissionTrajectory,          "#be781c")
    DECLARE_QML_SINGLE_COLOR(surveyPolygonInterior,         "green")
    DECLARE_QML_SINGLE_COLOR(surveyPolygonTerrainCollision, "red")

// Colors for UTM Adapter
#ifdef CONFIG_UTM_ADAPTER
    DECLARE_QML_COLOR(switchUTMSP,        "#b0e0e6", "#b0e0e6", "#b0e0e6", "#b0e0e6");
    DECLARE_QML_COLOR(sliderUTMSP,        "#9370db", "#9370db", "#9370db", "#9370db");
    DECLARE_QML_COLOR(successNotifyUTMSP, "#3cb371", "#3cb371", "#3cb371", "#3cb371");
#endif
}

void QMLPalette::setColorGroupEnabled(bool enabled)
{
    _colorGroupEnabled = enabled;
    emit paletteChanged();
}

void QMLPalette::setGlobalTheme(Theme newTheme)
{
    // Mobile build does not have themes
    if (_theme != newTheme) {
        _theme = newTheme;
        _signalPaletteChangeToAll();
    }
}

void QMLPalette::_signalPaletteChangeToAll()
{
    // Notify all objects of the new theme
    foreach (QMLPalette* palette, _paletteObjects) {
        palette->_signalPaletteChanged();
    }
}

void QMLPalette::_signalPaletteChanged()
{
    emit paletteChanged();
}
