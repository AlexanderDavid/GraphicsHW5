make:
	mkdir -p build && cd build && cmake .. && make -j && cd .. && cp ./build/bin/* .

catrom:
	./build/bin/catrom

subd:
	./build/bin/subd

clean:
	rm catrom catrom_points subd subd_points
