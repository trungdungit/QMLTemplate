/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#ifndef QMLPalette_h
#define QMLPalette_h

#include <QObject>
#include <QColor>
#include <QMap>

#define DECLARE_QML_COLOR(name, lightDisabled, lightEnabled, darkDisabled, darkEnabled) \
    { \
        PaletteColorInfo_t colorInfo = { \
            { QColor(lightDisabled), QColor(lightEnabled) }, \
            { QColor(darkDisabled), QColor(darkEnabled) } \
        }; \
        qmlApp()->toolbox()->corePlugin()->paletteOverride(#name, colorInfo); \
        _colorInfoMap[Light][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupEnabled]; \
        _colorInfoMap[Light][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupDisabled]; \
        _colorInfoMap[Dark][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupEnabled]; \
        _colorInfoMap[Dark][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupDisabled]; \
        _colors << #name; \
    }

#define DECLARE_QML_NONTHEMED_COLOR(name, disabledColor, enabledColor) \
    { \
        PaletteColorInfo_t colorInfo = { \
            { QColor(disabledColor), QColor(enabledColor) }, \
            { QColor(disabledColor), QColor(enabledColor) } \
        }; \
        qmlApp()->toolbox()->corePlugin()->paletteOverride(#name, colorInfo); \
        _colorInfoMap[Light][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupEnabled]; \
        _colorInfoMap[Light][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupDisabled]; \
        _colorInfoMap[Dark][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupEnabled]; \
        _colorInfoMap[Dark][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupDisabled]; \
        _colors << #name; \
    }

#define DECLARE_QML_SINGLE_COLOR(name, color) \
    { \
        PaletteColorInfo_t colorInfo = { \
            { QColor(color), QColor(color) }, \
            { QColor(color), QColor(color) } \
        }; \
        qmlApp()->toolbox()->corePlugin()->paletteOverride(#name, colorInfo); \
        _colorInfoMap[Light][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupEnabled]; \
        _colorInfoMap[Light][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupDisabled]; \
        _colorInfoMap[Dark][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupEnabled]; \
        _colorInfoMap[Dark][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupDisabled]; \
        _colors << #name; \
    }

#define DEFINE_QML_COLOR(NAME, SETNAME) \
    Q_PROPERTY(QColor NAME READ NAME WRITE SETNAME NOTIFY paletteChanged) \
    Q_PROPERTY(QStringList NAME ## Colors READ NAME ## Colors NOTIFY paletteChanged) \
    QColor NAME() const { return _colorInfoMap[_theme][_colorGroupEnabled  ? ColorGroupEnabled : ColorGroupDisabled][QStringLiteral(#NAME)]; } \
    QStringList NAME ## Colors() const { \
        QStringList c; \
        c << _colorInfoMap[Light][ColorGroupEnabled][QStringLiteral(#NAME)].name(QColor::HexRgb); \
        c << _colorInfoMap[Light][ColorGroupDisabled][QStringLiteral(#NAME)].name(QColor::HexRgb); \
        c << _colorInfoMap[Dark][ColorGroupEnabled][QStringLiteral(#NAME)].name(QColor::HexRgb); \
        c << _colorInfoMap[Dark][ColorGroupDisabled][QStringLiteral(#NAME)].name(QColor::HexRgb); \
        return c; \
    } \
    void SETNAME(const QColor& color) { _colorInfoMap[_theme][_colorGroupEnabled  ? ColorGroupEnabled : ColorGroupDisabled][QStringLiteral(#NAME)] = color; _signalPaletteChangeToAll(); }

/*!
 QMLPalette is used in QML ui to expose color properties for the QML palette. There are two
 separate palettes in QML, light and dark. The light palette is for outdoor use and the dark
 palette is for indoor use. Each palette also has a set of different colors for enabled and
 disabled states.

 Usage:

        import QGroundControl.Palette 1.0

        Rectangle {
            anchors.fill:   parent
            color:          QMLPal.window

            QMLPalette { id: QMLPal: colorGroupEnabled: enabled }
        }
*/

class QMLPalette : public QObject
{
    Q_OBJECT

public:
    enum ColorGroup {
        ColorGroupDisabled = 0,
        ColorGroupEnabled,
        cMaxColorGroup
    };

    enum Theme {
        Light = 0,
        Dark,
        cMaxTheme
    };
    Q_ENUM(Theme)

    typedef QColor PaletteColorInfo_t[cMaxTheme][cMaxColorGroup];

    Q_PROPERTY(Theme        globalTheme         READ globalTheme        WRITE setGlobalTheme        NOTIFY paletteChanged)
    Q_PROPERTY(bool         colorGroupEnabled   READ colorGroupEnabled  WRITE setColorGroupEnabled  NOTIFY paletteChanged)
    Q_PROPERTY(QStringList  colors              READ colors             CONSTANT)

    DEFINE_QML_COLOR(window,                        setWindow)
    DEFINE_QML_COLOR(windowShadeLight,              setWindowShadeLight)
    DEFINE_QML_COLOR(windowShade,                   setWindowShade)
    DEFINE_QML_COLOR(windowShadeDark,               setWindowShadeDark)
    DEFINE_QML_COLOR(text,                          setText)
    DEFINE_QML_COLOR(warningText,                   setWarningText)
    DEFINE_QML_COLOR(button,                        setButton)
    DEFINE_QML_COLOR(buttonBorder,                  setButtonBorder)
    DEFINE_QML_COLOR(buttonText,                    setButtonText)
    DEFINE_QML_COLOR(buttonHighlight,               setButtonHighlight)
    DEFINE_QML_COLOR(buttonHighlightText,           setButtonHighlightText)
    DEFINE_QML_COLOR(primaryButton,                 setPrimaryButton)
    DEFINE_QML_COLOR(primaryButtonText,             setPrimaryButtonText)
    DEFINE_QML_COLOR(textField,                     setTextField)
    DEFINE_QML_COLOR(textFieldText,                 setTextFieldText)
    DEFINE_QML_COLOR(mapButton,                     setMapButton)
    DEFINE_QML_COLOR(mapButtonHighlight,            setMapButtonHighlight)
    DEFINE_QML_COLOR(mapIndicator,                  setMapIndicator)
    DEFINE_QML_COLOR(mapIndicatorChild,             setMapIndicatorChild)
    DEFINE_QML_COLOR(mapWidgetBorderLight,          setMapWidgetBorderLight)
    DEFINE_QML_COLOR(mapWidgetBorderDark,           setMapWidgetBorderDark)
    DEFINE_QML_COLOR(mapMissionTrajectory,          setMapMissionTrajectory)
    DEFINE_QML_COLOR(brandingPurple,                setBrandingPurple)
    DEFINE_QML_COLOR(brandingBlue,                  setBrandingBlue)
    DEFINE_QML_COLOR(colorGreen,                    setColorGreen)
    DEFINE_QML_COLOR(colorOrange,                   setColorOrange)
    DEFINE_QML_COLOR(colorRed,                      setColorRed)
    DEFINE_QML_COLOR(colorGrey,                     setColorGrey)
    DEFINE_QML_COLOR(colorBlue,                     setColorBlue)
    DEFINE_QML_COLOR(alertBackground,               setAlertBackground)
    DEFINE_QML_COLOR(alertBorder,                   setAlertBorder)
    DEFINE_QML_COLOR(alertText,                     setAlertText)
    DEFINE_QML_COLOR(missionItemEditor,             setMissionItemEditor)
    DEFINE_QML_COLOR(statusFailedText,              setstatusFailedText)
    DEFINE_QML_COLOR(statusPassedText,              setstatusPassedText)
    DEFINE_QML_COLOR(statusPendingText,             setstatusPendingText)
    DEFINE_QML_COLOR(surveyPolygonInterior,         setSurveyPolygonInterior)
    DEFINE_QML_COLOR(surveyPolygonTerrainCollision, setSurveyPolygonTerrainCollision)
    DEFINE_QML_COLOR(toolbarBackground,             setToolbarBackground)
    DEFINE_QML_COLOR(toolStripFGColor,              setToolStripFGColor)
    DEFINE_QML_COLOR(toolStripHoverColor,           setToolStripHoverColor)
    DEFINE_QML_COLOR(groupBorder,                   setGroupBorder)

#ifdef CONFIG_UTM_ADAPTER
    DEFINE_QML_COLOR(switchUTMSP,                   setSwitchUTMSP)
    DEFINE_QML_COLOR(sliderUTMSP,                   setSliderUTMSP)
    DEFINE_QML_COLOR(successNotifyUTMSP,            setSuccessNotifyUTMSP)
#endif

     QMLPalette(QObject* parent = nullptr);
    ~QMLPalette();

    QStringList colors                      () const { return _colors; }
    bool        colorGroupEnabled           () const { return _colorGroupEnabled; }
    void        setColorGroupEnabled        (bool enabled);

    static Theme    globalTheme             () { return _theme; }
    static void     setGlobalTheme          (Theme newTheme);

signals:
    void paletteChanged ();

private:
    static void _buildMap                   ();
    static void _signalPaletteChangeToAll   ();
    void        _signalPaletteChanged       ();
    void        _themeChanged               ();

    static Theme                _theme;             ///< There is a single theme for all palettes
    bool                        _colorGroupEnabled; ///< Currently selected ColorGroup. true: enabled, false: disabled
    static QStringList          _colors;

    static QMap<int, QMap<int, QMap<QString, QColor>>> _colorInfoMap;   // theme -> colorGroup -> color name -> color
    static QList<QMLPalette*> _paletteObjects;    ///< List of all active QMLPalette objects
};

#endif
