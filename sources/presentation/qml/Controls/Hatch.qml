import QtQuick 2.6

ShaderEffect {
    id: shader

    property color color: palette.negativeColor

    fragmentShader:"
    varying highp vec2 qt_TexCoord0;
    uniform vec4 color;

    void main(void)
    {
        gl_FragColor = mix(vec4(0.0, 0.0, 0.0, 0.0), color, sin((qt_TexCoord0.x + qt_TexCoord0.y) / 0.02));
    }"
}
