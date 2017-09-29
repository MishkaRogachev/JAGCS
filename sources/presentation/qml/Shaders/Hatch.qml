import QtQuick 2.6

ShaderEffect {
    id: shader

    property color color: palette.dangerColor
    property real xFactor: 35
    property real yFactor: xFactor * width / height

    fragmentShader:"
    varying highp vec2 qt_TexCoord0;
    uniform highp float xFactor;
    uniform highp float yFactor;
    uniform highp vec4 color;

    void main(void)
    {
        gl_FragColor = mix(vec4(0.0, 0.0, 0.0, 0.0), color,
                        sin(qt_TexCoord0.x * yFactor + qt_TexCoord0.y * xFactor));
    }"
}
