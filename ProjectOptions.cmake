macro(project_setup_options)

  option(project_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
  option(project_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
  option(project_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)

endmacro()

macro(project_local_options)
  include(cmake/StandardProjectSettings.cmake)

  add_library(project_warnings INTERFACE)
  add_library(project_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  project_set_project_warnings(
    project_warnings
    ${project_WARNINGS_AS_ERRORS}
    ""
    ""
    "")

  include(cmake/StaticAnalyzers.cmake)
  if(project_ENABLE_CLANG_TIDY)
    project_enable_clang_tidy(project_options ${project_WARNINGS_AS_ERRORS})
  endif()

  if(project_ENABLE_CPPCHECK)
    project_enable_cppcheck(${project_WARNINGS_AS_ERRORS} "")
  endif()

endmacro()
