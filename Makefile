upload_firmware:
	pio run --target upload

compile_firmware:
	pio run

check_quality:
	codespell
