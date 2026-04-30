BUILD_TYPE=Ninja

BUILD_FOLDER=build$BUILD_TYPE
SOURCE_FOLDER=projects

if [ ! -e $BUILD_FOLDER ] 
then mkdir $BUILD_FOLDER 
fi

cd $BUILD_FOLDER

cmake -G $BUILD_TYPE ../$SOURCE_FOLDER
cmake --build .



cp ../run_tests.sh .
#cp ../$SOURCE_FOLDER/