macro(qss_add_test component)
    add_executable(${component} ${component}.cpp)
    add_test(${component} ${component})
    target_link_libraries(${component}
                          Qt5::Core
                          Qt5::Network
                          Qt5::Test
                          QtQiniu)
    target_include_directories(${component}
                               PUBLIC ${PROJECT_SOURCE_DIR}/lib)
endmacro(qss_add_test)
qss_add_test(UtilTest)