PREFIX:=/usr/local

install:
	install -t $(PREFIX)/bin gemini2terminal
	install -t $(PREFIX)/bin gemini-handler
	install -t $(PREFIX)/bin gemini-get
	install -t $(PREFIX)/bin gemini-message-handler
	install -t $(PREFIX)/bin set_terminal_title
	install -t $(PREFIX)/bin uri_write_cache
	install -t $(PREFIX)/bin run_stdio_handler_by_mime_type
