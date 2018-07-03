import QtQuick 2.6

ShaderEffect {
    id: shader

    //property alias sourceItem: sourceEffect.sourceItem
    property real pi: Math.PI

//    property variant source: ShaderEffectSource {
//        id: sourceEffect
//        hideSource: true
//    }

    property var source

    fragmentShader:"
        varying highp vec2 qt_TexCoord0;
        uniform sampler2D source;
        uniform highp float pi;

        void main(void)
        {
            highp vec4 sourceColor = texture2D(source, qt_TexCoord0);
            gl_FragColor = mix(vec4(0.0, 0.0, 0.0, 0.0), sourceColor, sin(qt_TexCoord0.y * pi));
        }"
}
