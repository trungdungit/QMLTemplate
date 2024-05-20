pragma Singleton

import QtQuick 2.3

Item {
    property alias emailValidate    : emailValidate
    property alias isoTimeValidate  : isoTimeValidate
    property alias ptTimeValidate   : ptTimeValidate
    property alias cronTabValidator : cronTabValidator
    property alias ipAddressValidate: ipAddressValidate
    property alias portValidate     : portValidate
    property alias stringValidate   : stringValidate
    property alias integerValidate  : integerValidate
    property alias hourValidate     : hourValidate
    property alias minuteValidate   : minuteValidate
    property alias fullHourValidate : fullHourValidate

    RegExpValidator {
        id: ipAddressValidate
        regExp: /^(([0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}([0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
    }

    RegExpValidator {
        id: portValidate
        regExp: /^([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$/
    }

    RegExpValidator {
        id: emailValidate
        regExp: /^(([^<>()[\]\.,;:\s@\"]+(\.[^<>()[\]\.,;:\s@\"]+)*)|(\".+\"))@(([^<>()[\]\.,;:\s@\"]+\.)+[^<>()[\]\.,;:\s@\"]{2,})$/i
    }

    RegExpValidator {
        id: isoTimeValidate
        regExp: /^\d{4}-\d\d-\d\dT\d\d:\d\d:\d\d(\.\d+)?(([+-]\d\d:\d\d)|Z)?$/i
    }

    RegExpValidator {
        id: ptTimeValidate
        regExp: /PT(([0-9]|[0-1][0-9]|2[0-3])H|([0-9][0-9]?[0-9]?[0-9]?)(M|S))+$/
    }

    RegExpValidator {
        id: cronTabValidator
        regExp: /(@(annually|yearly|monthly|weekly|daily|hourly|reboot))|(@every (\d+(ns|us|µs|ms|s|m|h))+)|((((\d+,)+\d+|(\d+(\/|-)\d+)|\d+|\*) ?){5,7})/
    }

    RegExpValidator {
        id: stringValidate
        regExp: /[0-9A-F]+/
    }

    RegExpValidator {
        id: integerValidate
        regExp: /(\d{1,9})$/
    }

    RegExpValidator {
        id: hourValidate
        regExp: /^([0-9]|[0-1][0-9]|2[0-3])$/
    }

    RegExpValidator {
        id: minuteValidate
        regExp: /^([0-9][0-9]?[0-9]?[0-9]?)$/
    }

    RegExpValidator {
        id: fullHourValidate
        regExp: /^([0-9]|[0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$/
    }
}
