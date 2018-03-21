import QtQuick 2.6

ShaderEffect {
    id: shader

    property color color: customPalette.highlightColor
    property real angle: 0
    property real pi: Math.PI

    fragmentShader:"
    varying highp vec2 qt_TexCoord0;
    uniform highp vec4 color;
    uniform highp float angle;
    uniform highp float pi;

    highp float atan2(in highp float y, in highp float x)
    {
        return x == 0.0 ? sign(y) * pi / 2.0 : atan(y, x) * 1.0;
    }

    void main(void)
    {
        gl_FragColor = atan2(qt_TexCoord0.y - 0.5, qt_TexCoord0.x - 0.5) + pi > angle ?
                             vec4(0.0, 0.0, 0.0, 0.0) : color;
    }"
}
