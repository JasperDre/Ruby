echo "Initializing submodules (1/5)"
git submodule update --init --recursive
mkdir Dependencies
echo "Generating GLFW (2/5)"
cd Dependencies
mkdir GLFW
cd ..
cmake -DGLFW_USE_HYBRID_HPG=ON -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -S Submodules/glfw -B Dependencies/GLFW
echo "Building GLFW (3/5)"
cmake --build Dependencies/GLFW --target glfw --config Debug
echo "Generating GLAD (4/5)"
cd Dependencies
mkdir GLAD
cd ..
cmake -S Submodules/glad -B Dependencies/GLAD
echo "Building GLAD (5/5)"
cmake --build Dependencies/GLAD --target glad --config Debug