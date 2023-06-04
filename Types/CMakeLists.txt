set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Types.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Quaternion.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Matrix.cpp"
)

set(MOD_DEPS
    Fw/Types
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/test.cpp"
)

register_fprime_ut()
