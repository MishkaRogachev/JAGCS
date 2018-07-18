# By MishkaRogachev(mishkarogachev@gmail.com)
# Macro generates qml-files from ${TS_FILES} and add it to arg TR_QRCS qrc resource file
macro(tr_to_qrc TRANSLATIONS_QRC)
    qt5_add_translation(QM_FILES ${TS_FILES})
    file(WRITE ${TRANSLATIONS_QRC} "<RCC>\n\t<qresource prefix=\"/\">")
    foreach(QM_FILE ${QM_FILES})
        get_filename_component(QM_FILE_NAME ${QM_FILE} NAME)
        file(APPEND ${TRANSLATIONS_QRC} "\n\t\t<file alias=\"${QM_FILE_NAME}\">${QM_FILE_NAME}</file>")
    endforeach()
    file(APPEND ${TRANSLATIONS_QRC} "\n\t</qresource>\n</RCC>")
    list(APPEND QRC_FILES ${TRANSLATIONS_QRC})
endmacro()

