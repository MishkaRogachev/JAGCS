import QtQuick 2.6

ShaderEffect {
    id: shader

    property alias sourceItem: sourceEffect.sourceItem

    property variant source: ShaderEffectSource {
        id: sourceEffect
        hideSource: true
    }

    fragmentShader:"
        varying vec2 qt_TexCoord0;
        uniform sampler2D source;

        void main(void)
        {
            vec4 sourceColor = texture2D(source, qt_TexCoord0);
            gl_FragColor = mix(vec4(0.0, 0.0, 0.0, 0.0), sourceColor, sin(qt_TexCoord0.y * 3.141593));
        }"
}
