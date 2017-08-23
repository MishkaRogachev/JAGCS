import QtQuick 2.6

ShaderEffect {
    id: shader

    property color hatchColor: palette.negativeColor

    fragmentShader:"
    varying highp vec2 qt_TexCoord0;
    uniform vec4 hatchColor;

    void main(void)
    {
        gl_FragColor = mix(vec4(0.0, 0.0, 0.0, 0.0), hatchColor, sin((qt_TexCoord0.x + qt_TexCoord0.y) / 0.02));
    }"
}
