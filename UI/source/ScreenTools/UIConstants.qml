pragma Singleton

import QtQuick 2.0
import QtQuick.Controls.Material 2.3

import QMLTemplate 1.0
import QMLTemplate.SettingsManager 1.0

Item {
    id: root

    //------------------------ Material params ---------------------
    property bool darkTheme: false
    property int appAccent: darkTheme ? Material.Red : Material.DeepOrange

    //------------------ Notification type messages color ----------
    property color success
    property color error
    property color warning
    property color info

    //------------------ Icons MainBoard ---------------------------
    readonly property string iLinked: "\uf0c1"
    readonly property string iUnlinked: "\uf127"

    //------------------ Icons notification ------------------------
    readonly property string iChecked: "\uf00c"
    readonly property string iError: "\uf06a"
    readonly property string iWarning: "\uf071"
    readonly property string iInfo: "\uf05a"
    readonly property string iSuccess: "\uf058"

    //------------------- Nav / Categrory Icons --------------------
    readonly property string iHomepage: "\uf015"
    readonly property string iSystem: "\uf233"
    readonly property string iLiveView: "\uf03d"
    readonly property string iDeviceMgmt: "\uf109"
    readonly property string iStranger: "\uf21b"
    readonly property string iPuzzlePiece: "\uf12e"
    readonly property string iGeneralConfigs: "\uf085"
    readonly property string iClock: "\uf017"
    readonly property string iKeyboard: "\uf11c"
    readonly property string iSync: "\uf021"
    readonly property string iSquareChecked: "\uf14a"
    readonly property string iSquareUnchecked: "\uf146"

    //------------------- Toolbar Icons --------------------
    readonly property string iColumns: "\uf0db"
    readonly property string iCrosshairs: "\uf05b"
    readonly property string iHDD: "\uf0a0"
    readonly property string iFileDownload: "\uf019"
    readonly property string iFileUpload: "\uf574"
    readonly property string iDark: "\uf186"
    readonly property string iLight: "\uf185"
    readonly property string iLogout: "\uf2f5"

    //------------------- Sidebar Icons ----------------------------
    readonly property string iAlert: "\uf0f3"
    readonly property string iAlgorithm: "\uf14e"
    readonly property string iCamera: "\uf030"
    readonly property string iCaretLeft: "\uf0d9"
    readonly property string iCaretRight: "\uf0da"
    readonly property string iComDisk: "\uf51f"
    readonly property string iBack: "\uf04a"
    readonly property string iEdit: "\uf044"
    readonly property string iDevice: "\uf109"
    readonly property string iList: "\uf0ca"
    readonly property string ivList: "\uf58e"
    readonly property string iTools: "\uf4a3"
    readonly property string iSignal: "\uf012"
    readonly property string iSearch: "\uf00e"
    readonly property string iSpaceShuttle: "\uf197"

    //-------------------- Windows icons ------------------------
    readonly property string iSliders: "\uf1de"
    readonly property string iUpload: "\uf093"
    readonly property string iVoiceControl: "\uf028"
    readonly property string iX: "\uf00d"
    readonly property string iRedo: "\uf01e"
    readonly property string iRestart: "\uf011"
    readonly property string iPlayState: "\uf7a5"
    readonly property string iStopState: "\uf04b"
    readonly property string iCaretDown: "\uf0d7"
    readonly property string iCaretUp: "\uf0de"
    readonly property string iChevronLeft: "\uf053"
    readonly property string iChevronRight: "\uf054"
    readonly property string iChevronDown: "\uf078"
    readonly property string iChevronFirstLeft: "\uf048"
    readonly property string iChevronLastRight: "\uf051"
    readonly property string iArrowLeft: "\uf060"
    readonly property string iArrowRight: "\uf061"
    readonly property string iExport: "\uf56e"
    readonly property string iFolder: "\uf07b"
    readonly property string iTrash: "\uf1f8"
    readonly property string iEye: "\uf06e"
    readonly property string iEyeSlash: "\uf070"
    readonly property string iUserPlus: "\uf234"
    readonly property string iUserMinus: "\uf503"
    readonly property string iCircleChecked: "\uf058"
    readonly property string iXChecked: "\uf057"
    readonly property string iCalendar: "\uf073"

    //---------------------- Configs icons ----------------------
    readonly property string iSettings: "\uf013"
    readonly property string iSave: "\uf0c7"
    readonly property string iCommon: "\uf6ff"
    readonly property string iStream: "\uf550"
    readonly property string iSequenceTasks: "\uf0ae"
    readonly property string iUser: "\uf007"
    readonly property string iUsers: "\uf0c0"
    readonly property string iReturnScreen: "\uf78c"
    readonly property string iOpenFullScreen: "\uf065"
    readonly property string iRefresh: "\uf2f1"
    readonly property string iUpdate: "\uf021"

    //-------------------Chart ---------------------------------
    readonly property string iAdd: "\uf067"
    readonly property string iDelete: "\uf1f8"
    readonly property string iChartLine: "\uf24d"
    readonly property string iReset: "\uf2ea"
    readonly property string iZoom: "\uf002"
    readonly property string iCopy: "\uf0c5"
    readonly property string iTranslation: "\uf047"
    readonly property string iLogs: "\uf093"
    readonly property string iCrop: "\uf125"

    //------------------ RP ------------------------------------
    readonly property string iLens: "\ue2df"

    //------------------ Usual Color -------------------------------
    //------- Basic
    readonly property color redColor: "#FF0000"
    readonly property color blackColor: "#2f3640"
    readonly property color fuzzyblackColor: "#2f364025"
    readonly property color purebackColor: "#000000"
    readonly property color whiteColor: "#ffffff"
    readonly property color deactiveColor: "#808080"
    readonly property color genBorderColor: "#4DC7F1"
    readonly property color vibrantGreen: "#17a81a"
    readonly property color orangeRed: "#ff4500"
    readonly property color neutral: "#e6e6e6"
    readonly property color goldColor: "#ffd700"
    readonly property color green: "#008000"
    readonly property color grayish: "#A59C9C"
    readonly property color grayShape: "#D9D9D9"

    //------- Text
    property color warningColor
    property color cateCirTextColor
    property color textColor
    property color textFooterColor
    property color textBlueColor
    property color textSideBarColor
    property color tableHeaderColor
    property color textSideActive

    //------- Button
    readonly property color textBtnColor: "#ffffff"
    readonly property color btnCateColor: "#CAD3C8"
    readonly property color btnCancelColor: "#576574"
    readonly property color flatButtonColor: "#ffffff"
    property color btnActiveColor
    property color btnDeleteColor
    property color btnRestartColor
    property color btnSaveColor
    property color btnHoverColor

    //------- Shadow
    property color dropshadowColor

    //------- Border
    property color sidebarBorderColor
    property color borderBlue

    //------- Background
    property color bgColorOverlay
    property color cfProcessingOverlayBg
    property color sidebarConfigBg
    property color sidebarActiveBg
    property color sidebarBgItemLevel2
    property color sectionBg
    property color titleColorOverlay
    property color sectionHeader
    property color categoryEleBgColor
    property color categoryEleActiveColor
    property color cateOverlayBg
    property color activeNav
    property color presentColor
    property color absentColor

    //------- Record
    readonly property color recordIconBg: "#eb4d4b"
    readonly property color recordIconColor: "#ff7979"

    //------- Others
    property color grayColor
    property color darkGrayColor: "#212121"
    readonly property color transparentColor: "transparent"

    //------------------ Fonts -----------------------------------
    readonly property string fontComicSans: "Comic Sans MS"
    readonly property string fontMonospace: "Monospace"
    readonly property string customFont: /*"Nunito, sans-serif;" //*/ /*"Inter, sans-serif;"*/ "Bai Jamjuree Medium"
    readonly property string textFont: /*"Inter, sans-serif;"*/ "Bai Jamjuree Medium"
    readonly property string secondaryTextFont: /*"Barlow, sans-serif;"*/ "Bai Jamjuree Medium"

    Connections {
        target: QMLTemplate.settingsManager.appSettings.darkTheme
        function onRawValueChanged(value) {
            setBaseTheme(value)
        }
    }

    function setBaseTheme(theme) {
        darkTheme = theme
        if (darkTheme === true) {
            appAccent = Material.Red
            success = "#1dd1a1"
            error = "#FF7675"
            warning = "#e67e22"
            info = "#0984e3"
            textColor = "#ffffff"
            textFooterColor = "#b2bec3"
            textBlueColor = "#0a3d62"
            textSideBarColor = "#64E0FF"
            tableHeaderColor = "#6b90b2"
            textSideActive = "#23b99a"
            btnRestartColor = "#576574"
            btnActiveColor = "#006fc3"
            btnDeleteColor = "#F95454"
            btnSaveColor = "#006fc3"
            btnHoverColor = "#369dcc"
            dropshadowColor = "#57606f"
            sidebarBorderColor = "#636e72"
            borderBlue = "#0984e3"
            bgColorOverlay = "#222f3e"
            titleColorOverlay = "#4b5869"
            cfProcessingOverlayBg = "#2D3436"
            sidebarConfigBg = "#2D3C4B"
            sidebarActiveBg = "#00AEE6"
            sidebarBgItemLevel2 = "#1D2833"
            sectionHeader = "#171735"
            categoryEleBgColor = "#4b6584"
            categoryEleActiveColor = "#6C8D96"
            cateOverlayBg = "#808e9b"
            activeNav = "#222f3e"
            sectionBg = "#4b636e"
            grayColor = "#dfe4ea"
            darkGrayColor = "#212121"
            warningColor = "#ffeb3b"
            cateCirTextColor = "#778CA3"
            presentColor = "#00FF00"
            absentColor = "#FF0000"
        } else {
            appAccent = Material.DeepOrange
            success = "#01B428"
            error = "#E00101"
            warning = "#ffb300"
            info = "#289DF6"
            textColor = "#000000"
            textFooterColor = "#2f3640"
            textBlueColor = "#ADACAA"
            textSideBarColor = "#00AEE6"
            tableHeaderColor = "#000000"
            textSideActive = "#C2E4EF"
            btnActiveColor = "#D9D9D9"
            btnDeleteColor = "#F95454"
            btnRestartColor = "#b4b6c4"
            btnSaveColor = "#00AEE6"
            btnHoverColor = "#006fc3"
            dropshadowColor = "#DBD7D7"
            sidebarBorderColor = "#090B0B"
            borderBlue = "#289DF6"
            bgColorOverlay = "#FFFFFF"
            titleColorOverlay = "#adb2b8"
            cfProcessingOverlayBg = "#F4F6F4"
            sidebarConfigBg = "#FFFFFF"
            sidebarActiveBg = "#00AEE6"
            sidebarBgItemLevel2 = "#1D2833"
            sectionHeader = "#7e8a9a"
            categoryEleBgColor = "#A9C3E6"
            categoryEleActiveColor = "#CCEFFA"
            cateOverlayBg = "#FFFFFF"
            activeNav = "#778597"
            sectionBg = "#d9f3ff"
            grayColor = "#678087" //"#2D3436"
            warningColor = "#ffc107"
            cateCirTextColor = "#778CA3"
            presentColor = "#197AFA"
            absentColor = "#FC0505"
        }
    }

    Component.onCompleted: {
        setBaseTheme(
            QMLTemplate.settingsManager.appSettings.darkTheme.rawValue)
    }
}
