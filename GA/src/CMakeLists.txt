# If you create new headers/cpp files, add them to these list!
set(HEADER_FILES
	SrcMain.h
    Parser.h
    Translator.h
    NW.h
)

set(SOURCE_FILES
	SrcMain.cpp
    Parser.cpp
    Translator.cpp
    NW.cpp
)

# Don't change this
add_library(src ${SOURCE_FILES} ${HEADER_FILES})
