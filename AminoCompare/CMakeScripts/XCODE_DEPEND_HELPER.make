# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.main.Debug:
PostBuild.src.Debug: /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/Debug/main
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/Debug/main:\
	/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Debug/libsrc.a\
	/opt/intel/tbb/lib/libtbb.dylib
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/Debug/main


PostBuild.src.Debug:
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Debug/libsrc.a:
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Debug/libsrc.a


PostBuild.tests.Debug:
PostBuild.src.Debug: /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/Debug/tests
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/Debug/tests:\
	/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Debug/libsrc.a\
	/opt/intel/tbb/lib/libtbb.dylib
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/Debug/tests


PostBuild.main.Release:
PostBuild.src.Release: /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/Release/main
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/Release/main:\
	/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Release/libsrc.a\
	/opt/intel/tbb/lib/libtbb.dylib
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/Release/main


PostBuild.src.Release:
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Release/libsrc.a:
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Release/libsrc.a


PostBuild.tests.Release:
PostBuild.src.Release: /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/Release/tests
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/Release/tests:\
	/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Release/libsrc.a\
	/opt/intel/tbb/lib/libtbb.dylib
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/Release/tests


PostBuild.main.MinSizeRel:
PostBuild.src.MinSizeRel: /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/MinSizeRel/main
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/MinSizeRel/main:\
	/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/MinSizeRel/libsrc.a\
	/opt/intel/tbb/lib/libtbb.dylib
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/MinSizeRel/main


PostBuild.src.MinSizeRel:
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/MinSizeRel/libsrc.a:
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/MinSizeRel/libsrc.a


PostBuild.tests.MinSizeRel:
PostBuild.src.MinSizeRel: /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/MinSizeRel/tests
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/MinSizeRel/tests:\
	/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/MinSizeRel/libsrc.a\
	/opt/intel/tbb/lib/libtbb.dylib
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/MinSizeRel/tests


PostBuild.main.RelWithDebInfo:
PostBuild.src.RelWithDebInfo: /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/RelWithDebInfo/main
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/RelWithDebInfo/main:\
	/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/RelWithDebInfo/libsrc.a\
	/opt/intel/tbb/lib/libtbb.dylib
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/RelWithDebInfo/main


PostBuild.src.RelWithDebInfo:
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/RelWithDebInfo/libsrc.a:
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/RelWithDebInfo/libsrc.a


PostBuild.tests.RelWithDebInfo:
PostBuild.src.RelWithDebInfo: /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/RelWithDebInfo/tests
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/RelWithDebInfo/tests:\
	/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/RelWithDebInfo/libsrc.a\
	/opt/intel/tbb/lib/libtbb.dylib
	/bin/rm -f /Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/tests/RelWithDebInfo/tests




# For each target create a dummy ruleso the target does not have to exist
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Debug/libsrc.a:
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/MinSizeRel/libsrc.a:
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/RelWithDebInfo/libsrc.a:
/Users/zhongchu/Desktop/itp435/pa4-Dontmovedad/src/Release/libsrc.a:
/opt/intel/tbb/lib/libtbb.dylib:
