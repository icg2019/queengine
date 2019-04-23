dir = build/

all: build

clean:
	@echo "Cleaning...	"
	@rm -rf $(dir)

build:
	@echo "Building..."
	@mkdir $(dir) && \
	cd $(dir) && \
	cmake ..

comp:
	cd $(dir) && \
	make

run:
	@cd $(dir) && \
	 ./queengine

.PHONY: list
list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
