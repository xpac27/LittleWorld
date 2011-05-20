all: release

debug:
	@mkdir -p build && \
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Debug .. && \
	make

release:
	@mkdir -p build && \
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release .. && \
	make

clean:
	cd build && \
	make clean

