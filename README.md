# conan 
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan


# conan_profile
os=Windows  
os_build=Windows  
arch=x86_64  
arch_build=x86_64  
compiler=Visual Studio  
compiler.version=15  
compiler.runtime=MTd  
build_type=Debug  


# cmake
MT 환경이 아닌 경우 CMAKE_CXX_FLAGS_RELEASE, CMAKE_CXX_FLAGS_DEBUG 주석

# build
mkdir build
conan install ..

# cmake x86
cmake -DCMAKE_GENERATOR_PLATFORM=x86 ..

# cmake x64
cmake -DCMAKE_GENERATOR_PLATFORM=x64 .. 
