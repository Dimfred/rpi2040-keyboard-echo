.ONESHELL:
SHELL := /bin/bash
all: help
.PHONY: init cmake build clean help

################################################################################
# APP
init: ## init project (run once)
	git submodule update --init --recursive
	# which arm-none-eabi-gcc (you will need the arm compiler)

cmake: ## init cmake (run once, or after clean)
	if [ -d build ]; then
		exit 0
	fi
	mkdir -p build
	cd build
	export PICO_SDK_PATH=deps/pico-sdk
	cmake \
		-DCMAKE_C_COMPILER=$$(which arm-none-eabi-gcc) \
		-DCMAKE_CXX_COMPILER=$$(which arm-none-eabi-g++) ..

build: cmake ## build the app
	cd build
	make -j8

clean: ## clean the app
	rm -rf build

################################################################################
# HELP
help: ## print this help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-10s\033[0m %s\n", $$1, $$2}'
