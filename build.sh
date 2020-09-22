#!/bin/bash
#################################################################################
#    _____ _______ ________      __     By: Steve Sampson
#   / ____|__   __|  ____\ \    / /     Email: mail@stephensampson.dev
#  | (___    | |  | |__   \ \  / /      Created: 2020-09-16
#   \___ \   | |  |  __|   \ \/ /       Modified: 2020-09-16
#   ____) |  | |  | |____   \  /        Description: TODO:
#  |_____/   |_|  |______|   \/
#################################################################################

if [[ "$#" -ne 1 ]]; then
	echo "You must enter exactly one command line argument";
	echo "Acceptable values are: \"Debug\" or \"Release\"";
fi

main() {
  if [[ $1 == "Debug" ]]; then
      echo "Building as Debug...";
      build_debug;
  elif [[ $1 == "Release" ]]; then
      echo "Building as Release...";
      build_release;
  elif [[ $1 == "Both" ]]; then
      echo "Building as Debug...";
      build_debug;
      echo "Building as Release...";
      build_release;
  else
      echo "Invalid input.";
      exit 1;
  fi
}

build_debug () {
  rm -rf cmake-build-debug
  cmake -H. -DCMAKE_BUILD_TYPE=Debug -B./cmake-build-debug
  make -C./cmake-build-debug
  make CoverageHtml -C./cmake-build-debug | tee cmake-build-debug/CoverageOutput.log
}

build_release () {
  rm -rf cmake-build-release
  cmake -H. -DCMAKE_BUILD_TYPE=Release -B./cmake-build-release
  make -C./cmake-build-release
  ./cmake-build-release/learningprotobuf_bench | tee cmake-build-release/BenchOutput.log
}

main $1;