cmake_minimum_required(VERSION 3.4)

project(custompass)

# 设置编译模式
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")	#/MT
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")		#/MTd

# 添加源码目录
aux_source_directory(./Obfuscator  src_1)
set(srcs ${src_1})

# 生成动态链接库，那么在Windows下就是dll，最终会生成custompass.dll
add_library(custompass SHARED ${srcs})

# 添加头文件包含目录，头文件包含还有CMake后生成的include目录
include_directories(E:/Git_Code/llvmdynobj/llvm-12.0.0.src/include E:/Git_Code/llvmdynobj/llvm-12.0.0.build/include)


# link_directories不起作用 参见 https://stackoverflow.com/questions/31438916/cmake-cannot-find-library-using-link-directories
# TARGET_LINK_LIBRARIES(custompass LLVMPasses LLVMCore)

set(mylibdir "E:/Git_Code/llvmdynobj/llvm-12.0.0.build/Debug/lib")
set(VTKLIBS LLVMCore LLVMSupport LLVMAnalysis LLVMBinaryFormat LLVMTransformUtils LLVMRemarks LLVMProfileData LLVMDemangle LLVMBitstreamReader)
foreach(libname ${VTKLIBS})
        SET(FOUND_LIB "FOUND_LIB-NOTFOUND")
        find_library(FOUND_LIB NAMES ${libname} HINTS ${mylibdir} NO_DEFAULT_PATH)
		IF (FOUND_LIB)
			message("found lib: ${FOUND_LIB}")
			LIST(APPEND mylibs ${FOUND_LIB})
		ELSE() 
			MESSAGE("not lib found: ${libname}") 
		ENDIF ()
endforeach(libname)
#message(${mylibs})

#message(${CPPUNIT_LIBRARY})
target_link_libraries(custompass PUBLIC ${mylibs})	