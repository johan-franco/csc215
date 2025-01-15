CC=g++
STD=c++17

build/%.o: src/%.cpp
	@mkdir -p build
	@$(CC) -MM -MT $@ $< > build/$*.d
	$(CC) -c -o $@ $< -std=$(STD)

build/test_bigints: build/test_bigints.o build/BigInt.o
	$(CC) -o $@ $^ -std=$(STD)

-include build/*.d

.PHONY: test all clean

test: build/test_bigints
	./build/test_bigints

clean:
	rm -rf build
