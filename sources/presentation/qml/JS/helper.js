.pragma library

function mapToRange(value, minValue, maxValue, length) {
    return (value - minValue) / (maxValue - minValue) * length;
}

function decimals(num) {
    return (num.toString().split('.')[1] || []).length;
}

function pad(num, size) {
    var str = num.toString();
    while (str.length < size) str = "0" + str;
    return str;
}

function degreesToDms(degrees, lng) {
    var sign = degrees < 0 ? -1 : 1
    var abs = Math.abs(degrees);
    var deg = Math.floor(abs);
    var frac = (abs - deg) * 60;
    var min = Math.floor(frac);
    var sec = Math.round((frac - min) * 6000) / 100;

    if (sec >= 60) { sec -= 60; min++; }
    if (min >= 60) { min -= 60; deg++; }
    var degLimit = (lng ? 180 : 90);
    if (deg >= degLimit) { deg -= degLimit; sign = -sign; }

    return {
        sign: sign,
        deg: deg,
        min: min,
        sec: sec.toFixed(2)
    }
}

function dmsToDegree(sign, deg, min, sec) {
    return sign * (deg + min / 60.0 + sec / 3600.0);
}

function degreesToDmsString(degrees, lng) {
    if (isNaN(degrees)) return "NaN"
    var dms = degreesToDms(degrees, lng);
    return pad(dms.deg, 3) + "\u00B0" +
           pad(dms.min, 2) + "\'" +
           pad(dms.sec, 5) + "\"" +
           (dms.sign < 0 ? lng ? "W" : "S" : lng ? "E" : "N");
}

function dmsStringToDegree(string, lng) {
    var split = string.split("\u00B0");
    if (split.length < 2) return NaN;
    var deg = split[0];
    split = split[1].split("\'");
    if (split.length < 2) return NaN;
    var min = split[0];
    split = split[1].split("\"");
    var sec = split[0];
    var sign = split[1] === "W" || split[1] === "S" ? -1 : 1;
    return dmsToDegree(sign, parseInt(deg, 10), parseInt(min, 10), parseFloat(sec, 10));
}

function isDmsString(string) {
    return 0 < string.indexOf("\u00B0") < string.indexOf("\'") < string.indexOf("\"");
}

