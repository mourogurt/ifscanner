.PHONY: clean All

All:
	@echo "----------Building project:[ unit_test_log_multithreads - Release ]----------"
	@cd "unit_test_log_multithreads" && $(MAKE) -f  "unit_test_log_multithreads.mk"
clean:
	@echo "----------Cleaning project:[ unit_test_log_multithreads - Release ]----------"
	@cd "unit_test_log_multithreads" && $(MAKE) -f  "unit_test_log_multithreads.mk" clean
