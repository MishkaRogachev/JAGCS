.pragma library

function mapToRange(value, minValue, maxValue, length) {
    return (value - minValue) / (maxValue - minValue) * length;
}

function pad(num, size) {
    var str = num.toString();
    while (str.length < size) str = "0" + str;
    return str;
}

function degreesToDms(degrees) {
    var deg = degrees | 0;
    var frac = Math.abs(degrees - deg);
    var min = (frac * 60) | 0;
    var sec = frac * 3600 - min * 60;

    return {
        sign: degrees < 0 ? -1 : 1,
        deg:  Math.abs(deg),
        min: min,
        sec: sec
    }
}

function dmsToDegree(deg, min, sec) {
    return deg + min / 60.0 + sec / 3600.0;
}

function degreesToDmsString(degrees, lng) {
    var dms = degreesToDms(degrees);
    return pad(dms.deg, 3) + "\u00B0" +
           pad(dms.min, 2) + "\'" +
           pad(dms.sec.toFixed(2), 5) + "\"" +
           (dms.sign < 0 ? lng ? "W" : "S" : lng ? "E" : "N");
}

function dmsStringToDegree(string, lng) {
    var split = string.split("\u00B0");
    if (split.cout < 2) return 0.0;
    var deg = split[0];
    split = split[1].split("\'");
    if (split.cout < 2) return 0.0;
    var min = split[0];
    split = split[1].split("\"");
    var sec = split[0];
    var sign = split[1] === "W" || split[1] === "S" ? -1 : 1;
    return dmsToDegree(sign * parseInt(deg), parseInt(min), parseFloat(sec));
}
