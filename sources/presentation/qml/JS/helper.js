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
    var deg = Math.floor(degrees);
    var frac = (degrees - deg) * 60;
    var min = Math.floor(frac);
    var sec = Math.round((frac - min) * 6000) / 100;

    if (sec >= 60) { sec -= 60; min++; }
    if (min >= 60) { min -= 60; deg++; }
    deg = Math.abs(deg)
    var degLimit = (lng ? 180 : 90);
    if (deg >= degLimit) deg -= degLimit;

    return {
        sign: degrees < 0 ? -1 : 1,
        deg: deg,
        min: min,
        sec: sec.toFixed(2)
    }
}

function dmsToDegree(deg, min, sec) {
    return deg + min / 60.0 + sec / 3600.0;
}

function degreesToDmsString(degrees, lng) {
    var dms = isNaN(degrees) ? degreesToDms(0, lng) : degreesToDms(degrees, lng);
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
    return dmsToDegree(sign * parseInt(deg), parseInt(min), parseFloat(sec));
}

