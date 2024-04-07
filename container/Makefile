.PHONY: build

build:
	cd build && make
fmt:
	find test -name "*.cpp" | grep -v build | xargs clang-format -i
	find test -name "*.cc" | grep -v build | xargs clang-format -i
	find test -name "*.h" | grep -v build | xargs clang-format -i
	#find test -name "*.hpp" | grep -v build | xargs clang-format -i
