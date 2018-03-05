.pragma library

function mapToRange(value, minValue, maxValue, length) {
    return (value - minValue) / (maxValue - minValue) * length;
}

function mapFromRange(pos, minValue, maxValue, length) {
    return pos / length * (maxValue - minValue) + minValue;
}

function decimals(num) {
    return (num.toString().split('.')[1] || []).length;
}

function stringToReal(str, decimalPoint) {
    if (decimalPoint !== ".") return parseFloat(str.replace(decimalPoint, "."));
    return parseFloat(str);
}

function realToString(num, decimalPoint) {
    var str = num.toString();
    if (decimalPoint !== ".") return str.replace(".", decimalPoint);
    return str;
}

function pad(num, size) {
    var str = num.toString();
    while (str.length < size) str = "0" + str;
    return str;
}

function padReal(num, sizeBefore, sizeAfter, decimalPoint) {
    var split = realToString(num, decimalPoint).split(decimalPoint, 2);

    return pad(split.length > 0 ? split[0] : 0, sizeBefore) + decimalPoint +
           pad(split.length > 1 ? split[1] : 0, sizeBefore);
}

function formatTime(time) {
    return pad(time.getHours(), 2) + ":" +
            pad(time.getMinutes(), 2) + ":" +
            pad(time.getSeconds(), 2);
}

function degreesToDms(degrees, lng, secondsPrecision) {
    var sign = degrees < 0 ? -1 : 1
    var abs = Math.abs(degrees);
    var deg = Math.floor(abs);
    var frac = (abs - deg) * 60;

    if (Math.ceil(frac) - frac <= Math.pow(10, -7)) frac = Math.ceil(frac);

    var min = Math.floor(frac);
    var sec = (frac - min) * 60;

    var degLimit = (lng ? 180 : 90);
    if (deg > degLimit) deg = degLimit;

    return {
        sign: sign,
        deg: deg,
        min: min,
        sec: sec.toFixed(secondsPrecision)
    }
}

function dmsToDegree(sign, deg, min, sec) {
    return sign * (deg + min / 60.0 + sec / 3600.0);
}

function degreesToDmsString(degrees, lng, secondsPrecision) {
    if (isNaN(degrees)) return "NaN"
    var dms = degreesToDms(degrees, lng, secondsPrecision);
    return pad(dms.deg, lng ? 3 : 2) + "\u00B0" +
           pad(dms.min, 2) + "\'" +
           pad(dms.sec, 3 + secondsPrecision) + "\"" +
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

function degreesToString(degree, precision) {
    return degree.toFixed(precision);
}

function stringToDegree(string) {
    return parseFloat(string)
}
