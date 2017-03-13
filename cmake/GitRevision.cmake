find_package(Git)
if(GIT_FOUND)
    execute_process(COMMAND ${GIT_EXECUTABLE} rev-list HEAD
          COMMAND wc -l
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
          OUTPUT_VARIABLE git_out
          ERROR_VARIABLE git_error
          RESULT_VARIABLE git_result_code
          OUTPUT_STRIP_TRAILING_WHITESPACE)

    if(NOT ${git_result_code} EQUAL 0)
      SET (GIT_REVISION unknown)
    else()
      SET (GIT_REVISION ${git_out})
    endif()
endif()
