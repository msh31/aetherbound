function(embed_resource resource_path output_file variable_name)
    file(READ ${resource_path} hex_content HEX)
    
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " array_content ${hex_content})
    string(REGEX REPLACE ", $" "" array_content ${array_content})
    
    file(SIZE ${resource_path} file_size)
    file(WRITE ${output_file}
        "#pragma once\n"
        "#include <cstddef>\n\n"
        "static const unsigned char ${variable_name}_DATA[] = {\n    ${array_content}\n};\n"
        "static const size_t ${variable_name}_SIZE = ${file_size};\n"
    )
endfunction()

function(add_embedded_resources target)
    set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/resources")
    set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
    
    file(MAKE_DIRECTORY ${GENERATED_DIR})
    
    set(RESOURCE_FILES "IDLE.png" "RUN.png" "HURT.png" "ATTACK.png")
    set(RESOURCE_VARS "IDLE" "RUN" "HURT" "ATTACK")
    set(GENERATED_HEADERS)
    
    list(LENGTH RESOURCE_FILES NUM_RESOURCES)
    math(EXPR LAST_INDEX "${NUM_RESOURCES} - 1")
    
    foreach(INDEX RANGE ${LAST_INDEX})
        list(GET RESOURCE_FILES ${INDEX} RESOURCE_FILE)
        list(GET RESOURCE_VARS ${INDEX} RESOURCE_VAR)
        
        set(RESOURCE_PATH "${RESOURCE_DIR}/${RESOURCE_FILE}")
        set(OUTPUT_HEADER "${GENERATED_DIR}/${RESOURCE_VAR}_resource.h")
        
        embed_resource(${RESOURCE_PATH} ${OUTPUT_HEADER} ${RESOURCE_VAR})
        list(APPEND GENERATED_HEADERS ${OUTPUT_HEADER})
    endforeach()

    target_include_directories(${target} PRIVATE ${GENERATED_DIR})
    add_custom_target(${target}_resources DEPENDS ${GENERATED_HEADERS})
    add_dependencies(${target} ${target}_resources)
endfunction()