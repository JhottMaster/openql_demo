all_unix: 
	@echo "Make sure to run with sudo! Installing..."
	$(MAKE) -C jheatt_engine_library/ clean
	$(MAKE) -C jheatt_engine_library/ unix
	$(MAKE) -C jheatt_engine_library/ uninstall
	$(MAKE) -C jheatt_engine_library/ install
	$(MAKE) -C jheatt_engine_demo/ clean
	$(MAKE) -C jheatt_engine_demo/ create_unix_dirs
	@echo "Finished! Output in build/demo directory"

all_osx:
	@echo "Make sure to run with sudo! Installing..."
	@echo "Make sure to run with sudo! Installing..."
	$(MAKE) -C jheatt_engine_library/ clean
	$(MAKE) -C jheatt_engine_library/ osx
	$(MAKE) -C jheatt_engine_library/ uninstall
	$(MAKE) -C jheatt_engine_library/ install
	$(MAKE) -C jheatt_engine_demo/ clean
	$(MAKE) -C jheatt_engine_demo/ create_osx_dirs
	@echo "Finished! Output in build/demo directory"

clean:
	rm -r ./build/* || true